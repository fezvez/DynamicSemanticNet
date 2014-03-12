#ifndef GDL_H
#define GDL_H

#include <QString>
#include <QSharedPointer>
#include <QMap>
#include <QSet>


class GDL;
typedef QSharedPointer<GDL> PGDL;



class GDL
{
public:
    enum GDL_TYPE{
        NONE,
        ROLE,
        BASE,
        INIT,
        TRUE,
        NEXT,
        DOES,
        GOAL,
        LEGAL,
        INPUT,
        TERMINAL
    };



public:
    virtual QString toString() const;
    virtual bool isGround() const = 0;
    virtual QString buildNameRecursively() = 0;

    virtual ~GDL();

public:
    static void init(){
        mapString2GDLType.clear();
        mapString2GDLType.insert(QString("none"), GDL_TYPE::NONE);
        mapString2GDLType.insert(QString("role"), GDL_TYPE::ROLE);
        mapString2GDLType.insert(QString("base"), GDL_TYPE::BASE);
        mapString2GDLType.insert(QString("init"), GDL_TYPE::INIT);
        mapString2GDLType.insert(QString("true"), GDL_TYPE::TRUE);
        mapString2GDLType.insert(QString("next"), GDL_TYPE::NEXT);
        mapString2GDLType.insert(QString("does"), GDL_TYPE::DOES);
        mapString2GDLType.insert(QString("goal"), GDL_TYPE::GOAL);
        mapString2GDLType.insert(QString("legal"), GDL_TYPE::LEGAL);
        mapString2GDLType.insert(QString("input"), GDL_TYPE::INPUT);
        mapString2GDLType.insert(QString("terminal"), GDL_TYPE::TERMINAL);

        mapGDLType2String.clear();
        mapGDLType2String.insert(GDL_TYPE::NONE ,QString("none"));
        mapGDLType2String.insert(GDL_TYPE::ROLE ,QString("role"));
        mapGDLType2String.insert(GDL_TYPE::BASE ,QString("base"));
        mapGDLType2String.insert(GDL_TYPE::INIT ,QString("init"));
        mapGDLType2String.insert(GDL_TYPE::TRUE ,QString("true"));
        mapGDLType2String.insert(GDL_TYPE::NEXT ,QString("next"));
        mapGDLType2String.insert(GDL_TYPE::DOES ,QString("does"));
        mapGDLType2String.insert(GDL_TYPE::GOAL ,QString("goal"));
        mapGDLType2String.insert(GDL_TYPE::LEGAL,QString("legal"));
        mapGDLType2String.insert(GDL_TYPE::INPUT,QString("input"));
        mapGDLType2String.insert(GDL_TYPE::TERMINAL,QString("terminal"));
    }

    static GDL_TYPE getGDLTypeFromString(const QString & s){
        if(mapString2GDLType.contains(s)){
            return mapString2GDLType[s];
        }
        return GDL_TYPE::NONE;
    }

    static QString getStringFromGDLType(GDL_TYPE t){
        if(mapGDLType2String.contains(t)){
            return mapGDLType2String[t];
        }
        return QString("Type unknown");
    }

    static void setSkolemNames(bool b){
        useSkolemNames = b;
    }



public:
    static QMap<QString, GDL_TYPE> mapString2GDLType;
    static QMap<GDL_TYPE, QString> mapGDLType2String;
    static bool useSkolemNames;

protected:
    QString name;
};




#endif // GDL_H
