#include "gdl_notsentence.h"

GDL_NotSentence::GDL_NotSentence(PSentence s):
    sentence(s)
{
}

bool GDL_NotSentence::isGround() const{
    return false;
}
