#ifndef __ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

/* Architecture-specific global data */
struct arch_global_data {
};

#include <asm-generic/global_data.h>

#define DECLARE_GLOBAL_DATA_PTR	register volatile gd_t *gd asm ("$r10")

#endif /* __ASM_GBL_DATA_H */
