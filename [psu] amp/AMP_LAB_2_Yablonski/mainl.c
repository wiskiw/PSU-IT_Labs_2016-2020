#include <bcm2835.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define PIN RPI_V2_GPIO_P1_33
#define PWM_CHANNEL 1
#define RANGE 1024 

#define PERCENT 0.8

// •	GPIO 12 (PWM channel 0) – режим Alt5;
// •	GPIO 32 (PWM channel 0) – режим Alt0;
// •	GPIO 33 (PWM channel 1) – режим Alt0;
// •	GPIO 35 (PWM channel 1) – режим Alt5.


int main(int argc, char **argv) { 
	int direction = 1;
	int data = 1; 
	int count = 0;

	if (!bcm2835_init()) 
		return 1; 
	
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT0); 
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16); 
	bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1); 
	bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

	if(argc > 2 && strcmp(argv[1], "set") == 0){ 
      	// SET MODE
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP); 
		int state = atoi(argv[2]); 
		bcm2835_gpio_write(PIN, state);
		
	} else if(argc > 2 && strcmp(argv[1], "shim") == 0) { 
      	// SHIM MODE
	    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE); 
	    while (count < 1) {
	        if (data == 1) {
	            direction = 1;
			} else if (data >=  atoi(argv[2])-1) {
	            count++;
	            direction = -1;
	        }

	        data += direction;
	        bcm2835_pwm_set_data(PWM_CHANNEL, data);
	    }
		
	} else { 
      	// DEFAULT
		bcm2835_pwm_set_range(PWM_CHANNEL, RANGE); 
	    while (count < 1) {
	        if (data == 1) {
	            direction = 1;
	        } else if (data >= RANGE * PERCENT-1) {
	            count++;
	            direction = -1;
	        }
	        data += direction;
	        bcm2835_pwm_set_data(PWM_CHANNEL, data);
	        bcm2835_delay(1);
	    }
	}
	
	bcm2835_close(); 
	return 0; 
}
