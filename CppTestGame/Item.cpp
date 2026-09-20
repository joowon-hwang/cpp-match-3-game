#include "Item.h"

#include <cmath>
#include <QGraphicsSceneMouseEvent>

Item::Item(
    EventListener* listener,
    const std::string& path,
    int row,
    int column,
    QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , _listener(listener)
    , _path(path)
    , _row(row)
    , _column(column)
{
    setPixmap(QPixmap(QString::fromStdString(_path)));
}

std::string Item::path() const
{
    return _path;
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
    _pressPos = event->scenePos();
    event->accept();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF releasePos = event->scenePos();

    qreal dx = releasePos.x() - _pressPos.x();
    qreal dy = releasePos.y() - _pressPos.y();

    constexpr qreal threshold = 30.0;

    Direction direction;

    if (std::abs(dx) > std::abs(dy))
    {
        if (dx > threshold)
        {
            direction = Direction::Right;
        }
        else if (dx < -threshold)
        {
            direction = Direction::Left;
        }
        else
        {
            event->accept();
            return;
        }
    }
    else
    {
        if (dy > threshold)
        {
            direction = Direction::Down;
        }
        else if (dy < -threshold)
        {
            direction = Direction::Up;
        }
        else
        {
            event->accept();
            return;
        }
    }

    if (_listener != nullptr)
    {
        _listener->itemDragEvent(this, direction);
    }

    event->accept();
}