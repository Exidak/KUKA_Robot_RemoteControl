#pragma once
class YaSpeechKit : public QObject
{
	Q_OBJECT
public:
	YaSpeechKit(QObject *parent = 0);

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

