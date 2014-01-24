#include "gdl_rule.h"

GDL_Rule::GDL_Rule(PRelation h, QVector<PSentence> b):
    head(h),
    body(b)
{

}

bool GDL_Rule::isGround() const{
    return false;
}
