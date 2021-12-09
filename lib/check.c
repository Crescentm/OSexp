#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
#include "config.h"
#include "check.h"
#include <stdio.h>

PUBLIC int check(char *filename, int pos, int byteCount) {
    int hFile;

    hFile = open(filename, O_RDWR);
    if (hFile < 0) {
        hFile = open(filename, O_CREAT | O_RDWR);
    }

    printf("hFile = %d, filename = %s, position = %d, size = %d\n", hFile, filename, pos, byteCount);

    if (hFile < 0) {
        printf("fail to check\n");
        return hFile;
    }

    char buf[1];
    unsigned int checksum=0;

    for (int i = 0; i < 100; i++) {
        read(hFile, buf, 1);

        checksum = checksum ^ (unsigned int)buf[0];
    }
    printf("checksum = %d\n",checksum);
    close(hFile);
    return checksum;
}

PUBLIC int find_position(struct check check_table[], char *filename) {
    printf("filenam = %s\n", filename);
    for (int i = 0; i < check_count; i++) {
        if (strcmp(check_table[i].filename, filename) == 0) {
            return i;
        }
    }
    return -1;
}