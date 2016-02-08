#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sfmlwidget.h"
#include <qcolordialog.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    // file filters
    const QString JSON_FILTER = "Json files(*.json)";
    const QString ALL_FILTER = "All files(*)";

    // file extensions
    const QString JSON_EXT = ".json";

private slots:
    void on_actionExit_triggered();

    void setRange(int value);
    void setRotation(int value);
    void setAmount(int amount);
    void setSpeed(int speed);
    void setLife(int lifetime);

    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    void on_lineEditRange_editingFinished();
    void on_lineEditRotation_editingFinished();
    void on_toolButtonColor_clicked();
    void on_lineEditColor_editingFinished();
    void on_lineEditAmount_editingFinished();
    void on_lineEditSpeed_editingFinished();
    void on_lineEditLife_editingFinished();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void on_actionClear_triggered();

private:
    virtual void showEvent(QShowEvent* e);
    virtual void paintEvent(QPaintEvent* e);

};

#endif // MAINWINDOW_H
