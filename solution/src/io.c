#include "io.h"

void print_err(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

FILE* file_open_rb(const char* path) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) print_err("Cannot open file to read");
    return fp;
}

FILE* file_open_wb(const char* path) {
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) print_err("Cannot open file to write");
    return fp;
}

void file_close(FILE* fp) {
    if (fclose(fp)) print_err("Cannot close file");
}
