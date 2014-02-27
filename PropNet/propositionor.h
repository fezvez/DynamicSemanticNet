#ifndef PROPOSITIONOR_H
#define PROPOSITIONOR_H

#include "proposition.h"

#include <QVector>

class PropositionOr;
typedef QSharedPointer<PropositionOr> PPropOr;

class PropositionOr : public Proposition
{
public:
    PropositionOr(QVector<PProposition> l, QString n);

    bool isTrue() const;

protected:
    QVector<PProposition> list;
};

#endif // PROPOSITIONOR_H
