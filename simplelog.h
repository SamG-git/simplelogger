/* Simple logging header file for C and C++. 5 log levels are 
 * are available to the users: ERROR, WARN, INFO, DEBUG and 
 * TRACE. Setting the log level to TRACE will output all log
 * messages, DEBUG will output everything bar TRACE and so-on.
 *
 * Author: S J GEORGE
 * Date: 2022/05/14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_VARIABLE "LOG_LEVEL"
#define DEFAULT_LOG_LEVEL 3

//void simplelog_write_message(char* message);
//int simplelog_get_level();

//void log_error(char* message);
//void log_warn(char* message);
//void log_info(char* message);
//void log_debug(char* message);
//void log_trace(char* message);

//Converts string log-level to number.
int simplelog_get_level(){
	const char* lev = getenv(LOG_VARIABLE);
	
	if(lev == NULL){
		return DEFAULT_LOG_LEVEL;
	}

	if(strcmp(lev,"TRACE") == 0){
		return 5;
	} else if(strcmp(lev,"DEBUG") == 0){
		return 4;
	} else if(strcmp(lev,"INFO") == 0){
		return 3;
	} else if(strcmp(lev,"WARN") == 0){
		return 2;
	} else if(strcmp(lev,"ERROR") == 0){
		return 1;
	} else{
		return DEFAULT_LOG_LEVEL;
	}
}

//Placeholder for log message file writing
void simplelog_write_message(char* message){
	fprintf(stderr, message);
	fprintf(stderr, "\n");
}

void log_error(char* message){
	int level = simplelog_get_level();
	if(level >= 1){
		simplelog_write_message(message);
	}
}

void log_warn(char* message){
	int level = simplelog_get_level();
	if(level >= 2){
		simplelog_write_message(message);
	}
}

void log_info(char* message){
	int level = simplelog_get_level();
	if(level >= 3){
		simplelog_write_message(message);
	}
}

void log_debug(char* message){
	int level = simplelog_get_level();
	if(level >= 4){
		simplelog_write_message(message);
	}
}

void log_trace(char* message){
	int level = simplelog_get_level();
	if(level >= 5){
		simplelog_write_message(message);
	}
}
