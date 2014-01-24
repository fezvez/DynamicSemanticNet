#ifndef PLAYER_H
#define PLAYER_H

#include "GDL/gdl.h"
#include "GDL/gdl_constant.h"
#include "GDL/gdl_variable.h"
#include "GDL/gdl_relationalsentence.h"
#include "GDL/gdl_rule.h"
#include "GDL/gdl_functionalterm.h"
#include "GDL/gdl_notsentence.h"

#include <QStringList>
#include <QObject>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QSharedPointer>

typedef QSharedPointer<GDL> PGDL;
typedef QSharedPointer<GDL_Rule> PRule;
typedef QSharedPointer<GDL_Sentence> PSentence;
typedef QSharedPointer<GDL_RelationalSentence> PRelation;
typedef QSharedPointer<GDL_FunctionalTerm> PFunction;
typedef QSharedPointer<GDL_NotSentence> PNotSentence;

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent);

public slots:
    void updateKif(const QStringList &sl);

private:
    void processKifLine(QString line);
    PRule processRule(QString line);
    PSentence processSentence(QString line);
    PRelation processRelation(QString line);
    PTerm processTerm(QString line);
    PFunction processFunction(QString line);


    QStringList split(QString line);

private:
    QVector<PGDL> gdlList;

    QStringList rawKif;
    QStringList lineKif;

    QRegExp ruleRegExp;
    QRegExp wordRegExp;
    QRegExp whitespaceRegExp;
    QRegExp leftPar;
    QRegExp rightPar;
};

#endif // PLAYER_H
