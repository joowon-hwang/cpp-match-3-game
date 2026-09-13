#include "Item.h"
#include <cmath>

Item::Item(const std::string& path, int row, int column, QGraphicsItem* parent): 
QGraphicsPixmapItem(parent),
_path(path),
_row(row),
_column(column)
{
	setPixmap(QPixmap(QString::fromStdString(_path)));
}

std::string Item::path() const
{
	return std::string();
}

int Item::row() const
{
	return _row;
}

int Item::column() const
{
	return _column;
}

void Item::setRow(int row)
{
	_row = row;
}

void Item::setColumn(int column)
{
	_column = column;
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Press";
	qDebug() << event->scenePos();
	_pressPos = event->scenePos();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "Release";

	QPointF releasePos = event->scenePos();
	qDebug() << releasePos;

	qreal dx = releasePos.x() - _pressPos.x();
	qreal dy = releasePos.y() - _pressPos.y();

	const qreal threshold = 30.0;

	if (std::abs(dx) >= std::abs(dy)) {
		if ((dx) >= threshold) {
			qDebug() << "moved right";
		}
		else if ((dx) <= -threshold) {
			qDebug() << "moved left";
		}
	}
	else {
		if ((dy) >= threshold) {
			qDebug() << "moved down";
		}
		else if ((dy) <= -threshold) {
			qDebug() << "moved up";
		}
	}
}
