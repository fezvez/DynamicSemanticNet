#ifndef GDL_H
#define GDL_H

#include <QString>
#include <QSharedPointer>

class GDL;
typedef QSharedPointer<GDL> PGDL;

class GDL
{
public:
    QString toString() const;
    virtual bool isGround() const = 0;

    virtual ~GDL();

protected:
    QString name;
};

#endif // GDL_H
