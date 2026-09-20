#pragma once

#include <vector>
#include <random>
#include <set>
#include <utility>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPointF>

#include "Item.h"

class QGraphicsScene;

class Board : public Item::EventListener
{
private:
    QGraphicsScene* _scene;
    std::vector<std::vector<Item*>> _items;

    std::random_device _device;
    std::mt19937 _gen;

    QGraphicsRectItem _root;

public:
    Board(QGraphicsScene* scene);
    ~Board();

    void initBoard();

    void addItem(int row, int column);
    void removeItem(int row, int column);

    QPointF calculatePos(int row, int column);

    std::set<std::pair<int, int>> findMatches();

    void processMatches();

    void swapItems(int r1, int c1, int r2, int c2);

    void itemDragEvent(
        Item* item,
        Item::Direction direction) override;
};