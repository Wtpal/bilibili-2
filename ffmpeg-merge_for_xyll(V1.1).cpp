#include<Windows.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include <time.h>
using namespace std;
char address[500]="C:\\bilibili\\2807112-夏音梨梨";
char x1[]="ffmpeg -i ";
char x2[]=" -c copy -bsf:v h264_mp4toannexb -f mpegts ";
char x3[]=" -c copy -bsf:a aac_adtstoasc -movflags +faststart ";
char x4[]="\"concat:";
char x5[3000];
char x[5000];
char ts[100][10];
char mp4[100][10];
char temp[100]="flv";
char output[100];//输出文件名，包含后缀名 
int n,T,i=1,p,record=1,flag=1;
void init_mpeg(); 
void init_ts();
void init_mp4();
//void init_input();

void format();
int main()
{
	//printf("使用须知：\n\t1.素材文件请保存在同一文件夹下，名称编号以01.xxx,02.xxx,....命名\n\t2.目录尽量为英文名称避免可能出现的bug\n\t3.各种输出文件将会保存至素材文件所在的目录\n");
	//printf("注：以下说明来自网络\n\t1.第一种拼接方式需要视频尺寸一致\n\t2.规格不同的视频合并后可能会有无法预测的结果。\n\t3.待补充\n\n");
	printf("有N个视频需要被合并。\nN=");
	scanf("%d",&n); 
//	sprintf(address,"F:\\1111111");
	printf("合成T个视频。\nT=");
	scanf("%d",&T);
	printf("\n"); 
	p=n%T;
	
	printf("初始化中。。。\n"); 
	init_ts();
	init_mp4();
	printf("初始化结束。\n");
	
	for(int z=1;z<=T;z++)
		format();
	printf("\n素材合并完成\n");
	system("pause");
	return 0;
}
void init_ts()
{
	for(int i=0;i<100;++i)
	{
		ts[i][0]='\\';
		ts[i][1]=(i/10)+'0';
		ts[i][2]=(i%10)+'0';
		ts[i][3]='.';
		ts[i][4]='t';
		ts[i][5]='s';
	}
	return;
}
void init_mp4()
{
	for(int i=0;i<100;++i)
	{
		mp4[i][0]=(i/10)+'0';
		mp4[i][1]=(i%10)+'0';
		mp4[i][2]='.';
		mp4[i][3]=temp[0];
		mp4[i][4]=temp[1];
		mp4[i][5]=temp[2];
	}
	return;
}
void format()
{
		memset(x5,0,sizeof(x5));
		memset(x,0,sizeof(x));
		memset(output,0,sizeof(output));
		int n_temp,i_temp=i;
		if(p) {n_temp=(n/T)+1;p--;}
		else n_temp=n/T;
		for(i;i<i_temp+n_temp;++i)
		{
			printf("\n即将处理第%d个素材",i);
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".\n");
			sprintf(x,"%s%s\\%s%s%s%s",x1,address,mp4[i],x2,address,ts[i]);
			puts(x);
			system(x);
			printf("\n第%d个素材处理成功\n",i);
		}
		printf("\n第%d部分素材处理完毕\n",record++);
		time_t t = time(0);
		strftime( output, sizeof(output), "%m.%d",localtime(&t) );
		//printf("\n输出文件名称为(包含后缀名):");
		//scanf("%s",output);
		int p=0,j;//now position
		for(int w=i_temp;w<i_temp+n_temp;++w)
		{
			
			for(j=0;j<strlen(address);++j)
			{
				x5[p+j]=address[j];
			}
			x5[p+j]=ts[w][0];
			x5[p+j+1]=ts[w][1];
			x5[p+j+2]=ts[w][2];
			x5[p+j+3]=ts[w][3];
			x5[p+j+4]=ts[w][4];
			x5[p+j+5]=ts[w][5];
			if(w!=n) x5[p+j+6]='|';
			p+=(7+strlen(address));
		}
		x5[p+j-strlen(address)-1]='\"';
		sprintf(x,"%s%s%s%s%s\\%s(%d).flv",x1,x4,x5,x3,address,output,flag++);
		puts(x);
		system(x);
	return;
}
