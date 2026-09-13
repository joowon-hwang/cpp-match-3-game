#pragma once
#include <random>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>

#include "Consts.h"

#include <vector>

class Board
{
private:
	QGraphicsScene* _scene;
	std::vector<std::vector<QGraphicsPixmapItem*>> _items;

	std::random_device _device;

	std::mt19937 _gen;

	QGraphicsRectItem _root;

public:
	Board(QGraphicsScene*scene);
	~Board();

	int Mid_Board_width();

	int Mid_Board_height();

	void initBoard();

	void addItem(int row, int column);
	void removeItem(int row, int column);

	QPointF calculatePos(int row, int column);

	
};