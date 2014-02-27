#include "propositionand.h"

PropositionAnd::PropositionAnd(QVector<PProposition> l, QString n):
    Proposition(n),
    list(l)
{
}

bool PropositionAnd::isTrue() const{
    for(PProposition prop : list){
        if(!prop->isTrue()){
            return false;
        }
    }
    return true;
}
