#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    friend void LengthAnalizer();
    friend void SetLabelText();

private slots:

    void on_b0_clicked();

    void on_b1_clicked();

    void on_b2_clicked();

    void on_b3_clicked();

    void on_b4_clicked();

    void on_b5_clicked();

    void on_b6_clicked();

    void on_b7_clicked();

    void on_b8_clicked();

    void on_b9_clicked();

    void on_b_back_clicked();

    void on_b_C_clicked();

    void on_b_1_div_x_clicked();

    void on_b_sqr_clicked();

    void on_b_plus_clicked();

    void on_b_eq_clicked();

    void on_b_mines_clicked();

    void on_b_power_clicked();

    void on_b_div_clicked();

    void on_b_sqrt_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
