#ifndef GDL_RELATIONALSENTENCE_H
#define GDL_RELATIONALSENTENCE_H

#include "gdl_sentence.h"

class GDL_RelationalSentence : public GDL_Sentence
{
public:
    GDL_RelationalSentence();

    bool isGround() const;
};

#endif // GDL_RELATIONALSENTENCE_H
