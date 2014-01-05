#include "player.h"

#include <QDebug>

Player::Player(QObject *parent):
    QObject(parent)
{
}

void Player::updateKif(const QStringList & sl){
    rawKif = QStringList(sl);

    qDebug() << "Kif processed in Player!";

    for(int i=0; i<rawKif.size(); ++i){
        qDebug() << rawKif[i];
    }
}
