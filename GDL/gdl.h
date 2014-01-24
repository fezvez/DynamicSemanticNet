#ifndef GDL_H
#define GDL_H

#include <QString>

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
