#define offsetof(struct_name,field_name) \
    (unsigned int)&((struct_name)0)->field_name