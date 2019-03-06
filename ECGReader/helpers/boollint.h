/*!
 * @brief My own personal implementation of stdbool and stdint
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

#ifndef __BOOLINT_H__
#define __BOOLINT_H__

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;
typedef signed char   int8_t;
typedef signed int    int16_t;
typedef signed long   int32_t;

typedef unsigned long LONG;
typedef unsigned short WORD;
typedef unsigned char BYTE;

#ifndef BOOL
#ifndef FALSE
#define FALSE 0u
#define false 0u
#define TRUE  1u
#define true  1u
#endif

typedef uint8_t BOOL;
typedef uint8_t bool;

#endif

#ifndef NULL
#define NULL 0x0000000000000000
#define null NULL
#endif

#endif /* __BOOLINT_H__ */
