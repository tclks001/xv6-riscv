#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/**
 *  Run the following code.
    ```
    unsigned int i = 0x00646c72;
    printf("H%x Wo%s", 57616, &i);
    ```
    What is the output? Here's an ASCII table that maps bytes to characters.
    The output depends on that fact that the RISC-V is little-endian.
    If the RISC-V were instead big-endian what would you set i to in order to yield the same output?
    Would you need to change 57616 to a different value?
 */
void main()
{
    unsigned int i = 0x00646c72;
    printf("H%x Wo%s", 57616, &i);
    exit(0);
}
/**
 * Output:
 * HE110 World
 *
 * 57616(decimal) = E110(hex)
 * Why 0x00646c72 is "rld"?
 * 0x64='d', 0x6c='l', 0x72='r'
 * Moreover, RISC-V is little-endian, so the order of bytes in memory is reversed.
 * So i = 0x00646c72 is meaning {0x72, 0x6c, 0x64, 0x00}, that is "rld\0".
 * If we run it on a big-endian machine, we should use 0x726c6400 instead.
 */