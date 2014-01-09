#include "gdl_constant.h"

GDL_Constant::GDL_Constant(const QString & s):
{
    name = QString(s);
}

QString& GDL_Constant::toString(){
    return name;
}

bool GDL_Constant::isGround(){
    return true;
}
