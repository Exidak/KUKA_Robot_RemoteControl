#pragma once
class VoiceRecordDlg : public QDialog
{
	Q_OBJECT
public:
	VoiceRecordDlg(QObject *parent);
	~VoiceRecordDlg();
private:
	void initDialog();
private slots:
	void slotChangeAudioLevel(const QAudioBuffer &buf);
	void slotStateChanged(QMediaRecorder::State state);
	void slotRecorderStatusChanged(QMediaRecorder::Status status);
	void slotDisplayErrorMessage();
	void slotSent2Recognize();
	void slotGetReply(QNetworkReply* ans);
protected:
	QAudioRecorder * m_audioRecorder;

	QPushButton *btnRecordStart;
	QPushButton *btnRecordPause;
	QPushButton *btnRecordStop;
};

