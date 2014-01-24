#include "gdl_orsentence.h"

GDL_OrSentence::GDL_OrSentence(PSentence s):
    sentence(s)
{
}

bool GDL_OrSentence::isGround() const{
    return false;
}
