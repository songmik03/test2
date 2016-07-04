#include <stdio.h>

int main()
{
	char word[50]="hi~ world";

/*	word[0]='h';
	word[1]='i';
	word[2]= 0x00; //	문장끝에 NULL값을 넣어줌
*/
	/*for(int i=0;i<2;i++) {

		printf("%c", word[i]);
	}
	*/
	printf("%s \r\n", word);

	/*int i=0;
	while(word[i] != 0x00) {
		printf("%c", word[i]);
		i++;
	}
*/
	for(int i=0;i<50;i++) {
		//printf("%d", word[i]);
	}
	printf("add :");
	scanf("%s",(word+9));

	//*(word+2) = 0x00;
	//
	printf("your input : %s \r\n", word);


	return 0; 
}
