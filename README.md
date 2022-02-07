# Parse_DateTime
Parsing dates w/ times or dates

Searching the internet, you'd suppose it to be hard, parsing datetimes and dates as if people were careless and inattentive. Most proposed solutions to parsing freeform datetimes involve stepping through the various shoes looking for the one that fits your princess.

The requiements are much looser than the usual computer datetime formats. Separators can be anything that's not a digit or letter, by requiring four digit years, there's only one real ambiguity, the ordering of months versus days when both are expressed as numbers. So only two rules and you're done: a) all year values must be expressed as four digits and b) when expressing month/day/year with numbers, the date must be rendered as mm/dd/yyyy.

At this point regular expressions will do the job without breaking a sweat. In this case, I used QRegExp (normally I'd use PCRE) which is one of the weaker regular expression libraries (for example, no lookback). Doesn't matter, the task is too simple.
