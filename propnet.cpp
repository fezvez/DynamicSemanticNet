#include "propnet.h"

#include <QDebug>

PropNet::PropNet(QObject *parent):
    Herbrand(parent)
{

}

void PropNet::loadKif(const QStringList &sl){
    Herbrand::loadKif(sl);
    generatePropNet();
}

void PropNet::generatePropNet(){
    qDebug() << "PROPNET";
}

