#include<iostream>
#include<unistd.h>
#include<cppgpio.hpp>
using namespace std;

int main(){
	GPIO::DigitalOut prvi(6);
	GPIO::DigitalOut drugi(13);
	GPIO::DigitalOut treci(19);
	while(true){
	prvi.on();
	drugi.on();
	treci.off();
	usleep(100000);
}
}
