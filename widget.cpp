#include "widget.h"
#include "ui_widget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    textEdit = new QTextEdit(this);
    loadKifButton = new QPushButton("Load Kif", this);
    bla = new QLabel("Bla", this);

    leftMenuGroupBox = new QGroupBox("Left Menu", this);
    topMenuGroupBox = new QGroupBox("Top menu", this);
    textEditGroupBox = new QGroupBox("Text edit", this);

    QVBoxLayout *leftMenuLayout = new QVBoxLayout();
    leftMenuLayout->addWidget(loadKifButton);
    leftMenuGroupBox->setLayout(leftMenuLayout);

    QHBoxLayout *topMenuLayout = new QHBoxLayout();
    topMenuLayout->addWidget(bla);
    topMenuGroupBox->setLayout(topMenuLayout);

    QGridLayout *textEditLayout = new QGridLayout();
    textEditLayout->addWidget(textEdit,0,0,1,1);
    textEditGroupBox->setLayout(textEditLayout);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(leftMenuGroupBox,1,0,2,1);
    layout->addWidget(topMenuGroupBox,0,0,1,3);
    layout->addWidget(textEditGroupBox,1,1,2,2);
    this->setLayout(layout);

    setWindowTitle("Dynamic Semantic Net");
}

Widget::~Widget()
{
    delete ui;
}
