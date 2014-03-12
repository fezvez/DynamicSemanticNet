#include "gdl.h"

QString GDL::toString() const{
    return name;
}

GDL::~GDL(){

}

QMap<QString, GDL::GDL_TYPE> GDL::mapString2GDLType = QMap<QString, GDL::GDL_TYPE>();
QMap<GDL::GDL_TYPE, QString> GDL::mapGDLType2String = QMap<GDL::GDL_TYPE, QString>();
bool GDL::useSkolemNames = false;
