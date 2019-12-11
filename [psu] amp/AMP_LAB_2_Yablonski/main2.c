#include <bcm2835.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define PIN RPI_V2_GPIO_P1_32 
#define PWM_CHANNEL 0

#define DEFAULT_DATA 1
#define DEFAULT_RANGE 1024 
#define REPEATS 5 

/**
вар 10	
Используемый GPIO ввод 32	
Заполнение ШИМ 80%:
	shim = 1024
	data = 80 * shim / 100 = 819
**/

int main(int argc, char **argv) {

	int direction = 1;
	int state = 0;
	int count = 0;
	
	int data = DEFAULT_DATA; 
	int range = DEFAULT_RANGE;
	
	// <appname> SETPARAM <value> SHIMPARAM <value>
	if (argc == 5) {
	
		int dataParamIndex = 1;
		if (strcmp(argv[dataParamIndex], "data") == 0){
			data = atoi(argv[dataParamIndex + 1]); 
		}
		
		int rangeParamIndex = 3;
		if(strcmp(argv[rangeParamIndex], "range") == 0) { 
			range = atoi(argv[rangeParamIndex+1]);
		}
		
	} else {
		// not enouth args
		//return 2;
	}
	
	// setup bcm2835
	if (!bcm2835_init()) {
		return 1; 
	}
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT0); // Соответствие порта GPIO и режима дополнительных функций
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16); // dvider часов можно изменять с помощью
	bcm2835_pwm_set_mode(PWM_CHANNEL, 1, 1); 
	bcm2835_pwm_set_range(PWM_CHANNEL, range); 
	bcm2835_pwm_set_data(PWM_CHANNEL, data);

	while (count < REPEATS) {
        if (data == 1) {
		   direction = 1;
		}
		if (data == RANGE-1) {
            count++;
            direction = -1;
        }
        data += direction;
		
        bcm2835_pwm_set_data(PWM_CHANNEL, data);
        bcm2835_delay(1);
    }
	
	bcm2835_close(); 
	return 0; 
}
