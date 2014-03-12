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
#include "GDL/gdl_nextsentence.h"

#include <QStringList>
#include <QObject>
#include <QRegExp>
#include <QStringList>
#include <QVector>
#include <QSharedPointer>
#include <QMap>
#include <QSet>

class Stratum;
typedef QSharedPointer<Stratum> PStratum;

class Stratum{
public:
    Stratum(PConstant n);

    void addDependency(PStratum s);
    void addDependencyNegative(PStratum s);

    PConstant getNode();
    int getStrata() const;
    bool updateStrata();
    bool updateStrataStrongly();

    QString toString();

public:
    static bool greaterThan(PStratum s1, PStratum s2){
      return s1->getStrata()<s2->getStrata();
    }

private:
    PConstant node;
    QSet<PStratum> dependency;
    QSet<PStratum> dependencyNegative;

    int strata;
};

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
    void generateStratum();
    void generateInformation();

signals:
    void output(const QString & message);
    void outputDebug(const QString & message);

private:
    void processKifLine(QString line);
    PRule processRule(QString line);
    PSentence processSentence(QString line);
    PRelation processRelation(QString line, bool isHead = false, GDL::GDL_TYPE type = GDL::NONE);
    PTerm processTerm(QString line);
    PFunction processFunction(QString line);

    QStringList split(QString line);

private:


protected:
    QStringList rawKif;
    QStringList lineKif;

    QRegExp ruleRegExp;
    QRegExp whitespaceRegExp;
    QRegExp leftPar;
    QRegExp rightPar;

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

    QMap<PConstant, QVector<PConstant>> skolemMap;

protected:
    QMap<PConstant, PStratum> stratumMap;
    QVector<QVector<PConstant>> stratifiedConstants;

    QMap<PConstant, QVector<PRule>> constantToRuleMap;
    QMap<PConstant, QVector<PRelation>> constantToRelationMap;


};




#endif // HERBRAND_H
