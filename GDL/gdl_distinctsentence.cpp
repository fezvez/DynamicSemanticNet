#include "gdl_distinctsentence.h"

GDL_DistinctSentence::GDL_DistinctSentence(PTerm t1, PTerm t2):
    term1(t1),
    term2(t2)

{
    name = QString("distinct (") + term1->toString() + " " + term2->toString() + ')';
}



bool GDL_DistinctSentence::isGround() const{
    return (term1->isGround() && term2->isGround());
}

QString GDL_DistinctSentence::buildNameRecursively(){
    return QString("distinct (") + term1->buildNameRecursively() + " " + term2->buildNameRecursively() + ')';
}
