#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Board.h"

/*
// 1. 시간 진행 객체 생성
    QTimeLine* timeLine = new QTimeLine(1200);

    timeLine->setFrameRange(0, 100);
    timeLine->setUpdateInterval(16);
    timeLine->setEasingCurve(QEasingCurve::InOutQuad);

    // 2. 위치 애니메이션 객체 생성
    QGraphicsItemAnimation* animation =
        new QGraphicsItemAnimation(timeLine);

    // 3. 이동할 아이템 지정
    animation->setItem(item);

    // 4. 시간 진행 객체 연결
    animation->setTimeLine(timeLine);

    // 5. 시작 위치와 목표 위치 지정
    animation->setPosAt(0.0, item->pos());
    animation->setPosAt(1.0, QPointF(280, 60));

    // 6. 진행 값 확인
    QObject::connect(
        timeLine,
        &QTimeLine::valueChanged,
        [item](qreal value)
        {
            qDebug() << "Progress:" << value;
            qDebug() << "Position:" << item->pos();
        }
    );

    // 7. 애니메이션 완료 확인
    QObject::connect(
        timeLine,
        &QTimeLine::finished,
        []()
        {
            qDebug() << "Animation finished!";
        }
    );

    // 8. 애니메이션 시작
    timeLine->start();
*/


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    Board board(&scene);

    QGraphicsView view(&scene);
    view.setWindowTitle("Match 3 Game");
    view.setFixedSize(800, 600);

    view.show
    ();

    return a.exec();
}

