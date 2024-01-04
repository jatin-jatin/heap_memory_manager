#include<stdint.h>
#define MM_MAX_STRUCT_NAME 64

typedef struct vm_page_family_{
    char struct_name[MM_MAX_STRUCT_NAME];
    uint32_t struct_size;
}vm_page_family_t;

typedef struct vm_page_for_families_{

    struct  vm_page_for_families_ *next;
    vm_page_family_t vm_page_family[0];
}vm_page_for_families_t;

#define MAX_FAMILIES_PER_VM_PAGE    \
    (SYSTEM_PAGE_SIZE- sizeof(vm_page_for_families_t*))/sizeof(vm_page_family_t)

#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr,curr) \
{\
    uint32_t count=0;\
    for(curr = (vm_page_family_t*)&vm_page_for_families_ptr->vm_page_family[0];\
     curr->struct_size!=0 && count<MAX_FAMILIES_PER_VM_PAGE;curr++,count++){
# define ITERATE_PAGE_FAMILIES_END }}

vm_page_family_t *
lookup_page_family_by_name (char *struct_name);

typedef enum{
    MM_FALSE,
    MM_TRUE
} vm_bool_t;


typedef struct block_meta_data_{
    vm_bool_t is_free;
    uint32_t block_size;
    uint32_t offset;    /*offset from the start of the page*/
    struct block_meta_data_ *prev_block;
    struct block_meta_data_ *next_block;
} block_meta_data_t;

