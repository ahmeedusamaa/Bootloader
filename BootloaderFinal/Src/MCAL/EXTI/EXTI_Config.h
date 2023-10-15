/*
 * EXTI_Config.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Adham Ehab
 */

#ifndef MCAL_EXTI_EXTI_CONFIG_H_
#define MCAL_EXTI_EXTI_CONFIG_H_

//Hardware interrupt selection
//To configure the 23 lines as interrupt sources, use the following procedure:
//• Configure the mask bits of the 23 interrupt lines (EXTI_IMR)
//• Configure the Trigger selection bits of the interrupt lines (EXTI_RTSR and EXTI_FTSR)
//• Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
//external interrupt controller (EXTI) so that an interrupt coming from one of the 23 lines
//can be correctly acknowledged.
//Hardware event selection
//To configure the 23 lines as event sources, use the following procedure:
//• Configure the mask bits of the 23 event lines (EXTI_EMR)
//• Configure the Trigger selection bits of the event lines (EXTI_RTSR and EXTI_FTSR)
//Software interrupt/event selection
//The 23 lines can be configured as software interrupt/event lines. The following is the
//procedure to generate a software interrupt.
//• Configure the mask bits of the 23 interrupt/event lines (EXTI_IMR, EXTI_EMR)
//• Set the required bit in the software interrupt register (EXTI_SWIER)

#endif /* MCAL_EXTI_EXTI_CONFIG_H_ */
