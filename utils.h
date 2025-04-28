#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <list>

#define LABEL_MAX_LENGTH    16
#define LABEL_FONT_SIZE     34
#define elif else if


inline std::string
    font_family("Segoe UI"),
    default_label("0"),
    background_label("0"),
    foreground_label(""),
    s_temp
;

inline std::list<short> decrement_history;

inline char operation;

inline int
    font_size,
    background_label_length,
    foreground_label_length
;

inline bool
    label_length_is_max = false,
    example_is_solved = false,
    zero_division = false,
    special_char_is_previous = false,
    L4 = false, L7 = false,
    L10 = false, L13 = false,
    L16 = false
;

namespace Utils {

inline Ui::MainWindow *ui;

void ApplySpecificOperation(const char op);
void ApplyOperation(const char op);
void LabelChange(const char &num);
void SetupUI(Ui::MainWindow *ui);
void LengthAnalizer(bool *_l);
void SetMiniLabelText();
void LengthAnalizer();
void SetLabelText();
void SetFGLabel();
void Backspace();
void Perform();
void Strip();
void Clear();

bool DefaultLabelIsZero();

int Find(std::string &str, const char &c);

const char *FormatLabel();

}

#endif // UTILS_H
