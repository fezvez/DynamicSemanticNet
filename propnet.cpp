#include "propnet.h"
#include "GDL/gdl_tools.h"

#include <QDebug>
#include <QSet>

PropNet::PropNet(QObject *parent):
    Herbrand(parent)
{

}

void PropNet::loadKif(const QStringList &sl){
    Herbrand::loadKif(sl);
    generatePropNet();
}

void PropNet::generatePropNet(){
    qDebug() << "\n\nPROPNET";

    GDL::GDL_TYPE base = GDL::BASE;
    QVector<PRelation> baseContainer = mapTypeToRelationContainer[base];

    for(PRelation relation : baseContainer){
        Q_ASSERT(relation->isGround());
        QString s = relation->toString();
        PProposition prop = PProposition(new PropositionConstant(relation->toString()));
        addBaseProposition(s, prop);
    }

    GDL::GDL_TYPE none = GDL::NONE;
    QVector<PRelation> noneContainer = mapTypeToRelationContainer[none];

    for(PRelation relation : noneContainer){
        Q_ASSERT(relation->isGround());
        QString s = relation->toString();
        PProposition prop = PProposition(new PropositionConstant(relation->toString()));
        addStandardProposition(s, prop);
    }

    GDL::GDL_TYPE role = GDL::ROLE;
    QVector<PRelation> roleContainer = mapTypeToRelationContainer[role];

    for(PRelation relation : roleContainer){
        Q_ASSERT(relation->isGround());
        QString s = relation->toString();
        PProposition prop = PProposition(new PropositionConstant(relation->toString()));
        addRoleProposition(s, prop);
    }

    initProposition = PProposition(new PropositionConstant(QString("init")));
//    GDL::GDL_TYPE init = GDL::INIT;
//    QVector<PRelation> initContainer = mapTypeToRelationContainer[init];

//    for(PRelation relation : initContainer){
//        Q_ASSERT(relation->isGround());
//        QString s = relation->toString();
//        PProposition prop = PProposition(new PropositionConstant(relation->toString()));
//        addInitProposition(s, prop);
//    }

    constructDependency();

    for(PProposition prop : propositions.values()){
        qDebug() << "Proposition : " << prop->toString();
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
    basePropositions.insert(s,p);
}

void PropNet::constructDependency(){
    qDebug() << "Dependency construction\n\n";
    for(GDL::GDL_TYPE type : mapTypeToRuleContainer.keys()){
        QVector<PRule> rules = mapTypeToRuleContainer[type];
        for(PRule rule : rules){
            qDebug() << "Rule of type " << GDL::getStringFromGDLType(type) << "\t: " << rule->toString();
            qDebug() << "Rule has head " << rule->getHead()->getRelationConstant()->toString()
                     << "\tDependence : " << GDL_Tools::printMembers(rule->getDependentConstants())
                     << "\tNegative Dependence : " << GDL_Tools::printMembers(rule->getDependentConstantsNegative());
        }
    }


}
