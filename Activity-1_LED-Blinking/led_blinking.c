#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO 60

void write_gpio(const char *path, const char *value)
{
    FILE *fp = fopen(path, "w");
    
    if (fp == NULL)
    {
    	perror(path);
    	exit(EXIT_FAILURE);
    }
    
    fprintf(fp, "%s", value);
    fclose(fp);
}

int main(void)
{
    char path[100];
    
    printf("GPIO LED Blinking Program\n");
    
    /* Configure GPIO as output */
    
    snprintf(path, sizeof(path), "/sys/class/gpio%d/direction", GPIO);
    
    write_gpio(path, "out");
    
    /* Blink LED */
    while(1)
    {
    	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", GPIO);
    	
    	/* LED ON*/
    	write_gpio(path, "1");
    	printf("LED OFF\n");
    	sleep(1);
    	
    	/* LED ON*/
    	write_gpio(path, "0");
    	printf("LED OFF\n");
    	sleep(1);
    }
    
    return 0;
}
