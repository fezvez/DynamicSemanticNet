#ifndef GDL_ORSENTENCE_H
#define GDL_ORSENTENCE_H

#include "gdl_sentence.h"

#include <QSharedPointer>
#include <QVector>

class GDL_OrSentence;
typedef QSharedPointer<GDL_OrSentence> POrSentence;

class GDL_OrSentence : public GDL_Sentence
{
public:
    GDL_OrSentence(QVector<PSentence> b);

    bool isGround() const;


private:
    QVector<PSentence> body;
};

#endif // GDL_ORSENTENCE_H
