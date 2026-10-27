#include "include/app/MainWindow.h"
#include "ui_MainWindow.h"

#include "QuiltCanvas.h"
#include "Tiles.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui_{new Ui::MainWindow}
{
    ui_->setupUi(this);

    canvas_ = new QuiltCanvas({
            .tileScaleIn = ui_->sizeWidget->tileSize(),
            .quiltWidthIn = ui_->sizeWidget->quiltWidth(),
            .quiltHeightIn = ui_->sizeWidget->quiltHeight(),
            .parent=this
    });
    ui_->quiltView->setCanvas(canvas_);

    connect(ui_->sizeWidget, &SizeWidget::tileSizeChanged, canvas_, &QuiltCanvas::setTileScale);
    connect(ui_->sizeWidget, &SizeWidget::quiltHeightChanged, canvas_, &QuiltCanvas::setQuiltHeight);
    connect(ui_->sizeWidget, &SizeWidget::quiltWidthChanged, canvas_, &QuiltCanvas::setQuiltWidth);

    canvas_->addTile(WideRhomb(ui_->sizeWidget->tileSize()));
}

MainWindow::~MainWindow(){
    delete ui_;
}