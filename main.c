#include <stdio.h>

#include "simplelog.h"

int main() {
		
	//Output messages to stdout
	//log_error("ERROR MESSAGE");
	//log_warn("WARN MESSAGE");
	//log_info("INFO MESsAGE");
	//log_debug("DEBUG MESSAGE");
	//log_trace("TRACE MESSAGE");
	log_num(1,"NUMBER MESSAGE");
	//Output messages to file
	for(int i=1000; i<3000; i++){
		char* message = malloc(sizeof(char)*5);
		sprintf(message, "%d", i);
		//logf_error("file.log", message);
		logf_num("file.log", 1, message);
		free(message);
	}
	
	return 0;
}
