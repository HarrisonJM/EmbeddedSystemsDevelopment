/*!
 * @brief My own personal implementation of stdbool and stdint
 * @author Harrison J Marcks
 * @date 12/11/2018
 */

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;
typedef signed char   int8_t;
typedef signed int    int16_t;
typedef signed long   int32_t;

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
