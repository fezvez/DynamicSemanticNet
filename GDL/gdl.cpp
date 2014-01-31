#include "gdl.h"

QString GDL::toString() const{
    return name;
}

GDL::~GDL(){

}

QMap<QString, GDL_TYPE> GDL::mapGDLType = QMap<QString, GDL_TYPE>();

