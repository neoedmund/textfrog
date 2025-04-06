
typedef struct tomem_entry_s {
	char * fn ;
	size_t size ;
	size_t off ;
	struct tomem_entry_s * next ;
} tomem_entry ;


EXPORT_API  int tomem_main ( char * tarfn , tomem_entry * * entries , void * * targetBuf ) ;

