#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT_MAX "4294967295"
#define INT_MIN "-2147483648"
#define INT_MAX 2147483647

//functie wrapper peste apelul de sistem write
static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//functia care transforma numarul dat ca input in baza-base
//si returneaza un string
char *toString(unsigned int input, int base) 
{ 
	//bufferul care isi va pastra valoarea la fiecare rulare a functiei
	static char buffer[20]; 
	char *str; 
	str = &buffer[19]; 
	*str = '\0'; 
	int rest;

	while (input != 0) {
		rest = input % base;
		input /= base; 
		if (rest >= 0 && rest <= 9) 
			*--str = (char)(rest + '0');
		else 
			*--str = (char)(rest - 10 + 'a'); 
	}  
	
	return(str); 
}
//functia care transforma un numal hexazecimal in decimal
unsigned int hexToDec(char hex[]) 
{    
    int base = 1; 
    unsigned int decimal = 0; 
    int i = strlen(hex) - 1;
    
    while (i >= 0) {    
        if (hex[i] >= '0' && hex[i] <= '9') { 
            decimal += (hex[i] - 48) * base; 
            base *= 16; 
        } 
        else if (hex[i] >= 'a' && hex[i] <= 'f') { 
            decimal += (hex[i] - 87) * base; 
            base *= 16; 
        } 
        i--;
    } 
    return decimal; 
} 
int iocla_printf(const char *format, ...)
{
	int i = 0, j = 0; //contoarele din format si respectiv output
	
	char *output = calloc(sizeof(char), 100000); //stringul care va pastra outputul final
	
	char *str_temp; //stringul auxiliar in care se pastreaza temporar 
			//valorile inputului dupa transformarea in string
	
	unsigned int after_hexa; //numarul temporar care va pastra valoare decimala
			//dupa tranfomarea din hexa
	
	int input; //specificatorul citit prin format[]
	
	va_list args;
	va_start(args, format);

	do {
		if (format[i] == '%') {
			i++;
			switch (format[i]){
				case 'c':
				{
					input = va_arg(args, int);
					output[j] = (char)input; //promovare la char dupa ce a trecut prin ...
					j++;
					break;
				}
				case 'd':
				{
					input = va_arg(args, int);
					//cazul daca numarul este negativ
					if (input < 0) {
						input = -input;
						strcpy(&output[j], "-");
						j++;
					}
					str_temp = toString(input, 10);
					strcpy(&output[j], str_temp);
					j += strlen(str_temp);
					break;
				}
				case 'x':
				{
					input = va_arg(args, int);
					str_temp = toString(input, 16); //transform input in b16
					strcpy(&output[j], str_temp);
					j += strlen(str_temp);
					break;
				}
				case 'u':
				{
					input = va_arg(args, int);
					//cazul daca input e negativ
					if (input < 0) {
						str_temp = toString(input, 16); //transform input in b16
						after_hexa = hexToDec(str_temp); //apoi transform nr din b16 in b10
						str_temp = toString(after_hexa, 10); //si din b10 in string 
					}
					//cazul pozitiv
					else {
						str_temp = toString(input, 10); //se transforma input in string
					}
					strcpy(&output[j], str_temp);
					j += strlen(str_temp);
					break;
				}
				case 's':
				{
					str_temp = va_arg(args, char*);
					strcpy(&output[j], str_temp);
					j += strlen(str_temp);
					break;
				}
				case '%':
				{
					output[j] = '%';
					j++;
					break;
				}
			}
		}
		else {
			//copii caracterele care nu trebuie formatate in output
			output[j] = format[i];
			j++;
		}
		i++;

	} while (format[i]); //conditie pana se termina caracterele de format

	write_stdout(output, j); //afisarea finala 
	va_end(args);
	free(output);
	return j;
}
int main(int argc, char const *argv[])
{

	iocla_printf("%d\n0x%x\n%%%u\n",3,-3,-15);
	printf("%d\n0x%x\n%%%u\n",3,-3,-15);
	printf("%u\n", -100);
	return 0;
}