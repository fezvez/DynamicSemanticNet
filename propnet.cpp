#include "propnet.h"


#include <QDebug>
#include <QStringBuilder>
#include <QtCore>



PropNet::PropNet(QObject *parent):
    QObject(parent)
{
    ruleRegExp = QRegExp("<=");
    wordRegExp = QRegExp("\\S+");
    whitespaceRegExp = QRegExp("\\s+");
    leftPar = QRegExp("^\\($");
    rightPar = QRegExp("^\\)$");

}

void PropNet::loadKif(const QStringList & sl){
    // Load file
    rawKif = QStringList(sl);

    cleanFile();
    generateHerbrand();
    generatePropNet();
}

void PropNet::cleanFile(){
    qDebug() << "Kif loaded in PropNet!";
    qDebug() << "Printing kif";

    for(int i=0; i<rawKif.size(); ++i){
        qDebug() << rawKif[i];
    }


    // Clean file
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

    qDebug() << "Kif processed in PropNet!";
    qDebug() << "Printing kif";
    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << lineKif[i];
    }

    emit output(QString("Kif loaded and cleaned"));
}

void PropNet::generateHerbrand(){


    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << "\nProcessing line " << lineKif[i];
        processKifLine(lineKif[i]);
    }

    emit output(QString("Herbrand generated"));
}

void PropNet::generatePropNet(){

}


void PropNet::processKifLine(QString line){
    if(line.contains(ruleRegExp)){
        processRule(line);
    }
    else{
        processRelation(line);
    }
}



PRule PropNet::processRule(QString line){
    qDebug() << "Rule " << line;

    QStringList splitLine = split(line);

    Q_ASSERT(splitLine[0] == QString("<="));

    PRelation head = processRelation(splitLine[1]);
    QVector<PSentence> body;

    for(int i = 2; i<splitLine.size(); ++i){
        body.append(processSentence(splitLine[i]));
    }

    return PRule(new GDL_Rule(head, body));
}

PSentence PropNet::processSentence(QString line){
    qDebug() << "Sentence " << line;

    QStringList splitLine = split(line);
    if(splitLine[0] == QString("distinct")){
        qDebug() << "Sentence is DISTINCT sentence";
    }
    else if(splitLine[0] == QString("not")){
        qDebug() << "Sentence is NOT sentence";
        Q_ASSERT(splitLine.size() == 2);
        PSentence subSentence = processRelation(splitLine[1]);
        PNotSentence notSentence = PNotSentence(new GDL_NotSentence(subSentence));
        return qSharedPointerCast<GDL_Sentence>(notSentence);
    }
    else{
        qDebug() << "Sentence is relational sentence";
        return qSharedPointerCast<GDL_Sentence>(processRelation(line));
    }
}

PRelation PropNet::processRelation(QString line){
    qDebug() << "Relational sentence " << line;

    QStringList splitLine = split(line);

    qDebug() << "Relation constant is : " << splitLine[0];
    PConstant head = PConstant(new GDL_Constant(splitLine[0]));
    QVector<PTerm> body;

    if(splitLine[0] == QString("base")
            || splitLine[0] == QString("init")
            || splitLine[0] == QString("next")
            || splitLine[0] == QString("true")){
            Q_ASSERT(splitLine.size() == 2);
            PRelation relation = processRelation(splitLine[1]);
            //PRelation t= qSharedPointerCast<GDL_RelationalSentence>(relation);
            return relation;
    }
    else if(splitLine[0] == QString("input")
            || splitLine[0] == QString("legal")
            || splitLine[0] == QString("does")) {
        Q_ASSERT(splitLine.size() == 3);
        body.append(qSharedPointerCast<GDL_Term>(processTerm(splitLine[1])));
        body.append(qSharedPointerCast<GDL_Term>(processTerm(splitLine[2])));
    }
    else {
        for(int i = 1; i<splitLine.size(); ++i){
            body.append(qSharedPointerCast<GDL_Term>(processTerm(splitLine[i])));
        }
    }

    return PRelation(new GDL_RelationalSentence(head, body));
}

PTerm PropNet::processTerm(QString line){
    qDebug() << "Term " << line;
    QStringList splitLine = split(line);

    if(splitLine.size() == 1){
        if(splitLine[0][0] == QChar('?')){
            qDebug() << "Variable " << splitLine[0];
            return PTerm(new GDL_Variable(splitLine[0]));
        }
        else{
            qDebug() << "Constant " << splitLine[0];
            return PTerm(new GDL_Constant(splitLine[0]));
        }
    }
    else{
        qDebug() << "WE HAVE A FUNCTIONAL TERM";
        return processFunction(line);
    }
}

PFunction PropNet::processFunction(QString line){
    qDebug() << "Function " << line;
    QStringList splitLine = split(line);

    PConstant function = PConstant(new GDL_Constant(splitLine[0]));

    QVector<PTerm> body;
    for(int i = 0; i<splitLine.size(); ++i){
        PTerm term = processTerm(splitLine[i]);
        body.append(term);
    }

    return PFunction(new GDL_FunctionalTerm(function, body));
}


QStringList PropNet::split(QString line){
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

//    for(int i = 0; i<answer.size(); ++i){
//        qDebug() << "Split : " << answer[i];
//    }

    return answer;
}

