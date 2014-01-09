#ifndef GDL_TERM_H
#define GDL_TERM_H

class GDL_Term : public GDL
{
public:
    QString& toString() = 0;
    bool isGround() = 0;

protected:
    QString name;
};

#endif // GDL_TERM_H
