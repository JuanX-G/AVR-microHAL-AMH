#ifndef CONFIG_H
#define CONFIG_H
/* CPU frequency --- it is advised to stay above 2MHz--4MHz on capable CPUs; 
 * that is to maintain timings for various protocols 
 */
#define F_CPU 8000000UL 

/* Baud rate for UART */
#define UART_BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * UART_BAUDRATE)) - 1)

/* Enable interrupt based uart reciveing*/
#define INTERRUPT_UART_CEN
/* Buffer size for interrupt based UART --- if that's not used, the value below is ignored 
 * MUST be a power of 2 for the code to compile
 */
/* Debounce time for buttons when using the button.h driver*/
#define BUTTON_DEBOUNCE_TIME 20  

#define UART_BUFFER_SIZE 16

#define INTERRUPT_ADC_CEN
#endif
