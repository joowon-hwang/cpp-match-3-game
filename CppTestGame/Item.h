#pragma once
#include <string>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Item : public QGraphicsPixmapItem
{
public:
	enum class Direction {
		Up,
		Down,
		Left,
		Right

	};

	Item(const std::string& path, int row, int column, QGraphicsItem* parent);
	std::string path() const;
	int row() const;
	int column() const;

	void setRow(int row);
	void setColumn(int column);

	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:

	std::string _path;
	int _row;
	int _column;

	QPointF _pressPos;

}; 