#ifndef GDL_CONSTANT_H
#define GDL_CONSTANT_H

#include "gdl_term.h"

#include <QString>

class GDL_Constant : public GDL_Term
{
public:
    GDL_Constant(const QString & s);
    GDL_Constant(const GDL_Constant & constant);

    bool isGround() const;


};

#endif // GDL_CONSTANT_H
