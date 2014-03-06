#include "gdl_relationalsentence.h"

#include <QDebug>

GDL_RelationalSentence::GDL_RelationalSentence(PConstant h, QVector<PTerm> b, GDL_TYPE t):
    head(h),
    body(b),
    type(t)
{
    buildName();
    dependentConstants.insert(h);
}

QString GDL_RelationalSentence::toString() const{
    if(useHumanReadableNames){
        return humanReadableName;
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
    humanReadableName = getHead()->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Relation with arity 0 : " << humanReadableName;
        break;
    case 1:
        humanReadableName = QString('(') + humanReadableName + ' ' + body[0]->toString() + ')';
        break;
    default:
        humanReadableName = QString('(') + humanReadableName + " (" + body[0]->toString();
        for(int i=1; i<body.size(); ++i){
            humanReadableName = humanReadableName + " " + body[i]->toString();
        }
        humanReadableName = humanReadableName + "))";
        break;
    }

    if(type==GDL::NEXT){
        humanReadableName = QString("next ") + humanReadableName;
    }
    name = humanReadableName;

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

PConstant GDL_RelationalSentence::getHead(){
    return getRelationConstant();
}

GDL::GDL_TYPE GDL_RelationalSentence::getType(){
    return type;
}

bool GDL_RelationalSentence::useHumanReadableNames = false;
