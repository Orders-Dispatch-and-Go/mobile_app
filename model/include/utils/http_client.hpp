#include <qcontainerfwd.h>
#include <qnetworkaccessmanager.h>
#include <QJsonDocument>
#include <QNetworkReply>

class http_client_t : public QObject
{
    Q_OBJECT
public:
    explicit http_client_t(QObject *parent = nullptr) : QObject(parent) {}

    template<typename T>
    T get(const QString &url);

    template<typename T, typename U>
    T post(const QString &url, const U &data);

    template<typename T>
    T post(const QString &url);
    
private:
    QNetworkAccessManager m_manager;

    static std::optional<QJsonObject> json_from_byte_array(const QByteArray& data);
};