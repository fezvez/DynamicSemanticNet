#include "gdl_notsentence.h"

GDL_NotSentence::GDL_NotSentence(PSentence s):
    sentence(s)
{
    name = QString("not (") + sentence->toString() + ')';
    dependentConstantsNegative = sentence->getDependentConstants();
    dependentConstants = sentence->getDependentConstantsNegative();
}

bool GDL_NotSentence::isGround() const{
    return sentence->isGround();
}

QString GDL_NotSentence::buildNameRecursively(){
   return QString("not (") + sentence->buildNameRecursively() + ')';
}
