#include "TileSelector.h"
#include "ui_TileSelector.h"

TileSelector::TileSelector(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TileSelector)
{
    ui->setupUi(this);
}

TileSelector::~TileSelector()
{
    delete ui;
}
