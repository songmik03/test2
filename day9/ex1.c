#include <stdio.h>

//#define pi 3.14
const double pi=3.14;


int main()
{
	
	double _pi = 3.14;

	int a = 10, b = 20;


	//const int *ap = &a;
	const int *ap;
	ap = &a;
	ap = &b;
	
	b=21;
	//*ap = 21;
	

	//pi = 2.14;
	_pi = 2.14;
  
  	printf("%f %d\r\n",pi,*ap);
}


