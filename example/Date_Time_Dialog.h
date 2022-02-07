#ifndef DATE_TIME_DIALOG_H
#define DATE_TIME_DIALOG_H

/**************************************************************************
**
** Copyright (C) 2022 Ken Crossen, example expanded into useful application
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Redistributions in source code or binary form may not be sold.
**
**************************************************************************/

#include <QtCore>
#include <QString>
#include <QDialog>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QDateTime>
#include <QCheckBox>

#include "Calculator_UI.h"
#include "Keyboard.h"

class APCalcClass;

class DateTimeDialog : public QDialog {
    Q_OBJECT

public:
    DateTimeDialog ( QWidget *parent );

private:
    APCalcClass* APCalc_Widget;

    LineEdit *Begin_DateTime_LineEdit;
    LineEdit *End_DateTime_LineEdit;

    QLabel *Begin_Date_Label;
    QLabel *End_Date_Label;

    LineEdit *Year_Span_LineEdit;
    LineEdit *Month_Span_LineEdit;
    LineEdit *Day_Span_LineEdit;

    LineEdit *WeekDay_Span_LineEdit;
    LineEdit *Weekend_Span_LineEdit;

    LineEdit *Hour_Span_LineEdit;
    LineEdit *Minute_Span_LineEdit;
    LineEdit *Second_Span_LineEdit;

    LineEdit *Span_As_Weeks_LineEdit;
    LineEdit *Span_As_Days_LineEdit;
    LineEdit *Span_As_Hours_LineEdit;

    LineEdit *Span_As_Minutes_LineEdit;
    LineEdit *Span_As_Seconds_LineEdit;
    LineEdit *Span_As_Milliseconds_LineEdit;

    bool User_Changed_Span = false;

    QList<QCheckBox*> Days_Of_Week;

    Keyboard *DateTime_Dialog_Keyboard;

    LineEdit*
    New_LineEdit ( bool Accept_Input = true, bool Text_Change_Aware = true );

    void
    Weekday_Weekend_CheckBoxes ( );

    void
    Clear_Span ( bool User_Triggered );

    void
    Clear_As_Span ( );

private slots:
    void
    onClearBeginDateTimeLineEdit ( );

    void
    onClearEndDateTimeLineEdit ( );

    void
    onGotFocus ( );

    void
    onCalculateClicked ( );

    void
    onDismissClicked ( );

    void
    onTextEdited ( const QString &text );

    void
    onClearClicked ( );
};

#endif // DATE_TIME_DIALOG_H
