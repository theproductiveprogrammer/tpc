Wildcard Pattern Matching


Write a program that matches input words against patterns which may contain the wildcards * and ?, and outputs the total number of words that match the patterns.
Both the words and patterns are ASCII Strings, both of which can be of upto 256 characters in length.

The definition of the wildcards is:
  * - Matches 0 or more of any character
  ? - Matches any 1 character

\ is used as the escape sequence:
  \* matches a *
  \? matches a ?
  \\ matches a \

\ followed by any character apart from *,? and \ is an invalid input. The behaviour of the program is undefined for such an input. (and hence can't be tested)

The program should accept the command line:
 pm [-d] <input-file> <pattern-file>

where, <input-file> contains the words (one per line) against which patterns are to be matched.
<pattern-file> contains the patterns (one per line)

The program must output the total number of matches found across all patterns to the standard output.
The optional argument -d is used to verify the output. When this argument is passed, the program must output the all the input words which match the patterns, followed by the total number of matches, to the standard output. The relative order of words in the input file must be maintained in the output file, and the patterns must be processed in the same order as patterns in the pattern file. Matches against each pattern must be separated by a blank line.
 found for each pattern in the same order, followed by the total number of matches.

For evaluation of performance, execution of the program will be done without the -d option.


Examples:
Input file:
abcd
abcde
acerbic
treat
treasure
10\2
A*B=X

Pattern file:
abc
abcd
a*
abcd*
abc?
a\*b*

pm -d input.txt pattern.txt

abcd

abcd
abcde
acerbic
A*B = X

abcd
abcde

abcd

A*B = X

9


pm input.txt pattern.txt
9

NOTE:
abc matches nothing.
abcd matches {abcd}
a* matches {abcd,abcde,acerbic,A*B=X}
abcd* matches {abcd,abcd}
abc? matches {abcd}
a\*b* matches {A*B=X}


A sample input file containing 88000+ words, a pattern file and the expected output is attached.

The fastest program wins the TPC trophy, ties will be resolved by code quality.

Happy coding. :)

Notes:
 - Memory limit: 512 MB
 - The performance will be tested on my machine. (32-bit Core 2 Duo @ 2.93 GHz, Widows 7, 3 GB RAM)

