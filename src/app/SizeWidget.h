#pragma once

#include <QWidget>

namespace Ui {
class SizeWidget;
}

class SizeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SizeWidget(QWidget *parent = nullptr);
    ~SizeWidget();

    double tileSize() const;
    double quiltHeight() const;
    double quiltWidth() const;

signals:
    void tileSizeChanged(double sizeIn);
    void quiltHeightChanged(double heightIn);
    void quiltWidthChanged(double widthIn);

private:
    void onTileSizeTextChanged(QString text);
    void onQuiltHeightTextChangd(QString text);
    void onQuiltWidthTextChanged(QString text);

    Ui::SizeWidget* ui;
};
