#include "widget.h"
#include "ui_widget.h"

#include <QGridLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    textEdit = new QTextEdit(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(textEdit);

    setWindowTitle("Dynamic Semantic Net");
}

Widget::~Widget()
{
    delete ui;
}
