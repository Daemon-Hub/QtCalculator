#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define LABEL_MAX_LENGTH    16
#define LABEL_FONT_SIZE     34

#include <iomanip>
#include <sstream>
#include <cmath>

std::string
    font_family("Segoe UI"),
    default_label("0"),
    background_label("0"),
    s_temp
;

std::list<short> decrement_history;

char operation;

int font_size,
    background_label_length,
    foreground_label_length
;

bool
    label_length_is_max = false,
    zero_division = false,
    example_is_solved = false,
    L4  = false,
    L7  = false,
    L10 = false,
    L13 = false,
    L16 = false
;

// ==================================================================== //

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    font_size = ui->label_default->font().pointSize();
    background_label_length = 1;
    foreground_label_length = 1;
}


MainWindow::~MainWindow()
{
    delete ui;
}

// ==================================================================== //

void MainWindow::Perform() {
    switch (operation) {
    case '+':
        default_label = std::to_string(std::stod(background_label) + std::stod(default_label));
        break;
    case '-':
        default_label = std::to_string(std::stod(background_label) - std::stod(default_label));
        break;
    case '*':
        default_label = std::to_string(std::stod(background_label) * std::stod(default_label));
        break;
    case '/':
        default_label = std::to_string(std::stod(background_label) / std::stod(default_label));
        break;
    default:
        break;
    }
    background_label.clear();
    operation = NULL;
}


bool MainWindow::Find(std::string& str, const char& c) {
    for(int i = 0; i < str.length(); i++)
        if (c == str[i]) return true;
    return false;
}


void MainWindow::LengthAnalizer(bool* _l)
{
    if (!(*_l))
    {
        foreground_label_length++;
        *_l = true;
    }
    else {
        foreground_label_length--;
        *_l = false;
    }
}


void MainWindow::LengthAnalizer()
{
    short length = default_label.length() - background_label_length;
    if (length == 0) return;

    background_label_length += length;
    foreground_label_length += length;

    if ((background_label_length >= LABEL_MAX_LENGTH) && (example_is_solved))
    {
        ui->label_default->setFont(
            QFont(
                font_family.c_str(),
                font_size-= 3*( background_label_length-LABEL_MAX_LENGTH+
                                background_label_length-length ),
                QFont::Bold
                )
            );
    }
    else if (background_label_length >= 11)
    {
        short decrement = background_label_length > 13 ?
                        (background_label_length > 14 ? 1 : 2 ): 3; // Perfect

        if (length > 0) {
            ui->label_default->setFont(
                QFont(
                    font_family.c_str(),
                    font_size-=decrement,
                    QFont::Bold
                )
            );
            decrement_history.push_back(decrement);
        }
        else {
            short increment = decrement_history.back();
                              decrement_history.pop_back();
            ui->label_default->setFont(
                QFont(
                    font_family.c_str(),
                    font_size+=increment,
                    QFont::Bold
                )
            );
        }
    }
    else if (font_size != LABEL_FONT_SIZE)
    {
        ui->label_default->setFont(
            QFont(
                font_family.c_str(),
                font_size=LABEL_FONT_SIZE,
                QFont::Bold
                )
            );
    }
}


const char* MainWindow::FormatLabel()
{
    if ((background_label_length < 4) || (example_is_solved)) {
        LengthAnalizer(&L4);
        return default_label.c_str();
    }
    char c_temp[background_label_length + 1];
    default_label.copy(c_temp, sizeof(c_temp));
    c_temp[background_label_length] = '\0';

    s_temp = std::string(c_temp);
    s_temp.insert(background_label_length - 3, " ");
    LengthAnalizer(&L4);

    if (background_label_length >= 7)
    {
        s_temp.insert(background_label_length - 6, " ");
        LengthAnalizer(&L7);
    } else {
        LengthAnalizer(&L7);
    }

    if (background_label_length >= 10)
    {
        s_temp.insert(background_label_length - 9, " ");
        LengthAnalizer(&L10);
    } else {
        LengthAnalizer(&L10);
    }

    if (background_label_length >= 13)
    {
        s_temp.insert(background_label_length - 12, " ");
        LengthAnalizer(&L13);
    } else {
        LengthAnalizer(&L13);
    }

    if (background_label_length >= 16)
    {
        s_temp.insert(background_label_length - 15, " ");
        LengthAnalizer(&L16);
    } else {
        LengthAnalizer(&L16);
    }

    return s_temp.c_str();

}


void MainWindow::Strip()
{
    for (int i = default_label.length()-1; i > 0; i--) {
        if (default_label[i] == '.')
        {
            default_label.pop_back();
            break;
        }
        else if (default_label[i] == '0')
            default_label.pop_back();
        else break;
    }
}


void MainWindow::SetLabelText()
{
    if (Find(default_label, '.')) Strip();

    if ((background_label_length >= LABEL_MAX_LENGTH) && (!example_is_solved)) {
        label_length_is_max = true;
        return;
    }

    LengthAnalizer();

    ui->label_default->setText(QString(FormatLabel()));
    ui->label_mini->setText(QString((background_label + operation).c_str()));
    s_temp.clear();
}


void MainWindow::LabelChange(const char& num)
{
    if (
        ((default_label.length() == 1) && DefaultLabelIsZero())
        || zero_division || example_is_solved
    ) {
        if (zero_division) zero_division = false;
        if (example_is_solved) example_is_solved = false;
        default_label = num;
    }
    else default_label += num;
    SetLabelText();
}


void MainWindow::Backspace()
{
    if (default_label.length() == 1) {
        if (DefaultLabelIsZero()) return;
        else default_label = "0";
    }
    else default_label.pop_back();
    LengthAnalizer();
    SetLabelText();
}


bool MainWindow::DefaultLabelIsZero()
{
    return std::stod(default_label) == 0.0;
}

// ==================================================================== //

void MainWindow::on_b0_clicked()
{
    LabelChange('0');
}


void MainWindow::on_b1_clicked()
{
    LabelChange('1');
}


void MainWindow::on_b2_clicked()
{
    LabelChange('2');
}


void MainWindow::on_b3_clicked()
{
    LabelChange('3');
}


void MainWindow::on_b4_clicked()
{
    LabelChange('4');
}


void MainWindow::on_b5_clicked()
{
    LabelChange('5');
}


void MainWindow::on_b6_clicked()
{
    LabelChange('6');
}


void MainWindow::on_b7_clicked()
{
    LabelChange('7');
}


void MainWindow::on_b8_clicked()
{
    LabelChange('8');
}


void MainWindow::on_b9_clicked()
{
    LabelChange('9');
}


void MainWindow::on_b_back_clicked()
{
    Backspace();
}


void MainWindow::on_b_C_clicked()
{
    default_label = "0";
    LengthAnalizer();
    SetLabelText();
}


void MainWindow::on_b_1_div_x_clicked()
{
    example_is_solved = true;
    double temp { (double)(1.0f/std::stod(default_label)) };
    std::stringstream ss;
    if (temp < double(0.000000000000001)) {
        ss << std::setprecision(8) << std::scientific << temp;
    } else {
        ss << std::setprecision(14) << temp;
    }
    if (DefaultLabelIsZero()) {
        default_label = "Деление на ноль невозможно";//0,000000000000001
        zero_division = true;
    }
    else default_label = ss.str();
    LengthAnalizer();
    SetLabelText();
}


void MainWindow::on_b_sqr_clicked()
{
    double number { std::stod(default_label) } ;
    if (number == 0) return;
    default_label = std::to_string(number * number);
    example_is_solved = true;
    SetLabelText();
}


void MainWindow::on_b_eq_clicked()
{
    if (operation) {
        Perform();
        SetLabelText();
    }
}


void MainWindow::ApplyOperation(const char op) {
    if (operation) {
        Perform();
        SetLabelText();
    }

    operation = op;
    double number { std::stod(default_label) };
    background_label = default_label;
    default_label.clear();
}


void MainWindow::on_b_plus_clicked()
{
    ApplyOperation('+');
}


void MainWindow::on_b_mines_clicked()
{
    ApplyOperation('-');
}


void MainWindow::on_b_power_clicked()
{
    ApplyOperation('*');
}


void MainWindow::on_b_div_clicked()
{
    ApplyOperation('/');
}

