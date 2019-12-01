#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "md5.h"


/**************************************************************************** 
��������: hex_to_str 
��������: ʮ������ת�ַ��� 
�������: ptr �ַ��� buf ʮ������ len ʮ�������ַ����ĳ��ȡ� 
�������: �� 
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
MD5:	ת���ɴ�д��MD5ֵ
Val:	Ҫ���ҵ�ֵ
RpVal:  Ҫ�滻��ֵ	
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

	//���û���ƴ��
	char *ConstString = "f4hguNAg";

	MD5_CTX context;
	long dtLength;
	char szHash[256] = {0};
	TCHAR szBuffer[256] = {0};
	int i = 0;
	int n = 0;
	char j = 0;
	printf("---------doc2pdf2 V5.0ע���-------\n\n");

	printf("�������û���: ");
	scanf("%s",UserName);
	if ( strlen(UserName) >= 240 )
	{
		printf("�û������ܳ���240λ\n");
		return -1;
	}


	for (i=0; i<strlen(UserName); i++)
	{
		//--������
		if (isdigit(UserName[i]) != 0)
		{
			continue;
		}
		else
		{
			//--����ĸ
			if ( isalpha(UserName[i])!=0)
			{
				//--�ж��Ǵ�Сд��ת���ɴ�д
				if(UserName[i]>='a'&& UserName[i]<='z') 
				{
						BigStrName[i] = UserName[i] - 32;
						continue;
				}
			}

		}
	}
	

	//--�û�����̶��ַ�ƴ�ղ�����MD5ֵ
	strcat(BigStrName,ConstString);
//	strncpy(BigStrName+strlen(BigStrName), ConstString, strlen(ConstString));

	//����MD5ֵ
	MD5Init(&context);
	MD5Update(&context, BigStrName, strlen(BigStrName));
	MD5Final(szHash, &context);


	//--��MD5ֵת�����ַ�
	hex_to_str(MD5, szHash, strlen(szHash));


	//--��MD5�ַ���ת���ɴ�д
	for (n=0; n<strlen(MD5); n++)
	{
		//--�ж��Ǵ�Сд��ת���ɴ�д
		if(MD5[n]>='a'&& MD5[n]<='z') 
		{
			MD5[n] -= 32;
			continue;
		}
	}

	//--���Ҳ��滻��MD5�ַ�
	FindVal_Replace(MD5, '1', 'Z');//1�滻��Z

	FindVal_Replace(MD5, '2', 'W');//2�滻��W

	FindVal_Replace(MD5, '0', 'K');//0�滻��K

	FindVal_Replace(MD5, '3', 'T');//3�滻��T

	FindVal_Replace(MD5, '8', 'P');//8�滻��P

	FindVal_Replace(MD5, '7', 'S');//7�滻��S

	//-����ע����
	strncpy(License, MD5, 12);

	printf("ע����:%s\n",License);
	system("pause");

	return 0;
}