#pragma once
class YaSpeechKit : public QObject
{
	Q_OBJECT
public:
	YaSpeechKit();

	void requestRecognition(const QByteArray &arr);
signals:
	void sigError(const QString &err);
	void sigComplete(const QString &err);
private slots:
	void slotGetReply(QNetworkReply * reply);
protected:
	QNetworkAccessManager * _manager;
	QNetworkRequest request;
};

