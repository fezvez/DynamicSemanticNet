#include "gdl_relationalsentence.h"

#include <QDebug>

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b, GDL_TYPE t):
    head(h),
    body(b),
    type(t)
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
        break;
    default:
        name = name + " (" + body[0]->toString();
        for(int i=1; i<body.size(); ++i){
            name = name + ", " + body[i]->toString();
        }
        name = name + ")";
        break;
    }



    if(type==GDL::BASE){
        name = QString("base (") + name + ')';
    }

    if(type==GDL::TRUE){
        name = QString("true (") + name + ')';
    }

    if(type==GDL::INIT){
        name = QString("init (") + name + ')';
    }
}

PConstant GDL_RelationalSentence::getRelation(){
    return head;
}

GDL::GDL_TYPE GDL_RelationalSentence::getType(){
    return type;
}
