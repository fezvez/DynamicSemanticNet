#ifndef GDL_RULE_H
#define GDL_RULE_H

#include "gdl.h"
#include "gdl_relationalsentence.h"
#include "gdl_sentence.h"

#include <QVector>
#include <QSharedPointer>

class GDL_Rule;
typedef QSharedPointer<GDL_Rule> PRule;

class GDL_Rule : public GDL
{
public:
    GDL_Rule(PRelation h, QVector<PSentence> b);

    bool isGround() const;
    PRelation getHead();

private:
    void buildName();

private:
    PRelation head;
    QVector<PSentence> body;
};

#endif // GDL_RULE_H
