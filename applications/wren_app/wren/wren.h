/** @file wren.h
*
* @brief Wren configuration and API
*
* @par
* @copyright Copyright © 2018 Doug Currie, Londonderry, NH, USA
*/

#ifndef WREN_H
#define WREN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <storage/storage.h>

/* ############## Configuration ############## */

/** @def WREN_UNALIGNED_ACCESS_OK
* @brief non-zero enables reads and writes of multi-byte values from/to unaligned addresses.
* Default to safe mode: no unaligned accesses.
*/
#ifndef WREN_UNALIGNED_ACCESS_OK
#define WREN_UNALIGNED_ACCESS_OK (0)
#endif

/** @def WREN_STANDALONE
* @brief non-zero enables main() with command line config and read-eval-print loop.
* Default to standalone; set to 0 if you want to use Wren as a library.
*/
#ifndef WREN_STANDALONE
#define WREN_STANDALONE (0)
#endif

/* ################## Types ################## */

#if 0

/** Type of a Wren-language value.
*/
typedef intptr_t wValue;
/* and how to printf it
*/
#define PRVAL "ld"

/** Type of the unsigned version of a Wren-language value.
*/
typedef uintptr_t wUvalu; 

#else

/** Type of a Wren-language value.
*/
typedef int32_t wValue;
/* and how to printf it
*/
#define PRVAL "d"

/** Type of the unsigned version of a Wren-language value.
*/
typedef uint32_t wUvalu; 

#endif

/** Type of a Wren-language index into the_store. Must be half the size of wValue or smaller.
*/
typedef uint16_t wIndex;
/* and how to printf it
*/
#define PRIDX "u"

/** Type of a Wren-language pointer to C function.
*/
typedef wValue (*apply_t)(); // the type of C functions for CCALL and wren_bind_c_function()
/* and how to printf it
*/
#define PRPTR "p"

/* ################### API ################### */


void wren_initialize (void);

void wren_bind_c_function (const char *name, apply_t fn, const uint8_t arity);

void wren_load_file (File *fp);

void wren_read_eval_print_loop (void);

#ifdef __cplusplus
}
#endif

#endif /* WREN_H */

void debug(const char* s)
{
  printf("DEBUG %s\r\n", s);
}
