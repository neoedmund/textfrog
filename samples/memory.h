// for textfrog
typedef long pid_t ;
typedef long ssize_t ;
typedef long size_t ;

typedef struct iovec {
	void * iov_base ;
	/* Starting address */
	size_t iov_len ;
	/* Number of bytes to transfer */
} iovec ;

struct user_fpregs_struct {
	unsigned short cwd ;
	unsigned short swd ;
	unsigned short ftw ;
	unsigned short fop ;
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

typedef struct user_regs_struct {
	unsigned long long int r15 ;
	unsigned long long int r14 ;
	unsigned long long int r13 ;
	unsigned long long int r12 ;
	unsigned long long int rbp ;
	unsigned long long int rbx ;
	unsigned long long int r11 ;
	unsigned long long int r10 ;
	unsigned long long int r9 ;
	unsigned long long int r8 ;
	unsigned long long int rax ;
	unsigned long long int rcx ;
	unsigned long long int rdx ;
	unsigned long long int rsi ;
	unsigned long long int rdi ;
	unsigned long long int orig_rax ;
	unsigned long long int rip ;
	unsigned long long int cs ;
	unsigned long long int eflags ;
	unsigned long long int rsp ;
	unsigned long long int ss ;
	unsigned long long int fs_base ;
	unsigned long long int gs_base ;
	unsigned long long int ds ;
	unsigned long long int es ;
	unsigned long long int fs ;
	unsigned long long int gs ;
} user_regs_struct ;

API ssize_t process_vm_readv ( pid_t pid ,
	const struct iovec * local_iov ,
	unsigned long liovcnt ,
	const struct iovec * remote_iov ,
	unsigned long riovcnt ,
	unsigned long flags ) ;
API ssize_t process_vm_writev ( pid_t pid ,
	const struct iovec * local_iov ,
	unsigned long liovcnt ,
	const struct iovec * remote_iov ,
	unsigned long riovcnt ,
	unsigned long flags ) ;


#define __WALL		0x40000000 /* Wait for any child.  */

enum __ptrace_request {
	/* Indicate that the process making this request should be traced.
     All signals received by this process can be intercepted by its
     parent, and its parent can use the other `ptrace' requests.  */
	PTRACE_TRACEME = 0 ,

	/* Return the word in the process's text space at address ADDR.  */
	PTRACE_PEEKTEXT = 1 ,

	/* Return the word in the process's data space at address ADDR.  */
	PTRACE_PEEKDATA = 2 ,

	/* Return the word in the process's user area at offset ADDR.  */
	PTRACE_PEEKUSER = 3 ,

	/* Write the word DATA into the process's text space at address ADDR.  */
	PTRACE_POKETEXT = 4 ,

	/* Write the word DATA into the process's data space at address ADDR.  */
	PTRACE_POKEDATA = 5 ,

	/* Write the word DATA into the process's user area at offset ADDR.  */
	PTRACE_POKEUSER = 6 ,

	/* Continue the process.  */
	PTRACE_CONT = 7 ,

	/* Kill the process.  */
	PTRACE_KILL = 8 ,

	/* Single step the process.  */
	PTRACE_SINGLESTEP = 9 ,

	/* Get all general purpose registers used by a processes.  */
	PTRACE_GETREGS = 12 ,

	/* Set all general purpose registers used by a processes.  */
	PTRACE_SETREGS = 13 ,

	/* Get all floating point registers used by a processes.  */
	PTRACE_GETFPREGS = 14 ,

	/* Set all floating point registers used by a processes.  */
	PTRACE_SETFPREGS = 15 ,

	/* Attach to a process that is already running. */
	PTRACE_ATTACH = 16 ,

	/* Detach from a process attached to with PTRACE_ATTACH.  */
	PTRACE_DETACH = 17 ,

	/* Get all extended floating point registers used by a processes.  */
	PTRACE_GETFPXREGS = 18 ,

	/* Set all extended floating point registers used by a processes.  */
	PTRACE_SETFPXREGS = 19 ,

	/* Continue and stop at the next entry to or return from syscall.  */
	PTRACE_SYSCALL = 24 ,

	/* Get a TLS entry in the GDT.  */
	PTRACE_GET_THREAD_AREA = 25 ,

	/* Change a TLS entry in the GDT.  */
	PTRACE_SET_THREAD_AREA = 26 ,

	PTRACE_ARCH_PRCTL = 30 ,

	/* Continue and stop at the next syscall, it will not be executed.  */
	PTRACE_SYSEMU = 31 ,

	/* Single step the process, the next syscall will not be executed.  */
	PTRACE_SYSEMU_SINGLESTEP = 32 ,

	/* Execute process until next taken branch.  */
	PTRACE_SINGLEBLOCK = 33 ,

	/* Set ptrace filter options.  */
	PTRACE_SETOPTIONS = 0x4200 ,

	/* Get last ptrace message.  */
	PTRACE_GETEVENTMSG = 0x4201 ,

	/* Get siginfo for process.  */
	PTRACE_GETSIGINFO = 0x4202 ,

	/* Set new siginfo for process.  */
	PTRACE_SETSIGINFO = 0x4203 ,

	/* Get register content.  */
	PTRACE_GETREGSET = 0x4204 ,

	/* Set register content.  */
	PTRACE_SETREGSET = 0x4205 ,

	/* Like PTRACE_ATTACH, but do not force tracee to trap and do not affect
     signal or group stop state.  */
	PTRACE_SEIZE = 0x4206 ,

	/* Trap seized tracee.  */
	PTRACE_INTERRUPT = 0x4207 ,

	/* Wait for next group event.  */
	PTRACE_LISTEN = 0x4208 ,

	/* Retrieve siginfo_t structures without removing signals from a queue.  */
	PTRACE_PEEKSIGINFO = 0x4209 ,

	/* Get the mask of blocked signals.  */
	PTRACE_GETSIGMASK = 0x420a ,

	/* Change the mask of blocked signals.  */
	PTRACE_SETSIGMASK = 0x420b ,

	/* Get seccomp BPF filters.  */
	PTRACE_SECCOMP_GET_FILTER = 0x420c ,

	/* Get seccomp BPF filter metadata.  */
	PTRACE_SECCOMP_GET_METADATA = 0x420d ,

	/* Get information about system call.  */
	PTRACE_GET_SYSCALL_INFO = 0x420e
} ;

enum __ptrace_setoptions {
	PTRACE_O_TRACESYSGOOD = 0x00000001 ,
	PTRACE_O_TRACEFORK = 0x00000002 ,
	PTRACE_O_TRACEVFORK = 0x00000004 ,
	PTRACE_O_TRACECLONE = 0x00000008 ,
	PTRACE_O_TRACEEXEC = 0x00000010 ,
	PTRACE_O_TRACEVFORKDONE = 0x00000020 ,
	PTRACE_O_TRACEEXIT = 0x00000040 ,
	PTRACE_O_TRACESECCOMP = 0x00000080 ,
	PTRACE_O_EXITKILL = 0x00100000 ,
	PTRACE_O_SUSPEND_SECCOMP = 0x00200000 ,
	PTRACE_O_MASK = 0x003000ff
} ;

API long ptrace ( /*enum __ptrace_request*/ int request , pid_t pid , void * addr , void * data ) ;
API pid_t wait ( int * wstatus ) ;
API pid_t waitpid ( pid_t pid , int * wstatus , int options ) ;

