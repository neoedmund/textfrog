/* Utility to test libdisasm. Disassembles from the start of a * file. */
/* Compile with 
gcc  -lZydis testzydis.c -I/usr/local/include  -o testzydis.run
*/

# include <stdio.h>
# include <inttypes.h>
# include <Zydis/Zydis.h>

int main ( int argc , char * * argv ) {
	printf ( "ZydisDecodedInstructionAvx=%d\n" , sizeof ( ZydisDecodedInstructionAvx ) ) ; // 
	printf ( "ZydisDecodedInstructionMeta=%d\n" , sizeof ( ZydisDecodedInstructionMeta ) ) ; // 
	printf ( "ZydisDecodedInstructionRaw=%d\n" , sizeof ( ZydisDecodedInstructionRaw ) ) ; //
	printf ( "ZydisDecodedInstruction=%d\n" , sizeof ( ZydisDecodedInstruction ) ) ; // 
	printf ( "ZydisDecodedOperand=%d\n" , sizeof ( ZydisDecodedOperand ) ) ; // 
	printf ( "ZydisDisassembledInstruction=%d\n" , sizeof ( ZydisDisassembledInstruction ) ) ; // 
	/*
ZydisDecodedInstructionAvx=36
ZydisDecodedInstructionMeta=20
ZydisDecodedInstructionRaw=216
ZydisDecodedInstruction=328
ZydisDecodedOperand=80
ZydisDisassembledInstruction=1232
	*/
}

