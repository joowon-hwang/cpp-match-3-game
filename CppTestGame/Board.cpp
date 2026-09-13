#include "Board.h"
#include "Item.h"

Board::Board(QGraphicsScene* scene): _scene(scene), _gen(_device())

{

	_scene->sceneRect().width();
	_scene->sceneRect().height();
	
	_scene->addItem(&_root);

	_root.setPos(Mid_Board_width(), Mid_Board_height());
	_root.setScale(1.0);
	_root.setRotation(0);

	_items.resize(Consts::BOARD_LENGTH, std::vector<QGraphicsPixmapItem*>(Consts::BOARD_LENGTH, nullptr));
	initBoard();
}

Board::~Board()
{
	auto children = _root.childItems();
	for (auto* child : children) {
		delete child;
	}
}

int Board::Mid_Board_width() {
	return ((*_scene).sceneRect().width() - (Consts::BOARD_LENGTH * Consts::TILE_SIZE)) / 2;
}

int Board::Mid_Board_height() {
	return ((*_scene).sceneRect().height() - (Consts::BOARD_LENGTH * Consts::TILE_SIZE)) / 2;
}


void Board::initBoard()
{
	for (int row = 0; row < Consts::BOARD_LENGTH; row++) {
		for (int column = 0; column < Consts::BOARD_LENGTH; column++) {
			addItem(row, column);
		}
	}
}

void Board::addItem(int row, int column)
{
	std::uniform_int_distribution<int> dis(0, 11);
	int typeIndex = dis(_gen);
	std::string pathStr = Consts::paths[typeIndex];

	// 1. 세로 만든 Item 클래스로 동적 생성 (부모를 _root로 지정)
	Item* item = new Item(pathStr, row, column, &_root);

	// 2. 생성자에서 로드된 이미지를 가져와 격자 크기(TILE_SIZE)에 맞게 조절 후 재설정
	QPixmap pixmap = item->pixmap();
	pixmap = pixmap.scaled(Consts::TILE_SIZE, Consts::TILE_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	item->setPixmap(pixmap);

	// 3. 매칭 판별을 위한 데이터 테그 저장
	item->setData(0, typeIndex);

	// 4. 화면 배치 및 2차원 격자 배열에 저장
	item->setPos(calculatePos(row, column));
	_items[row][column] = item;
}

void Board::removeItem(int row, int column)
{
}

QPointF Board::calculatePos(int row, int column)
{
	qreal x1 = row * Consts::TILE_SIZE;
	qreal y1 = column * Consts::TILE_SIZE;
	return QPointF(x1,y1);
}
