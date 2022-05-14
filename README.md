# Simplelogger

A simple, header only C/C++ logging solution. Five log-levels are available to the user: ERROR, WARN, INFO, DEBUG, INFO and TRACE. The user can set the log-level by setting an environment variable, `LOG_LEVEL` by defualt. Setting the log-level will result in the following output:

ERROR: error
WARN: error, warn
INFO (default): error, warn, info
DEBUG: error, warn, info, debug
TRACE: error, warn, info, debug, trace

main.c shows an example of how to use the logging library. The default log-level and environment variable can be altered by changing the `DEFAULT_LOG_LEVEL` and `LOG_VARIABLE` defines in simplelog.h. 

