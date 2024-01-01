#define ITERATE_LIST_BEGIN(list_ptr,node_ptr) \
{ \
    dll_node_t *_node_ptr = NULL \
    node_ptr = list_ptr->head; \
    for(;node_ptr!=NULL;node_ptr=_node_ptr){ \
    _node_ptr = node_ptr->right;


#define ITERATE_LIST_END }}

// The above defined macros are really useful for ensuring correct iterations over linked list
// This is a good example of code reusability