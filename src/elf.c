#include <unistd.h>
#include <fcntl.h>

// Minimal ELF64 Structure Specifications
typedef struct {
    unsigned char e_ident[16];
    unsigned short e_type;
    unsigned short e_machine;
    unsigned int e_version;
    unsigned long e_entry;
    unsigned long e_phoff;
    unsigned long e_shoff;
    unsigned int e_flags;
    unsigned short e_ehsize;
    unsigned short e_phentsize;
    unsigned short e_phnum;
    unsigned short e_shentsize;
    unsigned short e_shnum;
    unsigned short e_shstrndx;
} Elf64_Ehdr;

typedef struct {
    unsigned int p_type;
    unsigned int p_flags;
    unsigned long p_offset;
    unsigned long p_vaddr;
    unsigned long p_paddr;
    unsigned long p_filesz;
    unsigned long p_memsz;
    unsigned long p_align;
} Elf64_Phdr;

void write_elf_binary(const char *filename, unsigned char *machine_code, int code_size) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (fd < 0) {
        write(2, "[ELF ERROR] Failed to create output binary file\n", 48);
        return;
    }

    Elf64_Ehdr ehdr = {
        .e_ident = {0x7f, 'E', 'L', 'F', 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // ELF64 Magic
        .e_type = 2,        // ET_EXEC (Executable file)
        .e_machine = 62,    // EM_X86_64 (AMD x86-64 architecture)
        .e_version = 1,
        .e_entry = 0x400080, // Virtual address memory entry point
        .e_phoff = sizeof(Elf64_Ehdr),
        .e_shoff = 0,
        .e_flags = 0,
        .e_ehsize = sizeof(Elf64_Ehdr),
        .e_phentsize = sizeof(Elf64_Phdr),
        .e_phnum = 1,       // Single program header loop entry
        .e_shentsize = 0,
        .e_shnum = 0,
        .e_shstrndx = 0
    };

    Elf64_Phdr phdr = {
        .p_type = 1,        // PT_LOAD (Loadable segment)
        .p_flags = 5,        // PF_R | PF_X (Readable and Executable permissions)
        .p_offset = 0,
        .p_vaddr = 0x400000,
        .p_paddr = 0x400000,
        .p_filesz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + code_size,
        .p_memsz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + code_size,
        .p_align = 0x1000
    };

    // Recalculate entry based on structural header sizes
    ehdr.e_entry = phdr.p_vaddr + sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr);

    write(fd, &ehdr, sizeof(ehdr));
    write(fd, &phdr, sizeof(phdr));
    write(fd, machine_code, code_size);
    close(fd);
    
    write(1, "[ELF] Native Linux compilation completed successfully\n", 54);
}
