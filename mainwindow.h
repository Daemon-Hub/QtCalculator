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

private slots:
    // --------------------------------------- //

    void ApplyOperation(const char op);
    void LabelChange(const char& num);
    void LengthAnalizer(bool* _l);
    void LengthAnalizer();
    void SetLabelText();
    void Backspace();
    void Perform();
    void Strip();

    bool DefaultLabelIsZero();
    bool Find(std::string& str, const char& c);

    const char* FormatLabel();

    // --------------------------------------- //

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
