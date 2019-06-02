/* *********************************************************************
*                  面向过程程序设计综合应用
*    选    题  设备管理系统 Equipment Management System
*    姓    名  黄远鹏        学    号  183401050225
*    班    级  软件1802
*    完成时间  2019年5月31日
* ******************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct _Date
{
	int year,month,day;
};
typedef struct _Equipment
{
	int id;    // 设备编号(8位数)
	char name[50];   // 仪器名称
	char type[50];   // 型号规格
	double price;    // 单价
	struct _Date boughtDate;    // 购入日期
	char person[50];    // 领用人
	char status[100];    // 使用状况
	char postscript[110];    // 备注(50字内)
	struct _Equipment *pre,*next;   // 前趋与后继指针
	_Equipment()   // 构造函数初始化两个指针为NULL
	{
		pre=NULL;
		next=NULL;
	}
}equip;

void ChangeColor();
inline void PrintDirection();
void InputFromFile();
equip *head=new equip;   // 此程序里的链表是"带头结点"的双向链表
bool isSaved=false;   // true:已保存过数据   false:无保存记录

int main()
{
	char choice;      // choice 接收由用户输入的指令代码
	while(true)
	{
		system("cls");     // 清屏
		system("title 设备管理系统");     // 更改窗口标题
		PrintDirection();

		choice = getchar();
		fflush(stdin);
		switch(choice)
		{
		case '1':InputFromFile();break;
		case '2':break;
		case '3':break;
		case '4':break;
		case '5':break;
		case '6':break;
		case '7':break;
		case '8':break;
		case '9':ChangeColor();break;
		case '0':break;

		default:puts("输入错误，请重新输入。");system("pause");break;
		}

	}


	return 0;
}

/* *********************************************************************
|    函数名：ChangeColor
|    函数功能：更改窗口背景颜色与字体颜色
\  ******************************************************************** */
void ChangeColor()
{
	system("title 设备管理系统  -  颜色修改");
	char ColorChoice[3]="";
	puts("请输入您要更改的背景与字体颜色，字符不区分大小写，以回车结束：");
	puts("    0 = 黑色	     8 = 灰色");
	puts("    1 = 蓝色	     9 = 淡蓝色");
	puts("    2 = 绿色	     A = 淡绿色");
	puts("    3 = 浅绿色     B = 淡浅绿色");
	puts("    4 = 红色	     C = 淡红色");
	puts("    5 = 紫色	     D = 淡紫色");
	puts("    6 = 黄色	     E = 淡黄色");
	puts("    7 = 白色	     F = 亮白色");
	puts("示例: 输入\"fc\"将设置背景为亮白色，字体为淡红色。");
	puts("如需恢复默认颜色，请输入\"**\"；返回主菜单，请输入\"##\"。");
	printf(">>> ");
	while(true)
	{
		ColorChoice[0]=getchar();
		ColorChoice[1]=getchar();
		fflush(stdin);
		if(strcmp(ColorChoice,"**")==0)     // 恢复默认颜色
		{
			system("color 07");
			break;
		}
		else if(strcmp(ColorChoice,"##")==0)    // 返回主菜单
			break;
		else if(!isxdigit(ColorChoice[0]) || !isxdigit(ColorChoice[1]))  // 输入错误
			printf("输入错误，请重新输入：");
		else if(ColorChoice[0]==ColorChoice[1])  // 背景与字体同色
			printf("不能将背景与字体设置为同一颜色。请重新输入：");
		else
		{
			char ColorMode[10]="color ";
			strcat(ColorMode,ColorChoice);
			system(ColorMode);
			break;
		}
	}
	return;
}
/* *********************************************************************
|    函数名：InputFromFile
|    函数功能：从文件读入已有信息
\  ******************************************************************** */
void InputFromFile()
{
	system("title 设备管理系统 - 从文件录入信息");
	puts("请输入文件名或文件的地址，以回车结束。注意：地址中的'\\'应写作\"\\\\\"。");
	printf(">>> ");
	char fileName[200];       // 文件名或地址
	scanf("%[^\n]",fileName);
	FILE *fp=fopen(fileName,"r");
	if(fp==NULL)   // 未打开成功
	{
		puts("无法打开指定的文件，请重试。");
		system("pause");
		return;
	}
	equip *p=head;
	while(p->next!=NULL)
	{
		p=p->next;       // 从链表尾开始添加新内容
	}
	char temp[500];   // 假定一条数据的最大长度为500个字符
	equip *s;
	int cnt=0;   // 记录读入数据条数
	while(fgets(temp,500,fp)!=NULL)
	{
		s=new equip;
		p->next=s;
		s->pre=p;
		sscanf(temp,"%d %s %s %lf %d-%d-%d %s %s %s",&s->id,s->name,s->type,
			&s->price,&s->boughtDate.year,&s->boughtDate.month,&s->boughtDate.day,
			s->person,s->status,s->postscript);
		p=s;
		cnt++;
	}
	printf("成功读入 %d 条数据。",cnt);
	system("pause");
	return;
}

/* *********************************************************************
|    函数名：PrintDirection
|    函数功能：输出提示信息
\  ******************************************************************** */
inline void PrintDirection()
{
	printf("     * * * * *  设 备 管 理 系 统  * * * * *\n\n");
	puts("     * * * * * *   输入 / 添加   * * * * * *");
	puts("             1 - 从文件录入信息");
	puts("             2 - 批量录入新信息");
	puts("             3 - 增加一条新信息");
	puts("     * * * * * *   查询 / 保存   * * * * * *");
	puts("             4 - 查看信息");
	puts("             5 - 关键字查找");
	puts("             6 - 保存已有信息");
	puts("     * * * * * *   修改 / 删除   * * * * * *");
	puts("             7 - 修改信息");
	puts("             8 - 删除信息");
	puts("     * * * * * *     系统设置    * * * * * *");
	puts("             9 - 修改窗口与字体颜色");
	puts("             0 - 退出系统");
	printf("请选择：");
}



/* *********************************************************************
|    函数名：111
|    函数功能：111
|    接口参数：111
|    返回值：111
\  ******************************************************************** */