#ifndef PROPNET_H
#define PROPNET_H

#include "herbrand.h"
#include "PropNet/proposition.h"
#include "PropNet/propositionand.h"
#include "PropNet/propositionor.h"
#include "PropNet/propositionnot.h"
#include "PropNet/propositionconstant.h"

class PropNet : public Herbrand
{
    Q_OBJECT
public:
    PropNet(QObject * parent = 0);


public slots:
    void loadKif(const QStringList &sl);

protected:
    void generatePropNet();

    QMap<QString, PProposition> propositions;
    QMap<QString, PProposition> basePropositions;
    QMap<QString, PProposition> rolePropositions;
    QMap<QString, PProposition> standardPropositions;
    PProposition initProposition;

private:
    void addBaseProposition(QString s, PProposition p);
    void addRoleProposition(QString s, PProposition p);
    void addStandardProposition(QString s, PProposition p);

    void constructDependency();

};

#endif // PROPNET_H
