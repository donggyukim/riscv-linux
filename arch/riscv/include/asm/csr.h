#ifndef _ASM_RISCV_CSR_H
#define _ASM_RISCV_CSR_H

#include <linux/const.h>

/* Status register flags */
#define SR_IE   _AC(0x00000001,UL) /* Interrupt Enable */
#define SR_PIE  _AC(0x00000008,UL) /* Previous IE */
#define SR_PS   _AC(0x00000010,UL) /* Previously Supervisor */
#define SR_FS   _AC(0x00003000,UL) /* Floating-point Status */
#define SR_XS   _AC(0x0000C000,UL) /* Extension Status */
#define SR_MPRV _AC(0x00010000,UL) /* Memory Privilege */
#ifndef __riscv64
# define SR_SD  _AC(0x80000000,UL) /* FS/XS dirty */
#else
# define SR_SD  _AC(0x8000000000000000,UL) /* FS/XS dirty */
#endif

/* Interrupt Enable and Interrupt Pending flags */
#define SIE_SSIE _AC(0x00000002,UL) /* Software Interrupt Enable */
#define SIE_STIE _AC(0x00000020,UL) /* Timer Interrupt Enable */

#define EXC_INST_MISALIGNED     0
#define EXC_INST_ACCESS         1
#define EXC_BREAKPOINT          3
#define EXC_LOAD_ACCESS         5
#define EXC_STORE_ACCESS        7
#define EXC_SYSCALL             8

#ifndef __ASSEMBLY__

#define CSR_ZIMM(val) \
	(__builtin_constant_p(val) && ((unsigned long)(val) < 0x20))

#define csr_swap(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(__v)) { 					\
		__asm__ __volatile__ (				\
			"csrrw %0, " #csr ", %1"		\
			: "=r" (__v) : "i" (__v));		\
	} else {						\
		__asm__ __volatile__ (				\
			"csrrw %0, " #csr ", %1"		\
			: "=r" (__v) : "r" (__v));		\
	}							\
	__v;							\
})

#define csr_read(csr)						\
({								\
	register unsigned long __v;				\
	__asm__ __volatile__ (					\
		"csrr %0, " #csr : "=r" (__v));			\
	__v;							\
})

#define csr_write(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(__v)) {					\
		__asm__ __volatile__ (				\
			"csrw " #csr ", %0" : : "i" (__v));	\
	} else {						\
		__asm__ __volatile__ (				\
			"csrw " #csr ", %0" : : "r" (__v));	\
	}							\
})

#define csr_read_set(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(val)) {					\
		__asm__ __volatile__ (				\
			"csrrs %0, " #csr ", %1"		\
			: "=r" (__v) : "i" (__v));		\
	} else {						\
		__asm__ __volatile__ (				\
			"csrrs %0, " #csr ", %1"		\
			: "=r" (__v) : "r" (__v));		\
	}							\
	__v;							\
})

#define csr_set(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(__v)) {					\
		__asm__ __volatile__ (				\
			"csrs " #csr ", %0" : : "i" (__v));	\
	} else {						\
		__asm__ __volatile__ (				\
			"csrs " #csr ", %0" : : "r" (__v));	\
	}							\
})

#define csr_read_clear(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(__v)) {					\
		__asm__ __volatile__ (				\
			"csrrc %0, " #csr ", %1"		\
			: "=r" (__v) : "i" (__v));		\
	} else {						\
		__asm__ __volatile__ (				\
			"csrrc %0, " #csr ", %1"		\
			: "=r" (__v) : "r" (__v));		\
	}							\
	__v;							\
})

#define csr_clear(csr,val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	if (CSR_ZIMM(__v)) {					\
		__asm__ __volatile__ (				\
			"csrc " #csr ", %0" : : "i" (__v));	\
	} else {						\
		__asm__ __volatile__ (				\
			"csrc " #csr ", %0" : : "r" (__v));	\
	}							\
})

#endif /* __ASSEMBLY__ */

#endif /* _ASM_RISCV_CSR_H */
