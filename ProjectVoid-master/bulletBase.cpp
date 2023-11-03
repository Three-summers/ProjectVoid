
#include "bulletBase.h"

QTimer *BulletBase::m_timer_static = nullptr;

BulletBase::BulletBase(QPointF pos_, qreal angle_, qreal speed_, qreal damage_, int penetration_, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, m_scene(scene), m_speed(speed_), m_damage(damage_), m_penetration(penetration_)
{
    // 设置子弹初始位置和角度
    setPos(pos_);
    setRotation(angle_);

    // 计时器绑定
    connect(m_timer_static, &QTimer::timeout, this, &BulletBase::enemyHitCheck);
    connect(m_timer_static, &QTimer::timeout, this, &BulletBase::move);

    m_scene->addItem(this);

    hurt_count = 0;

}



void BulletBase::enemyHitCheck()
{
    // 碰撞检测，包含与当前图形项发生碰撞的其他图形项。列表中的每个元素都是指向 QGraphicsItem 的指针
    QList<QGraphicsItem*> coItems = this->collidingItems();
    for (QGraphicsItem* item : coItems) {
        // 动态转换，它用于将指向基类的指针或引用转换为指向派生类的指针或引用
        EnemyBase* enemy = dynamic_cast<EnemyBase*>(item);
        // 如果转换成功则代表碰撞项就为EnemyBase类
        if (enemy) {
            bool flag = false;
            // 检查伤害过的列表中有没有这一个怪物，如果没有则设置true，否则为false直接返回
            for (auto p : hurt_enemy_list) {
                if (p == enemy) flag = true;
            }
            if (flag) return;
            // 造成伤害
            enemy->hurt(m_damage);
            // 添加进列表
            hurt_enemy_list.append(enemy);
            hurt_count++;
            // 判断hurt_count是否超过穿透次数，如是则移除该项
            if (hurt_count > m_penetration){
                m_scene->removeItem(this);
                deleteLater();
            }
            return;
        }
    }
    // 超过边界直接删除
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700) deleteLater();
}

void BulletBase::move()
{
    // 获取当前朝向角度
    qreal angle = rotation();

    // 将角度转换为弧度
    qreal radian = qDegreesToRadians(angle);

    // 计算出当前移动的距离
    qreal distance = m_speed;

    // 计算出下一个位置
    qreal dy = distance * qSin(radian);
    qreal dx = distance * qCos(radian);

    // 移动到下一个位置
    moveBy(dx, dy);
}

