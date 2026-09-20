#pragma once

#include <string>
#include <QGraphicsPixmapItem>
#include <QPointF>

class QGraphicsSceneMouseEvent;

class Item : public QGraphicsPixmapItem
{
public:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    class EventListener
    {
    public:
        virtual ~EventListener() = default;

        virtual void itemDragEvent(
            Item* item,
            Direction direction) = 0;
    };

    static int count;

    Item(
        EventListener* listener,
        const std::string& path,
        int row,
        int column,
        QGraphicsItem* parent
    );

    std::string path() const;

    int row() const;
    int column() const;

    void setRow(int row);
    void setColumn(int column);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    EventListener* _listener = nullptr;

    std::string _path;
    int _row;
    int _column;

    QPointF _pressPos;
};

