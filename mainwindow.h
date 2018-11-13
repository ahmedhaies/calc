#ifndef EPSILON
    #define EPSILON 2.2204460492503131e-16
#endif
#ifndef PI
    #define PI 3.14159265
#endif
#ifndef MAINWINDOW_H
    #define MAINWINDOW_H
    #include <QMainWindow>
    namespace Ui {
    class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool AreSame(double a, double b);

    private:
        Ui::MainWindow *ui;
    /*
    protected:
        void keyPressEvent(QKeyEvent * e);
    */
    private slots:
        void DigitPressed();
        void on_pushButtonDot_released();
        void UnaryOpPressed();
        void on_pushButtonClear_released();
        void on_pushButtonEqual_released();
        void OprationPressed();
        void on_pushButtonDel_released();
    };

#endif // MAINWINDOW_H
