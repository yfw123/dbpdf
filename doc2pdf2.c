#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "md5.h"


/**************************************************************************** 
函数名称: hex_to_str 
函数功能: 十六进制转字符串 
输入参数: ptr 字符串 buf 十六进制 len 十六进制字符串的长度。 
输出参数: 无 
*****************************************************************************/  

void hex_to_str(char *ptr,unsigned char *buf,int len)  
{  
	int i=0;
	for(i = 0; i < len; i++)  
	{  
		sprintf(ptr, "%02x",buf[i]);  
		ptr += 2;  
	}  
} 


/*
MD5:	转换成大写的MD5值
Val:	要查找到值
RpVal:  要替换的值	
*/
void FindVal_Replace(char* MD5, char Val, char RpVal)
{

	int i = 0;

	if (NULL == MD5 || 0 == Val || 0 == RpVal)
	{
		return;
	}


	for (i=0; i<strlen(MD5); i++)
	{
		if ( Val == MD5[i] )
		{
			MD5[i] = RpVal;
		}
	}
}

int main(int argc, char* argv[])
{
	char UserName[256] = {0};
	char License[256] = {0};
	char BigStrName[256] = {0};
	char MD5[256] = {0};

	//与用户名拼凑
	char *ConstString = "f4hguNAg";

	MD5_CTX context;
	long dtLength;
	char szHash[256] = {0};
	TCHAR szBuffer[256] = {0};
	int i = 0;
	int n = 0;
	char j = 0;
	printf("---------doc2pdf2 V5.0注册机-------\n\n");

	printf("请输入用户名: ");
	scanf("%s",UserName);
	if ( strlen(UserName) >= 240 )
	{
		printf("用户名不能超过240位\n");
		return -1;
	}


	for (i=0; i<strlen(UserName); i++)
	{
		//--是数字
		if (isdigit(UserName[i]) != 0)
		{
			continue;
		}
		else
		{
			//--是字母
			if ( isalpha(UserName[i])!=0)
			{
				//--判断是大小写并转换成大写
				if(UserName[i]>='a'&& UserName[i]<='z') 
				{
						BigStrName[i] = UserName[i] - 32;
						continue;
				}
			}

		}
	}
	

	//--用户名与固定字符拼凑并计算MD5值
	strcat(BigStrName,ConstString);
//	strncpy(BigStrName+strlen(BigStrName), ConstString, strlen(ConstString));

	//计算MD5值
	MD5Init(&context);
	MD5Update(&context, BigStrName, strlen(BigStrName));
	MD5Final(szHash, &context);


	//--将MD5值转换成字符
	hex_to_str(MD5, szHash, strlen(szHash));


	//--将MD5字符串转换成大写
	for (n=0; n<strlen(MD5); n++)
	{
		//--判断是大小写并转换成大写
		if(MD5[n]>='a'&& MD5[n]<='z') 
		{
			MD5[n] -= 32;
			continue;
		}
	}

	//--查找并替换掉MD5字符
	FindVal_Replace(MD5, '1', 'Z');//1替换成Z

	FindVal_Replace(MD5, '2', 'W');//2替换成W

	FindVal_Replace(MD5, '0', 'K');//0替换成K

	FindVal_Replace(MD5, '3', 'T');//3替换成T

	FindVal_Replace(MD5, '8', 'P');//8替换成P

	FindVal_Replace(MD5, '7', 'S');//7替换成S

	//-拷贝注册码
	strncpy(License, MD5, 12);

	printf("注册码:%s\n",License);
	system("pause");

	return 0;
}