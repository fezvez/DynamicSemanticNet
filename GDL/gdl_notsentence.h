#ifndef GDL_NOTSENTENCE_H
#define GDL_NOTSENTENCE_H

#include "gdl_sentence.h"

#include <QSharedPointer>

typedef QSharedPointer<GDL_Sentence> PSentence;

class GDL_NotSentence : public GDL_Sentence
{
public:
    GDL_NotSentence(PSentence s);

    bool isGround() const;

private:
    PSentence sentence;
};

#endif // GDL_NOTSENTENCE_H
