#include "gdl_notsentence.h"

GDL_NotSentence::GDL_NotSentence(PSentence s):
    sentence(s)
{
    name = QString("not (") + s->toString() + ')';
    dependentConstantsNegative = s->getDependentConstants();
    dependentConstants = s->getDependentConstantsNegative();
}

bool GDL_NotSentence::isGround() const{
    return sentence->isGround();
}
