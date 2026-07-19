#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Link directly to our compiler engine pipeline
void compile_file(const char *source_code, const char *output_binary);

int main(int argc, char **argv) {
    if (argc < 2) {
        write(2, "Usage: wsmc <input_file.wsm>\n", 29);
        return 1;
    }

    const char *input_filename = argv[1];
    
    // Raw system call file interface (No standard library fopen/fread bloat)
    int fd = open(input_filename, O_RDONLY);
    if (fd < 0) {
        write(2, "[FATAL ERROR] Unable to locate target source file\n", 50);
        return 1;
    }

    // Allocate stack buffer memory for the raw source stream code
    char source_buffer[4096];
    int bytes_read = read(fd, source_buffer, 4095);
    if (bytes_read < 0) {
        write(2, "[FATAL ERROR] Internal read error from input file stream\n", 57);
        close(fd);
        return 1;
    }
    source_buffer[bytes_read] = '\0'; // Hard string termination
    close(fd);

    write(1, "[SYSTEM] Source file loaded successfully into memory stream\n", 60);

    // Trigger the actual native machine code construction sequence
    compile_file(source_buffer, "output.bin");

    return 0;
}
