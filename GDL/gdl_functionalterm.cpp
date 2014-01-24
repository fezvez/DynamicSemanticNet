#include "gdl_functionalterm.h"

#include <QStringBuilder>

GDL_FunctionalTerm::GDL_FunctionalTerm(PConstant function, QVector<PTerm> body):
    functionName(function)
{
    functionBody = body;
    buildName();
}

bool GDL_FunctionalTerm::isGround() const{
    for(PTerm term : functionBody)
    {
        if(!term->isGround())
            return false;
    }
    return true;
}

void GDL_FunctionalTerm::buildName(){

}
