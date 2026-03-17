#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("Usage: %s <VAS_MB> <PageSize_KB> <VirtualAddress>\n",argv[0]);
        return 1;
    }

    long long vas = atof(argv[1]) * 1024 * 1024;
    long long page_size = atof(argv[2]) * 1024;
    long long vaddr = atoll(argv[3]);

    int total_pages = vas / page_size;
    int page_table[100];

    for(int i=0;i<total_pages;i++)
        page_table[i] = -1;

    printf("Enter frame numbers for first 10 pages:\n");
    for(int i=0;i<10 && i<total_pages;i++)
        scanf("%d",&page_table[i]);

    int vpn = vaddr / page_size;
    int offset = vaddr % page_size;

    if(vpn>=total_pages || page_table[vpn]==-1)
        printf("PAGE TABLE MISS\n");
    else
        printf("<%d,%d>\n",page_table[vpn],offset);

    return 0;
}
