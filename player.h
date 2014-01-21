#ifndef PLAYER_H
#define PLAYER_H

#include <QStringList>
#include <QObject>
#include <QRegExp>
#include <QStringList>


class Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent);

public slots:
    void updateKif(const QStringList &sl);

private:
    void processKifLine(QString line);
    void processRule(QString line);
    void processLiteral(QString line);
    void processRelation(QString line);
    void processTerm(QString line);
    QStringList split(QString line);

private:
    QStringList rawKif;
    QStringList lineKif;

    QRegExp ruleRegExp;
    QRegExp wordRegExp;
    QRegExp whitespaceRegExp;
    QRegExp leftPar;
    QRegExp rightPar;
};

#endif // PLAYER_H
