#ifndef GDL_RULE_H
#define GDL_RULE_H

#include "gdl.h"
#include "gdl_relationalsentence.h"
#include "gdl_sentence.h"

#include <vector>
#include <QVector>
#include <QSharedPointer>

typedef QSharedPointer<GDL_Sentence> PSentence;
typedef QSharedPointer<GDL_RelationalSentence> PRelation;

using namespace std;

class GDL_Rule : public GDL
{
public:
    GDL_Rule(PRelation h, QVector<PSentence> b);

    bool isGround() const;

private:
    PRelation head;
    QVector<PSentence> body;
};

#endif // GDL_RULE_H
