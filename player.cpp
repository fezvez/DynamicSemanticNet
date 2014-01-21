#include "player.h"

#include <QDebug>
#include <QStringBuilder>
#include <QtCore>

Player::Player(QObject *parent):
    QObject(parent)
{
    ruleRegExp = QRegExp("<=");
    wordRegExp = QRegExp("\\S+");
    whitespaceRegExp = QRegExp("\\s+");
    leftPar = QRegExp("^\\($");
    rightPar = QRegExp("^\\)$");

}

void Player::updateKif(const QStringList & sl){
    rawKif = QStringList(sl);

    qDebug() << "Kif processed in Player!";
    qDebug() << "Printing kif";

    for(int i=0; i<rawKif.size(); ++i){
        qDebug() << rawKif[i];
    }



    QString currentLine;
    bool isLineContinuation = false;
    int nbParenthesis, nbLeftParenthesis, nbRightParenthesis;

    for(int i=0; i<rawKif.size(); ++i){
        nbLeftParenthesis = rawKif[i].count('(');
        nbRightParenthesis = rawKif[i].count(')');
        if(isLineContinuation){
            currentLine.append(' ');
        }
        else{
            currentLine.clear();
            nbParenthesis = 0;

        }
        currentLine.append(rawKif[i]);

        nbParenthesis += (nbLeftParenthesis - nbRightParenthesis);

        Q_ASSERT(nbParenthesis >= 0);

        if(nbParenthesis>0){
            isLineContinuation = true;
        }
        else{
            isLineContinuation = false;
            lineKif.append(currentLine);
        }
    }

    qDebug() << "Kif processed in Player!";
    qDebug() << "Printing kif";
    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << lineKif[i];
    }

    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << "Processing line " << lineKif[i];
        processKifLine(lineKif[i]);
    }
}

void Player::processKifLine(QString line){
    if(line.contains(ruleRegExp)){
        processRule(line);
    }
    else{
        processRelation(line);
    }
}



void Player::processRule(QString line){
    qDebug() << "Rule " << line;

    QStringList splitLine = split(line);

    Q_ASSERT(splitLine[0] == QString("<="));

    processRelation(splitLine[1]);

    for(int i = 2; i<splitLine.size(); ++i){
        processLiteral(splitLine[i]);
    }
}

void Player::processLiteral(QString line){

    qDebug() << "Literal " << line;

    QStringList splitLine = split(line);
    if(splitLine[0] == QString("distinct")){
        qDebug() << "DISTINCT";
    }
    if(splitLine[0] == QString("not")){
        qDebug() << "NOT";
    }
    processRelation(line);

}

void Player::processRelation(QString line){
    qDebug() << "Relation " << line;

    QStringList splitLine = split(line);

    qDebug() << "Relation : " << splitLine[0];

    for(int i = 1; i<splitLine.size(); ++i){
        processTerm(splitLine[i]);
    }
}

void Player::processTerm(QString line){
    qDebug() << "Term " << line;
    QStringList splitLine = split(line);


}


QStringList Player::split(QString line){
    QStringList answer;
    QString currentPart;

    line.replace('(', " ( ");
    line.replace(')', " ) ");
    line = line.trimmed();


    QStringList rawSplit = line.split(whitespaceRegExp);
    //     for(int i = 0; i<rawSplit.size(); ++i){
    //         qDebug() << rawSplit[i].length() << "\t" << rawSplit[i];
    //     }

    Q_ASSERT((leftPar.indexIn(rawSplit.first()) == 0 &&
             rightPar.indexIn(rawSplit.last()) == 0) ||
             (rawSplit.size() == 1));

    if(rawSplit.size() == 1){
        answer = rawSplit;
        return answer;
    }

    int nbParenthesis = 0;

    for(int i = 1 ; i<rawSplit.size() - 1; ++i){


        if(leftPar.indexIn(rawSplit[i]) == 0){
            nbParenthesis++;
        }
        else if(rightPar.indexIn(rawSplit[i]) == 0){
            nbParenthesis--;
        }

        currentPart.append(rawSplit[i]);
        currentPart.append(' ');

        if(nbParenthesis == 0){
            answer.append(currentPart.trimmed());
            currentPart.clear();
        }
    }

    for(int i = 0; i<answer.size(); ++i){
        qDebug() << "Split : " << answer[i];
    }

    return answer;
}

