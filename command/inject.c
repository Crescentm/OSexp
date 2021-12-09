#include <stdio.h>

int inject(char *filename) {
    char inject_code[] = {
	0x00,0x00,0x00,0x00,0x00
   };
    int old_file = open(filename, O_RDWR);
    lseek(old_file, 0, SEEK_SET);
    write(old_file, inject_code, sizeof(inject_code));
    printf("Finish inject\n");
    close(old_file);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2)
    {
        printf("usage：./inject <elf_filepath>\n");
        exit(0);
    }
    inject(argv[1]);
    return 0;
}