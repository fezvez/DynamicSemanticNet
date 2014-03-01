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
    QSet<PConstant> getChildConstants();

protected:
    QSet<PConstant> childConstants;
};

#endif // GDL_SENTENCE_H
