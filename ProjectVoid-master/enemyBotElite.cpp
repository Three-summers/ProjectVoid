#include "enemyBotElite.h"

EnemyBotElite::EnemyBotElite(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{pl, scene, parent}
{
    // 加载动画
    m_movie = new QMovie(":/images/images/enemy/en_bot_elite.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(50);
    m_movie->start();

    setScale(4.5);
    setTransformOriginPoint(8, 10);

    // 基本数据
    health = 75;
    xp = 3;
    speed = 2;
}

void EnemyBotElite::load()
{
    QImage img(m_movie->currentImage());
    if (is_hurt) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x) {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) {
                    line[x * 4] = 255;
                    line[x * 4 + 1] = 255;
                    line[x * 4 + 2] = 255;
                }
            }
        }
    }
    qreal angle = QLineF(pos(), m_player->pos()).angle();
    if ( (angle > 90 && angle < 270) || (angle < -90 && angle > -270)){
        img.mirrored(true, false);
    }
    setPixmap(QPixmap::fromImage(img));
}
