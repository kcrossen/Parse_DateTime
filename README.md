# Parse_DateTime
Parsing dates w/ times or dates

Searching the internet, you'd suppose it to be hard, parsing datetimes and dates as if people were careless and inattentive. Most proposed solutions to parsing freeform datetimes involve stepping through the various shoes looking for the one that fits your princess.

The requiements are much looser than the usual computer datetime formats. Separators can be anything that's not a digit or letter, by requiring four digit years, there's only one real ambiguity, the ordering of months versus days when both are expressed as numbers. So only two rules and you're done: a) all year values must be expressed as four digits and b) when expressing month/day/year with numbers, the date must be rendered as mm/dd/yyyy.

At this point regular expressions will do the job without breaking a sweat. In this case, I used QRegExp (normally I'd use PCRE) which is one of the weaker regular expression libraries (for example, no lookback). Doesn't matter, the task is too simple.

The usual (but more relaxed) ISO 8601 format is supported directly, but any "reasonable" ordering of the following datetime "atoms" will be correctly parsed if the user follows the above two requirements. If you want to support "unreasonable" formats, for example "8:00p 2022 3 feb", this can easily be added. Just study at the currently supported formats to see how.
1) 2022 to express thne year
2) Feb OR febuary OR 02 (if the mm/dd/yyyy rule is followed) to express the month
3) 6 OR 06 to express the day of the month
4) 8:00 OR 8:00a OR 8:00am OR 8:00p OR 8:00pm OR 08:00 OR 08:00a OR 08:00am OR 08:00p OR 08:00pm OR 18:30, etc. to expres the time
5) 2nd Tue Feb 2021 OR 3rd Monday Feb 2021 OR 4th Sat June 2021, etc. to schedule an election
6) time zones are not supported, all datetimes are assumed to be local or UTC or whatever you need
