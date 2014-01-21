#ifndef GDL_FUNCTIONALTERM_H
#define GDL_FUNCTIONALTERM_H

#include "gdl_term.h"
#include "gdl_constant.h"
#include "../Trilogic.h"

#include <QVector>
#include <QSharedPointer>

using namespace std;

typedef QSharedPointer<GDL_Term> PTerm;

class GDL_FunctionalTerm : public GDL_Term
{
public:
    GDL_FunctionalTerm(const GDL_Constant &function, QVector<PTerm> body);

    bool isGround() const;

private:
    void buildName();

private:
    GDL_Constant functionName;
    QVector<PTerm> functionBody;
    TRILOGIC ground;
};

#endif // GDL_FUNCTIONALTERM_H
