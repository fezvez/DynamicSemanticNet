#include "gdl_orsentence.h"

GDL_OrSentence::GDL_OrSentence(QVector<PSentence> b):
    body(b)
{
    for(PSentence s : b){
        dependentConstants = dependentConstants.unite(s->getDependentConstants());
        dependentConstantsNegative = dependentConstantsNegative.unite(s->getDependentConstantsNegative());
    }
}


bool GDL_OrSentence::isGround() const{
    for(PSentence sentence : body){
        if(!sentence->isGround()){
            return false;
        }
    }
    return true;
}
