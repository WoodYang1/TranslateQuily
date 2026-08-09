#include "httpclient.h"
#include "settingdata.h"
HttpClient::HttpClient(QObject *parent)
    : QObject{parent},_appId(SettingData::instance().getAppId()),_apiKey(SettingData::instance().getApiKey())
{}

void HttpClient::translate(const QString &text,const QString &from,const QString &to, TranslateCallback callback)
{
    if(text.isEmpty()){
        callback(false,"翻译内容为空");
        qDebug()<<"翻译内容为空.";
        return;
    }
    //生成当前时间的毫秒时间戳
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());
    qDebug()<<timestamp;
    //组装请求参数(用于签名)
    QMap<QString, QString> params;
    params["from"] = from;
    params["to"] = to;
    params["appId"] = _appId;
    params["srcText"] = text;
    params["timestamp"] = timestamp;
    QString authStr = generateAuthStr(params);

    QJsonObject request;
    request["from"] = from;
    request["to"] = to;
    request["appId"] = _appId;
    request["srcText"] = text;
    request["authStr"] = authStr;
    request["timestamp"] = timestamp;


    QJsonDocument doc(request);
    QByteArray postData = doc.toJson();
    QNetworkRequest req(QUrl("https://api.niutrans.com/v2/text/translate"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = _manager.post(req, postData);

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        // 响应处理留空，下一步再写
        if (reply->error() != QNetworkReply::NoError) {
            callback(false, "网络错误: " + reply->errorString());
            reply->deleteLater();
            return;
        }
    QByteArray data = reply->readAll();
    //解析json
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data,&parseError);
    if(parseError.error != QJsonParseError::NoError){
        callback(false, "JSON解析失败: " + parseError.errorString());
        reply->deleteLater();
        return;
    }
    QJsonObject obj = doc.object();
    if (obj.contains("tgtText")) {
        // 翻译成功
        QString result = obj["tgtText"].toString();
        callback(true, result);
    } else {
        // 翻译失败，提取错误信息
        QString errCode = obj["errorCode"].toString();
        QString errMsg = obj["errorMsg"].toString();
        callback(false, "错误码: " + errCode + ", 信息: " + errMsg);
    }
    reply->deleteLater();
    });
}

QString HttpClient::md5(const QString &str) const
{
    QByteArray bytes = str.toUtf8();
    QByteArray hash = QCryptographicHash::hash(bytes, QCryptographicHash::Md5);
    return hash.toHex();
}

HttpClient *HttpClient::instance()
{
    static HttpClient inst;  // C++11 起线程安全
    return &inst;
}

QString HttpClient::generateAuthStr(const QMap<QString, QString> &params)
{
    // 1. 把 apikey 加入参数列表
    QMap<QString, QString> allParams = params;
    allParams.insert("apikey", _apiKey);

    // 2. 按键名排序（QMap 默认按 key 排序，所以直接用 keys()）
    QStringList keys = allParams.keys();

    // 3. 拼接成 "key1=value1&key2=value2" 格式
    QStringList parts;
    for (const QString& key : keys) {
        if (!allParams[key].isEmpty()) {
            parts << key + "=" + allParams[key];
        }
    }
    QString paramStr = parts.join("&");

    // 4. MD5 加密
    return md5(paramStr);
}
