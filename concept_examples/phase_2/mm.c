#include<stdio.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>
#include"mm.h"
#include<assert.h>

static size_t SYSTEM_PAGE_SIZE = 0;

void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();
}

static void* mm_get_new_vm_from_kernel(int units){
    char *vm_page = mmap(
        0,
        units*SYSTEM_PAGE_SIZE,
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE,
        0,0);
    if(vm_page==MAP_FAILED){
        printf("Error : VM page allocation Failed\n"); 
        return NULL;
    }
    memset(vm_page,0,units*SYSTEM_PAGE_SIZE);
    return (void*)vm_page;
}

static void mm_return_vm_page_to_kernel(void *vm_page,int units){
    if(munmap(vm_page,units*SYSTEM_PAGE_SIZE)){
        printf("Error : Could not munmap VM page to kernel\n");
    }
}


static vm_page_for_families_t *first_vm_page_for_families = NULL;
// static uint32_t max_capacity = MAX_FAMILIES_PER_VM_PAGE; this does not work because the right side is not constant
// static uint32_t vm_page_allocated_num_entries=0;

// void mm_instantiate_new_page_family(char*struct_name,uint32_t struct_size){
//     if(first_vm_page_for_families==NULL || vm_page_allocated_num_entries==MAX_FAMILIES_PER_VM_PAGE){
//         vm_page_for_families_t*second = first_vm_page_for_families;
//         first_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_from_kernel(1);
//         first_vm_page_for_families->next=second;
//         vm_page_allocated_num_entries=0;
//     }
//     strcpy(first_vm_page_for_families->vm_page_family[vm_page_allocated_num_entries].struct_name,struct_name);
//     first_vm_page_for_families->vm_page_family[vm_page_allocated_num_entries].struct_size=struct_size;
//     vm_page_allocated_num_entries++;
// }


void mm_instantiate_new_page_family(char*struct_name,uint32_t struct_size){
    vm_page_family_t *vm_page_family_curr = NULL;
    vm_page_for_families_t *new_vm_page_for_families= NULL;
    if(struct_size > SYSTEM_PAGE_SIZE){
        printf("Error : %s() Structure %s size exceeds system page size\n",__FUNCTION__,struct_name);
        return ;
    }
    if(!first_vm_page_for_families){
        first_vm_page_for_families = (vm_page_for_families_t*)mm_get_new_vm_from_kernel(1);
        first_vm_page_for_families->next =NULL;
        strncpy(first_vm_page_for_families->vm_page_family[0].struct_name,struct_name,MM_MAX_STRUCT_NAME);
        first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
        return ;
    }
    uint32_t count = 0;
    ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families,vm_page_family_curr){
        if(strncmp(vm_page_family_curr->struct_name,struct_name,MM_MAX_STRUCT_NAME) != 0){
            count++;
            continue;
        }
        assert(0);
    }ITERATE_PAGE_FAMILIES_END;
    if(count == MAX_FAMILIES_PER_VM_PAGE){
        new_vm_page_for_families = (vm_page_for_families_t *)mm_get_new_vm_from_kernel(1);
        new_vm_page_for_families->next = first_vm_page_for_families;
        first_vm_page_for_families = new_vm_page_for_families;
        vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
    }
    strncpy(vm_page_family_curr->struct_name,struct_name,MM_MAX_STRUCT_NAME);
    vm_page_family_curr->struct_size = struct_size;
}


void mm_print_registered_page_families (){
    vm_page_for_families_t *iter_vm_page_for_families= first_vm_page_for_families;
    while(iter_vm_page_for_families!=NULL){
        vm_page_family_t *curr;
        for(int count=0;count<MAX_FAMILIES_PER_VM_PAGE;count++){
            if(iter_vm_page_for_families->vm_page_family[count].struct_size==0)break;
            curr = &iter_vm_page_for_families->vm_page_family[count]; 
            printf("Page Family:%s,%d\n",curr->struct_name,curr->struct_size);
        }
        iter_vm_page_for_families=iter_vm_page_for_families->next;
    }
}

vm_page_family_t *
lookup_page_family_by_name (char *struct_name){
    vm_page_for_families_t *iter_vm_page_for_families= first_vm_page_for_families;
    vm_page_family_t* res = NULL;
    while(iter_vm_page_for_families!=NULL){
        vm_page_family_t *curr;
        for(int count=0;count<MAX_FAMILIES_PER_VM_PAGE;count++){
            if(iter_vm_page_for_families->vm_page_family[count].struct_size==0)break;
            curr = &iter_vm_page_for_families->vm_page_family[count]; 
            if(strncmp(struct_name,curr->struct_name,MM_MAX_STRUCT_NAME)==0){
                res = curr;
                break;
            }
        }
        if(res) break;
        iter_vm_page_for_families=iter_vm_page_for_families->next;
    }

    return res;

}


