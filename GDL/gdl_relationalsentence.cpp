#include "gdl_relationalsentence.h"

#include <QDebug>

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b, GDL_TYPE t):
    head(h),
    body(b),
    type(t)
{
    buildName();
    childConstants.insert(h);
}

QString GDL_RelationalSentence::toString() const{
    if(useRawNames){
        return rawName;
    }
    return name;
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
    rawName = head->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Relation with arity 0 : " << rawName;
        break;
    case 1:
        rawName = QString('(') + rawName + ' ' + body[0]->toString() + ')';
        break;
    default:
        rawName = QString('(') + rawName + " (" + body[0]->toString();
        for(int i=1; i<body.size(); ++i){
            rawName = rawName + " " + body[i]->toString();
        }
        rawName = rawName + "))";
        break;
    }

    if(type==GDL::NEXT){
        rawName = QString("next ") + rawName;
    }
    name = rawName;

    if(type==GDL::BASE){
        name = QString("base ") + name;
    }

    if(type==GDL::TRUE){
        name = QString("true ") + name;
    }

    if(type==GDL::INIT){
        name = QString("init ") + name;
    }


}

PConstant GDL_RelationalSentence::getRelationConstant(){
    return head;
}

GDL::GDL_TYPE GDL_RelationalSentence::getType(){
    return type;
}

bool GDL_RelationalSentence::useRawNames = false;
