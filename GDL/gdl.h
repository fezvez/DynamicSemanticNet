#ifndef GDL_H
#define GDL_H

#include <QString>
#include <QSharedPointer>
#include <QMap>

class GDL;
typedef QSharedPointer<GDL> PGDL;

enum GDL_TYPE{
    NONE,
    ROLE,
    BASE,
    INIT,
    TRUE,
    NEXT,
    LEGAL,
    DOES
};

class GDL
{
public:
    QString toString() const;
    virtual bool isGround() const = 0;

    virtual ~GDL();

    static void initGDLType(){
        mapGDLType.clear();
        mapGDLType.insert(QString("none"), GDL_TYPE::NONE);
        mapGDLType.insert(QString("role"), GDL_TYPE::ROLE);
        mapGDLType.insert(QString("base"), GDL_TYPE::BASE);
        mapGDLType.insert(QString("init"), GDL_TYPE::INIT);
        mapGDLType.insert(QString("true"), GDL_TYPE::TRUE);
        mapGDLType.insert(QString("next"), GDL_TYPE::NEXT);
        mapGDLType.insert(QString("legal"), GDL_TYPE::LEGAL);
        mapGDLType.insert(QString("does"), GDL_TYPE::DOES);
    }

    static GDL_TYPE getGDLType(const QString & s){
        if(mapGDLType.contains(s)){
            return mapGDLType[s];
        }
        return GDL_TYPE::NONE;
    }



protected:
    QString name;

    static QMap<QString, GDL_TYPE> mapGDLType;
};




#endif // GDL_H
