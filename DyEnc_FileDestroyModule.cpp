//Copyright (c) 2022 Qilu University of Technology, Faculty of Computer Science & Technology, Duyu (No.202103180009).
//DyEncryptor File Destroy Module v2.0
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <windows.h>
#define COMPLIER "TDM-GCC 4.9.2 64-Bit Release"
#define EXENAME "DyEnc_FileDestroyModule.exe"
using namespace std;
enum filled_Mode
{
	USING_FIBYTE,
	USING_RANDOM
} fi_mode=USING_FIBYTE;
size_t getFileSize1(const char *fileName) 
{
	try {
	SetFileAttributes(fileName,0);
	}
	catch(int exception){
	;}
	if(fileName == NULL || access(fileName,F_OK)) return -1;
	struct stat statbuf;
	stat(fileName, &statbuf);
	size_t filesize = statbuf.st_size;
	return filesize;
}
void err(const char *describtion)
{
	HANDLE hConsole=GetStdHandle((STD_ERROR_HANDLE));
	SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY|FOREGROUND_RED);
	fprintf(stderr,"[ERROR]%s",describtion);
	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	exit(1);
}
char *renameFile(const char *oldNameAndPath,const char *newName)
{
	char q1[1024];char q2[1024];
	strcpy(q1,oldNameAndPath);strcpy(q2,newName);
	char *p_q01=strrchr(q1,'\\');
	char *p_q02=strrchr(q2,'\\');
	if(p_q01)
	{
		*(p_q01+1)=0;
		if(p_q02)
		{
			++p_q02;
			strcat(q1,p_q02);
		}
		else strcat(q1,q2);
		p_q01=q1;
	}
	else p_q01=q2;
	rename(oldNameAndPath,p_q01);
	rename(oldNameAndPath,p_q01);
	return p_q01;
}
int main(int argc,char *argv[])
{
	//Prepare
	printf("[INFOS]Copyright (c) 2022 Qilu University of Technology, Faculty of Computer Science & Technology, Duyu (No.202103180009).\n");
	printf("[DESCR]DyEncryptor File Destroy Module v2.0\n");
	printf("%s%s%s%s%s","Built and packaged with ",COMPLIER,". __",__DATE__,".\n");
	printf("[STEPS]Verify the environment.\n");
	char des[1024];sprintf(des,"Arguments Error.\nUsage: %s %s %s %s\nfillData=-1 means using random number.",(strrchr(argv[0], '\\')+1),"[fileName]","[fillData]","[fileSize]");
	if(argc<=1) err(des);
	char *filename=argv[1];
    int realFileSize=getFileSize1(filename);
    int fi_size=realFileSize;
    char fi_byte=0;
    if(realFileSize==-1) err("File not exist or file has no access.");
	if(argc==2)
	{
		fi_mode=USING_FIBYTE;
		fi_byte=0;
		fi_size=realFileSize;
	}
	if(argc==3 || argc==4)
	{
		try
		{
			int tempNum=atoi(argv[2]);
			if((tempNum>=0 && tempNum<=255)||(tempNum==-1))
			{
				fi_byte=tempNum;
				if(tempNum==-1) fi_mode=USING_RANDOM;
				else fi_mode=USING_FIBYTE;
			}
			else err("Argument02 should be in 0~255.");
		}
		catch(int exception)
		{
			char temp02[100];itoa(exception,temp02,10);
			err(strcat(temp02," - Argument02 should be a number."));
		}
		if(argc==4)
		{
			int temp03=realFileSize;
			try
			{
				temp03=atoi(argv[3]);
				if(temp03<0) err("File size is too small");
				fi_size=temp03;
			}
			catch(int exception)
			{
				char temp03[100];itoa(exception,temp03,10);
				err(strcat(temp03," - Argument03 should be a number."));
			}
		}
		else fi_size=realFileSize;
	}
	if(argc>4) err("Too many arguments.");
	//Execute
	printf("[STEPS]Fill data for the first time.\n");
	FILE *f=fopen(filename,"wb");
	if(fi_mode==USING_FIBYTE)
	{
		char buffer[1024];
		memset(buffer,fi_byte,sizeof(buffer));
		for(int q=1;q<=realFileSize/sizeof(buffer)+1;++q) fwrite(buffer,sizeof(buffer),1,f);
	}
	else
	{
		char buffer[1024];char *bp=buffer;int con=1;
		while(con<=sizeof(buffer))
		{
			srand((int)time(0)+con);
			*bp=rand()%256;++bp;
			++con;
		}
		for(int q=1;q<=realFileSize/sizeof(buffer)+1;++q) fwrite(buffer,sizeof(buffer),1,f);
	}
	fclose(f);
	printf("[STEPS]Fill data for the second time.\n");
	FILE *f02=fopen(filename,"wb");
	if(fi_mode==USING_FIBYTE)
	{
		char buffer[1024];
		memset(buffer,fi_byte,sizeof(buffer));
		for(int q=1;q<=fi_size/sizeof(buffer)+1;++q) fwrite(buffer,sizeof(buffer),1,f02);
	}
	else
	{
		char buffer[1024];char *bp=buffer;int con=1;
		while(con<=sizeof(buffer))
		{
			srand((int)time(0)+con);
			*bp=rand()%256;++bp;
			++con;
		}
		for(int q=1;q<=fi_size/sizeof(buffer)+1;++q) fwrite(buffer,sizeof(buffer),1,f02);
	}
	fclose(f02);
	printf("[STEPS]Rename and delete file.\n");
	char str[11];char *str02;
	for(int e=0;e<=9;++e)
	{
		srand((int)time(0)+e);
		str[e]=65+rand()%26;
	}
	str[10]=0;
	str02=renameFile(filename,str);
	for(int w=1;w<=10;++w) remove(str02);
	printf("[STEPS]Completed.");
	exit(0);
}

