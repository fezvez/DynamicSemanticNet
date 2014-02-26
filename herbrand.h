#ifndef HERBRAND_H
#define HERBRAND_H

#include "GDL/gdl.h"
#include "GDL/gdl_constant.h"
#include "GDL/gdl_variable.h"
#include "GDL/gdl_relationalsentence.h"
#include "GDL/gdl_distinctsentence.h"
#include "GDL/gdl_rule.h"
#include "GDL/gdl_functionalterm.h"
#include "GDL/gdl_notsentence.h"

#include <QStringList>
#include <QObject>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QSharedPointer>
#include <QMap>
#include <QSet>



class Herbrand : public QObject
{
    Q_OBJECT
public:
    Herbrand(QObject * parent = 0);

public slots:
    void loadKif(const QStringList &sl);

protected:
    void cleanFile();
    void generateHerbrand();
    void generateInformation();

signals:
    void output(const QString & message);
    void outputDebug(const QString & message);

private:
    void processKifLine(QString line);
    PRule processRule(QString line);
    PSentence processSentence(QString line);
    PRelation processRelation(QString line, GDL::GDL_TYPE type = GDL::NONE);
    PTerm processTerm(QString line);
    PFunction processFunction(QString line);

    QStringList split(QString line);

protected:
    QVector<PRule> ruleList;
    QVector<PRelation> relationList;

    QMap<QString, PConstant> constantMap;
    QSet<PConstant> objectConstantSet;
    QSet<PConstant> functionConstantSet;
    QSet<PConstant> relationConstantSet;

    QMap<GDL::GDL_TYPE, QVector<PRelation>> mapTypeToRelationContainer;
    QMap<GDL::GDL_TYPE, QVector<PRule>> mapTypeToRuleContainer;

    QVector<PRelation> baseRelations;
    QVector<PRelation> initRelations;
    QVector<PRelation> roleRelations;
    QVector<PRelation> standardRelations;

    QVector<PRule> baseRules;
    QVector<PRule> initRules;
    QVector<PRule> nextRules;
    QVector<PRule> goalRules;
    QVector<PRule> legalRules;
    QVector<PRule> inputRules;
    QVector<PRule> terminalRules;
    QVector<PRule> standardRules;


    QStringList rawKif;
    QStringList lineKif;

    QRegExp ruleRegExp;
    QRegExp whitespaceRegExp;
    QRegExp leftPar;
    QRegExp rightPar;
};

#endif // HERBRAND_H
