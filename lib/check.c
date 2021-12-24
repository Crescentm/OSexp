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
#define CRC_LOC 0x80

PUBLIC int check(char *filename, int pos, int byteCount) {
    int hFile;
    unsigned char buf[50000];

    hFile = open(filename, O_RDWR);
    if (hFile < 0) {
        hFile = open(filename, O_CREAT | O_RDWR);
    }

    printf("hFile = %d, filename = %s, position = %d, size = %d\n", hFile, filename, pos, byteCount);

    if (hFile < 0) {
        printf("fail to check\n");
        return hFile;
    }
    read(hFile,buf,byteCount);
    unsigned int checksum=0;

    char *data = (char *)buf;
    for (int i = 0; i < byteCount; i++) {
        if (i == CRC_LOC) {
            data++;
            continue;
        }
        checksum ^= *data++;
        for (int j = 0; j < 8; j++) {
            if (checksum & 1) {
                checksum = (checksum>>1)^0x8c;
            }else {
                checksum >>= 1;
            }
        }
        
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