#ifndef GDL_TERM_H
#define GDL_TERM_H

#include "gdl.h"

class GDL_Term : public GDL
{
public:
    bool isGround() const = 0;


};

#endif // GDL_TERM_H
