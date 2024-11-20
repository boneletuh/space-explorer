#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

float rand_float(void) {
    float r = (float)rand()/(float)RAND_MAX;
    r = (r-0.5)*2*(float)RAND_MAX;
    return r;
}

Color rand_color(void) {
    Color color;
    color.r = rand()&0xff;
    color.g = rand()&0xff;
    color.b = rand()&0xff;
    color.a = 0xff;
    return color;
}

// return a pointer to the contents of the file
// the pointer allocated using malloc() and should be freed after
char * read_file_contents(const char * file) {
    FILE * file_ptr = fopen(file, "rb");
    // get the size of the file
    fseek(file_ptr, 0L, SEEK_END);
    int file_size = ftell(file_ptr);
    rewind(file_ptr);

    char * buffer = malloc(sizeof(char) * (file_size + 1));
    for (int i = 0; !feof(file_ptr); i++) {
		buffer[i] = (char)fgetc(file_ptr);
    }
	buffer[file_size] = '\0';

    fclose(file_ptr);

	return buffer;
}