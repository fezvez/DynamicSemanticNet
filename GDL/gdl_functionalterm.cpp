#include "gdl_functionalterm.h"

#include <QDebug>

GDL_FunctionalTerm::GDL_FunctionalTerm(PConstant h, QVector<PTerm> b):
    head(h),
    body(b)
{
    buildName();
}

bool GDL_FunctionalTerm::isGround() const{
    for(PTerm term : body)
    {
        if(!term->isGround())
            return false;
    }
    return true;
}

void GDL_FunctionalTerm::buildName(){
    name = head->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Function with arity 0 : " << name;
        return;
    case 1:
        name = name + ' ' + body[0]->toString();
        return;
    default:
        break;
    }

    name = name + " (" + body[0]->toString();
    for(int i=1; i<body.size(); ++i){
        name = name + " " + body[i]->toString();
    }
    name = name + ")";
}

bool GDL_FunctionalTerm::operator==(const GDL_Term & t){
    return name==t.toString();
}
