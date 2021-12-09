#include "stdio.h"
#include "string.h"
#include "elf.h"

#include "stdio.h"
#include "string.h"
#include "elf.h"

//一页的大小，默认 4K
#define PAGESIZE 4096

// 计算新的地址，如：数据段地址，跳转地址等
void cal_addr(int entry, int addr[]);
// 注入函数
void inject(char *elf_file);
// 插入函数
void insert(Elf32_Ehdr elf_ehdr, int old_file, int old_entry);

// 计算新的地址
void cal_addr(int entry, int addr[])
{
    int temp = entry;
    int i;
    for (i = 0; i < 4; i++)
    {
        addr[i] = temp % 256;
        temp /= 256;
    }
}

// 注入函数
void inject(char *elf_file)
{
    printf("start to inject...\n");
    int old_entry;  // elf 文件的原入口地址

    // ELF Header Table 结构体
    Elf32_Ehdr elf_ehdr;
    // Program Header Table 结构体
    Elf32_Phdr elf_phdr;

    // 打开文件并读取ELF头信息到 elf_ehdr 上
    int old_file = open(elf_file, O_RDWR);	
    read(old_file, &elf_ehdr, sizeof(elf_ehdr));


    old_entry = elf_ehdr.e_entry;

    // 节区头部表格的偏移量增加一页
    elf_ehdr.e_shoff += PAGESIZE;

    int i = 0;

    printf("Modifying the program header table...\n");
    // 读取并修改程序头部表
    lseek(old_file, elf_ehdr.e_phoff + i * elf_ehdr.e_phentsize, SEEK_SET);
    read(old_file, &elf_phdr, sizeof(elf_phdr));
    
    printf("Inserting the injector...\n");
    // 插入注入程序
    insert(elf_ehdr, old_file, old_entry);
}

// 插入
void insert(Elf32_Ehdr elf_ehdr, int old_file, int old_entry)
{
    // 程序的原始入口地址
    int old_entry_addr[4];
    cal_addr(old_entry, old_entry_addr);

    // 数据段的地址, 45为数组中程序数据段的相对位置
	//printf("old_entry = 0x%x%x%x%x\n", old_entry_addr[3],old_entry_addr[2],old_entry_addr[1],old_entry_addr[0]);
    // 每一行对应一条汇编代码
    char inject_code[] = {
	0xc7, 0x04, 0x24, 0xf8, 0x17, 0x00, 0x00
   };
    int inject_size = sizeof(inject_code);

    // 防止注入代码太大
    if (inject_size > PAGESIZE)
    {
        printf("Injecting code is too big!\n");
        exit(0);
    }
	int filelen= lseek(old_file,0L,SEEK_END);  
	lseek(old_file,0L,SEEK_SET);  
	printf("[file size is %dB]\n",filelen);  

    // 插入注入代码到原 elf 文件中
    lseek(old_file, 0x1015, SEEK_SET);
    write(old_file, inject_code, inject_size);

    printf("Finished!\n");
}

int main(int argc, char **argv)
{
    //检查参数数量是否正确
    if (argc != 2)
    {
        printf("缺少 elf 文件参数，格式：./main <elf_filepath>\n");
        exit(0);
    }
    inject(argv[1]);
    return 0;
}
