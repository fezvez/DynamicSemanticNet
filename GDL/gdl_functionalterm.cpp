#include "gdl_functionalterm.h"

#include <QStringBuilder>

GDL_FunctionalTerm::GDL_FunctionalTerm(GDL_Constant & f, vector<GDL_Term> & b)
{
    functionName = GDL_Constant(f);
    functionBody = b;
    isGround = UNDEFINED;
    name = QString();
}

QString& GDL_FunctionalTerm::toString(){
    if(name.isEmpty()){

    }
    else{

    }
}

bool GDL_FunctionalTerm::isGround(){

}

