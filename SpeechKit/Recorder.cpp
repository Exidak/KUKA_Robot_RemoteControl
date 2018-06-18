#include "stdafx.h"
#include "tmp\moc_Recorder.cpp"


Recorder::Recorder(QObject *parent)
{
	_settings.setCodec("audio/pcm");
	_settings.setQuality(QMultimedia::HighQuality);
	_audioRecorder.setEncodingSettings(_settings);

	QAudioProbe *audioProbe = new QAudioProbe(this);
	if (audioProbe->setSource(&_audioRecorder)) {
		// Probing succeeded, audioProbe->isValid() should be true.
		connect(audioProbe, &QAudioProbe::audioBufferProbed, this, &Recorder::slotBufferProbed);
	}

	connect(&_audioRecorder, &QAudioRecorder::stateChanged, this, &Recorder::slotRecorderStateChanged);
	connect(&_audioRecorder, QOverload<QMediaRecorder::Error>::of(&QAudioRecorder::error), this, &Recorder::slotDRecorderError);

	timer = new QTimer(this);
	timer->setSingleShot(true);
	connect(timer, &QTimer::timeout, this, &Recorder::stopRecord);

	max = 0;
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
	// Note: Only the most common sample formats are supported
	if (!format.isValid())
		return qreal(0);

	if (format.codec() != "audio/pcm")
		return qreal(0);

	switch (format.sampleType()) {
	case QAudioFormat::Unknown:
		break;
	case QAudioFormat::Float:
		if (format.sampleSize() != 32) // other sample formats are not supported
			return qreal(0);
		return qreal(1.00003);
	case QAudioFormat::SignedInt:
		if (format.sampleSize() == 32)
			return qreal(INT_MAX);
		if (format.sampleSize() == 16)
			return qreal(SHRT_MAX);
		if (format.sampleSize() == 8)
			return qreal(CHAR_MAX);
		break;
	case QAudioFormat::UnSignedInt:
		if (format.sampleSize() == 32)
			return qreal(UINT_MAX);
		if (format.sampleSize() == 16)
			return qreal(USHRT_MAX);
		if (format.sampleSize() == 8)
			return qreal(UCHAR_MAX);
		break;
	}

	return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
	QVector<qreal> values;

	if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
		return values;

	if (buffer.format().codec() != "audio/pcm")
		return values;

	int channelCount = buffer.format().channelCount();
	values.fill(0, channelCount);
	qreal peak_value = getPeakValue(buffer.format());
	if (qFuzzyCompare(peak_value, qreal(0)))
		return values;

	switch (buffer.format().sampleType()) {
	case QAudioFormat::Unknown:
	case QAudioFormat::UnSignedInt:
		if (buffer.format().sampleSize() == 32)
			values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 16)
			values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 8)
			values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
		for (int i = 0; i < values.size(); ++i)
			values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
		break;
	case QAudioFormat::Float:
		if (buffer.format().sampleSize() == 32) {
			values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
			for (int i = 0; i < values.size(); ++i)
				values[i] /= peak_value;
		}
		break;
	case QAudioFormat::SignedInt:
		if (buffer.format().sampleSize() == 32)
			values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 16)
			values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
		if (buffer.format().sampleSize() == 8)
			values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
		for (int i = 0; i < values.size(); ++i)
			values[i] /= peak_value;
		break;
	}

	return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
	QVector<qreal> max_values;
	max_values.fill(0, channels);

	for (int i = 0; i < frames; ++i) {
		for (int j = 0; j < channels; ++j) {
			qreal value = qAbs(qreal(buffer[i * channels + j]));
			if (value > max_values.at(j))
				max_values.replace(j, value);
		}
	}

	return max_values;
}

void Recorder::slotBufferProbed(const QAudioBuffer &buf)
{
	_recordedData.append(buf.constData<char>(), buf.byteCount());

	QVector<qreal> levels = getBufferLevels(buf);
	qreal avrg = 0;
	for (auto lv : levels)
		avrg += lv;
	avrg /= (qreal)levels.size();

	if (avrg > max) max = avrg;

	if (avrg <= 0.045)
	{
		if (!timer->isActive())
			timer->start(1500);
	}
	else
		timer->stop();
}

void Recorder::slotRecorderStateChanged(QMediaRecorder::State state)
{
	switch (state) 
	{
	case QMediaRecorder::RecordingState:
		emit sigRecordStarted();
		break;
	case QMediaRecorder::StoppedState:
		emit sigRecordStoped();
		break;
	}
}

void Recorder::slotDRecorderError()
{
	emit sigRecordError(_audioRecorder.errorString());
}

void Recorder::ReverseBytes(void * start, int size)
{
	char *istart = (char*)start, *iend = istart + size;
	std::reverse(istart, iend);
}

void Recorder::startRecord()
{
	_audioRecorder.record();
}

void Recorder::stopRecord()
{
	_audioRecorder.stop();
}

bool Recorder::isRecording()
{
	return _audioRecorder.state() & QMediaRecorder::RecordingState;
}

QByteArray Recorder::getRecordedData()
{
	if (isRecording())
		return QByteArray();

	QByteArray data = _recordedData;
	// add header to bufData
	QByteArray header;
	QDataStream stream(&header, QIODevice::WriteOnly);
	int sizeBuf = int(data.size() + 36);
	ReverseBytes(&sizeBuf, 4);
	int sizeData = data.size();
	ReverseBytes(&sizeData, 4);
	stream << 0x52494646; // RIFF
	stream << sizeBuf; // size of  bufData + 44-8
	stream << 0x57415645; // WAWE 
	stream << 0x666d7420; // fmt 
	stream << 0x10000000; // size chunk
	stream << (short)0x0100; // PCM format
	stream << (short)0x0100; // channels
	stream << 0x80bb0000; // simple rate
	stream << 0x00770100; // byte rate
	stream << (short)0x0200; // blockAlign
	stream << (short)0x1000; // bitsPerSample
	stream << 0x64617461; // data
	stream << sizeData;// subchunk2Size
	data.prepend(header); // header 

	return data;
}
