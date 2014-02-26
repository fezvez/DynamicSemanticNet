#include "gdl_rule.h"

#include <QDebug>

GDL_Rule::GDL_Rule(PRelation h, QVector<PSentence> b):
    head(h),
    body(b)
{
    buildName();
}

bool GDL_Rule::isGround() const{
    for(PSentence sentence : body)
    {
        if(!sentence->isGround())
            return false;
    }
    return true;
}

void GDL_Rule::buildName(){
    name = QString("(<= ") + head->toString();
    switch(body.size()){
    case 0:
        qDebug() << "Rule with arity 0 : " << name;
        return;
    case 1:
        name = name + ' ' + body[0]->toString() + ')';
        return;
    default:
        break;
    }

    name = name + " (" + body[0]->toString();
    for(int i=1; i<body.size(); ++i){
        name = name + ") (" + body[i]->toString();
    }
    name = name + "))";
}

PRelation GDL_Rule::getHead(){
    return head;
}
