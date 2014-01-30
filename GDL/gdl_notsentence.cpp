#include "gdl_notsentence.h"

GDL_NotSentence::GDL_NotSentence(PSentence s):
    sentence(s)
{
    name = QString("not (") + s->toString() + ')';
}

bool GDL_NotSentence::isGround() const{
    return sentence->isGround();
}
