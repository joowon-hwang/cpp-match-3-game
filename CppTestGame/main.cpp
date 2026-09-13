#include <random>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include "Consts.h"
#include "Board.h"
#include <vector>

#include <iostream>

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(0, 0, 800, 600);

    QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, 200, 100);
    rect->setBrush(Qt::green);
    scene.addItem(rect);

    QPixmap imagePath("C:\\Users\\juwon\\OneDrive\\Desktop\\coding\\CppTestGame\\Images\\1.png");

    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem(imagePath);

    pixmap->setPos(300, 200);
    scene.addItem(pixmap);

    QGraphicsPixmapItem* pixmap2 = new QGraphicsPixmapItem(imagePath);

    pixmap2->setPos(192, 200);
    scene.addItem(pixmap2);

    std::random_device device;

    std::mt19937 gen(device());

    std::uniform_int_distribution<int> dis(0, 11);

    QString selectedPath = QString::fromStdString(Consts::paths[dis(gen)]);
    
    QGraphicsPixmapItem* Images = new QGraphicsPixmapItem(selectedPath);
    Images->setPos(350, 300);

    scene.addItem(Images);

    Board board(&scene);

    QGraphicsView view(&scene);
    view.setWindowTitle("Test Window");
    view.setFixedSize(800, 600);
    view.show();

    int* y = new int(100);

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [&]() {
        if (*y <= 600) {
            rect->setPos(0, *y - 100);
            (*y)++;
        }
        else {
            timer->stop();
        }
        });

    timer->start(3); // runs every 3 ms




    return a.exec();
}