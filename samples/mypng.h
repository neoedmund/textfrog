// mypng.h
typedef struct PngEnv {
	int w , h ;
	FILE * fp ;
	png_struct * png ;
	png_info * info ;
} PngEnv ;

API int write_png ( const char * filename , int width , int height , const uint8_t * data ) ;
API int read_png_gray_info ( PngEnv * env , const char * filename ) ;
API int read_png_gray_data ( PngEnv * env , const char * buf , int bufsize ) ;


