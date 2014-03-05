#ifndef STRATUM_H
#define STRATUM_H

#include "../GDL/gdl_rule.h"
#include "../GDL/gdl_relationalsentence.h"

class Stratum
{
public:
    Stratum(QVector<PRelation> e, QVector<PRule>i);

private:


private:
    QVector<PRelation> EDB;
    QVector<PRule> IDB;
};

#endif // STRATUM_H
