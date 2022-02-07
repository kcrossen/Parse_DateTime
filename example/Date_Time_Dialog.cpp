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

#include "Date_Time_Dialog.h"
#include "DragLabel.h"
#include "Keyboard.h"
#include "Parse_DateTime.h"
#include "Dialog_Defines.h"

#define Date_Time_Dialog_Window_Color QColor(240, 224, 208)
#define Date_Time_Dialog_Alternate_Color QColor(208, 240, 255)
#define Date_Time_Dialog_Button_Height 20
#define Date_Time_Dialog_Button_Width int(Scale_Screen_Dimension(APCalculator_WindowWidth) * 0.045)
#define Date_Time_Dialog_Button_PointSize 14

#define Clear_Button_Height 20
#define Clear_Button_Width 20

DateTimeDialog::DateTimeDialog ( QWidget *parent ) : QDialog ( parent ) {

#if defined(Q_OS_ANDROID)
#else
    setWindowTitle("Date/Time");
#endif

    this->setMinimumSize(Scale_Screen_Dimension(APCalculator_WindowWidth * 1.25),
                         Scale_Screen_Dimension(APCalculator_WindowHeight * 0.855));

    QPalette dialog_palette = this->palette();
    dialog_palette.setColor(QPalette::Window, Date_Time_Dialog_Window_Color);
    this->setPalette(dialog_palette);
    this->setAutoFillBackground(true);

    QFont dialog_font = this->font();
    dialog_font.setPointSize(Scale_Font_Dimension(Dialog_Button_Font_PointSize));
    this->setFont(dialog_font);

    QVBoxLayout* date_time_dialog_layout = new QVBoxLayout();
    date_time_dialog_layout->setContentsMargins(0, 0, 0, 0);
    date_time_dialog_layout->setSpacing(0);

#if defined(Q_OS_ANDROID)
    QHBoxLayout* dialog_title_layout = new QHBoxLayout();
    dialog_title_layout->setContentsMargins(0, 0, 0, 0);
    dialog_title_layout->setSpacing(0);

    PushButton* dialog_cancel_button = New_Dialog_Cancel_Button();
    connect(dialog_cancel_button, SIGNAL(clicked()), this, SLOT(onDismissClicked()));
    dialog_title_layout->addWidget(dialog_cancel_button, 0);

    DragLabel *window_title = New_Dialog_Title_DragLabel("Date/Time", Date_Time_Dialog_Window_Color);
    window_title->Set_Parent_Widget(this);
    dialog_title_layout->addWidget(window_title, 100);

    date_time_dialog_layout->addLayout(dialog_title_layout, 0);
#endif

    QFrame *date_time_frame = new QFrame(this);
    date_time_frame->setContentsMargins(0, 0, 0, 0);
    date_time_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#if defined(Q_OS_ANDROID)
    date_time_frame->setFrameStyle(QFrame::Box);
    date_time_frame->setLineWidth(2);
#else
    date_time_frame->setFrameStyle(QFrame::NoFrame);
#endif

    QVBoxLayout *date_time_frame_layout = new QVBoxLayout();
    date_time_frame_layout->setContentsMargins(Scale_Screen_Dimension(4), Scale_Screen_Dimension(4),
                                               Scale_Screen_Dimension(4), Scale_Screen_Dimension(4));
    date_time_frame_layout->setSpacing(0);

    QHBoxLayout *begin_label_end_label_layout = new QHBoxLayout();
    begin_label_end_label_layout->setContentsMargins(0, 0, 0, 0);
    begin_label_end_label_layout->setSpacing(Scale_Screen_Dimension(9));

    QLabel *begin_datetime_Label = new QLabel("Begin Date/Time:", this);
    begin_datetime_Label->setContentsMargins(0, 0, 0, 0);
    begin_datetime_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    begin_label_end_label_layout->addWidget(begin_datetime_Label);

    QLabel *end_datetime_Label = new QLabel("End Date/Time:", this);
    end_datetime_Label->setContentsMargins(0, 0, 0, 0);
    end_datetime_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    begin_label_end_label_layout->addWidget(end_datetime_Label);

    date_time_frame_layout->addLayout(begin_label_end_label_layout);

    QHBoxLayout *begin_datetime_end_datetime_layout = new QHBoxLayout();
    begin_datetime_end_datetime_layout->setContentsMargins(0, 0, 0, 0);
    begin_datetime_end_datetime_layout->setSpacing(0);

    Begin_DateTime_LineEdit = New_LineEdit(true, false); // Accept user input, Ignore user changes
    begin_datetime_end_datetime_layout->addWidget(Begin_DateTime_LineEdit);

    double icon_width_scale_scale = 0.65;
    double icon_height_scale_scale = 0.65;

    PushButton* begin_clear_button = new PushButton();
    begin_clear_button->setText("");
    begin_clear_button->setIcon(QIcon(":/icons/Cancel.png"));
    begin_clear_button->setIconSize(QSize(Scale_Screen_Dimension(Clear_Button_Width * icon_width_scale_scale),
                                          Scale_Screen_Dimension(Clear_Button_Height * icon_height_scale_scale)));
    begin_clear_button->setMinimumWidth(Scale_Screen_Dimension(Clear_Button_Width * 1));
    begin_clear_button->setMinimumHeight(Scale_Screen_Dimension(Clear_Button_Height));
    begin_clear_button->setMaximumHeight(Scale_Screen_Dimension(Clear_Button_Height));
    begin_clear_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(begin_clear_button, SIGNAL(clicked()), this, SLOT(onClearBeginDateTimeLineEdit()));
    begin_datetime_end_datetime_layout->addWidget(begin_clear_button);

    begin_datetime_end_datetime_layout->addSpacing(Scale_Screen_Dimension(9));

    End_DateTime_LineEdit = New_LineEdit(true, false); // Accept user input, Ignore user changes
    begin_datetime_end_datetime_layout->addWidget(End_DateTime_LineEdit);

    PushButton* end_clear_button = new PushButton();
    end_clear_button->setText("");
    end_clear_button->setIcon(QIcon(":/icons/Cancel.png"));
    end_clear_button->setIconSize(QSize(Scale_Screen_Dimension(Clear_Button_Width * icon_width_scale_scale),
                                        Scale_Screen_Dimension(Clear_Button_Height * icon_height_scale_scale)));
    end_clear_button->setMinimumWidth(Scale_Screen_Dimension(Clear_Button_Width * 1));
    end_clear_button->setMinimumHeight(Scale_Screen_Dimension(Clear_Button_Height));
    end_clear_button->setMaximumHeight(Scale_Screen_Dimension(Clear_Button_Height));
    end_clear_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(end_clear_button, SIGNAL(clicked()), this, SLOT(onClearEndDateTimeLineEdit()));
    begin_datetime_end_datetime_layout->addWidget(end_clear_button);

    date_time_frame_layout->addLayout(begin_datetime_end_datetime_layout);

    QHBoxLayout *begin_dayof_end_dayof_layout = new QHBoxLayout();
    begin_dayof_end_dayof_layout->setContentsMargins(0, 0, 0, 0);
    begin_dayof_end_dayof_layout->setSpacing(Scale_Screen_Dimension(0));

    Begin_Date_Label = new QLabel(this);
    Begin_Date_Label->setContentsMargins(0, 0, 0, 0);
    Begin_Date_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    begin_dayof_end_dayof_layout->addWidget(Begin_Date_Label);

    begin_dayof_end_dayof_layout->addSpacing(Scale_Screen_Dimension(9));

    End_Date_Label = new QLabel(this);
    End_Date_Label->setContentsMargins(0, 0, 0, 0);
    End_Date_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    begin_dayof_end_dayof_layout->addWidget(End_Date_Label);

    date_time_frame_layout->addLayout(begin_dayof_end_dayof_layout);

    date_time_frame_layout->addSpacing(Scale_Screen_Dimension(5));

    // Time span layout ...
    QLabel *span_components_label = new QLabel("Span components", this);
    span_components_label->setContentsMargins(0, 0, 0, 0);
    span_components_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    span_components_label->setAlignment(Qt::AlignHCenter);
    date_time_frame_layout->addWidget(span_components_label, 0);

    QHBoxLayout *date_time_span_layout = new QHBoxLayout();
    date_time_span_layout->setContentsMargins(0, 0, 0, 0);
    date_time_span_layout->setSpacing(Scale_Screen_Dimension(9));

    QGridLayout *date_span_gridlayout = new QGridLayout();
    date_span_gridlayout->setContentsMargins(0, 0, 0, 0);
    date_span_gridlayout->setSpacing(Scale_Screen_Dimension(0));
    // Year span
    QLabel *year_label = new QLabel("Years:", this);
    year_label->setContentsMargins(0, 0, 0, 0);
    date_span_gridlayout->addWidget(year_label, 0, 0);

    Year_Span_LineEdit = New_LineEdit();
    date_span_gridlayout->addWidget(Year_Span_LineEdit, 0, 1);

    // Month span
    QLabel *month_label = new QLabel("Months:", this);
    month_label->setContentsMargins(0, 0, 0, 0);
    date_span_gridlayout->addWidget(month_label, 1, 0);

    Month_Span_LineEdit = New_LineEdit();
    date_span_gridlayout->addWidget(Month_Span_LineEdit, 1, 1);

    // Day span
    QLabel *day_label = new QLabel("Days:", this);
    day_label->setContentsMargins(0, 0, 0, 0);
    date_span_gridlayout->addWidget(day_label, 2, 0);

    Day_Span_LineEdit = New_LineEdit();
    date_span_gridlayout->addWidget(Day_Span_LineEdit, 2, 1);

    // Weekday span
    QLabel *weekday_label = new QLabel("Weekdays:", this);
    weekday_label->setContentsMargins(0, 0, 0, 0);
    date_span_gridlayout->addWidget(weekday_label, 3, 0);

    WeekDay_Span_LineEdit = New_LineEdit();
    date_span_gridlayout->addWidget(WeekDay_Span_LineEdit, 3, 1);

    date_time_span_layout->addLayout(date_span_gridlayout);

    QGridLayout *time_span_gridlayout = new QGridLayout();
    time_span_gridlayout->setContentsMargins(0, 0, 0, 0);
    time_span_gridlayout->setSpacing(Scale_Screen_Dimension(0));
    // Hour span
    QLabel *hour_label = new QLabel("Hours:", this);
    hour_label->setContentsMargins(0, 0, 0, 0);
    time_span_gridlayout->addWidget(hour_label, 0, 0);

    Hour_Span_LineEdit = New_LineEdit();
    time_span_gridlayout->addWidget(Hour_Span_LineEdit, 0, 1);

    // Minute span
    QLabel *minute_label = new QLabel("Minutes:", this);
    minute_label->setContentsMargins(0, 0, 0, 0);
    time_span_gridlayout->addWidget(minute_label, 1, 0);

    Minute_Span_LineEdit = New_LineEdit();
    time_span_gridlayout->addWidget(Minute_Span_LineEdit, 1, 1);

    // Second span
    QLabel *second_label = new QLabel("Seconds:", this);
    second_label->setContentsMargins(0, 0, 0, 0);
    time_span_gridlayout->addWidget(second_label, 2, 0);

    Second_Span_LineEdit = New_LineEdit();
    time_span_gridlayout->addWidget(Second_Span_LineEdit, 2, 1);

    // Weekend span
    QLabel *weekend_label = new QLabel("Weekend Days:", this);
    weekend_label->setContentsMargins(0, 0, 0, 0);
    time_span_gridlayout->addWidget(weekend_label, 3, 0);

    Weekend_Span_LineEdit = New_LineEdit();
    time_span_gridlayout->addWidget(Weekend_Span_LineEdit, 3, 1);

    date_time_span_layout->addLayout(time_span_gridlayout);
    date_time_frame_layout->addLayout(date_time_span_layout, 100);
    // ... Time span layout

    date_time_frame_layout->addSpacing(Scale_Screen_Dimension(5));

    QHBoxLayout *weekday_weekend_layout = new QHBoxLayout();
    weekday_weekend_layout->setContentsMargins(0, 0, 0, 0);
    weekday_weekend_layout->setSpacing(Scale_Screen_Dimension(3));

    Weekday_Weekend_CheckBoxes();
    for (int idx = 0; idx < Days_Of_Week.count(); idx++) {
        weekday_weekend_layout->addWidget(Days_Of_Week[idx]);
    }

    date_time_frame_layout->addLayout(weekday_weekend_layout, 0);

    date_time_frame_layout->addSpacing(Scale_Screen_Dimension(5));

    DateTime_Dialog_Keyboard = new Keyboard(this, Begin_DateTime_LineEdit, DateTime_Keyboard);
    date_time_frame_layout->addWidget(DateTime_Dialog_Keyboard, 0);

    date_time_frame_layout->addSpacing(Scale_Screen_Dimension(5));

    // Span expressed as layout ...
    QFrame *expressed_as_frame = new QFrame();
    expressed_as_frame->setContentsMargins(0, 0, 0, 0);
    QPalette expressed_as_palette = expressed_as_frame->palette();
    expressed_as_palette.setColor(QPalette::Window, Date_Time_Dialog_Alternate_Color);
    expressed_as_frame->setPalette(expressed_as_palette);
    expressed_as_frame->setAutoFillBackground(true);
    expressed_as_frame->setFrameStyle(QFrame::NoFrame);

    QVBoxLayout *expressed_as_frame_layout = new QVBoxLayout;
    expressed_as_frame_layout->setContentsMargins(0, 0, 0, 0);
    expressed_as_frame_layout->setSpacing(4);

    QLabel *entire_span_as_label = new QLabel("Entire span expressed as:", this);
    entire_span_as_label->setContentsMargins(0, 0, 0, 0);
    entire_span_as_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    entire_span_as_label->setAlignment(Qt::AlignHCenter);
    expressed_as_frame_layout->addWidget(entire_span_as_label, 0);

    QHBoxLayout *date_time_span_as_layout = new QHBoxLayout();
    date_time_span_as_layout->setContentsMargins(0, 0, 0, 0);
    date_time_span_as_layout->setSpacing(Scale_Screen_Dimension(9));

    QGridLayout *date_span_as_gridlayout = new QGridLayout();
    date_span_as_gridlayout->setContentsMargins(0, 0, 0, 0);
    date_span_as_gridlayout->setSpacing(Scale_Screen_Dimension(0));
    // As weeks span
    QLabel *as_weeks_label = new QLabel("Weeks:", this);
    as_weeks_label->setContentsMargins(0, 0, 0, 0);
    date_span_as_gridlayout->addWidget(as_weeks_label, 0, 0);

    Span_As_Weeks_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    date_span_as_gridlayout->addWidget(Span_As_Weeks_LineEdit, 0, 1);

    // As days span
    QLabel *as_days_label = new QLabel("OR Days:", this);
    as_days_label->setContentsMargins(0, 0, 0, 0);
    date_span_as_gridlayout->addWidget(as_days_label, 1, 0);

    Span_As_Days_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    date_span_as_gridlayout->addWidget(Span_As_Days_LineEdit, 1, 1);

    // As hours span
    QLabel *as_hours_label = new QLabel("OR Hours:", this);
    as_hours_label->setContentsMargins(0, 0, 0, 0);
    date_span_as_gridlayout->addWidget(as_hours_label, 2, 0);

    Span_As_Hours_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    date_span_as_gridlayout->addWidget(Span_As_Hours_LineEdit, 2, 1);

    date_time_span_as_layout->addLayout(date_span_as_gridlayout);

    QGridLayout *time_span_as_gridlayout = new QGridLayout();
    time_span_as_gridlayout->setContentsMargins(0, 0, 0, 0);
    time_span_as_gridlayout->setSpacing(Scale_Screen_Dimension(0));
    // As minutes span
    QLabel *as_minutes_label = new QLabel("OR Minutes:", this);
    as_minutes_label->setContentsMargins(0, 0, 0, 0);
    time_span_as_gridlayout->addWidget(as_minutes_label, 0, 0);

    Span_As_Minutes_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    time_span_as_gridlayout->addWidget(Span_As_Minutes_LineEdit, 0, 1);

    // Minute span
    QLabel *as_seconds_label = new QLabel("OR Seconds:", this);
    as_seconds_label->setContentsMargins(0, 0, 0, 0);
    time_span_as_gridlayout->addWidget(as_seconds_label, 1, 0);

    Span_As_Seconds_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    time_span_as_gridlayout->addWidget(Span_As_Seconds_LineEdit, 1, 1);

    // Second span
    QLabel *as_millisecond_label = new QLabel("OR Millisecond:", this);
    as_millisecond_label->setContentsMargins(0, 0, 0, 0);
    time_span_as_gridlayout->addWidget(as_millisecond_label, 2, 0);

    Span_As_Milliseconds_LineEdit = New_LineEdit(false, false); // Reject user input, Ignore user changes
    time_span_as_gridlayout->addWidget(Span_As_Milliseconds_LineEdit, 2, 1);

    date_time_span_as_layout->addLayout(time_span_as_gridlayout);
    expressed_as_frame_layout->addLayout(date_time_span_as_layout);
    expressed_as_frame->setLayout(expressed_as_frame_layout);
    date_time_frame_layout->addWidget(expressed_as_frame, 100);
    // ... Span expressed as layout

    date_time_frame_layout->addSpacing(Scale_Screen_Dimension(5));

    QHBoxLayout* date_time_dialog_button_layout = new QHBoxLayout();
    date_time_dialog_button_layout->setContentsMargins(0, 0, 0, 0);
    date_time_dialog_button_layout->setSpacing(4);

    PushButton* dismiss_button = new PushButton();
    QFont dismiss_button_font = dismiss_button->font();
    dismiss_button_font.setPointSize(Scale_Font_Dimension(Date_Time_Dialog_Button_PointSize));
    dismiss_button->setFont(dismiss_button_font);
    dismiss_button->setText("Dismiss");
    dismiss_button->setMaximumHeight(Scale_Screen_Dimension(Date_Time_Dialog_Button_Height));
    dismiss_button->setMinimumWidth(Scale_Screen_Dimension(Date_Time_Dialog_Button_Width));
    connect(dismiss_button, SIGNAL(clicked()), this, SLOT(onDismissClicked()));
    date_time_dialog_button_layout->addWidget(dismiss_button, 0);

    date_time_dialog_button_layout->addStretch(100);

    PushButton* clear_button = new PushButton();
    QFont clear_button_font = clear_button->font();
    clear_button_font.setPointSize(Scale_Font_Dimension(Date_Time_Dialog_Button_PointSize));
    clear_button->setFont(clear_button_font);
    clear_button->setText("Clear");
    clear_button->setMaximumHeight(Scale_Screen_Dimension(Date_Time_Dialog_Button_Height));
    clear_button->setMinimumWidth(Scale_Screen_Dimension(Date_Time_Dialog_Button_Width));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    date_time_dialog_button_layout->addWidget(clear_button, 0);

    date_time_dialog_button_layout->addStretch(100);

    PushButton* calculate_button = new PushButton();
    QFont button_font = calculate_button->font();
    button_font.setPointSize(Scale_Font_Dimension(Date_Time_Dialog_Button_PointSize));
    calculate_button->setFont(button_font);
    calculate_button->setText("Calculate");
    calculate_button->setMaximumHeight(Scale_Screen_Dimension(Date_Time_Dialog_Button_Height));
    calculate_button->setMinimumWidth(Scale_Screen_Dimension(Date_Time_Dialog_Button_Width));
    connect(calculate_button, SIGNAL(clicked()), this, SLOT(onCalculateClicked()));
    date_time_dialog_button_layout->addWidget(calculate_button);

    date_time_frame_layout->addLayout(date_time_dialog_button_layout, 0);
    date_time_frame->setLayout(date_time_frame_layout);

    date_time_dialog_layout->addWidget(date_time_frame);
    this->setLayout(date_time_dialog_layout);

    APCalc_Widget = nullptr;
    // Walk back up the chain to find APCalcClass
    QWidget *parent_widget = this->parentWidget();
    while (not (parent_widget == nullptr)) {
        APCalc_Widget = qobject_cast<APCalcClass*>(parent_widget);

        // Walk up ancestor chain
        parent_widget = parent_widget->parentWidget();
    }
}

LineEdit*
DateTimeDialog::New_LineEdit ( bool Accept_Input, bool Text_Change_Aware ) {
    LineEdit *this_new_lineedit = new LineEdit(this);
    this_new_lineedit->setContentsMargins(0, 0, 0, 0);
    this_new_lineedit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this_new_lineedit->Set_Normal_QLineEdit_Behavior(true);
    if (not Accept_Input) {
        this_new_lineedit->setFocusPolicy(Qt::NoFocus);
    }
    connect(this_new_lineedit, SIGNAL(gotFocus()), this, SLOT(onGotFocus()));
    if (Text_Change_Aware) {
        connect(this_new_lineedit, SIGNAL(textEdited(QString)), this, SLOT(onTextEdited(QString)));
    }
    return this_new_lineedit;
}

void
DateTimeDialog::Weekday_Weekend_CheckBoxes ( ) {
    QCheckBox *monday_checkbox = new QCheckBox("Mon", this);
    monday_checkbox->setChecked(true);
    Days_Of_Week.append(monday_checkbox);

    QCheckBox *tuesday_checkbox = new QCheckBox("Tue", this);
    tuesday_checkbox->setChecked(true);
    Days_Of_Week.append(tuesday_checkbox);

    QCheckBox *wednesday_checkbox = new QCheckBox("Wed", this);
    wednesday_checkbox->setChecked(true);
    Days_Of_Week.append(wednesday_checkbox);

    QCheckBox *thursday_checkbox = new QCheckBox("Thu", this);
    thursday_checkbox->setChecked(true);
    Days_Of_Week.append(thursday_checkbox);

    QCheckBox *friday_checkbox = new QCheckBox("Fri", this);
    friday_checkbox->setChecked(true);
    Days_Of_Week.append(friday_checkbox);

    QCheckBox *saturday_checkbox = new QCheckBox("Sat", this);
    saturday_checkbox->setChecked(false);
    Days_Of_Week.append(saturday_checkbox);

    QCheckBox *sunday_checkbox = new QCheckBox("Sun", this);
    sunday_checkbox->setChecked(false);
    Days_Of_Week.append(sunday_checkbox);
}

void
DateTimeDialog::onGotFocus ( ) {
    LineEdit *focused_lineedit = (LineEdit*) sender();
    DateTime_Dialog_Keyboard->Set_Focus_Widget(focused_lineedit);
    focused_lineedit->setCursorPosition(focused_lineedit->text().length());
}

void
DateTimeDialog::onTextEdited ( const QString &text ) {
    Q_UNUSED(text)
    User_Changed_Span = true;
}

void
DateTimeDialog::onCalculateClicked ( ) {
    Clear_Span(false);
    Clear_As_Span();

    QString begin_datetime_text = Begin_DateTime_LineEdit->text();
    QString end_datetime_text = End_DateTime_LineEdit->text();

    QDateTime begin_datetime = Parse_DateTime_String(begin_datetime_text);
    QDateTime end_datetime = Parse_DateTime_String(end_datetime_text);

    QDate begin_date = QDate(0, 0, 0);
    Begin_Date_Label->setText("");
    if (begin_datetime_text.length() > 0) {
        QString begin_date_information = "Invalid";
        if (begin_datetime.isValid()) {
            begin_date = begin_datetime.date();
            begin_date_information = "";
            begin_date_information += begin_date.toString("ddd d MMM yyyy");
            begin_date_information += "; wk/yr: " + QString::number(begin_date.weekNumber());
            begin_date_information += "; day/yr: " + QString::number(begin_date.dayOfYear());
        }
        Begin_Date_Label->setText(begin_date_information);
    }

    QDate end_date = QDate(0, 0, 0);
    End_Date_Label->setText("");
    if (end_datetime_text.length() > 0) {
        QString end_date_information = "Invalid";
        if (end_datetime.isValid()) {
            end_date = end_datetime.date();
            end_date_information = "";
            end_date_information += end_date.toString("ddd d MMM yyyy");
            end_date_information += "; wk/yr: " + QString::number(end_date.weekNumber());
            end_date_information += "; day/yr: " + QString::number(end_date.dayOfYear());
        }
        End_Date_Label->setText(end_date_information);
     }

    if (begin_datetime.isValid() and end_datetime.isValid()) {
        int year_diff = end_date.year() - begin_date.year();
        int month_diff = end_date.month() - begin_date.month();
        int day_diff = end_date.day() - begin_date.day();

        qint64 week_days = 0;
        qint64 weekend_days = 0;
        int week_days_per_week = 0;

        for (int wk_idx = 0; wk_idx < 7; wk_idx++)
            if (Days_Of_Week[wk_idx]->isChecked()) week_days_per_week += 1;

        qint64 day_of_week_idx = begin_date.dayOfWeek() - 1;
        qint64 day_count = begin_date.daysTo(end_date);
        qint64 day_idx = 0;

        qint64 whole_week_count = day_count / 7;
        if (whole_week_count > 0) {
            week_days += week_days_per_week * whole_week_count;
            weekend_days += (7 - week_days_per_week) * whole_week_count;
            day_idx += whole_week_count * 7;
            // day_of_week_idx remains unchanged after ...
            // ... integer number of whole week cycles
        }

        // Deal w/ fractional week via brute force
        while (day_idx < day_count) {
            if (Days_Of_Week[day_of_week_idx]->isChecked()) week_days += 1;
            else weekend_days += 1;
            day_of_week_idx = (day_of_week_idx + 1) % 7;
            day_idx++;
        }

        QTime begin_time = begin_datetime.time();
        QTime end_time = end_datetime.time();

        int hour_diff = end_time.hour() - begin_time.hour();
        int minute_diff = end_time.minute() - begin_time.minute();
        int second_diff = end_time.second() - begin_time.second();
        // int millisecond_diff = end_time.msec() - begin_time.msec();

        // Year_Span_LineEdit->setText(QString::number(year_diff));
        // Month_Span_LineEdit->setText(QString::number(month_diff));
        // Day_Span_LineEdit->setText(QString::number(day_diff));
        // Hour_Span_LineEdit->setText(QString::number(hour_diff));
        // Minute_Span_LineEdit->setText(QString::number(minute_diff));
        // Second_Span_LineEdit->setText(QString::number(second_diff)); // + (millisecond_diff / 1000.0)));
        Year_Span_LineEdit->SetText_No_Undo(QString::number(year_diff));
        Month_Span_LineEdit->SetText_No_Undo(QString::number(month_diff));
        Day_Span_LineEdit->SetText_No_Undo(QString::number(day_diff));
        Hour_Span_LineEdit->SetText_No_Undo(QString::number(hour_diff));
        Minute_Span_LineEdit->SetText_No_Undo(QString::number(minute_diff));
        Second_Span_LineEdit->SetText_No_Undo(QString::number(second_diff)); // + (millisecond_diff / 1000.0)));

        // WeekDay_Span_LineEdit->setText(QString::number(week_days));
        // Weekend_Span_LineEdit->setText(QString::number(weekend_days));
        WeekDay_Span_LineEdit->SetText_No_Undo(QString::number(week_days));
        Weekend_Span_LineEdit->SetText_No_Undo(QString::number(weekend_days));

        qint64 milliseconds_span = begin_datetime.msecsTo(end_datetime);

        double as_weeks = (1.0 * milliseconds_span) / (1.0 * 7 * 24 * 60 * 60 * 1000);
        // Span_As_Weeks_LineEdit->setText(QString::number(as_weeks));
        Span_As_Weeks_LineEdit->SetText_No_Undo(QString::number(as_weeks));

        double as_days = (1.0 * milliseconds_span) / (1.0 * 24 * 60 * 60 * 1000);
        // Span_As_Days_LineEdit->setText(QString::number(as_days));
        Span_As_Days_LineEdit->SetText_No_Undo(QString::number(as_days));

        double as_hours = (1.0 * milliseconds_span) / (1.0 * 60 * 60 * 1000);
        // Span_As_Hours_LineEdit->setText(QString::number(as_hours));
        Span_As_Hours_LineEdit->SetText_No_Undo(QString::number(as_hours));


        double as_minutes = (1.0 * milliseconds_span) / (1.0 * 60 * 1000);
        // Span_As_Minutes_LineEdit->setText(QString::number(as_minutes));
        Span_As_Minutes_LineEdit->SetText_No_Undo(QString::number(as_minutes));

        double as_seconds = (1.0 * milliseconds_span) / (1.0 * 1000);
        // Span_As_Seconds_LineEdit->setText(QString::number(as_seconds));
        Span_As_Seconds_LineEdit->SetText_No_Undo(QString::number(as_seconds));

        // Span_As_Milliseconds_LineEdit->setText(QString::number(milliseconds_span));
        Span_As_Milliseconds_LineEdit->SetText_No_Undo(QString::number(milliseconds_span));

        User_Changed_Span = false;
    }
    else if ((begin_datetime.isValid()) and (end_datetime_text.length() == 0)) {
        end_datetime = begin_datetime;

        if ((Year_Span_LineEdit->text().length() > 0) or
            (Month_Span_LineEdit->text().length() > 0) or
            (Day_Span_LineEdit->text().length() > 0) or
            (Hour_Span_LineEdit->text().length() > 0) or
            (Minute_Span_LineEdit->text().length() > 0) or
            (Second_Span_LineEdit->text().length() > 0)) {
            end_datetime = end_datetime.addYears(Year_Span_LineEdit->text().toLongLong());
            end_datetime = end_datetime.addMonths(Month_Span_LineEdit->text().toLongLong());
            end_datetime = end_datetime.addDays(Day_Span_LineEdit->text().toLongLong());

            qint64 add_seconds = 0;
            add_seconds += Hour_Span_LineEdit->text().toLongLong() * (60 * 60);
            add_seconds += Minute_Span_LineEdit->text().toLongLong() * 60;
            add_seconds += Second_Span_LineEdit->text().toLongLong();
            end_datetime = end_datetime.addSecs(add_seconds);
        }
        else if ((WeekDay_Span_LineEdit->text().length() > 0) or
                 (Weekend_Span_LineEdit->text().length() > 0)) {
            end_datetime = begin_datetime;
            qint64 day_of_week_idx = begin_datetime.date().dayOfWeek() - 1;
            qint64 add_days = 0;

            qint64 add_week_days = 0;
            if (WeekDay_Span_LineEdit->text().length() > 0) {
                add_week_days = WeekDay_Span_LineEdit->text().toInt();
            }
            qint64 add_weekend_days = 0;
            if (Weekend_Span_LineEdit->text().length() > 0) {
                add_weekend_days = Weekend_Span_LineEdit->text().toInt();
            }

            int week_days_per_week = 0;
            for (int wk_idx = 0; wk_idx < 7; wk_idx++)
                if (Days_Of_Week[wk_idx]->isChecked()) week_days_per_week += 1;

            if (((week_days_per_week == 0) and (add_week_days > 0)) or
                ((week_days_per_week == 7) and (add_weekend_days > 0)) or
                // How would we know which to step if:
                ((add_week_days * add_weekend_days) < 0)) {
                // No way to win here
            }
            else {
                int add_another_day = 1;
                if (((add_week_days < 0) and (add_weekend_days < 0)) or
                    ((add_week_days < 0) and (add_weekend_days == 0)) or
                    ((add_week_days == 0) and (add_weekend_days < 0))) {
                    // Deal w/ stepping back in time
                    add_another_day = -1;
                    add_week_days = abs(add_week_days);
                    add_weekend_days = abs(add_weekend_days);
                }

                while ((add_week_days > 0) or (add_weekend_days > 0)) {
                    if (Days_Of_Week[day_of_week_idx]->isChecked()) add_week_days -= 1;
                    else add_weekend_days -= 1;
                    add_days += add_another_day;
                    day_of_week_idx = day_of_week_idx + add_another_day;
                    day_of_week_idx = (day_of_week_idx + 7) % 7;
                }
            }

            end_datetime = end_datetime.addDays(add_days);
        }

        QString end_date_text = end_datetime.toString(Qt::RFC2822Date);
        QRegExp time_zone_rx(timezone_cap, Qt::CaseInsensitive);
        int timezone_idx = end_date_text.indexOf(time_zone_rx, 0);
        if (timezone_idx >= 0) end_date_text = end_date_text.left(timezone_idx);
        // End_DateTime_LineEdit->setText(end_date_text);
        End_DateTime_LineEdit->SetText_No_Undo(end_date_text);

        End_Date_Label->setText("");
        if (end_date_text.length() > 0) {
            QString end_date_information = "Invalid";
            if (end_datetime.isValid()) {
                end_date = end_datetime.date();
                end_date_information = "";
                end_date_information += end_date.toString("ddd d MMM yyyy");
                end_date_information += "; wk/yr: " + QString::number(end_date.weekNumber());
                end_date_information += "; day/yr: " + QString::number(end_date.dayOfYear());
            }
            End_Date_Label->setText(end_date_information);
         }
    }
}

void
DateTimeDialog::onClearBeginDateTimeLineEdit ( ) {
    // Begin_DateTime_LineEdit->setText("");
    Begin_DateTime_LineEdit->Clear_No_Undo();
    Begin_Date_Label->setText("");
}

void
DateTimeDialog::onClearEndDateTimeLineEdit ( ) {
    // End_DateTime_LineEdit->setText("");
    End_DateTime_LineEdit->Clear_No_Undo();
    End_Date_Label->setText("");
}


void
DateTimeDialog::onClearClicked ( ) {
    Clear_Span(true);
    Clear_As_Span();
}

void
DateTimeDialog::Clear_Span ( bool User_Triggered ) {
    if (not User_Changed_Span) {
        // Year_Span_LineEdit->setText("");
        // Month_Span_LineEdit->setText("");
        // Day_Span_LineEdit->setText("");
        Year_Span_LineEdit->Clear_No_Undo();
        Month_Span_LineEdit->Clear_No_Undo();
        Day_Span_LineEdit->Clear_No_Undo();

        // WeekDay_Span_LineEdit->setText("");
        // Weekend_Span_LineEdit->setText("");
        WeekDay_Span_LineEdit->Clear_No_Undo();
        Weekend_Span_LineEdit->Clear_No_Undo();

        // Hour_Span_LineEdit->setText("");
        // Minute_Span_LineEdit->setText("");
        // Second_Span_LineEdit->setText("");
        Hour_Span_LineEdit->Clear_No_Undo();
        Minute_Span_LineEdit->Clear_No_Undo();
        Second_Span_LineEdit->Clear_No_Undo();
    }
    // Click "Clear" button twice to force clearing these
    if (User_Triggered) User_Changed_Span = false;
}

void
DateTimeDialog::Clear_As_Span ( ) {
    // Span_As_Weeks_LineEdit->setText("");
    // Span_As_Days_LineEdit->setText("");
    // Span_As_Hours_LineEdit->setText("");
    Span_As_Weeks_LineEdit->Clear_No_Undo();
    Span_As_Days_LineEdit->Clear_No_Undo();
    Span_As_Hours_LineEdit->Clear_No_Undo();

    // Span_As_Minutes_LineEdit->setText("");
    // Span_As_Seconds_LineEdit->setText("");
    // Span_As_Milliseconds_LineEdit->setText("");
    Span_As_Minutes_LineEdit->Clear_No_Undo();
    Span_As_Seconds_LineEdit->Clear_No_Undo();
    Span_As_Milliseconds_LineEdit->Clear_No_Undo();
}

void
DateTimeDialog::onDismissClicked ( ) {
    reject();
}
