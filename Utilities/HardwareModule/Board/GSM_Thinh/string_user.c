#include "string_user.h"
char Array2Print[6];
/*	*
	* compare all elements of 2 strings return 1 if they're equal
	*
	*/
char String_cmp(char* str1,char* str2)
{
	char temp=1;
	if ((*str1==0)||(*str2==0)){
		return 0;
	}
	while(*str1!=0&&*str2!=0)
	{
		if(*str1-*str2)
			temp=temp&0;
		else
			temp=temp&1;
		str1++;
		str2++;
	}
	return(temp);
}
/*	*
	* compare N elements of 2 strings return 1 if they're equal 
	*
	*/
char String_N_cmp(char* str1,char* str2,char N)
{
	char temp=1;
	char i=0;
	if ((*str1==0)||(*str2==0)){
		return 0;
	}
	for(i=0;i<=(N-1);i++)
	{
		if(*str1-*str2)
			temp=temp&0;
		else
			temp=temp&1;
		str1++;
		str2++;
	}
	return(temp);
}
/*	*
	* wait for description...
	*
	*/
void CRC8(char data,char* crc)
{
	char i=8;
	do{
		if((data^*crc)&0x01)
			*crc=((*crc^0x18)>>1)|0x80;
		else
			*crc=*crc>>1;
		data=data>>1;
		}while(--i);
}	
/*	*
	* convert decimal numbers with 4 digits to string return pointer to string 
	*
	*/
void Num2Str(int num,char*pointer)
{
	if(num<0)
	{
		*pointer='-';
		pointer++;
		num=(-1)*num;
	}	
	if(num>=1000)
	{
		*pointer=((char)(num/1000))+0x30;
		pointer++;
	}
 	if(num>=100)
	{
		*pointer=((char)((num%1000)/100))+0x30;
		pointer++;
	}
	if(num>=10)
	{
		*pointer=(char)((num%100)/10)+0x30;
		pointer++;
	}
	if(num>=1)
	{
		*pointer=(char)(num%10)+0x30;
		pointer++;
	}
	if(num==0)
	{
		*pointer=0x30;
		pointer++;
	}
	*pointer='\0';
}
/*	*
	* wait for description...
	*
	*/
unsigned int power_of_10(char exp)
{
	unsigned int num=1;
	char i=1;
	if(exp==0)
		return(num);
	else
	{
		for(i=1;i<=exp;i++)
			num=10*num;
		return(num);		
	}
}
/*	*
	* wait for description...
	*
	*/
char Str2Num_char(char* str)
{
	char minus=0;
	char num=0;
	char cnt=0;
	char* ptr=str;
	while(*ptr!='\0')
		ptr++;
	while(*str!='\0')
	{
		
		if(*str>=0x30&&*str<=0x39)
		{	
			ptr--;
			num=num+(*ptr-0x30)*(char)(power_of_10(cnt));
			cnt++;
		}
		else if(*str=='-')
			minus=1;
		else 
			return(0);
		str++;
	}
	if(minus==1)
		return(-1*num);
	else 
		return(num);
}
/*	*
	* wait for description...
	*
	*/
float Str2Num_fl(char* str)
{
	int div = 1;
	char divF = 0;
	long num=0;
	float tmp;
	while(*str!='\0')
		{	
		if(*str>=0x30&&*str<=0x39)
			{
			num *=10;
			num+=(*str-0x30);
			if(divF)
				div*=10;
			}
		else if(*str=='-')
			div=-1;
		else if(*str == '.')
			divF = 1;
		str++;
		}
	tmp=(float)num/div;
	return(tmp);
}
/*	*
	* wait for description...
	*
	*/
void Str_copy(char* source,char* des)
{
	do{
		*des=*source;
		des++;
		source++;
		}while(*source!='\0');
	*des = '\0';
}
/*	*
	* wait for description...
	*
	*/
void Str_N_copy(char* source,char* des,char N)
{
	char i;
	for(i=0;i<N;i++)
	{
		*des=*source;
		des++;
		source++;
	}
	*des = '\0';
}
/*	*
	* wait for description...
	*
	*/
char Str2Num_nchar(char* str, char n)
{
	char minus=0;
	char num=0;
	char cnt=0;
	char i;
	char* ptr=str;
	for(i=0;(i<n)&&(*ptr!='\0');i++)
		ptr++;
	for(i=0;(i<n)&&(*str!='\0');i++)
		{
		if(*str>=0x30&&*str<=0x39)
			{	
			ptr--;
			num=num+(*ptr-0x30)*(char)(power_of_10(cnt));
			cnt++;
			}
		else if(*str=='-')
			minus=1;
		else 
			return(0);
		str++;
	}
	if(minus==1)
		return(-1*num);
	else 
		return(num);
}
/*	*
	* wait for description...
	*
	*/
float Str2Num_nfl(char* str,char n)
{
	char i;
	int div = 1;
	char divF = 0;
	long num=0;
	float tmp;
	for(i=0;(i<n)&&(*str!='\0');i++)
		{	
		if(*str>=0x30&&*str<=0x39)
			{
			num *=10;
			num+=(*str-0x30);
			if(divF)
				div*=10;
			}
		else if(*str=='-')
			div=-1;
		else if(*str == '.')
			divF = 1;
		str++;
		}
	tmp=(float)num/div;
	return(tmp);
}
/*	*
	* wait for description...
	*
	*/
void Array_reset(char* Arr)
{	
	while(*Arr!='\0')
	{
		*Arr=0;
		Arr++;
	}	
}
