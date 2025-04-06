extern DECLSPEC int getpid ( void ) ;
extern DECLSPEC int kill ( int pid , int sig ) ;
extern DECLSPEC void * memcpy ( void * dest , const void * src , size_t n ) ;
extern DECLSPEC void * memset ( void * s , int c , size_t n ) ;
extern DECLSPEC void * malloc ( size_t size ) ;
extern DECLSPEC void free ( void * ptr ) ;
extern DECLSPEC size_t read ( int fd , void * buf , size_t count ) ;
extern DECLSPEC int system ( const char * command ) ;
extern DECLSPEC int chdir ( const char * path ) ;
extern DECLSPEC int reboot ( int cmd ) ;

# define O_RDONLY 00
# define O_WRONLY 01
# define O_RDWR 02

extern DECLSPEC long lseek ( int fd , long offset , int whence ) ;
extern DECLSPEC int open ( const char * pathname , int flags ) ;
extern DECLSPEC long write ( int fd , const void * buf , size_t count ) ;
extern DECLSPEC int close ( int fd ) ;

