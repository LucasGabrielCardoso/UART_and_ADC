/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H_
    #define	ADC_H_
    #include <xc.h>
    
    void ADC_Initializer(void);
    uint16_t ADC_Get_Value(uint8_t channel);
    
#endif	/* ADC_H_ */