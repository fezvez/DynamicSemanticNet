#ifndef PROPNET_H
#define PROPNET_H

#include "herbrand.h"

class PropNet : public Herbrand
{
    Q_OBJECT
public:
    PropNet(QObject * parent = 0);


public slots:
    void loadKif(const QStringList &sl);

protected:
    void generatePropNet();

};

#endif // PROPNET_H
