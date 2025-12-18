#pragma once


#include <QObject>

#include <qdatetime.h>
#include <qjsonobject.h>

class TAbstractDto {
public:
    TAbstractDto()                                         = default;
    TAbstractDto(const TAbstractDto &)                     = default;
    TAbstractDto(TAbstractDto &&)                          = delete;
    TAbstractDto &operator=(const TAbstractDto &)          = default;
    TAbstractDto &operator=(TAbstractDto &&)               = delete;
    [[nodiscard]] virtual QJsonObject toJsonObject() const = 0;
    virtual void fromJsonObject(const QJsonObject &)       = 0;

    virtual ~TAbstractDto() = default;
};
