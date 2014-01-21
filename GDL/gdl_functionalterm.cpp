#include "gdl_functionalterm.h"

#include <QStringBuilder>

GDL_FunctionalTerm::GDL_FunctionalTerm(const GDL_Constant & function, QVector<PTerm> body):
    functionName(function)
{
    functionBody = body;
    ground = UNDEFINED;
    buildName();
}

bool GDL_FunctionalTerm::isGround() const{
    if(!functionName.isGround())
        return false;
    for(PTerm term : functionBody)
    {
        if(!term->isGround())
            return false;
    }
    return true;
}

void GDL_FunctionalTerm::buildName(){

}
