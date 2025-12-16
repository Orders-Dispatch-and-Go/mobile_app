#pragma once

#include <QObject>
#include <qobject.h>
#include <qvariant.h>

class reply_t : public QObject {
    Q_OBJECT
public:
    explicit reply_t(QObject *parent = nullptr) :
        QObject(parent) { }

signals:
    void finished(const QVariant&);
    void reply_error(const QString&);
};
