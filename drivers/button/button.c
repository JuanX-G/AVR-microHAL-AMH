#include "button.h"
#include "../../config.h"

void button_init(button_t *btn, gpio_t *gpio) {
    btn->gpio = gpio;
    btn->state = 0;
    btn->last_raw = 0;
    btn->counter = 0;
}

/* Update the state of the button --- should be called before:
 * 		- button_is_pressed
 * 		- button_just_pressed
 * 		- button_just_released 
 * The register the newest state
 *
 * NOTES:
 * 	> The function makes a correction for the debounce of the button 
 * 	   using the BUTTON_DEBOUNCE config define
 */
void button_update(button_t *btn) {
    uint8_t raw = (gpio_read(btn->gpio) == GPIO_LOW); 

    if (raw != btn->last_raw) {
        btn->counter = 0;
    } else {
        if (btn->counter < BUTTON_DEBOUNCE_TIME) {
            btn->counter++;
        } else {
            btn->state = raw;
        }
    }
    btn->last_raw = raw;
}

/* Check if the button is down RIGHT NOW, a short press is likely to not be registered
 * RETURNS:
 * 	> 0 if button is not been pressed 
 * 	> 1 if it is pressed
 */
uint8_t button_is_pressed(button_t *btn) {
    return btn->state;
}

/* Check if the button has been pressed, the state if only updated using the button_update function
 * RETURNS:
 * 	> 0 if button has not been pressed 
 * 	> 1 if it has been pressed
 * NOTES:
 * 	> if you don't call button_update the state will NEVER change 
 */
uint8_t button_just_pressed(button_t *btn) {
    uint8_t ret = 0;

    if (btn->state && !btn->last_state)
        ret = 1;

    btn->last_state = btn->state;
    return ret;
}

/* Check if the button became unpressed, the state if only updated using the button_update function
 * RETURNS:
 * 	> 0 if button has not been released 
 * 	> 1 if it has been released
 * NOTES:
 * 	> if you don't call button_update the state will NEVER change 
 */
uint8_t button_just_released(button_t *btn) {
	uint8_t ret = (!btn->state && btn->last_state);
	btn->last_state = btn->state;
	return ret;
}
