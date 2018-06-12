#pragma once

class Recorder : public QObject
{
	Q_OBJECT

public:
	explicit Recorder(QObject *parent = 0);

	void startRecord();
	void stopRecord();
	bool isRecording();

	QByteArray getRecordedData();
signals:
	void sigRecordStarted();
	void sigRecordStoped();
	void sigRecordPaused();
	void sigRecordError(const QString &error);
private slots:
	void slotBufferProbed(const QAudioBuffer &buf);
	void slotRecorderStateChanged(QMediaRecorder::State state);
	void slotDRecorderError();
private:
	void ReverseBytes(void *start, int size);
protected:
	QAudioRecorder _audioRecorder;
	QAudioEncoderSettings _settings;

	QByteArray _recordedData;
};

