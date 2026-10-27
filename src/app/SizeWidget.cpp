#include "SizeWidget.h"
#include "ui_SizeWidget.h"

#include <QDoubleValidator>

constexpr auto DECIMALS{4};
constexpr auto MIN_SIZE{0.0}, TILE_SIZE_MAX{12.0}, QUILT_WIDTH_MAX{1200.0}, QUILT_HEIGHT_MAX{1200.0};
constexpr auto INITIAL_SIZE{2.0}, INITIAL_WIDTH{8.5}, INITIAL_HEIGHT{11.0};

SizeWidget::SizeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SizeWidget)
{
    ui->setupUi(this);

    ui->tileSizeEdit->setValidator(new QDoubleValidator(MIN_SIZE, TILE_SIZE_MAX, DECIMALS, ui->tileSizeEdit));
    ui->tileSizeEdit->setText(QString::number(INITIAL_SIZE));
    connect(ui->tileSizeEdit, &QLineEdit::textChanged, this, &SizeWidget::onTileSizeTextChanged);

    ui->quiltHeightEdit->setValidator(new QDoubleValidator(MIN_SIZE, QUILT_HEIGHT_MAX, DECIMALS, ui->quiltHeightEdit));
    ui->quiltHeightEdit->setText(QString::number(INITIAL_HEIGHT));
    connect(ui->quiltHeightEdit, &QLineEdit::textChanged, this, &SizeWidget::onQuiltHeightTextChangd);

    ui->quiltWidthEdit->setValidator(new QDoubleValidator(MIN_SIZE, QUILT_WIDTH_MAX, DECIMALS, ui->quiltWidthEdit));
    ui->quiltWidthEdit->setText(QString::number(INITIAL_WIDTH));
    connect(ui->quiltWidthEdit, &QLineEdit::textChanged, this, &SizeWidget::onQuiltWidthTextChanged);
}

SizeWidget::~SizeWidget()
{
    delete ui;
}

double SizeWidget::tileSize() const
{
    return ui->tileSizeEdit->text().toDouble();
}

double SizeWidget::quiltHeight() const
{
    return ui->quiltHeightEdit->text().toDouble();
}

double SizeWidget::quiltWidth() const
{
    return ui->quiltWidthEdit->text().toDouble();
}

void SizeWidget::onTileSizeTextChanged(QString text)
{
    emit tileSizeChanged(text.toDouble());
}

void SizeWidget::onQuiltHeightTextChangd(QString text)
{
    emit quiltHeightChanged(text.toDouble());
}

void SizeWidget::onQuiltWidthTextChanged(QString text)
{
    emit quiltWidthChanged(text.toDouble());
}
