#pragma once

#include "YaSpeechKit.h"
#include "Recorder.h"

class SpeechDlg : public QDialog
{
	Q_OBJECT
public:
	SpeechDlg(QWidget *parent);

	QString getResult();
private slots:
	void slotRecordStart();
	void slotRecordStop();
	void slotRecordError(const QString &error);

	void slotYaKitComplete(const QString &err);
	void slotYaKitError(const QString &err);

	void slotSend2Recognize();
protected:
	Recorder * _recorder;
	YaSpeechKit *_speechKit;

	QPushButton * btnRecordStart;
	QPushButton *btnRecordStop;
	QPushButton *btnSend;
	QTextEdit *textAnswer;

	QByteArray recorded_data;
};

