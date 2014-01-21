#ifndef GDL_VARIABLE_H
#define GDL_VARIABLE_H

#include "gdl_term.h"

class GDL_Variable : public GDL_Term
{
public:
    GDL_Variable(const QString & s);

    bool isGround() const;


};

#endif // GDL_VARIABLE_H
