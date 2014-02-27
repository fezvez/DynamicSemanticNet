#include "propositionconstant.h"

PropositionConstant::PropositionConstant(QString n):
    Proposition(n)
{

}

bool PropositionConstant::isTrue() const{
    return true;
}
