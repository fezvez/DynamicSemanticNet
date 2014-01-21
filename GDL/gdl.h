#ifndef GDL_H
#define GDL_H

#include <QString>

class GDL
{
public:
    QString toString() const;
    virtual bool isGround() const = 0;

protected:
    QString name;
};

#endif // GDL_H
