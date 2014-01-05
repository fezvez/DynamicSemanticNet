#ifndef PLAYER_H
#define PLAYER_H

#include <QStringList>
#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    Player(QObject *parent);

public slots:
    void updateKif(const QStringList &sl);

private:
    QStringList rawKif;
};

#endif // PLAYER_H
