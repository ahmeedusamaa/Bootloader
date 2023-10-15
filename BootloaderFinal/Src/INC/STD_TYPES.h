/*
 * STD_TYPES.h
 *
 *  Created on: Aug 8, 2023
 *      Author: ahmed osama
 */

#ifndef INC_STD_TYPES_H_
#define INC_STD_TYPES_H_

typedef unsigned char			uint8_t 	;
typedef signed char				sint8_t 	;
typedef unsigned short  		uint16_t 	;
typedef signed short 			sint16_t 	;
typedef unsigned int 			uint32_t 	;
typedef signed int 		  		sint32_t 	;
typedef unsigned long long 		uint64_t 	;
typedef signed long long 		sint64_t 	;
typedef float					float32_t 	;
typedef double					float64_t 	;

typedef enum {
    STATUS_SUCCESS,
    STATUS_ERROR,
    STATUS_IN_PROGRESS
} ReturnStatus;

#define NULL ((void*)0)

#endif /* INC_STD_TYPES_H_ */
