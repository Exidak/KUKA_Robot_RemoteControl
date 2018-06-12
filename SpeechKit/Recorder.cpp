#include "stdafx.h"
#include "Recorder.h"


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
}

void Recorder::slotBufferProbed(const QAudioBuffer &buf)
{
	_recordedData.append(buf.constData<char>(), buf.byteCount());
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
