#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/**
 *  In the following code, what is going to be printed after 'y='?
 *  (note: the answer is not a specific value.) Why does this happen?
 *  printf("x=%d y=%d", 3);
 */
void main()
{
    printf("x=%d y=%d", 3);
    exit(0);
}
/**
 * Output:
 * x=3 y=10155
 * The second address is not specific, it depends on the memory layout of the program.
 * So the program may read a garbage value from that address.
 */