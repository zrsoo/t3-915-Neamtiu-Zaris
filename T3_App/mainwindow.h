#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Slider.h"
#include <QListWidget>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct interval {
    std::string start;
    std::string end;
    std::string precipitation;
    std::string description;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void repopulate();
    void filter_checkbox();
    void reset_filters();

private:
    Ui::MainWindow *ui;
    FancySlider* slider = new FancySlider();

    std::vector<interval> i;
    QListWidget* mylistwidget = new QListWidget();

    QCheckBox* overcast = new QCheckBox();
    QCheckBox* foggy = new QCheckBox();
    QCheckBox* sunny = new QCheckBox();
    QCheckBox* rain = new QCheckBox();
    QCheckBox* thunderstorm = new QCheckBox();

    std::vector<QCheckBox*> checkboxes;
};
#endif // MAINWINDOW_H
