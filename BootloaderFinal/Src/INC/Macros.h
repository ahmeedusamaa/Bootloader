/*
 * Macros.h
 *
 *  Created on: Aug 8, 2023
 *      Author: ahmed osama
 */

#ifndef INC_MACROS_H_
#define INC_MACROS_H_


//setting a specific bit in a given register
//@BIT_MATH macros
#define SET_BIT(REG,BIT)			(REG |= 1<<BIT)
#define CLR_BIT(REG,BIT)			(REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)			(REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)			(((REG)&(1<<BIT))>>BIT)
#define SET_REG(REG)				(REG = 0xFFFFFFFF)
#define CLR_REG(REG)				(REG = 0x00000000)


#define SET			1
#define	CLR			0


#endif /* INC_MACROS_H_ */
