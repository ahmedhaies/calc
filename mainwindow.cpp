#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QKeyEvent>
//#include <QDebug>
static double FristNum;
static bool TheUserTypeingSecondNumber = false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton0, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton1, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton2, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton3, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton4, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton5, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton6, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton7, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton8, SIGNAL(released()), this, SLOT(DigitPressed()));
    connect(ui->pushButton9, SIGNAL(released()), this, SLOT(DigitPressed()));

    connect(ui->pushButtonPlusMinus, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonPercent, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonPower2, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButton10PowerX, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonSqrt, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonLog, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonExp, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonTan, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonCos, SIGNAL(released()), this, SLOT(UnaryOpPressed()));
    connect(ui->pushButtonSin, SIGNAL(released()), this, SLOT(UnaryOpPressed()));

    connect(ui->pushButtonAdd, SIGNAL(released()), this, SLOT(OprationPressed()));
    connect(ui->pushButtonMinus, SIGNAL(released()), this, SLOT(OprationPressed()));
    connect(ui->pushButtonMul, SIGNAL(released()), this, SLOT(OprationPressed()));
    connect(ui->pushButtonDivision, SIGNAL(released()), this, SLOT(OprationPressed()));
    connect(ui->pushButtonMod, SIGNAL(released()), this, SLOT(OprationPressed()));
    connect(ui->pushButtonPowerY, SIGNAL(released()), this, SLOT(OprationPressed()));

    ui->pushButtonAdd->setCheckable(true);
    ui->pushButtonMinus->setCheckable(true);
    ui->pushButtonMul->setCheckable(true);
    ui->pushButtonDivision->setCheckable(true);
    ui->pushButtonMod->setCheckable(true);
    ui->pushButtonPowerY->setCheckable(true);


    ui->label->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::AreSame(double a, double b)
{
    return std::fabs(a - b) < EPSILON;
}
/*
void MainWindow::keyPressEvent(QKeyEvent * e)
{
    //qDebug() << "a";
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent* key = static_cast<QKeyEvent*>(e);
        switch (key->key())
        {
        case Qt::Key_0:
            connect(ui->pushButton0, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_1:
            connect(ui->pushButton1, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_2:
            connect(ui->pushButton2, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_3:
            connect(ui->pushButton3, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_4:
            connect(ui->pushButton4, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_5:
            connect(ui->pushButton5, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_6:
            connect(ui->pushButton6, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_7:
            connect(ui->pushButton7, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_8:
            connect(ui->pushButton8, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        case Qt::Key_9:
            connect(ui->pushButton9, SIGNAL(released()), this, SLOT(DigitPressed()));
        break;
        }
    }
}
*/
void MainWindow::DigitPressed()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    double LabelNumber;
    QString NewLableString;
    if
    (
        (
            ui->pushButtonAdd->isChecked() ||
            ui->pushButtonMul->isChecked() ||
            ui->pushButtonDivision->isChecked() ||
            ui->pushButtonMinus->isChecked() ||
            ui->pushButtonMod->isChecked() ||
            ui->pushButtonPowerY->isChecked()
        )
        &&
        (
            !TheUserTypeingSecondNumber
        )

    )
    {
        LabelNumber = button->text().toDouble();
        TheUserTypeingSecondNumber = true;
    }
    else
    {
        LabelNumber = (ui->label->text() + button->text()).toDouble();
    }
    NewLableString = QString::number(LabelNumber, 'g', 15);
    ui->label->setText(NewLableString);
}

void MainWindow::on_pushButtonDot_released()
{
    if (!ui->label->text().contains("."))
        ui->label->setText(ui->label->text() + ".");
}

void MainWindow::UnaryOpPressed()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    double LabelNumber = ui->label->text().toDouble();
    QString NewLableString, FristNumberString = QString::number(LabelNumber, 'g', 15);
    QByteArray FristNumberArr = FristNumberString.toUtf8();
    char * FristNumberC_str = FristNumberArr.data(), Label2Text[512];

    if (button->text() == "+/-")
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "(+/-)%s", FristNumberC_str);
        ui->label_2->setText(Label2Text);

        if (!AreSame(LabelNumber, static_cast<double>(0)))
        {
            LabelNumber = LabelNumber * -1;
            NewLableString = QString::number(LabelNumber, 'g', 15);
            ui->label->setText(NewLableString);
        }
        else
        {
            ui->label->setText("Cannot get (+/-) by zero");
        }
    }
    else if (button->text() == "%")
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s%%", FristNumberC_str);
        ui->label_2->setText(Label2Text);

        if (!AreSame(LabelNumber, static_cast<double>(0)))
        {
            LabelNumber = LabelNumber * 0.01;
            NewLableString = QString::number(LabelNumber, 'g', 15);
            ui->label->setText(NewLableString);
        }
        else
        {
            ui->label->setText("Cannot get % by zero");
        }

    }
    else if (button->text() == "x^2")
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s^2", FristNumberC_str);
        ui->label_2->setText(Label2Text);

        LabelNumber = pow(LabelNumber, 2);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "10^x")
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "10^%s", FristNumberC_str);
        ui->label_2->setText(Label2Text);

        LabelNumber = pow(10, LabelNumber);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "√")
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "√%s", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = sqrt(LabelNumber);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "log")
    {
        sprintf_s(Label2Text, sizeof(Label2Text), "Log(%s)", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::log(LabelNumber);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "Exp")
    {
        sprintf_s(Label2Text, sizeof(Label2Text), "Exp(%s)", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::exp(LabelNumber);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "tan")
    {
        sprintf_s(Label2Text, sizeof(Label2Text), "tan(%s)", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::tan(LabelNumber * PI / 180.0);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "cos")
    {
        sprintf_s(Label2Text, sizeof(Label2Text), "cos(%s)", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::cos(LabelNumber * PI / 180.0);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
    else if (button->text() == "sin")
    {
        sprintf_s(Label2Text, sizeof(Label2Text), "sin(%s)", FristNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::sin(LabelNumber * PI / 180.0);
        NewLableString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLableString);
    }
}

void MainWindow::on_pushButtonClear_released()
{
    ui->pushButtonAdd->setChecked(false);
    ui->pushButtonMul->setChecked(false);
    ui->pushButtonDivision->setChecked(false);
    ui->pushButtonMinus->setChecked(false);
    ui->pushButtonMod->setChecked(false);
    ui->pushButtonPowerY->setChecked(false);

    TheUserTypeingSecondNumber = false;

    ui->label->setText("0");
    ui->label_2->setText("");
}

void MainWindow::on_pushButtonEqual_released()
{
    double LabelNumber, SecondNumber = ui->label->text().toDouble();
    QString NewLabelString, FristNumberString = QString::number(FristNum, 'g', 15), SecondNumberString = QString::number(SecondNumber, 'g', 15);
    QByteArray FristNumberArr = FristNumberString.toUtf8(), SecondNumberArr = SecondNumberString.toUtf8();
    char * FristNumberC_str = FristNumberArr.data(), * SecondNumberC_str = SecondNumberArr.data(), Label2Text[512];
    if (ui->pushButtonAdd->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s + %s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = FristNum + SecondNumber;
        NewLabelString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLabelString);
        ui->pushButtonAdd->setChecked(false);
    }
    else if (ui->pushButtonMul->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s ☓ %s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = FristNum * SecondNumber;
        NewLabelString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLabelString);
        ui->pushButtonMul->setChecked(false);

    }
    else if (ui->pushButtonDivision->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s / %s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        if (!AreSame(SecondNumber, static_cast<double>(0)))
        {
            LabelNumber = FristNum / SecondNumber;
            NewLabelString = QString::number(LabelNumber, 'g', 15);
            ui->label->setText(NewLabelString);
        }
        else
        {
            ui->label->setText("Cannot Divided by zero");
        }
        ui->pushButtonDivision->setChecked(false);
    }
    else if (ui->pushButtonMinus->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s - %s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = FristNum - SecondNumber;
        NewLabelString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLabelString);
        ui->pushButtonMinus->setChecked(false);
    }
    else if (ui->pushButtonMod->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s Mod %s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = std::fmod(FristNum , SecondNumber);
        NewLabelString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLabelString);
        ui->pushButtonMod->setChecked(false);
    }
    else if (ui->pushButtonPowerY->isChecked())
    {
        sprintf_s(Label2Text, sizeof (Label2Text), "%s^%s =", FristNumberC_str, SecondNumberC_str);
        ui->label_2->setText(Label2Text);
        LabelNumber = pow(FristNum , SecondNumber);
        NewLabelString = QString::number(LabelNumber, 'g', 15);
        ui->label->setText(NewLabelString);
        ui->pushButtonPowerY->setChecked(false);
    }

    TheUserTypeingSecondNumber = false;

}

void MainWindow::OprationPressed()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    FristNum = ui->label->text().toDouble();
    button->setChecked(true);
    if (button->text() == "/")
    {
        ui->label_2->setText("/");
    }
    else if (button->text() == "☓")
    {
        ui->label_2->setText("☓");
    }
    else if (button->text() == "-")
    {
        ui->label_2->setText("-");
    }
    else if (button->text() == "+")
    {
        ui->label_2->setText("+");
    }
    else if (button->text() == "Mod")
    {
        ui->label_2->setText("Mod");
    }
    else if (button->text() == "x^y")
    {
        ui->label_2->setText("^");
    }
}

void MainWindow::on_pushButtonDel_released()
{
    int len = ui->label->text().length();
    ui->label->setText(ui->label->text().remove(len - 1, 1));
    if (len <= 1)
    {
         ui->label->setText("0");
    }
}

