#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include "Slider.h"
#include <QCheckBox>
#include <QPushButton>

int string_to_int(std::string s)
{
    std::stringstream ss(s);

    int x = 0;
    ss >> x;

    return x;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector<std::string>result;
    std::stringstream ss(str);
    std::string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::string interval_toString(interval intrvl)
{
    return "start: " + intrvl.start + " ; end: " + intrvl.end + " ; precipitation: " + intrvl.precipitation + " ; description: " + intrvl.description;
}

//void read_intervals(std::vector<interval> i)
//{
//    std::ifstream fin("weather.txt");
//    std::string line;
//    interval intrvl;

//    while(fin >> line)
//    {
//        std::vector<std::string> tokens = tokenize(line, ';');

//        intrvl.start = tokens[0];
//        intrvl.end = tokens[1];
//        intrvl.precipitation = tokens[2];
//        intrvl.description = tokens[3];

//        QMessageBox* msg = new QMessageBox();
//        msg->setText(interval_toString(intrvl).c_str());
//        msg->show();

//        i.push_back(intrvl);
//    }
//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::ifstream fin("weather.txt");
    std::string line;
    interval intrvl;

    while(fin >> line)
    {
        std::vector<std::string> tokens = tokenize(line, ';');

        intrvl.start = tokens[0];
        intrvl.end = tokens[1];
        intrvl.precipitation = tokens[2];
        intrvl.description = tokens[3];

//        QMessageBox* msg = new QMessageBox();
//        msg->setText(interval_toString(intrvl).c_str());
//        msg->show();

        i.push_back(intrvl);
    }

//    for(auto intrvl : i)
//    {
//        QMessageBox* msg = new QMessageBox();
//        msg->setText(interval_toString(intrvl).c_str());
//        msg->show();
//    }

    for(auto intrvl : i)
    {
        mylistwidget->addItem(interval_toString(intrvl).c_str());
    }

    QGridLayout* gLay = new QGridLayout();

    slider->setValue(100);

    overcast->setText("overcast");
    foggy->setText("foggy");
    sunny->setText("sunny");
    rain->setText("rain");
    thunderstorm->setText("thunderstorm");

    overcast->setCheckState(Qt::CheckState::Checked);
    foggy->setCheckState(Qt::CheckState::Checked);
    sunny->setCheckState(Qt::CheckState::Checked);
    rain->setCheckState(Qt::CheckState::Checked);
    thunderstorm->setCheckState(Qt::CheckState::Checked);

    checkboxes.push_back(overcast);
    checkboxes.push_back(foggy);
    checkboxes.push_back(sunny);
    checkboxes.push_back(rain);
    checkboxes.push_back(thunderstorm);

    QPushButton* btnReset = new QPushButton();
    btnReset->setText("Reset all filters");

    gLay->addWidget(mylistwidget, 0, 0, 3, 3);
    gLay->addWidget(slider, 3, 0, 2, 2);
    gLay->addWidget(overcast, 5, 0, 1, 1);
    gLay->addWidget(foggy, 6, 0, 1, 1);
    gLay->addWidget(sunny, 7, 0, 1, 1);
    gLay->addWidget(rain, 8, 0, 1, 1);
    gLay->addWidget(thunderstorm, 9, 0, 1, 1);
    gLay->addWidget(btnReset, 10, 0, 1, 1);

    QObject::connect(slider, SIGNAL(sliderReleased()), this, SLOT(repopulate()));

    QObject::connect(overcast, SIGNAL(stateChanged(int)), this, SLOT(filter_checkbox()));
    QObject::connect(foggy, SIGNAL(stateChanged(int)), this, SLOT(filter_checkbox()));
    QObject::connect(sunny, SIGNAL(stateChanged(int)), this, SLOT(filter_checkbox()));
    QObject::connect(rain, SIGNAL(stateChanged(int)), this, SLOT(filter_checkbox()));
    QObject::connect(thunderstorm, SIGNAL(stateChanged(int)), this, SLOT(filter_checkbox()));
    QObject::connect(btnReset, SIGNAL(clicked()), this, SLOT(reset_filters()));

    QWidget* w = new QWidget();
    w->setLayout(gLay);
    this->setCentralWidget(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::repopulate()
{
    this->mylistwidget->clear();

    for(auto intrvl : i)
    {
        if(string_to_int(intrvl.precipitation) < this->slider->value())
            mylistwidget->addItem(interval_toString(intrvl).c_str());
    }
}

void MainWindow::filter_checkbox()
{
    this->mylistwidget->clear();
    for(auto checkbox : checkboxes)
    {
        if(checkbox->checkState() == Qt::Checked && checkbox->text() == "overcast")
            for(auto intrvl : i)
                {
                    if(string_to_int(intrvl.precipitation) < this->slider->value() && intrvl.description == "overcast")
                        mylistwidget->addItem(interval_toString(intrvl).c_str());
                }
        else if(checkbox->checkState() == Qt::Checked && checkbox->text() == "foggy")
            for(auto intrvl : i)
                {
                    if(string_to_int(intrvl.precipitation) < this->slider->value() && intrvl.description == "foggy")
                        mylistwidget->addItem(interval_toString(intrvl).c_str());
                }
        else if(checkbox->checkState() == Qt::Checked && checkbox->text() == "sunny")
            for(auto intrvl : i)
                {
                    if(string_to_int(intrvl.precipitation) < this->slider->value() && intrvl.description == "sunny")
                        mylistwidget->addItem(interval_toString(intrvl).c_str());
                }
        else if(checkbox->checkState() == Qt::Checked && checkbox->text() == "rain")
            for(auto intrvl : i)
                {
                    if(string_to_int(intrvl.precipitation) < this->slider->value() && intrvl.description == "rain")
                        mylistwidget->addItem(interval_toString(intrvl).c_str());
                }
        else if(checkbox->checkState() == Qt::Checked && checkbox->text() == "thunderstorm")
            for(auto intrvl : i)
                {
                    if(string_to_int(intrvl.precipitation) < this->slider->value() && intrvl.description == "thunderstorm")
                        mylistwidget->addItem(interval_toString(intrvl).c_str());
                }
    }
}

void MainWindow::reset_filters()
{
    slider->setValue(100);
    overcast->setCheckState(Qt::CheckState::Checked);
    foggy->setCheckState(Qt::CheckState::Checked);
    sunny->setCheckState(Qt::CheckState::Checked);
    rain->setCheckState(Qt::CheckState::Checked);
    thunderstorm->setCheckState(Qt::CheckState::Checked);
}
