#include "gdl_variable.h"

GDL_Variable::GDL_Variable(const QString & s)
{
    name = QString(s);
}


QString& GDL_Variable::toString(){
    return name;
}

bool GDL_Variable::isGround(){
    return false;
}
