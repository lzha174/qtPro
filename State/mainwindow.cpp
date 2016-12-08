#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfinalstate.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QState *s1 = new QState();
    QState *s11 = new QState(s1);
    QState *s12 = new QState(s1);
    QState *s13 = new QState(s1);
    s11->assignProperty(ui->stateLabel, "text", "In state s11");
    s12->assignProperty(ui->stateLabel, "text", "In state s12");
    s13->assignProperty(ui->stateLabel, "text", "In state s13");

    s11->addTransition(ui->changeState, SIGNAL(clicked()), s12);
    s12->addTransition(ui->changeState, SIGNAL(clicked()), s13);
    s13->addTransition(ui->changeState, SIGNAL(clicked()), s11);

    s1->setInitialState(s13);
    machine.addState(s1);
    QFinalState *s2 = new QFinalState();
    s1->addTransition(ui->quickB, SIGNAL(clicked()), s2);
    machine.addState(s2);
    machine.setInitialState(s1);

    QObject::connect(&machine, SIGNAL(finished()), this, SLOT(GetHit()));

    machine.start();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GetHit()
{
    QApplication::quit();
}
