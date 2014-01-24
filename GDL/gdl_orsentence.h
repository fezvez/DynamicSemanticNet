#ifndef GDL_ORSENTENCE_H
#define GDL_ORSENTENCE_H

#include "gdl_sentence.h"

#include <QSharedPointer>

typedef QSharedPointer<GDL_Sentence> PSentence;

class GDL_OrSentence : public GDL_Sentence
{
public:
    GDL_OrSentence(PSentence s);

    bool isGround() const;


private:
    PSentence sentence;
};

#endif // GDL_ORSENTENCE_H
