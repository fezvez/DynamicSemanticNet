#ifndef GDL_SENTENCE_H
#define GDL_SENTENCE_H

#include "gdl.h"
#include "gdl_constant.h"

class GDL_Sentence;
typedef QSharedPointer<GDL_Sentence> PSentence;

class GDL_Sentence : public GDL
{
public:
    bool isGround() const = 0;
    QString buildNameRecursively() = 0;

    QSet<PConstant> getDependentConstants();
    QSet<PConstant> getDependentConstantsNegative();

protected:
    QSet<PConstant> dependentConstants;
    QSet<PConstant> dependentConstantsNegative;
};

#endif // GDL_SENTENCE_H
