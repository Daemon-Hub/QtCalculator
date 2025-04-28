
#include <iomanip>
#include <sstream>
#include <cmath>

#include "utils.h"


namespace Utils
{

void SetupUI(Ui::MainWindow* ui)
{ Utils::ui = ui; }


void Perform()
{
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
    case '^':
    {
        double number { std::stod(default_label) } ;
        default_label = std::to_string(number * number);
        break;
    }
    case 's':
    {
        double number { std::stod(default_label) } ;
        default_label = std::to_string(std::sqrt(number));
        break;
    }
    case 'd':
    {
        std::stringstream ss;

        double temp { (double)(1.0/std::stod(default_label)) };

        if (temp <= double(0.000000000001))
            ss << std::setprecision(10)
               << std::scientific
               << temp;
        else
            ss << std::setprecision(8)
               << std::scientific
               << temp;

        if (Utils::DefaultLabelIsZero()) {
            default_label = "Деление на ноль невозможно";
            zero_division = true;
        } else
            default_label = ss.str();

        Utils::LengthAnalizer(); // Не убирать!
        break;
    }
    default:
        break;
    }
    background_label.clear();
    operation = NULL;
}


int Find(std::string& str, const char& c)
{
    for(int i = 0; i < str.length(); i++)
        if (c == str[i])
            return i;
    return -1;
}


const char* FormatLabel()
{
    if ((background_label_length < 4) || (example_is_solved)) {
        LengthAnalizer(&L4);
        return default_label.c_str();
    }

    int BLL = background_label_length;
    int dot_index = Find(default_label, '.');
    if (dot_index > -1) {
        s_temp = default_label.substr(0, dot_index);
        BLL = s_temp.length();
    }
    else
        s_temp = std::string(default_label);

    s_temp.insert(BLL - 3, " ");
    LengthAnalizer(&L4);

    if (BLL >= 7)
    {
        s_temp.insert(BLL - 6, " ");
        LengthAnalizer(&L7);
    } else {
        LengthAnalizer(&L7);
    }

    if (BLL >= 10)
    {
        s_temp.insert(BLL - 9, " ");
        LengthAnalizer(&L10);
    } else {
        LengthAnalizer(&L10);
    }

    if (BLL >= 13)
    {
        s_temp.insert(BLL - 12, " ");
        LengthAnalizer(&L13);
    } else {
        LengthAnalizer(&L13);
    }

    if (BLL >= 16)
    {
        s_temp.insert(BLL - 15, " ");
        LengthAnalizer(&L16);
    } else {
        LengthAnalizer(&L16);
    }

    if (dot_index > -1)
        s_temp += default_label.substr(dot_index);

    return s_temp.c_str();

}


void Strip()
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
    example_is_solved = true;
}


void LengthAnalizer(bool* _l)
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


void LengthAnalizer()
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
                font_size-= int(std::log(std::exp(background_label_length-LABEL_MAX_LENGTH+
                                                   background_label_length-length))),
                -1,true
            )
        );
    }
    else if (background_label_length >= 11)
    {
        //short decrement = background_label_length > 13 ? (background_label_length > 14 ? 1 : 2 ): 3; // Perfect

        short decrement = background_label_length <= 14 ? 2 : 1 ;

        if (length > 0) {
            ui->label_default->setFont(
                QFont(
                    font_family.c_str(),
                    font_size-=decrement,
                    -1,true
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
                    -1,true
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
                -1,true
            )
        );
    }
}


std::string FGorDefault() {
    return foreground_label.length() == 0 ?
             (default_label.length() == 0 ?
              background_label : default_label)
                               : foreground_label;
}


bool LastIsTheSimpleOperator()
{
    bool result = false;
    for (const char op : {'+', '-', '/', '*'})
        if (Find(foreground_label, op) == foreground_label.length()-1) {
            result = true;
            break;
        }
    return result;
}

void SetMiniLabelText()
{
    if (LastIsTheSimpleOperator()) {
        foreground_label = default_label + ' ' + operation;
    }
    elif (operation == '+' || operation == '-' ||
        operation == '*' || operation == '/')
        foreground_label = FGorDefault() + ' ' + operation;
    elif (operation == '^')
        foreground_label = '(' + FGorDefault() + ")²";
    elif (operation == 's')
        foreground_label = "√(" + FGorDefault() + ')';
    SetFGLabel();
}


void SetLabelText()
{
    if (Find(default_label, '.') > -1 &&
        Find(default_label, 'e') == -1) Strip();

    if ((background_label_length >= LABEL_MAX_LENGTH) && (!example_is_solved)) {
        //label_length_is_max = true; // not used
        return;
    }

    LengthAnalizer();

    ui->label_default->setText(QString(FormatLabel()));
    s_temp.clear();
}


void LabelChange(const char& num)
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


void Backspace()
{
    if (default_label.length() == 1) {
        if (DefaultLabelIsZero()) return;
        else default_label = "0";
    }
    else default_label.pop_back();
    LengthAnalizer();
    SetLabelText();
}


bool DefaultLabelIsZero()
{
    return std::stod(default_label) == 0.0;
}


void ApplyOperation(const char op)
{
    if (operation) {
        example_is_solved = true;
        Perform();
        SetLabelText();
    }
    operation = op;
    background_label = default_label;
    SetMiniLabelText();
    default_label.clear();
}


void ApplySpecificOperation(const char op)
{
    special_char_is_previous = true;
    example_is_solved = true;
    operation = op;
    SetMiniLabelText();
    Perform();
    SetLabelText();
}


void Clear()
{
    special_char_is_previous = false;
    example_is_solved = false;
    foreground_label.clear();
    default_label.clear();
    default_label = "0";
    operation = NULL;
    s_temp.clear();
    SetFGLabel();
    LengthAnalizer();
    SetLabelText();
}


void SetFGLabel() {
    ui->label_mini->setText(QString(foreground_label.c_str()));
}

}
