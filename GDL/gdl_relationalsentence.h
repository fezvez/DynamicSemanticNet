#ifndef GDL_RELATIONALSENTENCE_H
#define GDL_RELATIONALSENTENCE_H

#include "gdl_sentence.h"
#include "gdl_term.h"
#include "gdl_constant.h"

#include <QSharedPointer>
#include <QVector>

typedef QSharedPointer<GDL_Term> PTerm;
typedef QSharedPointer<GDL_Constant> PConstant;

class GDL_RelationalSentence : public GDL_Sentence
{
public:
    GDL_RelationalSentence(PConstant h, QVector<PTerm> b);

    bool isGround() const;

private:
    PConstant head;
    QVector<PTerm> body;

};

#endif // GDL_RELATIONALSENTENCE_H
