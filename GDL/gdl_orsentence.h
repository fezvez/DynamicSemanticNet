#ifndef GDL_ORSENTENCE_H
#define GDL_ORSENTENCE_H

#include "gdl_sentence.h"

class GDL_OrSentence : public GDL_Sentence
{
public:
    GDL_OrSentence();

    bool isGround() const;
};

#endif // GDL_ORSENTENCE_H
