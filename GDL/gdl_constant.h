#ifndef GDL_CONSTANT_H
#define GDL_CONSTANT_H

#include "gdl_term.h"

#include <QString>

class GDL_Constant : public GDL_Term
{
public:
    GDL_Constant(const QString & s);

    QString& toString();
    bool isGround();


};

#endif // GDL_CONSTANT_H
