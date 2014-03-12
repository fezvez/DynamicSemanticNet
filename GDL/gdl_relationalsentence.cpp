#include "gdl_relationalsentence.h"

#include <QDebug>

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b, GDL_TYPE t, PConstant skolemH):
    head(h),
    body(b),
    type(t),
    skolemHead(skolemH)
{
    buildName();
    buildSkolemName();
    dependentConstants.insert(h);
}

QString GDL_RelationalSentence::toString() const{
    if(useSkolemNames){
        return skolemName;
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
    name = getHead()->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Relation with arity 0 : " << name;
        break;
    case 1:
        name = QString('(') + name + ' ' + body[0]->toString() + ')';
        break;
    default:
        name = QString('(') + name + " (" + body[0]->toString();
        for(int i=1; i<body.size(); ++i){
            name = name + " " + body[i]->toString();
        }
        name = name + "))";
        break;
    }


    if(type==GDL::NEXT){
        name = QString("next ") + name;
    }
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

void GDL_RelationalSentence::buildSkolemName(){
    if(skolemHead.isNull()){
        skolemName = head->toString();
    }
    else{
        skolemName = skolemHead->toString();
    }

    switch(body.size()){
    case 0:
        qDebug() << "Relation with arity 0 : " << skolemName;
        break;
    case 1:
        skolemName = QString('(') + skolemName + ' ' + body[0]->toString() + ')';
        break;
    default:
        skolemName = QString('(') + skolemName + " (" + body[0]->toString();
        for(int i=1; i<body.size(); ++i){
            skolemName = skolemName + " " + body[i]->toString();
        }
        skolemName = skolemName + "))";
        break;
    }
}

QString GDL_RelationalSentence::buildNameRecursively(){
    QString answer = getHead()->buildNameRecursively();
    switch(body.size()){
    case 0:
        break;
    case 1:
        answer = QString('(') + answer + ' ' + body[0]->buildNameRecursively() + ')';
        break;
    default:
        answer = QString('(') + answer + " (" + body[0]->buildNameRecursively();
        for(int i=1; i<body.size(); ++i){
            answer = answer + " " + body[i]->buildNameRecursively();
        }
        answer = answer + "))";
        break;
    }

    return answer;
}

PConstant GDL_RelationalSentence::getRelationConstant(){
    return head;
}

PConstant GDL_RelationalSentence::getHead(){
    return getRelationConstant();
}

GDL::GDL_TYPE GDL_RelationalSentence::getType(){
    return type;
}


