#ifndef PARSE_DATETIME_H
#define PARSE_DATETIME_H

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

#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QRegExp>

#define date_sep QString("[^0-9a-z]+")
#define year_cap QString("([0-9][0-9][0-9][0-9])")
#define amonth_cap QString("([a-z][a-z][a-z]+)")
#define month_cap QString("([0-9][0-9])")
#define day_cap QString("([0-9][0-9]?)")
#define time_cap QString("([0-9][0-9]?):([0-9][0-9])(:[0-9][0-9])?(a|am|p|pm)?")
#define time_optional_cap QString("(?:[^0-9a-z]+([0-9][0-9]?):([0-9][0-9])(:[0-9][0-9])?(a|am|p|pm)?)?")

#define nthday_of_amonth_cap QString("(1st|2nd|3rd|4th|5th)[^0-9a-z]+([a-z][a-z][a-z]+)[^0-9a-z]+([a-z][a-z][a-z]+)")

#define timezone_cap QString("(\\s*[+-][0-9][0-9][0-9][0-9]?)")

    int
    Parse_Ordinal ( QString Ordinal_String );

    int
    Parse_DayOfWeek ( QString DayofWeek_String );

    int
    Parse_Month ( QString Month_String );

    QTime
    Parse_Time ( QRegExp Capturing_RegExp, int Hour_Capture_Ordinal = 4 );

    QDateTime
    Parse_DateTime_String ( QString DateTime_String );

#endif // DATE_TIME_DIALOG_H
