#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

typedef struct Room
{
	char house[10]; //房间号
	char name[20]; //客人姓名
	char standard[20]; //房间标准
	int cash; //押金
	int perday;
	int perhour;
	int choose; //客人选择收费方式，1为按天收费，0为按小时收费
	time_t time1970; //入住时间
} room; //房间的结构

void creatpassword(FILE*, char*); //创建密码函数
void creatroom(FILE*, room*); //创建房间函数
void creatguest(FILE*, room*, int); //创建客人函数
void login(room*, int, char*); //a.登记入住
void change(room*, int, char*); //b.入住信息修改

int main(int argc, char* argv[]) {
	bool judgment = false; //以此判断文件是否存在
	FILE* fpassword = NULL; //密码文件指针
	char password[17] = { 0 }; //密码长度最长为16位
	char theturecode[17] = { 0 }; //真正的密码
	char function = 0; //菜单功能项
	FILE* froom = NULL; //房间文件指针，完成不变量记录
	FILE* fguest = NULL; //客人文件指针，完成变量记录
	room* hotle = NULL; //结构数组
	char hou[10] = { 0 }; //房间号通用数组
	char sta[20] = { 0 }; //房间标准和客人姓名通用数组
	int num = 0; //房间数量


	if (judgment = fopen_s(&fpassword, "password.bin", "rb")) { //更安全的函数，正确打开返回0，不正确返回非0
		creatpassword(fpassword, password);
		judgment = fopen_s(&fpassword, "password.bin", "rb");
		if (judgment != 0) {
			exit(1); //打开文件失败，文件指针此时为未知值，强行终止程序
		}
	}
	fscanf_s(fpassword, "%s", theturecode, 17); //更安全的函数fscanf_s，宽域检查
	printf("欢迎进入酒店管理系统\n请输入密码：");
	while (1) {
		char ch = 0;
		scanf_s("%16s", password, 17); //防止缓冲区溢出
		printf("\n");
		while ((ch = getchar()) != '\n' && ch != EOF); //清空缓冲区，避免出现多个友好输出
		if ((strcmp(password, theturecode)) == 0) { //返回0则为相等
			break;
		}
		for (int ret = 0; ret < 17; ret++) {
			password[ret] = 0; //重置字符串数组为空
		}
		printf("密码错误，请重试：");
	}
	fclose(fpassword);
	for (int ret = 0; ret < 17; ret++) {
		password[ret] = 0; //重置字符串数组为空
	}


	if (judgment = fopen_s(&froom, "room.txt", "r")) { //更安全的函数，正确打开返回0，不正确返回非0
		creatroom(froom, hotle);
		judgment = fopen_s(&froom, "room.txt", "r");
		if (judgment != 0) {
			exit(1); //打开文件失败，文件指针此时为未知值，强行终止程序
		}
	}
	fscanf_s(froom, "%d\n", &num); //每从txt读一个数据换一次行
	hotle = (room*)malloc(sizeof(room) * num); //创建完文件或打开完文件直接将数据储存进内存
	for (int ret = 0; ret < num; ret++) {
		for (int i = 0; i < 10; i++) {
			hotle[ret].house[i] = 0;
		}
		for (int i = 0; i < 20; i++) {
			hotle[ret].name[i] = 0;
			hotle[ret].standard[i] = 0;
		}
		hotle[ret].cash = 0;
		hotle[ret].perday = 0;
		hotle[ret].perhour = 0;
		hotle[ret].choose = 0;
		hotle[ret].time1970 = 0; //结构数组的遍历
	} //初始化所有成员为0
	for (int ret = 0; ret < num; ret++) {
		fscanf_s(froom, "%s\n", hotle[ret].house, 10);
		fscanf_s(froom, "%s\n", hotle[ret].standard, 20);
		fscanf_s(froom, "%d\n", &hotle[ret].cash);
		fscanf_s(froom, "%d\n", &hotle[ret].perhour);
		fscanf_s(froom, "%d\n", &hotle[ret].perday);
	} //每从txt读一个数据换一次行


	if ((judgment = fopen_s(&fguest, "guest.txt", "r")) == 0) {//更安全的函数，正确打开返回0，不正确返回非0
		for (int ret = 0; ret < num; ret++) {
			fscanf_s(fguest, "%s\n", hotle[ret].name, 20);
			if (hotle[ret].name[0] == '0') {
				hotle[ret].name[0] = 0;
			} //重置文件中客人名字
			fscanf_s(fguest, "%d\n", &hotle[ret].choose);
			fscanf_s(fguest, "%lld\n", &hotle[ret].time1970);
		} //每从txt读一个数据换一次行
		fclose(fguest);
	}


menu: //菜单地点
	while (1) {
		char ch = 0;
		for (int ret = 0; ret < 60; ret++) {
			printf("\n"); //尽量通过多次输出覆盖密码
		}
		printf("------------------------------------------------------------------------------\n");
		printf("欢迎进入酒店房间登记与计费管理系统！\n");
		printf("请选择系统功能项：\n");
		printf("a.登记入住\n");
		printf("b.入住信息修改\n");
		printf("c.房间入住情况查询\n");
		printf("d.当前费用查询\n");
		printf("e. 结账退房\n");
		printf("f. 退出系统\n");
		printf("------------------------------------------------------------------------------\n");
		scanf_s("%c", &function, 1);


		switch (function) {
		case 97: //a.登记入住
			printf("请输入密码：");
			while (1) {
				char ch = 0;
				scanf_s("%16s", password, 17); //防止缓冲区溢出
				while ((ch = getchar()) != '\n' && ch != EOF); //清空缓冲区
				if ((strcmp(password, theturecode)) == 0) { //返回0则为相等
					break;
				}
				for (int ret = 0; ret < 17; ret++) {
					password[ret] = 0; //重置字符串数组为空
				}
				printf("密码错误，请重试：");
			}
			for (int ret = 0; ret < 17; ret++) {
				password[ret] = 0; //重置字符串数组为空
			}
			login(hotle, num, hou);
			break;


		case 98: //b.入住信息修改
			printf("请输入密码：");
			while (1) {
				char ch = 0;
				scanf_s("%16s", password, 17); //防止缓冲区溢出
				while ((ch = getchar()) != '\n' && ch != EOF); //清空缓冲区
				if ((strcmp(password, theturecode)) == 0) { //返回0则为相等
					break;
				}
				for (int ret = 0; ret < 17; ret++) {
					password[ret] = 0; //重置字符串数组为空
				}
				printf("密码错误，请重试：");
			}
			for (int ret = 0; ret < 17; ret++) {
				password[ret] = 0; //重置字符串数组为空
			}
			change(hotle, num, hou);
			break;


		case 99: //c.房间入住情况查询
			printf("（1）按房间号查询\n（2）按房间标准查询\n");
			getchar();
			scanf_s("%c", &function, 1);
			if (function == '1') {
				printf("请输入房间号：");
				scanf_s("%s", hou, 10);
				for (int ret = 0; ret < num; ret++) {
					if (strcmp(hou, hotle[ret].house) == 0) { //查询有没有这个房间
						for (int i = 0; i < 10; i++) {
							hou[i] = 0; //清空房间数组
						}
						if (hotle[ret].name[0] == 0) { //如果没有人住
							printf("当前房间无人\n");
							printf("房间标准：%s\n押金：%d\n", hotle[ret].standard, hotle[ret].cash);
							printf("每小时租金：%d\n每天租金：%d\n", hotle[ret].perhour, hotle[ret].perday);
							getchar();
							getchar();
							goto menu;
						}
						else { //如果有人住
							printf("该房已有客人");
							getchar();
							getchar();
							goto menu;
						}
					}
				}
				for (int i = 0; i < 10; i++) {
					hou[i] = 0; //清空房间数组
				}
				printf("查无此房");
				getchar();
				getchar();
			}
			else if (function == '2') {
				printf("请输入房间标准：");
				scanf_s("%s", sta, 20);
				printf("当前标准房间有：");
				for (int ret = 0; ret < num; ret++) {
					if (strcmp(sta, hotle[ret].standard) == 0) { //查询有没有这个房间标准
						if (hotle[ret].name[0] == 0) {
							printf("%s ", hotle[ret].house);
						}
					}
				}
				for (int i = 0; i < 10; i++) {
					sta[i] = 0; //清空房间标准数组
				}
				printf("\t按任意键返回");
				getchar();
				getchar();
			}
			else {
				printf("错误命令，按回车键返回");
				getchar();
				getchar();
			}
			break;


		case 100: //d.当前费用查询
			printf("（1）按房间号查询\n（2）按客人姓名查询\n");
			getchar();
			scanf_s("%c", &function, 1);
			if (function == '1') {
				printf("请输入房间号：");
				scanf_s("%s", hou, 10);
				for (int ret = 0; ret < num; ret++) {
					if (strcmp(hou, hotle[ret].house) == 0) {
						for (int i = 0; i < 10; i++) {
							hou[i] = 0; //清空房间数组
						}
						if (hotle[ret].name[0] != 0) {
							if (hotle[ret].choose == 1) {
								printf("当前费用为：%lld", ((time(NULL) - hotle[ret].time1970) / 86400 + 1) * hotle[ret].perday); //换算成天
							}
							else {
								printf("当前费用为：%lld", ((time(NULL) - hotle[ret].time1970) / 3600 + 1) * hotle[ret].perhour); //换算成时
							}
							getchar();
							getchar();
							goto menu;
						}
						else {
							printf("该房间未入住");
							getchar();
							getchar();
							goto menu;
						}
					}
				}
				for (int i = 0; i < 10; i++) {
					hou[i] = 0; //清空房间数组
				}
				printf("该房间不存在");
				getchar();
				getchar();
			}
			else if (function == '2') {
				printf("请输入客人姓名：");
				scanf_s("%s", sta, 20);
				for (int ret = 0; ret < num; ret++) {
					if (strcmp(sta, hotle[ret].name) == 0) {
						for (int i = 0; i < 10; i++) {
							sta[i] = 0; //清空客人姓名数组
						}
						if (hotle[ret].choose == 1) {
							printf("当前费用为：%lld", ((time(NULL) - hotle[ret].time1970) / 86400 + 1) * hotle[ret].perday); //换算成天
						}
						else {
							printf("当前费用为：%lld", ((time(NULL) - hotle[ret].time1970) / 3600 + 1) * hotle[ret].perhour); //换算成时
						}
						getchar();
						getchar();
						goto menu;
					}
				}
				for (int i = 0; i < 10; i++) {
					sta[i] = 0; //清空客人姓名数组
				}
				printf("该客人未登记");
				getchar();
				getchar();
			}
			else {
				printf("错误命令，按回车键返回");
				getchar();
				getchar();
			}
			break;


		case 101: //e. 结账退房
			printf("请输入房间号：");
			scanf_s("%s", hou, 10);
			for (int ret = 0; ret < num; ret++) {
				if (strcmp(hou, hotle[ret].house) == 0) {
					if (hotle[ret].choose == 1) {
						printf("退房成功，房间费用为：%lld\n", ((time(NULL) - hotle[ret].time1970) / 86400 + 1) * hotle[ret].perday); //换算成天
					}
					else {
						printf("退房成功，房间费用为：%lld\n", ((time(NULL) - hotle[ret].time1970) / 3600 + 1) * hotle[ret].perhour); //换算成时
					}
					printf("返还客人押金：%d", hotle[ret].cash);
					for (int i = 0; i < 20; i++) {
						hotle[ret].name[i] = 0;
					}
					hotle[ret].choose = 0;
					hotle[ret].time1970 = 0;
					for (int i = 0; i < 10; i++) {
						hou[i] = 0; //清空房间数组
					}
					getchar();
					getchar();
					goto menu;
				}
			}
			for (int i = 0; i < 10; i++) {
				hou[i] = 0; //清空房间数组
			}
			printf("该房间不存在或未入住");
			getchar();
			getchar();
			break;


		case 102: //f. 退出系统
			creatguest(fguest, hotle, num);
			exit(0);
		default:


			break;
		}
	}
}

void creatpassword(FILE* fpassword, char* password) {
	bool judgment = fopen_s(&fpassword, "password.bin", "wb"); //正确打开返回0，不正确返回非0，布尔变量判断创建文件时是否出现问题
	if (judgment != 0) {
		exit(-1); //创建文件失败，强制中止程序
	}
	printf("系统未设置密码\n请创建新密码（新密码不得大于16位）：");
	scanf_s("%16s", password, 17); //防止缓冲区溢出
	printf("\n");
	fprintf(fpassword, "%s", password);
	fclose(fpassword); //配对只写打开文件函数
	for (int ret = 0; ret < 17; ret++) {
		password[ret] = 0; //重置字符串数组为空
	}
}

void creatguest(FILE* fguest, room* hotle, int num) {
	bool judgment = fopen_s(&fguest, "guest.txt", "w"); //正确打开返回0，不正确返回非0，布尔变量判断创建文件时是否出现问题
	if (judgment != 0) {
		exit(-100); //创建文件失败，强制中止程序
	}
	for (int ret = 0; ret < num; ret++) { //每写进txt中一个数据就换一次行
		if (hotle[ret].name[0] == 0) { //防止写入文件为空
			fprintf(fguest, "%c\n", '0');
		}
		else {
			fprintf(fguest, "%s\n", hotle[ret].name);
		}
		fprintf(fguest, "%d\n", hotle[ret].choose);
		fprintf(fguest, "%lld\n", hotle[ret].time1970);
	} //顺序一定不能出错
	fclose(fguest); //关闭对应的只写文件
	free(hotle); //关闭程序前释放内存（虽然没用）
}

void creatroom(FILE* froom, room* hotle) {
	int num = 0; //酒店房间数量
	bool judgment = fopen_s(&froom, "room.txt", "w"); //正确打开返回0，不正确返回非0，布尔变量判断创建文件时是否出现问题
	if (judgment != 0) {
		exit(-1); //创建文件失败，强制中止程序
	}
	printf("酒店房间信息不存在\n请根据提示导入房间信息：\n\n");
	printf("本酒店共有房间数量：");
	scanf_s("%d", &num);
	fprintf(froom, "%d\n", num);
	hotle = (room*)malloc(sizeof(room) * num);
	printf("请录入每个房间信息\n\n");
	for (int ret = 0; ret < num; ret++) { //每写进txt中一个数据就换一次行
		printf("第%d个房间：\n", ret + 1);

		printf("门牌号：");
		scanf_s("%s", hotle[ret].house, 10);
		fprintf(froom, "%s\n", hotle[ret].house);

		printf("房间标准：");
		scanf_s("%s", hotle[ret].standard, 20);
		fprintf(froom, "%s\n", hotle[ret].standard);

		printf("房间押金：");
		scanf_s("%d", &hotle[ret].cash);
		fprintf(froom, "%d\n", hotle[ret].cash);

		printf("每小时金额：");
		scanf_s("%d", &hotle[ret].perhour);
		fprintf(froom, "%d\n", hotle[ret].perhour);

		printf("每天金额：");
		scanf_s("%d", &hotle[ret].perday);
		fprintf(froom, "%d\n", hotle[ret].perday);
		printf("\n");
	} //顺序不能出问题
	fclose(froom); //关闭配对的只写文件
	free(hotle); //释放掉装载信息的内存
}

void login(room* hotle, int num, char* hou) {
	printf("请输入入住房间号：");
	scanf_s("%s", hou, 10);
	for (int ret = 0; ret < num; ret++) {
		if (strcmp(hou, hotle[ret].house) == 0) { //查询有没有这个房间
			for (int i = 0; i < 10; i++) {
				hou[i] = 0; //清空房间数组
			}
			if (hotle[ret].name[0] == 0) { //如果没有人住
				printf("房间标准：%s\n押金：%d\n", hotle[ret].standard, hotle[ret].cash);
				printf("每小时租金：%d\n每天租金：%d\n", hotle[ret].perhour, hotle[ret].perday);
				printf("请输入客人姓名：");
				scanf_s("%s", hotle[ret].name, 20);
				printf("客人选择收费方式（1为按天，0为按时）：");
				scanf_s("%d", &hotle[ret].choose);
				hotle[ret].time1970 = time(NULL);
				printf("登记成功，按回车键返回");
				getchar();
				getchar();
				return;
			}
			else { //如果有人住
				printf("该房已有客人，按回车键返回");
				getchar();
				getchar();
				return;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		hou[i] = 0; //清空房间数组
	}
	printf("查无此房，按回车键返回");
	getchar();
	getchar();
}

void change(room* hotle, int num, char* hou) {
	printf("请输入入住房间号：");
	scanf_s("%s", hou, 11);
	for (int ret = 0; ret < num; ret++) {
		if (strcmp(hou, hotle[ret].house) == 0) { //查询有没有这个房间
			for (int i = 0; i < 10; i++) {
				hou[i] = 0; //清空房间数组
			}
			if (hotle[ret].name[0] == 0) { //如果没有人住
				printf("该房没有客人，按回车键返回");
				getchar();
				getchar();
				return;
			}
			else { //如果有人住
				printf("客人姓名：%s\n收费方式：%d\n时间：%lld时\n", hotle[ret].name, hotle[ret].choose, (time(NULL) - hotle[ret].time1970) / 60 + 1);
				printf("请输入客人姓名：");
				scanf_s("%s", hotle[ret].name, 20);
				printf("客人选择收费方式（1为按天，0为按时）：");
				scanf_s("%d", &hotle[ret].choose);
				printf("变更成功，按回车键返回");
				getchar();
				getchar();
				return;
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		hou[i] = 0; //清空房间数组
	}
	printf("查无此房，按任意键返回");
	getchar();
	getchar();
}