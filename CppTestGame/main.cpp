#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Board.h"

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

