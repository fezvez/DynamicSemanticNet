#ifndef GDL_NOTSENTENCE_H
#define GDL_NOTSENTENCE_H

#include "gdl_sentence.h"

#include <QSharedPointer>

class GDL_NotSentence;
typedef QSharedPointer<GDL_NotSentence> PNotSentence;

class GDL_NotSentence : public GDL_Sentence
{
public:
    GDL_NotSentence(PSentence s);

    bool isGround() const;

private:
    void buildChildConstants();

private:
    PSentence sentence;
};

#endif // GDL_NOTSENTENCE_H
