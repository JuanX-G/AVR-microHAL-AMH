#include "adc.h"
#include <avr/io.h>

#ifdef INTERRUPT_ADC_CEN
volataile uint16_t newest_adc_value;

ISR(ADC_vect) {
    newest_adc_value = ADC;
}

uint16_t adc_start_conversion(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    ADCSRA |= (1 << ADSC);
}
#endif
void adc_init(void) {
    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADEN) |
             (1 << ADPS2) |
             (1 << ADPS1) |
             (1 << ADPS0);
#ifdef INTERRUPT_ADC_CEN
    newest_adc_value = 0;
    ADCSRA |= (1 << ADIE);
#endif
}

