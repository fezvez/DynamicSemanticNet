#ifndef GDL_SENTENCE_H
#define GDL_SENTENCE_H

class GDL_Sentence : public GDL
{
public:
    QString& toString() = 0;
    bool isGround() = 0;
};

#endif // GDL_SENTENCE_H
