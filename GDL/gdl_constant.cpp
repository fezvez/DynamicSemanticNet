#include "gdl_constant.h"

#include <QDebug>

GDL_Constant::GDL_Constant(const QString & s){
name = s;
}

GDL_Constant::GDL_Constant(const GDL_Constant &constant){
    name = QString(constant.toString());
}

bool GDL_Constant::isGround() const{
    return true;
}

bool GDL_Constant::operator==(const GDL_Term & t){
    return name==t.toString();
}
