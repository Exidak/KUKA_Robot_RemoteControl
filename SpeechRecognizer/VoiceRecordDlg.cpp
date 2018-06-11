#include "stdafx.h"
#include "tmp\moc_VoiceRecordDlg.cpp"


VoiceRecordDlg::VoiceRecordDlg(QObject *parent)
{
	m_audioRecorder = new QAudioRecorder;

	QAudioEncoderSettings audioSettings;
	audioSettings.setCodec("audio/pcm");
	audioSettings.setQuality(QMultimedia::HighQuality);

	m_audioRecorder->setEncodingSettings(audioSettings);

	QString fileName = "/E:/programming/Robot/RemoteControl/RemoteControl/SpeechRecognizer/1.wav";//QFileDialog::getSaveFileName();
	//qDebug() << fileName;
	m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));

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

	connect(btnRecordStart, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::record);
	connect(btnRecordPause, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::pause);
	connect(btnRecordStop, &QPushButton::clicked, m_audioRecorder, &QAudioRecorder::stop);
	connect(btnSend, &QPushButton::clicked, this, &VoiceRecordDlg::slotSent2Recognize);

	hbButtons->addWidget(btnRecordStart);
	hbButtons->addWidget(btnRecordPause);
	hbButtons->addWidget(btnRecordStop);
	ltMain->addLayout(hbButtons);
	ltMain->addWidget(btnSend);
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

void VoiceRecordDlg::slotSent2Recognize()
{
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &VoiceRecordDlg::slotGetReply);
	QFile *file = new QFile("E:/programming/Robot/RemoteControl/RemoteControl/SpeechRecognizer/1.wav");
	if (file->open(QIODevice::ReadOnly)) {
		QUrlQuery query;
		query.addQueryItem("key", "5abce851-497a-4cfd-8121-8dc38d25870f");
		query.addQueryItem("uuid", "01ae13cb744628b58fb536d496daa1e6");
		query.addQueryItem("topic", "queries");
		query.addQueryItem("lang", "ru-RU");
		QUrl url("https://asr.yandex.net/asr_xml");
		url.setQuery(query);
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, "audio/x-wav");
		request.setHeader(QNetworkRequest::ContentLengthHeader, file->size());
		manager->post(request, file->readAll());
		file->close();
	}
}

void VoiceRecordDlg::slotGetReply(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray response = reply->readAll();
		qDebug() << response;
	}
	else // handle error
	{
		qDebug() << reply->errorString();
	}
}

void VoiceRecordDlg::slotChangeAudioLevel(const QAudioBuffer &buf)
{

}
