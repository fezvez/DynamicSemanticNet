#include "gdl_variable.h"

GDL_Variable::GDL_Variable(const QString & s)
{
    name = QString(s);
}


bool GDL_Variable::isGround() const{
    return false;
}
