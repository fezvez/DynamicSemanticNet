#include "gdl_constant.h"

GDL_Constant::GDL_Constant(const GDL_Constant &constant)
{
    name = QString(constant.toString());
}

bool GDL_Constant::isGround() const{
    return true;
}
