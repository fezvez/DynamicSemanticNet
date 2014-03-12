#include "propnet.h"
#include "GDL/gdl_tools.h"

#include <QDebug>
#include <QSet>

PropNet::PropNet(QObject *parent):
    Herbrand(parent)
{
    GDL::setSkolemNames(false);
}

void PropNet::loadKif(const QStringList &sl){
    Herbrand::loadKif(sl);
    //generatePropNet();
}

void PropNet::generatePropNet(){
    qDebug() << "\n\nPROPNET";

    for(QVector<PConstant> vec : stratifiedConstants){
        qDebug() << "\n\nSTRATUM";
        for(PConstant constant : vec){
            qDebug() << "Constant " << constant->toString();
            if(constantToRelationMap.contains(constant)){
                for(PRelation relation : constantToRelationMap[constant]){
                    if(relation->getType() == GDL::INIT){
                        continue;
                    }
                    qDebug() << "\tRelation " << relation->toString();
                }
            }

            if(constantToRuleMap.contains(constant)){
                for(PRule rule : constantToRuleMap[constant]){

                    qDebug() << "\tRule " << rule->toString();
                }
            }
        }
    }

    //propositionDatabase = PDatabase(new PropositionDatabase());

    for(QVector<PConstant> vec : stratifiedConstants){
        qDebug() << "\n\nSTRATUM 2";
        for(PConstant constant : vec){
            qDebug() << "Constant " << constant->toString();
            bool update = true;
            while(update){
                update = false;

                if(constantToRelationMap.contains(constant)){
                    for(PRelation relation : constantToRelationMap[constant]){
                        Q_ASSERT(relation->isGround());

                    }
                }

                if(constantToRuleMap.contains(constant)){
                    for(PRule rule : constantToRuleMap[constant]){

                    }
                }
            }

        }
    }

    qDebug() << "\n\nSTRATUM 3";

    for(PRule rule : ruleList){
        qDebug() << rule->toString();
        qDebug() << rule->buildNameRecursively();
    }
}

void PropNet::addBaseProposition(QString s, PProposition p){
    propositions.insert(s,p);
    basePropositions.insert(s,p);
}

void PropNet::addRoleProposition(QString s, PProposition p){
    propositions.insert(s,p);
    rolePropositions.insert(s,p);
}

void PropNet::addStandardProposition(QString s, PProposition p){
    propositions.insert(s,p);
    standardPropositions.insert(s,p);
}


