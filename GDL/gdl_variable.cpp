#include "gdl_variable.h"

GDL_Variable::GDL_Variable(const QString & s){
    name = s;
}


bool GDL_Variable::isGround() const{
    return false;
}

bool GDL_Variable::operator==(const GDL_Term & t){
    return false;
}
