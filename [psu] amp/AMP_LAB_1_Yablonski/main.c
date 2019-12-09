#include <bcm2835.h>  // GPIO
#define PIN RPI_V2_GPIO_P1_12 // определение используемого вывода GPIO 12 pin

#define DURATION_LONG 1000
#define DURATION_SHORT 300

void hightOff(long duration){
	bcm2835_gpio_write(PIN, LOW); 
	bcm2835_delay(duration);
}

void hightOn(long duration){
	bcm2835_gpio_write(PIN, HIGH); 
	bcm2835_delay(duration);
}

int main(int argc, char **argv){
	if (!bcm2835_init()){
		return 1;
	}
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	
	hightOn(DURATION_SHORT);
	hightOff(DURATION_SHORT);
	
	hightOn(DURATION_SHORT);
	hightOff(DURATION_LONG);
	
	hightOn(DURATION_LONG);
	hightOff(DURATION_LONG);
	
	bcm2835_close(); 
	return 0;
}
