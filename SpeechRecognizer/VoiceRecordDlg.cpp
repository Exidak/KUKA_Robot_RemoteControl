#include "stdafx.h"
#include <algorithm>
#include "tmp\moc_VoiceRecordDlg.cpp"


VoiceRecordDlg::VoiceRecordDlg(QObject *parent)
{
	m_audioRecorder = new QAudioRecorder;

	QAudioEncoderSettings audioSettings;
	audioSettings.setCodec("audio/pcm");
	audioSettings.setQuality(QMultimedia::HighQuality);

	m_audioRecorder->setEncodingSettings(audioSettings);

	QAudioProbe *audioProbe = new QAudioProbe(this);
	if (audioProbe->setSource(m_audioRecorder)) {
		// Probing succeeded, audioProbe->isValid() should be true.
		connect(audioProbe, &QAudioProbe::audioBufferProbed, this, &VoiceRecordDlg::slotChangeAudioLevel);
	}

	connect(m_audioRecorder, &QAudioRecorder::stateChanged, this, &VoiceRecordDlg::slotStateChanged);
	connect(m_audioRecorder, QOverload<QMediaRecorder::Error>::of(&QAudioRecorder::error), this, &VoiceRecordDlg::slotDisplayErrorMessage);

	initDialog();
}


VoiceRecordDlg::~VoiceRecordDlg()
{
}

void VoiceRecordDlg::initDialog()
{
	QVBoxLayout *ltMain = new QVBoxLayout(this);
	QHBoxLayout *hbButtons = new QHBoxLayout(this);
	btnRecordStart = new QPushButton(this);
	btnRecordStart->setText(QString::fromLocal8Bit("Запись"));
	//btnRecordStart->setEnabled(false);
	btnRecordPause = new QPushButton(this);
	btnRecordPause->setText(QString::fromLocal8Bit("Пауза"));
	//btnRecordPause->setEnabled(false);
	btnRecordStop = new QPushButton(this);
	btnRecordStop->setText(QString::fromLocal8Bit("Стоп"));
	//btnRecordStop->setEnabled(false);
	QPushButton *btnSend = new QPushButton(this);
	btnSend->setText(QString::fromLocal8Bit("Распознать"));
	textAnswer = new QTextEdit(this);
	textAnswer->setVisible(false);

	connect(btnRecordStart, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::record);
	connect(btnRecordPause, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::pause);
	connect(btnRecordStop, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::stop);
	connect(btnSend, &QPushButton::clicked, this, &VoiceRecordDlg::slotSent2Recognize);

	hbButtons->addWidget(btnRecordStart);
	hbButtons->addWidget(btnRecordPause);
	hbButtons->addWidget(btnRecordStop);
	ltMain->addLayout(hbButtons);
	ltMain->addWidget(btnSend);
	ltMain->addWidget(textAnswer);
}

void VoiceRecordDlg::slotStateChanged(QMediaRecorder::State state)
{
	switch (state) {
	case QMediaRecorder::RecordingState:
		btnRecordStart->setEnabled(false);
		btnRecordPause->setEnabled(true);
		btnRecordStop->setEnabled(true);
		break;
	case QMediaRecorder::PausedState:
		btnRecordStart->setEnabled(true);
		btnRecordPause->setEnabled(false);
		btnRecordStop->setEnabled(true);
		break;
	case QMediaRecorder::StoppedState:
		btnRecordStart->setEnabled(true);
		btnRecordPause->setEnabled(false);
		btnRecordStop->setEnabled(false);
		break;
	}

	btnRecordPause->setEnabled(m_audioRecorder->state() != QMediaRecorder::StoppedState);
}

void VoiceRecordDlg::slotRecorderStatusChanged(QMediaRecorder::Status status)
{
}

void VoiceRecordDlg::slotDisplayErrorMessage()
{
	QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"), m_audioRecorder->errorString(), QMessageBox::Ok, QMessageBox::Ok);
}


void ReverseBytes(void *start, int size)
{
	char *istart = (char*)start, *iend = istart + size;
	std::reverse(istart, iend);
}

void VoiceRecordDlg::slotSent2Recognize()
{
	// add header to bufData
	QByteArray header;
	QDataStream stream(&header, QIODevice::WriteOnly);
	int sizeBuf = int(bufData.size() + 36);
	ReverseBytes(&sizeBuf, 4);
	int sizeData = bufData.size();
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
	bufData.prepend(header); // header 

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &VoiceRecordDlg::slotGetReply);
	QUrlQuery query;
	query.addQueryItem("key", "5abce851-497a-4cfd-8121-8dc38d25870f");
	query.addQueryItem("uuid", "01ae13cb744628b58fb536d496daa1e6");
	query.addQueryItem("topic", "queries");
	query.addQueryItem("lang", "ru-RU");
	QUrl url("https://asr.yandex.net/asr_xml");
	url.setQuery(query);
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "audio/x-wav");
	request.setHeader(QNetworkRequest::ContentLengthHeader, bufData.size());
	manager->post(request, bufData);
}

void VoiceRecordDlg::slotGetReply(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray response = reply->readAll();
		textAnswer->setVisible(true);
		qDebug() << response;

		QXmlStreamReader element(response);
		double idealConfidence = 0;
		QString idealQuery;
		while (!element.atEnd()) {
			element.readNext();
			if (element.tokenType() != QXmlStreamReader::StartElement) continue;
			if (element.name() != "variant") continue;
			QXmlStreamAttribute attr = element.attributes().at(0);
			if (attr.value().toDouble() >= idealConfidence) {
				idealConfidence = attr.value().toDouble();
				element.readNext();
				idealQuery = element.text().toString();
			}
		}
		if (element.hasError()) 
			textAnswer->setText(element.errorString());
		textAnswer->setText(idealQuery);
	}
	else // handle error
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("Ошибка"), reply->errorString(), QMessageBox::Ok, QMessageBox::Ok);
	}
}

void VoiceRecordDlg::slotChangeAudioLevel(const QAudioBuffer &buf)
{
	bufData.append(buf.constData<char>(), buf.byteCount());
}
