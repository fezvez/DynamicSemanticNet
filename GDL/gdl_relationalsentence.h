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
    GDL_RelationalSentence(PConstant h, QVector<PTerm> b, GDL::GDL_TYPE t = GDL::NONE);

    bool isGround() const;

    PConstant getRelation();
    GDL::GDL_TYPE getType();

private:
    void buildName();

private:
    PConstant head;
    QVector<PTerm> body;
    GDL::GDL_TYPE type;

};

#endif // GDL_RELATIONALSENTENCE_H
