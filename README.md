# Simplelogger

A simple, header only C/C++ logging solution. Two logging types are available to the users: Numbered Severity and String Severity. The log-level during execution is given by the environment variable defined by `LOG_VARIABLE`, which is `LOG_LEVEL` by default. `LOG_LEVEL` has a value of 3/INFO by default.

NOTE: The user has to choose either Numbered Severity or String Severity - they cannot both be used int he same program.

## Numbered Severity

Numbered Severity allows the user to set the severity of a log based on a number - the higher the number, the lower the severity of the message. Severity is given by numbers between 1 and 9. In execution, the log leven is set by assigning the required environment variable to one of these numbers - all messages with a severity number equal to or less than this number will be outputted. Two numbered severity logging functions are given to the user:

- `void log_num(int log_lev, char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` is equal to or greater than `log_lev`.
- `void logf_num(char* log_file, int log_lev, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` is equal to or greater than `log_lev`.

## String Severity

String Severity allows the user to set the severity of a log based on a series of string levels. In a decending order of severity, these strings are:

1. ERROR
2. WARN
3. INFO
4. DEBUG
5. TRACE

At run-time, `LOG_LEVEL` is set to one of these strings. Any errors with that level of severity or greater are then outputted during execution. Ten string severity logging functions are given to the user:

- `void log_error(char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` severity is equal to or less than ERROR.
- `void log_warn(char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` severity is equal to or less than WARN.
- `void log_info(char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` severity is equal to or less than INFO.
- `void log_debug(char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` severity is equal to or less than DEBUG.
- `void log_trace(char* message)`: Prints the string `message` to `stderr` if `LOG_LEVEL` severity is equal to TRACE.
- `void logf_error(char* log_file, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` severity is equal to or less than ERROR.
- `void logf_warn(char* log_file, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` severity is equal to or less than WARN.
- `void logf_info(char* log_file, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` severity is equal to or less than INFO.
- `void logf_debug(char* log_file, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` severity is equal to or less than DEBUG.
- `void logf_trace(char* log_file, char* message)`: Prints the string `message` to the file with name `log_file` if `LOG_LEVEL` severity is equal to TRACE.

## Testing

The code is tested in three steps:

1. main.c is compiled and run, with the resulting output to `stderr` and `file.log` manually checked for errors.
2. `cppcheck --enable=all --inconclusive --library=posix main.c` is executed, with all warnings (excluding external libraries) fixed before step 3.
3. `valgrind --leak-check=full ./a.out` is executed. This step must report no memory leaks before a commit is made.
