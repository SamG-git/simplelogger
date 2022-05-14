#include <stdio.h>
#include "simplelog.h"

int main() {
	
	log_error("ERROR");
	log_warn("WARN");
	log_info("INFO");
	log_debug("DEBUG");
	log_trace("TRACE");	
	
	return 0;
}
