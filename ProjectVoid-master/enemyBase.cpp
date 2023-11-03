
#include "enemyBase.h"
#include "exp.h"

#include <QDebug> // debug

QRectF EnemyBase::pilebounds1 = QRectF(878, 721, 172, 308);
QRectF EnemyBase::pilebounds2 = QRectF(884, 1513, 172, 308);
QRectF EnemyBase::pilebounds3 = QRectF(2320, 1097, 172, 308);
QRectF EnemyBase::pilebounds4 = QRectF(3780, 731, 172, 308);
QRectF EnemyBase::pilebounds5 = QRectF(3764, 1509, 172, 308);

QTimer* EnemyBase::m_timer_static = nullptr;
QSoundEffect *EnemyBase::sfx_enemy_hurt = nullptr;

EnemyBase::EnemyBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, m_player(pl), m_scene(scene), is_hurt(false)
{
    // 移动和碰撞计时器，其中m_timer_static在gameEngine类中进行初始化
    // 敌人移动到角色的位置是有限定时间的
    connect(m_timer_static, &QTimer::timeout, this, &EnemyBase::hitBoxCheck);
    connect(m_timer_static, &QTimer::timeout, this, &EnemyBase::mobMove);
    connect(m_timer_static, &QTimer::timeout, this, &EnemyBase::load);
    connect(&hurt_timer, &QTimer::timeout, this, &EnemyBase::hurt_reload);
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);

    // 受击音效
}

void EnemyBase::mobMove()
{
    if (!m_player) {
        return;
    }
    // 计算出 Enemy 到 Player 的方向
    QLineF line(pos(), m_player->pos());

    // 计算出移动的距离和方向，运用单位圆来计算dx，dy，角度A对应的坐标就是(cos A,sin A)
    qreal dx = cos(line.angle() * M_PI / 180) * speed;
    qreal dy = -sin(line.angle() * M_PI / 180) * speed;
    QPointF newPos = pos() + QPointF(dx, dy);
    // 排除边界及障碍物
    if (pilebounds1.contains(newPos)
        || pilebounds2.contains(newPos)
        || pilebounds3.contains(newPos)
        || pilebounds4.contains(newPos)
        || pilebounds5.contains(newPos)) {
        // 判断怪物与角色之间的方向，如果dx>0，则代表怪物在角色的左边，dx<=0则反之，新的位置为当前位置加上一个偏移量speed
        if (dx > 0) { newPos = pos() + QPointF(speed, 0); }
        else { newPos = pos() + QPointF(-speed, 0); }
    }
    if (pilebounds1.contains(newPos)
        || pilebounds2.contains(newPos)
        || pilebounds3.contains(newPos)
        || pilebounds4.contains(newPos)
        || pilebounds5.contains(newPos)) {
        // 与上同理但是判断角色与怪物在y轴上的相对方向，当dy>0则代表角色在怪物下面，dy<=0则反之
        if (dy > 0) { newPos = pos() + QPointF(0, speed); }
        else { newPos = pos() + QPointF(0, -speed); }
    }
    if (pilebounds1.contains(newPos)
        || pilebounds2.contains(newPos)
        || pilebounds3.contains(newPos)
        || pilebounds4.contains(newPos)
        || pilebounds5.contains(newPos))
        newPos = pos() + QPointF(0, 0);

    // 移动 Enemy
    setPos(newPos);
}

void EnemyBase::hitBoxCheck()
{
    // 检测当前项与另一项是否发生碰撞，默认模式为相交碰撞检测模式，隐形调用当前项与m_player项之间的碰撞检测
    if (collidesWithItem(m_player))
        m_player->hurt();
}


void EnemyBase::hurt(qreal damage_)
{
    health -= damage_;
    sfx_enemy_hurt->play();
    is_hurt = true;
    hurt_timer.start(100);
    if (health <= 0) {
        emit enemyDeath();
    }
}

void EnemyBase::death()
{
    Exp *exp = new Exp(m_player, pos(), m_scene, 1);
    exp->setParentItem(this->parentItem());
    m_scene->addItem(exp);
    m_scene->removeItem(this);
    deleteLater();
}

void EnemyBase::hurt_reload()
{
    is_hurt = false;
    hurt_timer.stop();
}
