#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int g(int x)
{
    //   0:	1141                	addi	sp,sp,-16
    //   2:	e422                	sd	    s0,8(sp)
    //   4:	0800                	addi	s0,sp,16
    return x + 3;
}
//   6:	250d                	addiw	a0,a0,3
//   8:	6422                	ld	    s0,8(sp)
//   a:	0141                	addi	sp,sp,16
//   c:	8082                	ret

// 000000000000000e <f>:

int f(int x)
{
    //   e:	1141                	addi	sp,sp,-16
    //  10:	e422                	sd	    s0,8(sp)
    //  12:	0800                	addi	s0,sp,16
    return g(x);
}
//  14:	250d                	addiw	a0,a0,3
//  16:	6422                	ld	    s0,8(sp)
//  18:	0141                	addi	sp,sp,16
//  1a:	8082                	ret

// 000000000000001c <main>:

void main(void)
{
    //  1c:	1141                	addi	sp,sp,-16
    //  1e:	e406                	sd	    ra,8(sp)
    //  20:	e022                	sd	    s0,0(sp)
    //  22:	0800                	addi	s0,sp,16
    printf("%d %d\n", f(8) + 1, 13);
    //  24:	4635                	li	    a2,13       # argument 13 to function printf
    //  26:	45b1                	li	    a1,12       # argument 12 to function printf
    //  28:	00001517              	auipc   a0,0x1
    //  2c:	85850513              	addi    a0,a0,-1960 # 880 <malloc+0x100>
    //  30:	69c000ef              	jal	    6cc <printf>
    exit(0);
    //  34:	4501                	li	    a0,0
    //  36:	26e000ef          	    jal	    2a4 <exit>
}

/**
 * Which registers contain arguments to functions? For example, which register holds 13 in main's call to printf?
 *
 * Answer: a0, a1, and a2. For example, a2 holds 13 in main's call to printf.
 *
 * Where is the call to function f in the assembly code for main? Where is the call to g? (Hint: the compiler may inline functions.)
 *
 * Answer: The call to function f is inlined. Compiler inlines the "f(8) + 1" to 12 instead.
 * Similarly, the call to function g is inlined. Thus, calling to function f will be equivalent to calling to function g.
 *
 * At what address is the function printf located?
 *
 * Answer: 6cc.
 *
 * What value is in the register ra just after the jalr to printf in main?
 *
 * Answer: The address of the next instruction, that is, 0x34.
 *
 *
 */