
#include "weaponBase.h"


QTimer *m_timer = nullptr;

WeaponBase::WeaponBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, m_scene(scene), m_player(pl)
{
    fire_rate_boost = 1;
    damage_boost = 1;
    speed_boost = 1;
    fire_count = 0;
    is_fire = 0;
    round_boost = 0;
    penetration = 0;
    barrage = false;

    sfx_fire = new QSoundEffect(this); // 开火音效
    sfx_fire->setVolume(0.5);
    sfx_fire->setSource(QUrl::fromLocalFile(":/sfx/sfx/single_shot.wav"));

}



void WeaponBase::updatePos()
{
    setPos(m_player->pos());
}

void WeaponBase::rotateToCursor(const QPointF &target)
{
    // 将武器的变换原点坐标转换为场景坐标，并将结果存储在weaponPos中
    // 武器项自己的局部坐标系与场景坐标系的方向是相对的
    QPointF weaponPos = mapToScene(transformOriginPoint());
    // 将鼠标与武器的位置之差用两个变量存储
    double dx = target.x() - weaponPos.x();
    double dy = target.y() - weaponPos.y();
    // qAtan2(dx, dy)计算从武器位置指向鼠标光标位置的角度（弧度），然后使用 qRadiansToDegrees 将角度转换为度数
    // 最后，将结果加上90并取负数，以使武器旋转的方向与鼠标指向一致。最终通过调用 setRotation 来设置武器的旋转角度
    setRotation(-qRadiansToDegrees(qAtan2(dx, dy))+90);
    // qAtan2函数的坐标系是标准的笛卡尔坐标系，反转再加90度为转换的场景坐标系
}

void WeaponBase::setFireRateBoost(qreal fr)
{
    fire_rate_boost = fr;
}

void WeaponBase::setDamageBoost(qreal dmg)
{
    damage_boost = dmg;
}

void WeaponBase::setSpeedBoost(qreal sp)
{
    speed_boost = sp;
}

void WeaponBase::load()
{
    QImage img(pix.toImage());
    if ( (rotation() > 90 && rotation() < 270) || (rotation() < -90 && rotation() > -270)){
        img.mirrored(false, true); // 垂直镜像
    }
    setPixmap(QPixmap::fromImage(img));
}

void WeaponBase::fire_on()
{
    is_fire = true;
}

void WeaponBase::fire_off()
{
    is_fire = false;
}

qreal WeaponBase::getFireRateBoost()
{
    return fire_rate_boost;
}

qreal WeaponBase::getDamageBoost()
{
    return damage_boost;
}

qreal WeaponBase::getSpeedBoost()
{
    return speed_boost;
}

int WeaponBase::getRoundBoost() const
{
    return round_boost;
}

void WeaponBase::setRoundBoost(int newRound_boost)
{
    round_boost = newRound_boost;
}

qreal WeaponBase::getSpread() const
{
    return spread;
}

void WeaponBase::setSpread(qreal newSpread)
{
    spread = newSpread;
}

int WeaponBase::getPenetration() const
{
    return penetration;
}

void WeaponBase::setPenetration(int newPenetration)
{
    penetration = newPenetration;
}

bool WeaponBase::getBarrage() const
{
    return barrage;
}

void WeaponBase::setBarrage(bool newBarrage)
{
    barrage = newBarrage;
}



