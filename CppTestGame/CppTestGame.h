#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CppTestGame.h"

class CppTestGame : public QMainWindow
{
    Q_OBJECT

public:
    CppTestGame(QWidget *parent = nullptr);
    ~CppTestGame();

private:
    Ui::CppTestGameClass ui;
};

