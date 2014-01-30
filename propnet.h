#ifndef PROPNET_H
#define PROPNET_H

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



class PropNet : public QObject
{
    Q_OBJECT
public:
    PropNet(QObject * parent = 0);

public slots:
    void loadKif(const QStringList &sl);

private:
    void cleanFile();
    void generateHerbrand();
    void generatePropNet();

signals:
    void output(const QString & message);
    void outputDebug(const QString & message);

private:
    void processKifLine(QString line);
    PRule processRule(QString line);
    PSentence processSentence(QString line);
    PRelation processRelation(QString line);
    PTerm processTerm(QString line);
    PFunction processFunction(QString line);


    QStringList split(QString line);

private:

    QVector<PRule> ruleList;
    QVector<PRelation> relationList;

    QMap<QString, QVector<PRelation>> relationMap;

    QVector<PGDL> gdlList;
    QVector<PSentence> sentenceList;
    QVector<PConstant> constantList;


    QSet<PConstant> objectConstantSet;
    QSet<PConstant> functionConstantSet;
    QSet<PConstant> relationConstantSet;

    QMap<QString, PConstant> constantMap;

    QStringList rawKif;
    QStringList lineKif;

    QRegExp ruleRegExp;
    QRegExp wordRegExp;
    QRegExp whitespaceRegExp;
    QRegExp leftPar;
    QRegExp rightPar;
};

#endif // PROPNET_H
