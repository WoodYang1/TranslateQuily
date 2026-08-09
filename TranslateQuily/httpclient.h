#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDateTime>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
/*********************************************************
 * @file    httpclient.h
 * @brief   http客户端 用于向api发送请求 来实现翻译功能
 *
 * @author  木杨
 * @date    2026/08/08
 * @history
 *********************************************************/
using TranslateCallback = std::function<void(bool,const QString&)>;

class HttpClient : public QObject
{
    Q_OBJECT
private:
    explicit HttpClient(QObject *parent = nullptr);
    ~HttpClient() = default;
    HttpClient(const HttpClient&) = delete;
    HttpClient& operator=(const HttpClient&) = delete;
public:

    void translate(const QString& text,const QString &from,const QString &to,TranslateCallback callback);
    QString generateAuthStr(const QMap<QString, QString>& params);
    QString md5(const QString& str) const;
public:
    static HttpClient* instance();
private:
    QNetworkAccessManager _manager;
    QString _appId;
    QString _apiKey;
signals:
};

#endif // HTTPCLIENT_H
