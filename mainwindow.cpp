#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFrame>
#include <QProgressBar>
#include <QLabel>


#include <QCefSetting.h>
#include <QCefView.h>
#include <QCefContext.h>
#include <QDir>
#include <QShortcut>

#include <QObject>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::cout << "Hello World 1!" << std::endl;
    this->createCefView();
    //this->createStatusPopup();
    this->keybindings();
}

void MainWindow::keybindings() {
    QShortcut* downloadPopup = new QShortcut(QKeySequence(tr("Ctrl+Shift+O", "Pop download utility")), this);
    QShortcut* goBackward = new QShortcut(QKeySequence(tr("Shift+h", "Go backward")), this);
    QShortcut* goForward = new QShortcut(QKeySequence(tr("Shift+l", "Go backward")), this);


    QObject::connect(downloadPopup, &QShortcut::activated, this, &MainWindow::createStatusPopup);
    QObject::connect(goBackward, &QShortcut::activated, this->cefViewWidget, &CefViewWidget::browserGoBack);
    QObject::connect(goForward, &QShortcut::activated, this->cefViewWidget, &CefViewWidget::browserGoForward);
   // QObject::connect(goForward, &QShortcut::activated, this->cefViewWidget, &CefViewWidget::brow22);

}

void MainWindow::createStatusPopup() {
    QWidget *window = new QWidget;
    window->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QProgressBar* progressBar = new QProgressBar(window);
    QLabel* label1 = new QLabel();

    label1->setIndent(3); //indente le texte
    label1->setText("texte1");

    progressBar->setRange(0, 100);
    progressBar->setValue(40);

    QVBoxLayout* test = new QVBoxLayout(window);
    test->layout()->addWidget(label1);
    test->layout()->addWidget(progressBar);

    ui->centralWidget->layout()->addWidget(window);
}

void MainWindow::createCefView()
{
    QCefSetting setting;
    setting.setWindowlessFrameRate(60);
    setting.setBackgroundColor(QColor::fromRgba(qRgba(0, 0, 0, 0)));

    cefViewWidget = new CefViewWidget("https://www.google.fr/", &setting, this);
    ui->cefViewContainer->layout()->addWidget(cefViewWidget);
}

/*
 * new window
    QMainWindow* w = new QMainWindow(nullptr);
    w->setAttribute(Qt::WA_DeleteOnClose);

    QCefSetting settings;
    QCefView* view = new QCefView("https://cefview.github.io/QCefView/", &settings, w);

    w->setCentralWidget(view);
    w->resize(1024, 768);
    w->show();
*/

MainWindow::~MainWindow()
{
    delete ui;
}
