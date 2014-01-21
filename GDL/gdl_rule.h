#ifndef GDL_RULE_H
#define GDL_RULE_H

#include "gdl.h"
#include "gdl_relationalsentence.h"
#include "gdl_sentence.h"

#include <vector>

using namespace std;

class GDL_Rule : public GDL
{
public:
    GDL_Rule();

    bool isGround() const;

private:
    GDL_RelationalSentence head;
    vector<GDL_Sentence> body;
};

#endif // GDL_RULE_H
