#include "stdafx.h"
#include "tmp\moc_SpeechDlg.cpp"

SpeechDlg::SpeechDlg(QWidget * parent)
{
	_recorder = new Recorder(this);
	_speechKit = new YaSpeechKit(this);

	QVBoxLayout *ltMain = new QVBoxLayout(this);
	QHBoxLayout *hbButtons = new QHBoxLayout(this);
	lblStatus = new QLabel(this);
	lblStatus->setText(QString::fromLocal8Bit("������"));
	/*
	btnRecordStart = new QPushButton(this);
	btnRecordStart->setText(QString::fromLocal8Bit("������"));
	//btnRecordStart->setEnabled(false);
	btnRecordStop = new QPushButton(this);
	btnRecordStop->setText(QString::fromLocal8Bit("����"));
	btnRecordStop->setEnabled(false);
	//btnRecordStop->setEnabled(false);
	btnSend = new QPushButton(this);
	btnSend->setText(QString::fromLocal8Bit("����������"));
	btnSend->setEnabled(false);
	textAnswer = new QTextEdit(this);
	textAnswer->setVisible(false);
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	*/

	//connect(btnRecordStart, &QPushButton::clicked, _recorder, &Recorder::startRecord);
	//connect(btnRecordStop, &QPushButton::clicked, _recorder, &Recorder::stopRecord);
	//connect(btnSend, &QPushButton::clicked, this, &SpeechDlg::slotSend2Recognize);

	connect(_speechKit, &YaSpeechKit::sigError, this, &SpeechDlg::slotYaKitError);
	connect(_speechKit, &YaSpeechKit::sigComplete, this, &SpeechDlg::slotYaKitComplete);

	connect(_recorder, &Recorder::sigRecordStarted, this, &SpeechDlg::slotRecordStart);
	connect(_recorder, &Recorder::sigRecordStoped, this, &SpeechDlg::slotRecordStop);
	connect(_recorder, &Recorder::sigRecordError, this, &SpeechDlg::slotRecordError);

	//connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	//connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	hbButtons->addStretch(1);
	hbButtons->addWidget(lblStatus);
	hbButtons->addStretch(1);
	ltMain->addStretch(1);
	ltMain->addLayout(hbButtons);
	ltMain->addStretch(1);
	//ltMain->addWidget(btnSend);
	//ltMain->addWidget(textAnswer);
	//ltMain->addWidget(buttonBox);

	_recorder->startRecord();
}

void SpeechDlg::slotRecordStart()
{
	//btnRecordStart->setEnabled(false);
	//btnRecordStop->setEnabled(true);
}

QString SpeechDlg::getResult()
{
	//return textAnswer->toPlainText();
	return strResult;
}

void SpeechDlg::slotRecordStop()
{
	lblStatus->setText(QString::fromLocal8Bit("�������������"));
	//btnRecordStop->setEnabled(false);
	//btnSend->setEnabled(true);
	recorded_data = _recorder->getRecordedData();
	slotSend2Recognize();
}

void SpeechDlg::slotRecordError(const QString & error)
{
	QMessageBox::critical(this, QString::fromLocal8Bit("������"), error, QMessageBox::Ok, QMessageBox::Ok);
}

void SpeechDlg::slotYaKitComplete(const QString & str)
{
	//btnSend->setEnabled(false);
	//textAnswer->setVisible(true);
	//textAnswer->setText(str);

	strResult = str;
	accept();
}

void SpeechDlg::slotYaKitError(const QString & error)
{
	QMessageBox::critical(this, QString::fromLocal8Bit("������"), error, QMessageBox::Ok, QMessageBox::Ok);
}

void SpeechDlg::slotSend2Recognize()
{
	_speechKit->requestRecognition(recorded_data);
}
