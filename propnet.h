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
    QVector<PProposition> basePropositions;

private:
    void addBaseProposition(QString s, PProposition p);

};

#endif // PROPNET_H
