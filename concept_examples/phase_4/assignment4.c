/*
1. 
6095
2.  
-------------------
prev = NULL
next = 2048
-------------------
prev = 2000
next = 2476
-------------------
prev = 2048
next = NULL
-------------------

3.  
-------------------
prev = NULL
next = 2048
-------------------
prev = 2000
next = 2116
-------------------
prev = 2048
next = 2476
-------------------
prev = 2116
next = NULL
-------------------
4.
#define mm_bind_blocks_for_allocation(allocated_meta_block, free_meta_block) \
{/
    free_meta_block->next_block = allocated_meta_block->next;\
    free_meta_block->prev_block = allocated_meta_block;\
    allocated_meta_block->next_block = prev_meta_block;\
    if(free_meta_block->next_block!=NULL){ \
        free_meta_block->next_block->prev_block = free_meta_block;\
    }\
}

5. 
for(block_meta_data_t curr = first_meta_block;curr!=NULL,curr=curr->next_block){
    // code
}
6. 
int num_free_blocks=0,num_allocated_blocks=0;
block_meta_data_t largest_free_block=NULL, largest_allocated_block=NULL;
int largest_free_size=0,largest_allocated_size=0;
int consecutive_free_count=0;
for(block_meta_data_t curr = first_meta_block;curr!=NULL,curr=curr->next_block){
    if(curr->is_free){
        num_free_blocks++;
        consecutive_free_count++;
        if(curr->block_size>largest_free_size){
            largest_free_size = curr->block_size;
            largest_free_block = curr;
        }
    }else{
        num_allocated_blocks++;
        consecutive_free_count=0;
        if(curr->block_size>largest_allocated_size){
            largest_allocated_size = curr->block_size;
            largest_allocated_block = curr;
        }
    }
    if(consecutive_free_count>1){
        printf("Error: consecutive free blocks encountered\n");
        assert(0);
    }
}

*/