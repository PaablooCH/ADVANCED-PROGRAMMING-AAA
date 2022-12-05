#pragma once
#include "Globals.h"

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf(tmp_string, format, ap);
	va_end(ap);
	sprintf(tmp_string2, "\n%s(%d) : %s", file, line, tmp_string);
	OutputDebugString(tmp_string2);
}