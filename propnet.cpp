#include "propnet.h"

#include <QDebug>

PropNet::PropNet(QObject *parent):
    Herbrand(parent)
{

}

void PropNet::loadKif(const QStringList &sl){
    Herbrand::loadKif(sl);
    generatePropNet();
}

void PropNet::generatePropNet(){
    qDebug() << "PROPNET";

    GDL::GDL_TYPE base = GDL::BASE;
    QVector<PRelation> baseContainer = mapTypeToRelationContainer[base];

    for(PRelation relation : baseContainer){
        Q_ASSERT(relation->isGround());
        QString s = relation->toString();
        PProposition prop = PProposition(new PropositionConstant(relation->toString()));
        addBaseProposition(s, prop);
    }

    for(PProposition prop : propositions){
        qDebug() << "Proposition : " << prop->toString();
    }
}

void PropNet::addBaseProposition(QString s, PProposition p){
    propositions.insert(s,p);
    basePropositions.push_back(p);
}

