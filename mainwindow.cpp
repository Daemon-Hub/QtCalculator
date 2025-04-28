

#include "utils.h"

// ==================================================================== //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Utils::SetupUI(ui);
    font_size = ui->label_default->font().pointSize();
    background_label_length = 1;
    foreground_label_length = 1;
}


MainWindow::~MainWindow()
{ delete ui; }


void MainWindow::on_b0_clicked()
{
    Utils::LabelChange('0');
}


void MainWindow::on_b1_clicked()
{
    Utils::LabelChange('1');
}


void MainWindow::on_b2_clicked()
{
    Utils::LabelChange('2');
}


void MainWindow::on_b3_clicked()
{
    Utils::LabelChange('3');
}


void MainWindow::on_b4_clicked()
{
    Utils::LabelChange('4');
}


void MainWindow::on_b5_clicked()
{
    Utils::LabelChange('5');
}


void MainWindow::on_b6_clicked()
{
    Utils::LabelChange('6');
}


void MainWindow::on_b7_clicked()
{
    Utils::LabelChange('7');
}


void MainWindow::on_b8_clicked()
{
    Utils::LabelChange('8');
}


void MainWindow::on_b9_clicked()
{
    Utils::LabelChange('9');
}


void MainWindow::on_b_back_clicked()
{
    Utils::Backspace();
}


void MainWindow::on_b_C_clicked()
{
    Utils::Clear();
}


void MainWindow::on_b_1_div_x_clicked()
{
    Utils::ApplySpecificOperation('d');
}


void MainWindow::on_b_sqr_clicked()
{
    Utils::ApplySpecificOperation('^');
}


void MainWindow::on_b_sqrt_clicked()
{
    Utils::ApplySpecificOperation('s');
}


void MainWindow::on_b_eq_clicked()
{
    if (operation)
    {
        example_is_solved = true;
        Utils::Perform();
        Utils::SetMiniLabelText();
        Utils::SetLabelText();
    }
}


void MainWindow::on_b_plus_clicked()
{
    Utils::ApplyOperation('+');
}


void MainWindow::on_b_mines_clicked()
{
    Utils::ApplyOperation('-');
}


void MainWindow::on_b_power_clicked()
{
    Utils::ApplyOperation('*');
}


void MainWindow::on_b_div_clicked()
{
    Utils::ApplyOperation('/');
}



