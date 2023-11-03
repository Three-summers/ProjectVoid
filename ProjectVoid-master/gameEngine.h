
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QFontDatabase>
#include <QApplication>
#include <QSoundEffect>
#include <QTime>
#include <QThread>

#include "heartLabel.h"
#include "player.h"
#include "weaponBase.h"
#include "archiveMod.h"




class GameEngine : public QGraphicsView
{
    Q_OBJECT
public:
    GameEngine(const QString &weapon, const QString &load_archive = "none");
    void gamePause();
    void gameContinue();


signals:
    void Endgame();
    void Restart();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Player *m_player;
    QThread * m_archiveThread;

    WeaponBase *m_weapon;
    QString weapon_type;

    QList<HeartLabel*> heart_list;  //心脏对象列表

    int enemy_gen_count; // 敌人生成辅助计数器
    int bullet_gen_count; // 子弹生成辅助计数器

    void updateBackground();  //更新背景
    void setHealthBar();  //设置健康条

    // 敌人生成器
    void enemyGenerator();

    QGraphicsScene *m_scene;

    QTimer *main_timer;
    QTimer *phase_timer;

    QGraphicsPixmapItem *m_background;

    QPushButton *pb_pause;

    void phaseUp(); // 游戏阶段
    int phase;  //区分游戏阶段
    int phase_count;
    qreal enemy_generate_rate;
    qreal melee_enemy_rate;
    qreal ranged_enemy_rate;
    qreal charge_enemy_rate;
    qreal explosive_enemy_rate;
    qreal elite_enemy_rate;

    // 倒计时
    int countdown_count;
    QGraphicsTextItem *countdown_text;
    QTime countdown_time;
    void updateCountdown();

    // 角色升级
    int level;
    void levelCheck();
    QList<int> upgradeGenerator();
    void levelUp();

    // 经验条
    QGraphicsRectItem *exp_bar_bg;
    QGraphicsRectItem *exp_bar;
    QGraphicsTextItem *level_text;
    void setExpBar();

    // 金币
    int data_count;
    int data_amount;
    int data_collector;
    QGraphicsTextItem *data_text;
    void dataIncrement();
    QSettings *settings;

    // 存档
    QSettings *archive[3];
    void loadArchive(int sign);
    void saveArchive(int sign);
    void showArchive();
    void hideArchive();
    ArchiveMod *archive_mod[3];

    // 音效和bgm
    QSoundEffect *bgm_player;
    QSoundEffect *sfx_respawn;  //特技声音

    QRectF pilebounds1 = QRectF(878, 721, 172, 308);
    QRectF pilebounds2 = QRectF(884, 1513, 172, 308);
    QRectF pilebounds3 = QRectF(2320, 1097, 172, 308);
    QRectF pilebounds4 = QRectF(3780, 731, 172, 308);
    QRectF pilebounds5 = QRectF(3764, 1509, 172, 308);

    // 游戏结束
    void endgame_lose();
    void endgame_win();
    QGraphicsScene *end_scene;
};

#endif // GAMEENGINE_H
