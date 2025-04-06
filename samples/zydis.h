

/**
 * Defines the `ZydisMachineMode` enum.
 */
typedef enum ZydisMachineMode {
	/**
     * 64 bit mode.
     */
	ZYDIS_MACHINE_MODE_LONG_64 ,
	/**
     * 32 bit protected mode.
     */
	ZYDIS_MACHINE_MODE_LONG_COMPAT_32 ,
	/**
     * 16 bit protected mode.
     */
	ZYDIS_MACHINE_MODE_LONG_COMPAT_16 ,
	/**
     * 32 bit protected mode.
     */
	ZYDIS_MACHINE_MODE_LEGACY_32 ,
	/**
     * 16 bit protected mode.
     */
	ZYDIS_MACHINE_MODE_LEGACY_16 ,
	/**
     * 16 bit real mode.
     */
	ZYDIS_MACHINE_MODE_REAL_16

	/**
     * Maximum value of this enum.
     */
	//  ZYDIS_MACHINE_MODE_MAX_VALUE = ZYDIS_MACHINE_MODE_REAL_16,
	/**
     * The minimum number of bits required to represent all values of this enum.
     */
	//  ZYDIS_MACHINE_MODE_REQUIRED_BITS = ZYAN_BITS_TO_REPRESENT(ZYDIS_MACHINE_MODE_MAX_VALUE)
} ZydisMachineMode ;

struct ZydisDecodedInstructionAvx { //TODO just size
	char data [ 28 ] ;
	long x ;
} ;
struct ZydisDecodedInstructionMeta { //TODO just size
	char data [ 12 ] ;
	long x ;
} ;
struct ZydisDecodedInstructionRaw { //TODO just size
	char data [ 216 ] ;
} ;

/**
 * Information about a decoded instruction.
 */
typedef struct ZydisDecodedInstruction {
	/**
     * The machine mode used to decode this instruction.
     */
	ZydisMachineMode machine_mode ;
	/**
     * The instruction-mnemonic.
     */
	enum ZydisMnemonic mnemonic ;
	/**
     * The length of the decoded instruction.
     */
	ZyanU8 length ;
	/**
     * The instruction-encoding (`LEGACY`, `3DNOW`, `VEX`, `EVEX`, `XOP`).
     */
	enum ZydisInstructionEncoding encoding ;
	/**
     * The opcode-map.
     */
	enum ZydisOpcodeMap opcode_map ;
	/**
     * The instruction-opcode.
     */
	ZyanU8 opcode ;
	/**
     * The stack width.
     */
	ZyanU8 stack_width ;
	/**
     * The effective operand width.
     */
	ZyanU8 operand_width ;
	/**
     * The effective address width.
     */
	ZyanU8 address_width ;
	/**
     * The number of instruction-operands.
     *
     * Explicit and implicit operands are guaranteed to be in the front and ordered as they are
     * printed by the formatter in `Intel` mode. No assumptions can be made about the order of
     * hidden operands, except that they always located behind the explicit and implicit operands.
     */
	ZyanU8 operand_count ;
	/**
     * The number of explicit (visible) instruction-operands.
     *
     * Explicit and implicit operands are guaranteed to be in the front and ordered as they are
     * printed by the formatter in `Intel` mode.
     */
	ZyanU8 operand_count_visible ;
	/**
     * See @ref instruction_attributes.
     */
	long attributes ;
	/**
     * Information about CPU flags accessed by the instruction.
     *
     * The bits in the masks correspond to the actual bits in the `FLAGS/EFLAGS/RFLAGS`
     * register. See @ref decoder_cpu_flags.
     */
	const ZydisAccessedFlags * cpu_flags ;
	/**
     * Information about FPU flags accessed by the instruction.
     * 
     * See @ref decoder_fpu_flags.
     */
	const ZydisAccessedFlags * fpu_flags ;
	/**
     * Extended info for `AVX` instructions.
     */
	ZydisDecodedInstructionAvx avx ; //TODO
	/**
     * Meta info.
     */
	ZydisDecodedInstructionMeta meta ; //TODO
	/**
     * Detailed info about different instruction-parts like `ModRM`, `SIB` or
     * encoding-prefixes.
     */
	ZydisDecodedInstructionRaw raw ; //TODO
} ZydisDecodedInstruction ;

# define ZYDIS_MAX_OPERAND_COUNT 10 // TODO: Auto generate
/**
 * All commonly used information about a decoded instruction that Zydis can provide.
 *
 * This structure is filled in by calling `ZydisDisassembleIntel` or `ZydisDisassembleATT`.
 */
typedef struct ZydisDisassembledInstruction {
	/**
     * The runtime address that was passed when disassembling the instruction.
     */
	ZyanU64 runtime_address ;
	/**
     * General information about the decoded instruction in machine-readable format.
     */
	ZydisDecodedInstruction info ;
	/**
     * The operands of the decoded instruction in a machine-readable format.
     *
     * The amount of actual operands can be determined by inspecting the corresponding fields
     * in the `info` member of this struct. Inspect `operand_count_visible` if you care about
     * visible operands (those that are printed by the formatter) or `operand_count` if you're
     * also interested in implicit operands (for example the registers implicitly accessed by
     * `pushad`). Unused entries are zeroed.
     */
	//ZydisDecodedOperand operands [ ZYDIS_MAX_OPERAND_COUNT ] ; //TODO not used, only need size
	char operands [ 800 ] ;
	/**
     * The textual, human-readable representation of the instruction.
     *
     * Guaranteed to be zero-terminated.
     */
	char text [ 96 ] ;
} ZydisDisassembledInstruction ;

typedef ZyanU32 ZyanStatus ;

ZYDIS_EXPORT ZyanStatus ZydisDisassembleIntel ( ZydisMachineMode machine_mode ,
	long runtime_address , const void * buffer , long length ,
	ZydisDisassembledInstruction * instruction ) ;

