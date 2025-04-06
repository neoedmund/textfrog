/* Utility to test libdisasm. Disassembles from the start of a * file. */
/* Compile with 
gcc  -ldisasm testlibdisasm.c -o testdis.run
*/

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <unistd.h>
# include <libdis.h>

struct user_fpregs_struct {
	unsigned short int cwd ;
	unsigned short int swd ;
	unsigned short int ftw ;
	unsigned short int fop ;
	unsigned long long int rip ;
	unsigned long long int rdp ;
	unsigned int mxcsr ;
	unsigned int mxcr_mask ;
	unsigned int st_space [ 32 ] ;
	/* 8*16 bytes for each FP-reg = 128 bytes */
	unsigned int xmm_space [ 64 ] ;
	/* 16*16 bytes for each XMM-reg = 256 bytes */
	unsigned int padding [ 24 ] ;
} ;

int main ( int argc , char * * argv ) {
	printf ( "x86_reg_t=%d\n" , sizeof ( x86_reg_t ) ) ; //28
	printf ( "x86_insn_t=%d\n" , sizeof ( x86_insn_t ) ) ; //168
	printf ( "enum x86_options=%d\n" , sizeof ( enum x86_options ) ) ; //4
	printf ( "user_fpregs_struct=%d\n" , sizeof ( struct user_fpregs_struct ) ) ; //4
}
