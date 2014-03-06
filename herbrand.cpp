#include "herbrand.h"


#include <QDebug>
#include <QStringBuilder>
#include <QtCore>



Herbrand::Herbrand(QObject *parent):
    QObject(parent)
{
    ruleRegExp = QRegExp("<=");
    whitespaceRegExp = QRegExp("\\s+");
    leftPar = QRegExp("^\\($");
    rightPar = QRegExp("^\\)$");
}


void Herbrand::loadKif(const QStringList & sl){
    // Load file
    rawKif = QStringList(sl);

    cleanFile();
    generateHerbrand();
    generateStratum();
    //generateInformation();
}


void Herbrand::cleanFile(){
    qDebug() << "Kif loaded in Herbrand!";
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

    qDebug() << "Kif processed in Herbrand!";
    qDebug() << "Printing kif";
    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << lineKif[i];
    }

    emit output(QString("Kif loaded and cleaned"));
}


void Herbrand::generateHerbrand(){
    for(int i=0; i<lineKif.size(); ++i){
        qDebug() << "\n\nProcessing line " << lineKif[i];
        processKifLine(lineKif[i]);
    }
    emit output(QString("Herbrand generated"));
}

void Herbrand::generateStratum(){
    qDebug() << "\n\nGENERATE STRATUM";
    for(PRelation relation : relationList){
        qDebug() << "Relation : " << relation->toString();
        PConstant relationalConstant = relation->getRelationConstant();

        if(!stratumMap.contains(relationalConstant)){
            stratumMap.insert(relationalConstant, PStratum(new Stratum(relationalConstant)));
        }
    }

    for(PRule rule : ruleList){
        qDebug() << "Rule : " << rule->toString();
        PConstant head = rule->getHead()->getHead();


        if(!stratumMap.contains(head)){
            stratumMap.insert(head, PStratum(new Stratum(head)));
        }
        PStratum stratum = stratumMap[head];


        QSet<PConstant> dependents = rule->getDependentConstants();
        for(PConstant d : dependents){
            if(!stratumMap.contains(d)){
                stratumMap.insert(d, PStratum(new Stratum(d)));
            }
            stratum->addDependency(stratumMap[d]);
        }


        QSet<PConstant> dependentsNegative = rule->getDependentConstantsNegative();
        for(PConstant dn : dependentsNegative){
            if(!stratumMap.contains(dn)){
                stratumMap.insert(dn, PStratum(new Stratum(dn)));
            }
            stratum->addDependencyNegative(stratumMap[dn]);
        }
    }

    bool update = true;
    int nbIteration = 0;

    while(update && nbIteration<100){
        update = false;
        for(PStratum stratum : stratumMap.values()){
            stratum->updateStrataStrongly();
        }
    }

    for(PStratum s : stratumMap.values()){
        qDebug() << "Stratum " << s->toString();
    }
}


void Herbrand::generateInformation(){
    qDebug() << "\n\nLIST OF CONSTANTS";
    for(PConstant constant : objectConstantSet){
        qDebug() << "Object constant : " << constant->toString();
    }
    for(PConstant constant : relationConstantSet){
        qDebug() << "Relation constant : " << constant->toString();
    }
    for(PConstant constant : functionConstantSet){
        qDebug() << "Function constant : " << constant->toString();
    }

    qDebug() << "\n\nORDERED RELATIONS";

    mapTypeToRelationContainer.clear();
    mapTypeToRelationContainer.insert(GDL::BASE, baseRelations);
    mapTypeToRelationContainer.insert(GDL::INIT, initRelations);
    mapTypeToRelationContainer.insert(GDL::ROLE, roleRelations);
    mapTypeToRelationContainer.insert(GDL::NONE, standardRelations);

    for(PRelation relation:relationList){
        GDL::GDL_TYPE type = relation->getType();
        if(mapTypeToRelationContainer.contains(type)){
            mapTypeToRelationContainer[type].append(relation);
        }
        else{
            standardRelations.append(relation);
        }
    }

    for(GDL::GDL_TYPE type : mapTypeToRelationContainer.keys()){
        QVector<PRelation> container = mapTypeToRelationContainer[type];
        for(PRelation relation : container){
            qDebug() << "Relation of type " << GDL::getStringFromGDLType(type) << "\t: " << relation->toString();
        }
    }

    qDebug() << "\n\nORDERED RULES";

    mapTypeToRuleContainer.clear();
    mapTypeToRuleContainer.insert(GDL::BASE, baseRules);
    mapTypeToRuleContainer.insert(GDL::NEXT, nextRules);
    mapTypeToRuleContainer.insert(GDL::GOAL, goalRules);
    mapTypeToRuleContainer.insert(GDL::LEGAL, legalRules);
    mapTypeToRuleContainer.insert(GDL::INPUT, inputRules);
    mapTypeToRuleContainer.insert(GDL::TERMINAL, terminalRules);
    mapTypeToRuleContainer.insert(GDL::NONE, standardRules);

    for(PRule rule:ruleList){
        GDL::GDL_TYPE type = rule->getHead()->getType();
        if(mapTypeToRuleContainer.contains(type)){
            mapTypeToRuleContainer[type].append(rule);
        }
        else{
            standardRules.append(rule);
        }
    }

    for(GDL::GDL_TYPE type : mapTypeToRuleContainer.keys()){
        QVector<PRule> container = mapTypeToRuleContainer[type];
        for(PRule rule : container){
            qDebug() << "Rule of type " << GDL::getStringFromGDLType(type) << "\t: " << rule->toString();
        }
    }
}













/**
 * @brief Herbrand::processKifLine
 * @param line
 */

void Herbrand::processKifLine(QString line){
    if(line.contains(ruleRegExp)){
        ruleList.append(processRule(line));
    }
    else{
        relationList.append(processRelation(line));
    }
}



PRule Herbrand::processRule(QString line){
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

PSentence Herbrand::processSentence(QString line){
    qDebug() << "Sentence " << line;

    PSentence answer;
    QStringList splitLine = split(line);
    if(splitLine[0] == QString("distinct")){
        qDebug() << "Sentence is DISTINCT sentence";

        Q_ASSERT(splitLine.size() == 3);
        PTerm term1 = processTerm(splitLine[1]);
        PTerm term2 = processTerm(splitLine[2]);
        PDistinctSentence distinctSentence = PDistinctSentence(new GDL_DistinctSentence(term1, term2));
        answer = qSharedPointerCast<GDL_Sentence>(distinctSentence);
    }
    else if(splitLine[0] == QString("not")){
        qDebug() << "Sentence is NOT sentence";
        Q_ASSERT(splitLine.size() == 2);
        PSentence subSentence = processRelation(splitLine[1]);
        PNotSentence notSentence = PNotSentence(new GDL_NotSentence(subSentence));
        answer = qSharedPointerCast<GDL_Sentence>(notSentence);
    }
    else{
        qDebug() << "Sentence is relational sentence";
        answer = qSharedPointerCast<GDL_Sentence>(processRelation(line));
    }

    return answer;
}

PRelation Herbrand::processRelation(QString line, GDL::GDL_TYPE type){
    qDebug() << "Relational sentence " << line;

    PRelation answer;
    QStringList splitLine = split(line);

    qDebug() << "Relation constant is : " << splitLine[0];
    PConstant head = PConstant(new GDL_Constant(splitLine[0]));
    QString relationConstant = head->toString();
    if(!constantMap.contains(relationConstant)){
        constantMap.insert(relationConstant, head);
        relationConstantSet.insert(head);
    }
    head = constantMap[relationConstant];
    qDebug() << "Relation constant adress is : " << head.data();

    QVector<PTerm> body;
    GDL::GDL_TYPE subtype = GDL::getGDLTypeFromString(splitLine[0]);
    qDebug() << "Subtype is : " << GDL::getStringFromGDLType(subtype);

    if(splitLine[0] == QString("base")
            || splitLine[0] == QString("init")
            || splitLine[0] == QString("true")){
        Q_ASSERT(splitLine.size() == 2);
        PRelation relation = processRelation(splitLine[1], subtype);
        // Do a little something here
        //PRelation t= qSharedPointerCast<GDL_RelationalSentence>(relation);
        return relation;
    }
    else if(splitLine[0] == QString("next")){
        Q_ASSERT(splitLine.size() == 2);
        PRelation relation = processRelation(splitLine[1], subtype);

        return relation;
    }
    else if(splitLine[0] == QString("input")
            || splitLine[0] == QString("legal")
            || splitLine[0] == QString("does")) {
        Q_ASSERT(splitLine.size() == 3);
        body.append(processTerm(splitLine[1]));
        body.append(processTerm(splitLine[2]));
    }
    else {
        for(int i = 1; i<splitLine.size(); ++i){
            body.append(processTerm(splitLine[i]));
        }
    }

    if(type == GDL::NONE){

        answer = PRelation(new GDL_RelationalSentence(head, body, subtype));

    }
    else{
        if(type == GDL::NEXT){
            QString nextHeadName("next_HAX_");
            nextHeadName = nextHeadName + head->toString();
            PConstant nextHead = PConstant(new GDL_Constant(nextHeadName));

            QString relationConstant = nextHead->toString();
            if(!constantMap.contains(relationConstant)){
                constantMap.insert(relationConstant, nextHead);
                relationConstantSet.insert(nextHead);
            }
            nextHead = constantMap[relationConstant];

            answer = PRelation(new GDL_NextSentence(nextHead, head, body, type));
        }
        else{
            answer = PRelation(new GDL_RelationalSentence(head, body, type));
        }
    }

    return answer;
}

PTerm Herbrand::processTerm(QString line){
    qDebug() << "Term " << line;
    QStringList splitLine = split(line);

    if(splitLine.size() == 1){
        if(splitLine[0][0] == QChar('?')){
            qDebug() << "Variable " << splitLine[0];
            return PTerm(new GDL_Variable(splitLine[0]));
        }
        else{
            qDebug() << "Constant " << splitLine[0];
            PConstant constant = PConstant(new GDL_Constant(splitLine[0]));
            QString objectConstant = constant->toString();
            if(!constantMap.contains(objectConstant)){
                constantMap.insert(objectConstant, constant);
                objectConstantSet.insert(constant);
                constant = constantMap[objectConstant];
            }
            return qSharedPointerCast<GDL_Term>(constant);
        }
    }
    else{
        qDebug() << "WE HAVE A FUNCTIONAL TERM";
        return processFunction(line);
    }
}

PFunction Herbrand::processFunction(QString line){
    qDebug() << "Function " << line;

    PFunction answer;
    QStringList splitLine = split(line);

    PConstant function = PConstant(new GDL_Constant(splitLine[0]));
    QString functionConstant = function->toString();
    if(!constantMap.contains(functionConstant)){
        constantMap.insert(functionConstant, function);
        functionConstantSet.insert(function);
    }
    function = constantMap[functionConstant];

    QVector<PTerm> body;
    for(int i = 1; i<splitLine.size(); ++i){
        PTerm term = processTerm(splitLine[i]);
        body.append(term);
    }

    answer = PFunction(new GDL_FunctionalTerm(function, body));
    return answer;
}

/**
 * @brief Herbrand::split
 * @param line
 * @return
 */


QStringList Herbrand::split(QString line){
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



/**
  *
  */


Stratum::Stratum(PConstant n):
    node(n){
    strata = 0;
}

void Stratum::addDependency(PStratum s){
    dependency.insert(s);
}

void Stratum::addDependencyNegative(PStratum s){
    dependencyNegative.insert(s);
}

PConstant Stratum::getNode(){
    return node;
}

int Stratum::getStrata(){
    return strata;
}

QString Stratum::toString(){
    QString answer = node->toString();
    answer = answer + "\thas stratum : " + QString::number(strata) + "\tDependency :";
    for(PStratum s : dependency){
        answer = answer + s->getNode()->toString() + '\t';
    }
    for(PStratum s : dependencyNegative){
        answer = answer + "not (" + s->getNode()->toString() + ")\t";
    }
    return answer;
}

bool Stratum::updateStrata(){
    bool update = false;

    for(PStratum s : dependency){
        if(strata < s->getStrata()){
            strata = s->getStrata();
            update = true;
        }
    }

    for(PStratum s : dependencyNegative){
        if(strata <= s->getStrata()){
            strata = s->getStrata() + 1;
            update = true;
        }
    }

    return update;
}

bool Stratum::updateStrataStrongly(){
    bool update = false;

    for(PStratum s : dependency){
        if(strata <= s->getStrata()){
            strata = s->getStrata() + 1;
            update = true;
        }
    }

    for(PStratum s : dependencyNegative){
        if(strata <= s->getStrata()){
            strata = s->getStrata() + 1;
            update = true;
        }
    }

    return update;
}



