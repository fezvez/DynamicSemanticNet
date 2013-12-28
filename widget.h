#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTextEdit *textEdit;
    QPushButton *loadKifButton;
    QLabel *bla;

    QGroupBox *leftMenuGroupBox;
    QGroupBox *topMenuGroupBox;
    QGroupBox *textEditGroupBox;
};

#endif // WIDGET_H
