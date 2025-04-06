

/* by chatgpt, let's compile
gcc -shared -o libmypng.so mypng.c -lpng &&  nm -D libmypng.so
*/

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <png.h>

typedef struct PngEnv {
	int w , h ;
	FILE * fp ;
	png_structp png ;
	png_infop info ;
} PngEnv ;

int write_png ( const char * filename , int width , int height , const uint8_t * data ) {
	FILE * fp = fopen ( filename , "wb" ) ;
	if ( ! fp ) return 0 ;

	png_structp png = png_create_write_struct ( PNG_LIBPNG_VER_STRING , NULL , NULL , NULL ) ;
	if ( ! png ) return 0 ;

	png_infop info = png_create_info_struct ( png ) ;
	if ( ! info ) return 0 ;

	if ( setjmp ( png_jmpbuf ( png ) ) ) return 0 ;

	png_init_io ( png , fp ) ;

	// Set the image information
	png_set_IHDR (
		png ,
		info ,
		width , height ,
		8 , // 8 bits per channel
		PNG_COLOR_TYPE_GRAY ,
		PNG_INTERLACE_NONE ,
		PNG_COMPRESSION_TYPE_DEFAULT ,
		PNG_FILTER_TYPE_DEFAULT
	) ;
	png_write_info ( png , info ) ;

	// Write image data
	for ( int y = 0 ; y < height ; y ++ ) {
		png_write_row ( png , data + y * width ) ;
	}

	// End the writing process
	png_write_end ( png , NULL ) ;
	fclose ( fp ) ;

	if ( png && info )
	png_destroy_write_struct ( & png , & info ) ;
}

int read_png_gray_info ( PngEnv * env , const char * filename ) {
	FILE * fp = fopen ( filename , "rb" ) ;
	if ( ! fp ) return 0 ;

	png_byte header [ 8 ] ; // PNG header is 8 bytes
	fread ( header , 1 , 8 , fp ) ;

	if ( png_sig_cmp ( header , 0 , 8 ) ) {
		fclose ( fp ) ;
		printf ( "Error: %s is not a PNG file\n" , filename ) ;
		return 0 ;
	}

	// Create and initialize the png_struct and png_info structs
	png_structp png = png_create_read_struct ( PNG_LIBPNG_VER_STRING , NULL , NULL , NULL ) ;
	if ( ! png ) return 0 ;

	png_infop info = png_create_info_struct ( png ) ;
	if ( ! info ) return 0 ;

	//	if ( setjmp ( png_jmpbuf ( png ) ) ) return 0 ;
	// Set up the input control
	png_init_io ( png , fp ) ;
	png_set_sig_bytes ( png , 8 ) ; // Skip the header bytes
	// Read the PNG information
	png_read_info ( png , info ) ;

	int width = png_get_image_width ( png , info ) ;
	int height = png_get_image_height ( png , info ) ;
	png_byte color_type = png_get_color_type ( png , info ) ;
	png_byte bit_depth = png_get_bit_depth ( png , info ) ;

	printf ( "Width: %d, Height: %d, Color type: %d, Bit depth: %d\n" , width , height , color_type , bit_depth ) ;
	env -> fp = fp ;
	env -> w = width ;
	env -> h = height ;
	env -> png = png ;
	env -> info = info ;
	return 1 ;
}
int read_png_gray_data ( PngEnv * env , const char * buf , int bufsize ) {
	png_structp png = env -> png ;
	png_infop info = env -> info ;
	FILE * fp = env -> fp ;
	int height = env -> h ;

	int sizeR = png_get_rowbytes ( png , info ) ;
	if ( bufsize != sizeR * height ) {
		printf ( "error, not expected bufsize %d vs %d\n" , bufsize , sizeR * height ) ;
		return 0 ;
	}
	png_bytep * row_pointers = ( png_bytep * ) malloc ( sizeof ( png_bytep ) * height ) ;
	for ( int y = 0 ; y < height ; y ++ ) {
		row_pointers [ y ] = ( png_byte * ) ( buf + sizeR * y ) ;
	}

	// Read the image data
	png_read_image ( png , row_pointers ) ;

	// Cleanup
	fclose ( fp ) ;
	free ( row_pointers ) ;

	if ( png && info )
	png_destroy_read_struct ( & png , & info , NULL ) ;

	return 1 ;
}
