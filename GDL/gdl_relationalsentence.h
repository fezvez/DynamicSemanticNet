#ifndef GDL_RELATIONALSENTENCE_H
#define GDL_RELATIONALSENTENCE_H

#include "gdl_sentence.h"
#include "gdl_term.h"
#include "gdl_constant.h"

#include <QVector>

class GDL_RelationalSentence;
typedef QSharedPointer<GDL_RelationalSentence> PRelation;

class GDL_RelationalSentence : public GDL_Sentence
{
public:
    GDL_RelationalSentence(PConstant h, QVector<PTerm> b);

    bool isGround() const;

    PConstant getRelation();

private:
    void buildName();

private:
    PConstant head;
    QVector<PTerm> body;

};

#endif // GDL_RELATIONALSENTENCE_H
