#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    // 1. Validate Command Line Arguments
    if (argc != 4) {
        printf("Usage: %s <VAS_MB> <PageSize_KB> <VirtualAddress>\n", argv[0]);
        return 1;
    }

    // 2. Parse Arguments
    double vspace_mb = atof(argv[1]);
    double page_kb = atof(argv[2]);
    unsigned long long virtual_address = strtoull(argv[3], NULL, 10);

    // 3. Conversions
    unsigned long long page_size_bytes = (unsigned long long)(page_kb * 1024);
    unsigned long long vspace_bytes = (unsigned long long)(vspace_mb * 1024 * 1024);
    unsigned int total_pages = (unsigned int)(vspace_bytes / page_size_bytes);

    // 4. Initialize Page Table
    int *page_table = (int *)malloc(total_pages * sizeof(int));
    for (unsigned int i = 0; i < total_pages; i++) {
        page_table[i] = -1; 
    }

    int entries_to_fill = (total_pages < 10) ? total_pages : 10;
    printf("--- Initializing Page Table (First %d entries) ---\n", entries_to_fill);
    for (int i = 0; i < entries_to_fill; i++) {
        printf("Enter Frame Number for Page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    // 5. Address Translation Logic
    if (virtual_address >= vspace_bytes) {
        printf("\nError: Virtual Address %llu is out of bounds (Max: %llu).\n", virtual_address, vspace_bytes - 1);
        free(page_table);
        return 1;
    }

    unsigned int vpn = (unsigned int)(virtual_address / page_size_bytes);
    unsigned int offset = (unsigned int)(virtual_address % page_size_bytes);

    // 6. Final Output
    printf("\n--- Translation Result ---\n");
    if (vpn >= total_pages || page_table[vpn] == -1) {
        printf("Result: PAGE TABLE MISS!\n");
    } else {
        int pfn = page_table[vpn];
        
        // Calculate Physical Address: (Frame * PageSize) + Offset
        unsigned long long physical_address = ((unsigned long long)pfn * page_size_bytes) + offset;

        printf("Format:           <%d, %u>\n", pfn, offset);
        printf("Physical Address: %llu\n", physical_address);
        printf("Calculation:      (%d * %llu) + %u = %llu\n", pfn, page_size_bytes, offset, physical_address);
    }

    free(page_table);
    return 0;
}
