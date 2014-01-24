#ifndef GDL_FUNCTIONALTERM_H
#define GDL_FUNCTIONALTERM_H

#include "gdl_term.h"
#include "gdl_constant.h"
#include "../Trilogic.h"

#include <QVector>
#include <QSharedPointer>

using namespace std;

typedef QSharedPointer<GDL_Term> PTerm;
typedef QSharedPointer<GDL_Constant> PConstant;

class GDL_FunctionalTerm : public GDL_Term
{
public:
    GDL_FunctionalTerm(PConstant function, QVector<PTerm> body);

    bool isGround() const;

private:
    void buildName();

private:
    PConstant functionName;
    QVector<PTerm> functionBody;

};

#endif // GDL_FUNCTIONALTERM_H
