#include "Board.h"
#include "Consts.h"

Board::Board(QGraphicsScene* scene)
    : _scene(scene)
    , _gen(_device())
{
    _scene->addItem(&_root);

    _root.setPos(160, 60);

    _items.resize(
        Consts::BOARD_LENGTH,
        std::vector<Item*>(Consts::BOARD_LENGTH, nullptr)
    );

    initBoard();

    processMatches();
}

Board::~Board() = default;

void Board::initBoard()
{
    for (int row = 0; row < Consts::BOARD_LENGTH; row++)
    {
        for (int column = 0; column < Consts::BOARD_LENGTH; column++)
        {
            addItem(row, column);
        }
    }
}

void Board::addItem(int row, int column)
{
    std::uniform_int_distribution<int> dis(0, 11);

    int typeIndex = dis(_gen);
    std::string pathStr = Consts::paths[typeIndex];

    Item* item = new Item(
        this,
        pathStr,
        row,
        column,
        &_root
    );

    QPixmap pixmap = item->pixmap();

    pixmap = pixmap.scaled(
        Consts::TILE_SIZE,
        Consts::TILE_SIZE,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    item->setPixmap(pixmap);
    item->setData(0, typeIndex);
    item->setPos(calculatePos(row, column));

    _items[row][column] = item;
}




void Board::removeItem(int row, int column)
{
    if (row < 0 ||
        row >= Consts::BOARD_LENGTH ||
        column < 0 ||
        column >= Consts::BOARD_LENGTH)
    {
        return;
    }

    if (_items[row][column] == nullptr)
    {
        return;
    }

    delete _items[row][column];
    _items[row][column] = nullptr;
}

QPointF Board::calculatePos(int row, int column)
{
    qreal x = column * Consts::TILE_SIZE;
    qreal y = row * Consts::TILE_SIZE;

    return QPointF(x, y);
}

std::set<std::pair<int, int>> Board::findMatches()
{
    std::set<std::pair<int, int>> matchedIndices;

    for (int r = 0; r < Consts::BOARD_LENGTH; ++r)
    {
        for (int c = 0; c < Consts::BOARD_LENGTH - 2; ++c)
        {
            if (_items[r][c] == nullptr ||
                _items[r][c + 1] == nullptr ||
                _items[r][c + 2] == nullptr)
            {
                continue;
            }

            int type = _items[r][c]->data(0).toInt();

            if (type == _items[r][c + 1]->data(0).toInt() &&
                type == _items[r][c + 2]->data(0).toInt())
            {
                matchedIndices.insert({ r, c });
                matchedIndices.insert({ r, c + 1 });
                matchedIndices.insert({ r, c + 2 });
            }
        }
    }

    for (int c = 0; c < Consts::BOARD_LENGTH; ++c)
    {
        for (int r = 0; r < Consts::BOARD_LENGTH - 2; ++r)
        {
            if (_items[r][c] == nullptr ||
                _items[r + 1][c] == nullptr ||
                _items[r + 2][c] == nullptr)
            {
                continue;
            }

            int type = _items[r][c]->data(0).toInt();

            if (type == _items[r + 1][c]->data(0).toInt() &&
                type == _items[r + 2][c]->data(0).toInt())
            {
                matchedIndices.insert({ r, c });
                matchedIndices.insert({ r + 1, c });
                matchedIndices.insert({ r + 2, c });
            }
        }
    }

    return matchedIndices;
}

void Board::processMatches()
{
    std::set<std::pair<int, int>> _matchedIndices = findMatches();
    for (auto i : _matchedIndices) {
        removeItem(i.first, i.second);
    }

    for (int i = 0; i < Consts::BOARD_LENGTH; i++) {
        int empty_row = Consts::BOARD_LENGTH - 1;
        for (int j = Consts::BOARD_LENGTH - 1;j >= 0;j--) {
            if (_items[j][i] != nullptr) {
                if (j != empty_row) {
                    _items[empty_row][i] = _items[j][i];
                    _items[j][i] = nullptr;
                    _items[empty_row][i]->setRow(empty_row);
                    _items[empty_row][i]->setPos(calculatePos(empty_row,i));
                }
                empty_row--;
            }
        }
    }
    if (findMatches().empty()) {
        
    }
    else {
        processMatches();
    }

}

void Board::swapItems(int r1, int c1, int r2, int c2)
{
    if (r1 < 0 ||
        r1 >= Consts::BOARD_LENGTH ||
        c1 < 0 ||
        c1 >= Consts::BOARD_LENGTH)
    {
        return;
    }

    if (r2 < 0 ||
        r2 >= Consts::BOARD_LENGTH ||
        c2 < 0 ||
        c2 >= Consts::BOARD_LENGTH)
    {
        return;
    }

    if (_items[r1][c1] == nullptr ||
        _items[r2][c2] == nullptr)
    {
        return;
    }



    std::swap(_items[r1][c1], _items[r2][c2]);

    _items[r1][c1]->setRow(r1);
    _items[r1][c1]->setColumn(c1);

    _items[r2][c2]->setRow(r2);
    _items[r2][c2]->setColumn(c2);

    _items[r1][c1]->setPos(calculatePos(r1, c1));
    _items[r2][c2]->setPos(calculatePos(r2, c2));

    processMatches();
}

void Board::itemDragEvent(Item* item, Item::Direction direction)
{
    int r1 = item->row();
    int c1 = item->column();

    int r2 = r1;
    int c2 = c1;

    switch (direction)
    {
    case Item::Direction::Up:
        r2--;
        break;

    case Item::Direction::Down:
        r2++;
        break;

    case Item::Direction::Left:
        c2--;
        break;

    case Item::Direction::Right:
        c2++;
        break;
    }

    swapItems(r1, c1, r2, c2);
}