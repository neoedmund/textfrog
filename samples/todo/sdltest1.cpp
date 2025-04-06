# include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_timer.h>
int main ( int argc , char * argv [ ] ) {
	// returns zero on success else non-zero
	if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 ) {
		printf ( "error initializing SDL: %s\n" , SDL_GetError ( ) ) ;
	}

	printf ( "SDL_KeyCode=%d\n" , sizeof ( SDL_KeyCode ) ) ;
	printf ( "SDL_Scancode=%d\n" , sizeof ( SDL_Scancode ) ) ;
	SDL_Window * win = SDL_CreateWindow ( "GAME" , // creates a window
		SDL_WINDOWPOS_CENTERED ,
		SDL_WINDOWPOS_CENTERED ,
		1000 , 1000 , 0 ) ;
	int close = 0 ;
	while ( ! close ) {
		SDL_Event event ;

		// Events management
		while ( SDL_PollEvent ( & event ) ) {
			switch ( event . type ) {
				case SDL_QUIT :
				close = 1 ;
				break ;
				default :
				break ;
			}
		}
	}

	// close SDL
	SDL_Quit ( ) ;

	return 0 ;
}

