
#ifndef PLAYER_H
#define PLAYER_H


#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QSoundEffect>
#include <QUrl>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QGraphicsView *view, QObject *parent = nullptr);

    void addVelocity(int dx, int dy);  //添加速率
    void setVelocityX(int dx);  //设置x的速率大小
    void setVelocityY(int dy);  //设置y的速率大小
    void updatePos();
    void regen();  //重新生成

    QPointF posUpdate();

    void hurt();
    void resetInvincible();  //无敌时间

    // 数据接口
    int getHealth();
    void setHealth(int hp);
    double getPickupRange();
    int getExp();
    void setExp(int xp);

    qreal getSpeed();
    void setSpeed(qreal sp);

    void pickupExp(int xp);
    void load(); // 加载贴图

    qreal getDodge() const;
    void setDodge(qreal newDodge);  //设置闪避

    int getMax_hp() const;
    void setMax_hp(int newMax_hp);

    void setIs_regen(bool newIs_regen);

    qreal getInvincible_time() const;
    void setInvincible_time(qreal newInvincible_time);  //设置无敌

    qreal getSpeed_boost() const;
    void setSpeed_boost(qreal newSpeed_boost);

    bool getIs_still() const;

    bool getU_inthewind() const;
    void setU_inthewind(bool newU_inthewind);

    void inTheWind();

    bool getIs_inthewind() const;

signals:
    void playerHurt();
    void playerDeath();
    void playerRegen();

private:
    QVector2D m_velocity;
    int max_hp;
    int m_health;
    const int speed;
    int exp;
    qreal pickup_range;  //拾取经验速度
    qreal speed_boost;
    qreal dodge;  //躲闪
    bool is_regen = false;
    int regen_count = 0;


    bool is_invincible;
    QTimer *m_invincibleTimer;
    qreal invincible_time;

    bool u_inthewind = false;
    bool is_inthewind = false;
    int inthewind_count = 0;

    QGraphicsTextItem *m_healthBar;
    QGraphicsView *m_view;

    QMovie *mv_idle;  //停顿
    QMovie *mv_run;

    QRectF mapbounds;
    QRectF pilebounds1;
    QRectF pilebounds2;
    QRectF pilebounds3;
    QRectF pilebounds4;
    QRectF pilebounds5;

    QSoundEffect *sfx_hurt;  //特技伤害


};

#endif // PLAYER_H
