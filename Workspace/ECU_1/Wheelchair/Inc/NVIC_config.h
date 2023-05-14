/**************************************************************************/
/* Author      : Ibrahim Diab                                             */
/* File Name   : NVIC_config.h                                            */
/* Description : Configuration for NVIC core peripheral for Arm CORTEX-M3 */
/**************************************************************************/

#ifndef NVIC_CONFIG_H
#define NVIC_CONFIG_H

/*
 requirements:

- The RCC clock for the peripheral is enabled.
- The interrupt vector table is configured and loaded in memory.
- Any necessary initialization for the peripheral before generating the interrupt is performed.

Note: Failure to meet these requirements may result in undefined behavior.
 */


/* [Must] 
 Options:
 _4G_0S //  4 bits for groups & 0 bits for subgroups >> 16 G  0 S.
 _3G_1S //  3 bits for groups & 1 bits for subgroups >>  8 G  2 S.
 _2G_2S //  2 bits for groups & 2 bits for subgroups >>  4 G  4 S.
 _1G_3S //  1 bits for groups & 3 bits for subgroups >>  2 G  8 S.
 _0G_4S //  0 bits for groups & 4 bits for subgroups >>  0 G 16 S.
*/
#define NO_BITS_GROUBS_SUB   _4G_0S


#endif // NVIC_CONFIG_H
