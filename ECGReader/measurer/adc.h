/*!
 * @brief Definitions and declarations for ADC
 * @author Dan Steer & Len Biro
 * @date 10/12/2018
 */

#ifndef ADC_H_
#define ADC_H_

#define RDGSARRAYSIZE 192

extern volatile int rdg;
extern unsigned int rdgsIndex;
extern int rdgsArray[RDGSARRAYSIZE];

extern void ADCInitHardware(void);

extern void ADCStart(void);

#endif /* ADC_H_ */
