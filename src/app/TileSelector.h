#pragma once

#include <QWidget>

namespace Ui {
class TileSelector;
}

class TileSelector : public QWidget
{
    Q_OBJECT

public:
    explicit TileSelector(QWidget *parent = nullptr);
    ~TileSelector();


signals:
    void narrowRhombClicked();
    void wideRhombClicked();


private:
    Ui::TileSelector *ui;
};
