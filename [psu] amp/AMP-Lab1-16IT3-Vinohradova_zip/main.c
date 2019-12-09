#include <bcm2835.h> // ����������� ���������� bcm2835
#define PIN RPI_V2_GPIO_P1_12 // ����������� ������������� ������ GPIO
void hightOff(){
  bcm2835_gpio_write(PIN, LOW); 
  bcm2835_delay(1000);
}

void hightOn(){
  bcm2835_gpio_write(PIN, HIGH); 
  bcm2835_delay(1000);
}
int main(int argc, char **argv)
{
  if (!bcm2835_init()) // ������������� GPIO
    return 1;
  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP); // ��������� ����� �� �����
  for(int i=0;i<5;i++){
	hightOn();
	hightOff();
  }
  bcm2835_close(); // ���������� ������ � GPIO
  return 0;
}
