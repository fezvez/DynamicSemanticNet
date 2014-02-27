#ifndef PROPOSITIONCONSTANT_H
#define PROPOSITIONCONSTANT_H

#include "proposition.h"

class PropositionConstant;
typedef QSharedPointer<PropositionConstant> PPropConst;

class PropositionConstant : public Proposition
{
public:
    PropositionConstant(QString n);

    bool isTrue() const;
};

#endif // PROPOSITIONCONSTANT_H
