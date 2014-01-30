#include "gdl_relationalsentence.h"

#include <QDebug>

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b):
    head(h),
    body(b)
{
    buildName();
}

bool GDL_RelationalSentence::isGround() const{
    for(PTerm term : body)
    {
        if(!term->isGround()){
            return false;
        }
    }
    return true;
}

void GDL_RelationalSentence::buildName(){
    name = head->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Relation with arity 0 : " << name;
        return;
    case 1:
        name = name + ' ' + body[0]->toString();
        return;
    default:
        break;
    }

    name = name + " (" + body[0]->toString();
    for(int i=1; i<body.size(); ++i){
        name = name + ", " + body[i]->toString();
    }
    name = name + ")";
}
