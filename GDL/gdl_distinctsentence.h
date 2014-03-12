#ifndef GDL_DISTINCTSENTENCE_H
#define GDL_DISTINCTSENTENCE_H

#include "gdl_sentence.h"
#include "gdl_term.h"

#include <QSharedPointer>


class GDL_DistinctSentence;
typedef QSharedPointer<GDL_DistinctSentence> PDistinctSentence;

class GDL_DistinctSentence : public GDL_Sentence
{
public:
    GDL_DistinctSentence(PTerm t1, PTerm t2);

    bool isGround() const;
    QString buildNameRecursively();

protected:
    PTerm term1;
    PTerm term2;
};

#endif // GDL_DISTINCTSENTENCE_H
