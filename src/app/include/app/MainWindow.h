#pragma once

#include <QMainWindow>

namespace Ui{
class MainWindow;
}

class QuiltCanvas;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow* ui_;
    QuiltCanvas* canvas_;
};
