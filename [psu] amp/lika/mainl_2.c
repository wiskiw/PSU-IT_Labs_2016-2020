#include <bcm2835.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define PIN RPI_V2_GPIO_P1_33
#define PWM_CHANNEL 1
#define RANGE 1024 
int main(int argc, char **argv) 
{ 
	int direction = 1, data = 1, count = 0;

	if (!bcm2835_init()) 
		return 1; 
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT0); 
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16); 
	bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1); 
	bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

	if(argc > 2 && strcmp(argv[1], "set") == 0)
	{ 
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP); 
		int state = atoi(argv[2]); 
		bcm2835_gpio_write(PIN, state); 
		bcm2835_close(); 
	} 
	else if(argc > 2 && strcmp(argv[1], "shim") == 0)
	{ 
	    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE); 
	    while (count < 1)
	    {
	        if (data == 1)
	            direction = 1;
	        else if (data >=  atoi(argv[2])-1)
	        {
	            count++;
	            direction = -1;
	        }

	        data += direction;
	        bcm2835_pwm_set_data(PWM_CHANNEL, data);
	
	    }
	}
	else
	{ 
      	    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE); 
	    while (count < 1)
	    {
	        if (data == 1)
	            direction = 1;
	        else if (data >=  RANGE*0.2-1)
	        {
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
