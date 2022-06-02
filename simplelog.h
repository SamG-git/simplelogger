/* Simple logging header file for C and C++. 5 log levels are 
 * are available to the users: ERROR, WARN, INFO, DEBUG and 
 * TRACE.
 * 
 * Author: S J GEORGE
 * Date: 2022/05/14
 */

#include <stdio.h>
#include <stdlib.h>

#define LOG_VARIABLE "LOG_LEVEL"
#define DEFAULT_LOG_LEVEL 3 //Cannot be greater than 9
#define MAX_LOG_SIZE 1024
#define COPY_FILENAME ".tmp_log.log"

//Compares two strings

int simplelog_strcmp(const char *s1, const char *s2){
	char c1 = (char) *s1;
	char c2 = (char) *s2;
	
	while(c1 == c2){
		c1 = (char) *(s1++);
		c2 = (char) *(s2++);
		if(c1 == '\0' || c2 == '\0'){
			return c1 - c2;
		}
	}
	return c1 - c2;
}

//Converts string log-level to number.
int simplelog_get_str_level(){
	const char* lev = getenv(LOG_VARIABLE);

	if(lev == NULL){
		return DEFAULT_LOG_LEVEL;
	}

	if(simplelog_strcmp(lev,"TRACE") == 0){
		return 5;
	} else if(simplelog_strcmp(lev,"DEBUG") == 0){
		return 4;
	} else if(simplelog_strcmp(lev,"INFO") == 0){
		return 3;
	} else if(simplelog_strcmp(lev,"WARN") == 0){
		return 2;
	} else if(simplelog_strcmp(lev,"ERROR") == 0){
		return 1;
	} else{
		return DEFAULT_LOG_LEVEL;
	}
}

int simplelog_get_num_level(){
	const char* lev = getenv(LOG_VARIABLE);

	if(lev == NULL){
		return DEFAULT_LOG_LEVEL;
	}

	int lev_num = atoi(lev);

	if(lev_num == 0 || lev_num > 9){
		return DEFAULT_LOG_LEVEL;
	}
	return lev_num;
}

int simplelog_get_log_size(char *file_name){
	FILE *file = fopen(file_name, "r");
	if(file != NULL){
		int lines = 0;
		int ch;
		while((ch = fgetc(file)) != EOF){
			if(ch == '\n'){
				lines++;
			}
		}
		fclose(file);
		return lines;
	} else{
		return 0;
	}
}

void simplelog_write_stderr(char* preamble, char* message){
	fprintf(stderr, preamble);
	fprintf(stderr, message);
	fprintf(stderr, "\n");
	return;
}

//Placeholder for log message file writing
void simplelog_write_file(char* file_name, char* preamble, char* message){
	
	if(simplelog_strcmp(file_name, COPY_FILENAME) == 0){
		simplelog_write_stderr("[SIMPLELOG]: ", 
				        "log file same as COPY_FILENAME");
		simplelog_write_stderr(preamble, message);
		return;
	}
	
	FILE *file, *file_new;
	int lines = simplelog_get_log_size(file_name);

	if(lines < MAX_LOG_SIZE){
		if(lines == 0){
			file = fopen(file_name, "w");
		} else {
			file = fopen(file_name, "a");
		}
		
		if(file == NULL){
			simplelog_write_stderr("[SIMPLELOG]: ",
					"Unable to open log for appending");
			simplelog_write_stderr(preamble, message);
			return;
		}
		
		fprintf(file, preamble);
		fprintf(file, message);
		fprintf(file, "\n");
		fclose(file);

	} else if(lines == MAX_LOG_SIZE) {
		file = fopen(file_name, "r");
		file_new = fopen(COPY_FILENAME, "w");
		
		if(file == NULL || file_new == NULL){
			simplelog_write_stderr("[SIMPLELOG]: ",
					"Unable to open log for reading/writing");
			simplelog_write_stderr(preamble, message);
			return;
		}
		
		//Do not write first line to new file
		int ch;
		while((ch = fgetc(file)) != '\n');
		
		while((ch = fgetc(file)) != EOF){
			if(ch != EOF){
				fputc(ch, file_new);
			}
		}
		fprintf(file_new, preamble);
		fprintf(file_new, message);
		fprintf(file_new, "\n");

		fclose(file);
		fclose(file_new);
                
		//Copy new file to original file
		file = fopen(file_name, "w");
		file_new = fopen(COPY_FILENAME, "r");

		while((ch = fgetc(file_new)) != EOF){
			fputc(ch, file);
		}

		fclose(file);
		fclose(file_new);
		remove(COPY_FILENAME);
	} else {
		simplelog_write_stderr("[SIMPLELOG]: ",
				"Logfile larger than MAX_LOG_SIZE");
		simplelog_write_stderr(preamble, message);
	}
}

void logf_error(char* log_file, char* message){
	int level = simplelog_get_str_level();
	if(level >= 1){
		simplelog_write_file(log_file, "[ERROR]: ", message);
	}
}

void logf_warn(char* log_file, char* message){
	int level = simplelog_get_str_level();
	if(level >= 2){
		simplelog_write_file(log_file, "[WARN]: ", message);
	}
}

void logf_info(char* log_file, char* message){
	int level = simplelog_get_str_level();
	if(level >= 3){
		simplelog_write_file(log_file, "[INFO]: ", message);
	}
}

void logf_debug(char* log_file, char* message){
	int level = simplelog_get_str_level();
	if(level >= 4){
		simplelog_write_file(log_file, "[DEBUG]: ", message);
	}
}

void logf_trace(char* log_file, char*  message){
	int level = simplelog_get_str_level();
	if(level >= 5){
		simplelog_write_file(log_file, "[TRACE]: ", message);
	}
}

void logf_num(char* log_file, int log_lev, char* message){
	int level = simplelog_get_num_level();
	if(log_lev <= level){
		char preamble[26];
		sprintf(preamble, "[LOG LEVEL %d]: ", level);
		simplelog_write_file(log_file, preamble, message);
	}
}

//For simple logging to stderr instead of file.
void log_error(char* message){
	int level = simplelog_get_str_level();
	if(level >= 1){
		simplelog_write_stderr("[ERROR]: ", message);
	}
}

void log_warn(char* message){
	int level = simplelog_get_str_level();
	if(level >= 2){
		simplelog_write_stderr("[WARN]: ", message);
	}
}

void log_info(char* message){
	int level = simplelog_get_str_level();
	if(level >= 3){
		simplelog_write_stderr("[INFO]: ", message);
	}
}

void log_debug(char* message){
	int level = simplelog_get_str_level();
	if(level >= 4){
		simplelog_write_stderr("[DEBUG]: ", message);
	}
}

void log_trace(char*  message){
	int level = simplelog_get_str_level();
	if(level >= 5){
		simplelog_write_stderr("[TRACE]: ", message);
	}
}

void log_num(int log_lev, char* message){
	int level = simplelog_get_num_level();
	if(log_lev <= level){
		char preamble[26];
		sprintf(preamble, "[LOG LEVEL %d]: ", level);
		simplelog_write_stderr(preamble, message);
	}
}
