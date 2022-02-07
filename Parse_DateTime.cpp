#include "Parse_DateTime.h"

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

int
Parse_Ordinal ( QString Ordinal_String ) {
    if (Ordinal_String.toLower() == "1st") return 1;
    if (Ordinal_String.toLower() == "2nd") return 2;
    if (Ordinal_String.toLower() == "3rd") return 3;
    if (Ordinal_String.toLower() == "4th") return 4;
    if (Ordinal_String.toLower() == "5th") return 5;
    return -1;
}

int
Parse_DayOfWeek ( QString DayofWeek_String ) {
    if (DayofWeek_String.startsWith("Mon", Qt::CaseInsensitive)) return 0;
    if (DayofWeek_String.startsWith("Tue", Qt::CaseInsensitive)) return 1;
    if (DayofWeek_String.startsWith("Wed", Qt::CaseInsensitive)) return 2;
    if (DayofWeek_String.startsWith("Thu", Qt::CaseInsensitive)) return 3;
    if (DayofWeek_String.startsWith("Fri", Qt::CaseInsensitive)) return 4;
    if (DayofWeek_String.startsWith("Sat", Qt::CaseInsensitive)) return 5;
    if (DayofWeek_String.startsWith("Sun", Qt::CaseInsensitive)) return 6;
    return -1;
}

int
Parse_Month ( QString Month_String ) {
    if (Month_String.startsWith("Jan", Qt::CaseInsensitive)) return 1;
    if (Month_String.startsWith("Feb", Qt::CaseInsensitive)) return 2;
    if (Month_String.startsWith("Mar", Qt::CaseInsensitive)) return 3;
    if (Month_String.startsWith("Apr", Qt::CaseInsensitive)) return 4;
    if (Month_String.startsWith("May", Qt::CaseInsensitive)) return 5;
    if (Month_String.startsWith("Jun", Qt::CaseInsensitive)) return 6;
    if (Month_String.startsWith("Jul", Qt::CaseInsensitive)) return 7;
    if (Month_String.startsWith("Aug", Qt::CaseInsensitive)) return 8;
    if (Month_String.startsWith("Sep", Qt::CaseInsensitive)) return 9;
    if (Month_String.startsWith("Oct", Qt::CaseInsensitive)) return 10;
    if (Month_String.startsWith("Nov", Qt::CaseInsensitive)) return 11;
    if (Month_String.startsWith("Dec", Qt::CaseInsensitive)) return 12;
    return -1;
}

QTime
Parse_Time ( QRegExp Capturing_RegExp, int Hour_Capture_Ordinal ) {
    QTime parsed_time = QTime(12, 0, 0);

    if (Capturing_RegExp.cap(Hour_Capture_Ordinal).length() > 0) {
        int hours = Capturing_RegExp.cap(Hour_Capture_Ordinal).toInt();
        QString seconds_string = Capturing_RegExp.cap(Hour_Capture_Ordinal + 2);
        int seconds = 0;
        if (seconds_string.length() > 0) {
            seconds_string = seconds_string.remove(0, 1);
            seconds = seconds_string.toInt();
        }
        QString am_pm_string = Capturing_RegExp.cap(Hour_Capture_Ordinal + 3).toLower();
        if (am_pm_string.length() > 0) {
            if ((am_pm_string == "p") or (am_pm_string == "pm")) hours += 12;
        }
        parsed_time = QTime(hours,
                            Capturing_RegExp.cap(Hour_Capture_Ordinal + 1).toInt(), seconds);
    }

    return parsed_time;
}

QDateTime
Parse_DateTime_String ( QString DateTime_String ) {
    QDateTime parsed_datetime = QDateTime(QDate(0, 0, 0), QTime(0, 0, 0));
    QDate parsed_date;
    QTime parsed_time = QTime(12, 0, 0);
    int datetime_idx;

    QRegExp day_amonth_year_time_rx((day_cap + date_sep + amonth_cap + date_sep + year_cap + time_optional_cap),
                                    Qt::CaseInsensitive);
    QRegExp amonth_day_year_time_rx((amonth_cap + date_sep + day_cap + date_sep + year_cap + time_optional_cap),
                                    Qt::CaseInsensitive);
    QRegExp year_amonth_day_time_rx((year_cap + date_sep + amonth_cap + date_sep + day_cap + time_optional_cap),
                                    Qt::CaseInsensitive);
    QRegExp year_month_day_time_rx((year_cap + date_sep + month_cap + date_sep + day_cap + time_optional_cap),
                                   Qt::CaseInsensitive);
    QRegExp day_month_year_time_rx((day_cap + "-" + month_cap + "-" + year_cap + time_optional_cap),
                                   Qt::CaseInsensitive);
    QRegExp month_day_year_time_rx((month_cap + "/" + day_cap + "/" + year_cap + time_optional_cap),
                                   Qt::CaseInsensitive);

    QRegExp iso_datetime_rx((year_cap + "-" + month_cap + "-" + day_cap + "T" + time_cap), Qt::CaseInsensitive);

    QRegExp nthday_of_amonth_year_time_rx((nthday_of_amonth_cap + date_sep + year_cap + time_optional_cap),
                                          Qt::CaseInsensitive);

    // qDebug() << (day_cap + date_sep + amonth_cap + date_sep + year_cap + time_optional_cap);

    datetime_idx = DateTime_String.indexOf(day_amonth_year_time_rx, 0);
    if (datetime_idx >= 0) {
        int month_number = Parse_Month(day_amonth_year_time_rx.cap(2));
        parsed_date = QDate(day_amonth_year_time_rx.cap(3).toInt(),
                            month_number,
                            day_amonth_year_time_rx.cap(1).toInt());
        parsed_time = Parse_Time(day_amonth_year_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }

    datetime_idx = DateTime_String.indexOf(amonth_day_year_time_rx, 0);
    if (datetime_idx >= 0) {
        int month_number = Parse_Month(amonth_day_year_time_rx.cap(1));
        parsed_date = QDate(amonth_day_year_time_rx.cap(3).toInt(),
                            month_number,
                            amonth_day_year_time_rx.cap(2).toInt());
        parsed_time = Parse_Time(amonth_day_year_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }

    datetime_idx = DateTime_String.indexOf(year_amonth_day_time_rx, 0);
    if (datetime_idx >= 0) {
        int month_number = Parse_Month(year_amonth_day_time_rx.cap(2));
        parsed_date = QDate(year_amonth_day_time_rx.cap(1).toInt(),
                            month_number,
                            year_amonth_day_time_rx.cap(3).toInt());
        parsed_time = Parse_Time(year_amonth_day_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }

    // Use any separator as in yyyy-mm-dd, yyyy/mm/dd, etc. ...
    datetime_idx = DateTime_String.indexOf(year_month_day_time_rx, 0);
    if (datetime_idx >= 0) {
        parsed_date = QDate(year_month_day_time_rx.cap(1).toInt(),
                            year_month_day_time_rx.cap(2).toInt(),
                            year_month_day_time_rx.cap(3).toInt());
        parsed_time = Parse_Time(year_month_day_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }
    // ... Use any separator as in yyyy-mm-dd, yyyy/mm/dd, etc.

    // Must use "-" as in dd-mm-yyyy ...
    datetime_idx = DateTime_String.indexOf(day_month_year_time_rx, 0);
    if (datetime_idx >= 0) {
        parsed_date = QDate(day_month_year_time_rx.cap(1).toInt(),
                            day_month_year_time_rx.cap(2).toInt(),
                            day_month_year_time_rx.cap(3).toInt());
        parsed_time = Parse_Time(day_month_year_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }
    // ... Must use "-" as in dd-mm-yyyy

    // Must use "/" as in mm/dd/yyyy ...
    datetime_idx = DateTime_String.indexOf(month_day_year_time_rx, 0);
    if (datetime_idx >= 0) {
        parsed_date = QDate(month_day_year_time_rx.cap(3).toInt(),
                            month_day_year_time_rx.cap(1).toInt(),
                            month_day_year_time_rx.cap(2).toInt());
        parsed_time = Parse_Time(month_day_year_time_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }
    // ... Must use "/" as in mm/dd/yyyy

    datetime_idx = DateTime_String.indexOf(iso_datetime_rx, 0);
    if (datetime_idx >= 0) {
        parsed_date = QDate(iso_datetime_rx.cap(1).toInt(),
                            iso_datetime_rx.cap(2).toInt(),
                            iso_datetime_rx.cap(3).toInt());
        parsed_time = Parse_Time(iso_datetime_rx);
        parsed_datetime = QDateTime(parsed_date, parsed_time);
        return parsed_datetime;
    }

    datetime_idx = DateTime_String.indexOf(nthday_of_amonth_year_time_rx, 0);
    if (datetime_idx >= 0) {
        int day_of_week_ordinal = Parse_Ordinal(nthday_of_amonth_year_time_rx.cap(1));
        int day_of_week_number = Parse_DayOfWeek(nthday_of_amonth_year_time_rx.cap(2));
        if ((day_of_week_ordinal > 0) and (day_of_week_number >= 0)) {
            int day_number = 1;
            int month_number = Parse_Month(nthday_of_amonth_year_time_rx.cap(3));
            int year = nthday_of_amonth_year_time_rx.cap(4).toInt();
            QDate first_of_month_date = QDate(year, month_number, 1);
            int first_of_month_dayofweek = first_of_month_date.dayOfWeek() - 1;
            day_number += (day_of_week_number - first_of_month_dayofweek);
            day_number += ((day_of_week_ordinal - 1) * 7);
            if (day_number <= 0) day_number += 7;
            parsed_date = QDate(year, month_number, day_number);
            parsed_time = Parse_Time(nthday_of_amonth_year_time_rx, 5);
            parsed_datetime = QDateTime(parsed_date, parsed_time);
        }
        return parsed_datetime;
    }

    return parsed_datetime;
}
