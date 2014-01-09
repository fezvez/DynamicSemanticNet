#ifndef GDL_H
#define GDL_H

#include <QString>

class GDL
{
public:
    QString& toString() = 0;
    bool isGround() = 0;
};

#endif // GDL_H
