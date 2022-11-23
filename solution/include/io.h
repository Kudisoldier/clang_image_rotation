#pragma once

#include <stdio.h>
#include <stdlib.h>

void print_err(const char* msg);
FILE* file_open_rb(const char* path);
FILE* file_open_wb(const char* path);
void file_close(FILE* fp);
