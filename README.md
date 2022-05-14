# Simplelogger

A simple, header only C/C++ logging solution. Five log-levels are available to the user: ERROR, WARN, INFO, DEBUG, INFO and TRACE. The user can set the log-level by setting an environment variable, `LOG_LEVEL` by defualt. Setting the log-level will result in output from the following functions:


- ERROR: `log_error`
- WARN: `log_error`, `log_warn`
- INFO (default): `log_error`, `log_warn`, `log_info`
- DEBUG: `log_error`, `log_warn`, `log_info`, `log_debug`
- TRACE: `log_error`, `log_warn`, `log_info`, `log_debug`, `log_trace`

main.c shows an example of how to use the logging library. The default log-level and environment variable can be altered by changing the `DEFAULT_LOG_LEVEL` and `LOG_VARIABLE` defines in simplelog.h. 

