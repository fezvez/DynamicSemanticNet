#ifndef GDL_FUNCTIONALTERM_H
#define GDL_FUNCTIONALTERM_H

#include "gdl_term.h"
#include "gdl_constant.h"
#include "../Trilogic.h"

#include <vector>

using namespace std;

class GDL_FunctionalTerm : public GDL_Term
{
public:
    GDL_FunctionalTerm(GDL_Constant & f, vector<GDL_Term> & b);

    QString& toString();
    bool isGround();

private:
    GDL_Constant functionName;
    vector<GDL_Term> functionBody;
    TRILOGIC isGround;
};

#endif // GDL_FUNCTIONALTERM_H
