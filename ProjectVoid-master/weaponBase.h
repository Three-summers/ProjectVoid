
#ifndef WEAPONBASE_H
#define WEAPONBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>
#include <QtMath>

#include "player.h"

class WeaponBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit WeaponBase(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

    void updatePos();
    void rotateToCursor(const QPointF& target); // 旋转武器到光标处
    void setFireRateBoost(qreal fr);  // 开火速度提升
    void setDamageBoost(qreal dmg);  // 伤害提升
    void setSpeedBoost(qreal sp);  // 速度提升

    virtual void fire() = 0;
    void load();
    void fire_on();
    void fire_off();

    // 数据接口
    qreal getFireRateBoost();
    qreal getDamageBoost();
    qreal getSpeedBoost();

    static QTimer *m_timer;

    int getRoundBoost() const;
    void setRoundBoost(int newRound_boost);

    qreal getSpread() const;
    void setSpread(qreal newSpread); // 设置传播/弹射

    int getPenetration() const;
    void setPenetration(int newPenetration); //设置穿透

    bool getBarrage() const;
    void setBarrage(bool newBarrage); // 设置多发

signals:

protected:
    QGraphicsScene *m_scene;
    Player *m_player;
    qreal fire_rate_boost;
    qreal damage_boost;
    qreal speed_boost;
    int round_boost;
    qreal spread;
    int penetration;
    bool barrage;

    QPixmap pix;
    int fire_count;
    bool is_fire;

    // 音效
    QSoundEffect *sfx_fire;
};

#endif // WEAPONBASE_H
