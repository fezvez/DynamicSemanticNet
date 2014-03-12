#include "gdl_rule.h"

#include <QDebug>

GDL_Rule::GDL_Rule(PRelation h, QVector<PSentence> b):
    head(h),
    body(b)
{
    buildName();

    for(PSentence s : b){
        dependentConstants = dependentConstants.unite(s->getDependentConstants());
        dependentConstantsNegative = dependentConstantsNegative.unite(s->getDependentConstantsNegative());
    }

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

    name = name + " " + body[0]->toString();
    for(int i=1; i<body.size(); ++i){
        name = name + " " + body[i]->toString();
    }
    name = name + ")";
}

QString GDL_Rule::buildNameRecursively(){
    QString answer = QString("(<= ") + head->buildNameRecursively();
    switch(body.size()){
    case 0:
        qDebug() << "Rule with arity 0 : " << answer;
        return answer;
    case 1:
        answer = answer + ' ' + body[0]->buildNameRecursively() + ')';
        return answer;
    default:
        break;
    }

    answer = answer + " " + body[0]->buildNameRecursively();
    for(int i=1; i<body.size(); ++i){
        answer = answer + " " + body[i]->buildNameRecursively();
    }
    answer = answer + ")";

    return answer;
}

PRelation GDL_Rule::getHead(){
    return head;
}

QVector<PSentence> GDL_Rule::getBody(){
    return body;
}

QSet<PConstant> GDL_Rule::getDependentConstants(){
    return dependentConstants;
}

QSet<PConstant> GDL_Rule::getDependentConstantsNegative(){
    return dependentConstantsNegative;
}
