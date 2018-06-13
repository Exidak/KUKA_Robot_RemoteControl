#include "stdafx.h"
#include "tmp\moc_YaSpeechKit.cpp"


YaSpeechKit::YaSpeechKit(QObject *parent)
{
	_manager = new QNetworkAccessManager(this);
	connect(_manager, &QNetworkAccessManager::finished, this, &YaSpeechKit::slotGetReply);

	QUrlQuery query;
	query.addQueryItem("key", "5abce851-497a-4cfd-8121-8dc38d25870f");
	query.addQueryItem("uuid", "01ae13cb744628b58fb536d496daa1e6");
	query.addQueryItem("topic", "queries");
	query.addQueryItem("lang", "ru-RU");
	QUrl url("https://asr.yandex.net/asr_xml");
	url.setQuery(query);

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setProtocol(QSsl::SslV3);

	request.setUrl(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "audio/x-wav");
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setSslConfiguration(config);
}

void YaSpeechKit::slotGetReply(QNetworkReply * reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray response = reply->readAll();
		qDebug() << response;

		QXmlStreamReader element(response);
		double idealConfidence = 0;
		QString idealQuery;
		while (!element.atEnd()) {
			element.readNext();
			if (element.name() == "recognitionResults")
			{
				if (element.attributes().count())
				{
					QXmlStreamAttribute attr = element.attributes().at(0);
					if (attr.value().toDouble() == 0)
						emit sigError(QString::fromLocal8Bit("Невозможно распознать"));
				}
			}
			if (element.tokenType() != QXmlStreamReader::StartElement) continue;
			if (element.name() != "variant") continue;
			if (element.attributes().count())
			{
				QXmlStreamAttribute attr = element.attributes().at(0);
				if (attr.value().toDouble() >= idealConfidence) {
					idealConfidence = attr.value().toDouble();
					element.readNext();
					idealQuery = element.text().toString();
				}
			}
		}
		if (element.hasError())
			emit sigError(element.errorString());
		emit sigComplete(idealQuery);
	}
	else // handle error
	{
		emit sigError( reply->errorString());
	}
}

void YaSpeechKit::slotIgnoreSSLErr(QNetworkReply *reply, const QList<QSslError> &errors)
{
	reply->ignoreSslErrors();
}

void YaSpeechKit::requestRecognition(const QByteArray & bufData)
{
	request.setHeader(QNetworkRequest::ContentLengthHeader, bufData.size());
	_manager->post(request, bufData);
}
