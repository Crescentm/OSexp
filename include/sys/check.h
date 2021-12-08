/* checksum */
#define NR_CHECKFILES   20
struct check {
	char filename[MAX_FILENAME_LEN];
    int byteCount;
    int checkSum;
};
extern int check_count;
extern struct check check_table[NR_CHECKFILES];
extern int check(char *filename, int pos, int byteCount);
extern int find_position(struct check check_table[], char *filename);