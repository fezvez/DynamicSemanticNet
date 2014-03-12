#ifndef GDL_FUNCTIONALTERM_H
#define GDL_FUNCTIONALTERM_H

#include "gdl_term.h"
#include "gdl_constant.h"
#include "../Trilogic.h"

#include <QVector>
#include <QSharedPointer>

using namespace std;

class GDL_FunctionalTerm;
typedef QSharedPointer<GDL_FunctionalTerm> PFunction;

class GDL_FunctionalTerm : public GDL_Term
{
public:
    GDL_FunctionalTerm(PConstant h, QVector<PTerm> b);

    bool isGround() const;
    QString buildNameRecursively();
    bool operator==(const GDL_Term & t);


private:
    void buildName();

private:
    PConstant head;
    QVector<PTerm> body;

};

#endif // GDL_FUNCTIONALTERM_H
