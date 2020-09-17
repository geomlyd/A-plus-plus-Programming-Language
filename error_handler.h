#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

enum ErrorType {
	Error=0, Warning, FatalError
};

void error_handler_init(const char * name);
void error(ErrorType et, unsigned int line, const char * format, ...);
void error_handler_destroy();

#endif