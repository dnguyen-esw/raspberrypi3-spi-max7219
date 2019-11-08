#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
void display(long int number)
{
	int count=0;
	long n=number;
	while(n!=0)
	{
		count++;
		n/=10;
	}
	printf("So chu so: %d\n",count);

	unsigned char buffer[2];
	buffer[0] = 0x0B;//scan
	buffer[1] =count-1;
	wiringPiSPIDataRW(0, buffer, 2);
	
	for(int i=1;i<=count;i++)
	{
		buffer[0]=i;
		buffer[1]=number%10;
		number/=10;
		wiringPiSPIDataRW(0, buffer, 2);
		delay(3);
	}
	
	delay(3);
	
}

int main()
{
	
	unsigned char buffer[100];
	unsigned char mssv[8] ={1,6,1,4,6,0,9,1};
	// initialize SPI1 interface, speed 500 kHz
	wiringPiSetup();
	wiringPiSPISetup(0, 1000000);

	// send and read 1 byte
	
	buffer[0]=0x09;//decode
	buffer[1]=0xff;//B decode
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	buffer[0] = 0x0A;//inten
	buffer[1] =0x0F;//
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	buffer[0] = 0x0B;//scan
	buffer[1] =0x07;//
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	buffer[0] = 0x0C;//shutdown register
	buffer[1] =0x01;//normal operation
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	buffer[0]=0x0F;//display test
	buffer[1]=0x01;
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	buffer[0]=0x0F;//display data
	buffer[1]=0x00;
	wiringPiSPIDataRW(0, buffer, 2);
	delay(3);
	
	long num;
	
	//display(num);
	while(1)
	{
		long input;
		printf("Input number:");
		scanf("%ld", &input);
		printf("Your number:%ld\n",input);
		display(input);
	}

	return 0;
}
