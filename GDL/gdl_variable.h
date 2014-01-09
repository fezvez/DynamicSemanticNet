#ifndef GDL_VARIABLE_H
#define GDL_VARIABLE_H

#include "gdl_term.h"

class GDL_Variable : public GDL_Term
{
public:
    GDL_Variable(const QString & s);

    QString& toString();
    bool isGround();


};

#endif // GDL_VARIABLE_H
