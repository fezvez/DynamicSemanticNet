#ifndef GDL_NOTSENTENCE_H
#define GDL_NOTSENTENCE_H

#include "gdl_sentence.h"

class GDL_NotSentence : public GDL_Sentence
{
public:
    GDL_NotSentence();

    bool isGround() const;
};

#endif // GDL_NOTSENTENCE_H
