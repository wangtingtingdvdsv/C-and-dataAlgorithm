#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef struct HugeNumber {
	int sign;
	int* hugeNum;
	char power;
	char count;
}HugeNumber;

typedef unsigned char boolean;
#define TRUE 1
#define FALSE 0

int maxCount = 0;

void freeSpace(HugeNumber** hugeNumber);
void init(HugeNumber** hugeNumber);
void readFile(HugeNumber** hugeNumber, char* fileName);
void storageData(HugeNumber** hugeNumber, char* data);
void show(HugeNumber* hugeNumber);
boolean isHaveDot(char* str);
void storageHaveDotData(HugeNumber** hugeNumber, char* data);
void dealIntegerPart(HugeNumber** hugeNumber, int dotCount, char* data, int* length);
void dealDecimalPart(HugeNumber** hugeNumber, int dotCount, char* data, int* length);
int getDotIndex(char* data);
int getOneFromHugeNumber(int* hugeNumber, int index, int count);
void add(HugeNumber** resultHugeNumber, HugeNumber* hugeNumber1, HugeNumber* hugeNumber2);
void sub(HugeNumber** resultHugeNumber, HugeNumber* hugeNumber1, HugeNumber* hugeNumber2);  //两个巨大数相减
void applyForSpaceInAdd(HugeNumber** hugeNumber);
int getMaxCount(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2);
boolean isHugeNumberPositive(HugeNumber* hugeNumber);
int*  fromSourceToComplement(HugeNumber* hugeNumber);//将源码转换为补码
int judgeResultSign(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2, int carry);//判断运算结果的正负号
void  twoNumbersMultiply(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2, HugeNumber** resultHugeNumber);

void  twoNumbersMultiply(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2, HugeNumber** resultHugeNumber) {
	int i = 0;
	int j = 0;
	int subCarry = 0;
	int addCarry = 0;
	int result = 0;
	int* temp = (int*)calloc(sizeof(int), (hugeNumber1->count) + hugeNumber2->count);
	(*resultHugeNumber)->hugeNum = (int*)calloc(sizeof(int), (hugeNumber1->count) + hugeNumber2->count);
	(*resultHugeNumber)->count = (hugeNumber1->count) + hugeNumber2->count;
	for (i = 0; i < hugeNumber1->count; i++) {
		for (j = 0; j < hugeNumber2->count; j++) {
			 temp[i+j] += (hugeNumber1->hugeNum[i] * hugeNumber2->hugeNum[j] + subCarry)%10000;
			 subCarry = (hugeNumber1->hugeNum[i] * hugeNumber2->hugeNum[j] + subCarry) / 10000;
		}
		temp[i + j] = subCarry;
		subCarry = 0;
	}

	for (i = 0; i < hugeNumber1->count + hugeNumber2->count; i++) {
		(*resultHugeNumber)->hugeNum[i] = (temp[i] + addCarry) % 10000;
		addCarry = (temp[i] + addCarry) / 10000;
	}
	temp[i] = temp[i] + addCarry;
	
	//printf("==:%d\n", temp[i]);
	//printf("++:%d\n", (*resultHugeNumber)->hugeNum[i]);
	(*resultHugeNumber)->sign = hugeNumber1->sign^hugeNumber2->sign;
	

	show(*resultHugeNumber);

}

int judgeResultSign(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2, int carry) {
	int sign;
	if (hugeNumber1->sign == hugeNumber2->sign) {
		sign = hugeNumber1->sign;
	}
	else {
		sign = hugeNumber1->sign ^ hugeNumber2->sign ^ carry;
	}
	return sign;
}
int*  fromSourceToComplement(HugeNumber* hugeNumber) {   
	/*
		微易码补码(两数相加，两个正数相加除外)
		1.负数补码等于9999减去巨大数的每一位。（补码位数应为两个数中的最大count+1位）。
		2.将进位加到末位，再将之前进位所在的万进制位置为0；
		2.运算结果正负号判断（一正一负相加的情况）：用进位和两位巨大数的符号按位异或所得结果用来表示运算结果的正负。
		3.若运算结果为负，应将结果由补码转换为原码。转换方法：用9999减去补码的每一位
	*/

	int* complementNumber  = (int*)calloc(sizeof(int), maxCount + 1);
	int i;
	if (hugeNumber->sign == 0) {
		for (i = 0; i < hugeNumber->count; i++)
		{
			complementNumber[i] = hugeNumber->hugeNum[i];
		}
		for (i; i < maxCount + 1; i++) {
			complementNumber[i] = 0000;
		}
	}
	else if (hugeNumber->sign == 1)
	{
		for (i = 0; i < hugeNumber->count; i++)
		{
			complementNumber[i] = 9999 - hugeNumber->hugeNum[i];
		}
		for (i; i < maxCount + 1; i++) {
			complementNumber[i] = 9999;
		}
	}
	return complementNumber;
}

boolean isHugeNumberPositive(HugeNumber* hugeNumber) {
	if (hugeNumber->sign == 0) {
		return TRUE;
	}
	else if (hugeNumber->sign == 1) {
		return FALSE;
	}
}

int getMaxCount(HugeNumber* hugeNumber1, HugeNumber* hugeNumber2) {
	if (hugeNumber1->count > hugeNumber2->count){
		return hugeNumber1->count;
	} else {
		return hugeNumber2->count;
	}
}
void applyForSpaceInAdd(HugeNumber** hugeNumber) {
	
		(*hugeNumber)->hugeNum = (int*)calloc(sizeof(int), maxCount+2);
		(*hugeNumber)->count = maxCount + 2;
	
	//结构体中的power还未被赋值。

}
void sub(HugeNumber** resultHugeNumber, HugeNumber* hugeNumber1, HugeNumber* hugeNumber2) {
	HugeNumber* hugeNumberOpposite = NULL;
	init(&hugeNumberOpposite);
	hugeNumberOpposite->hugeNum = (int*)calloc(sizeof(int), hugeNumber2->count);
	hugeNumberOpposite->count = hugeNumber2->count;
	hugeNumberOpposite->hugeNum = hugeNumber2->hugeNum;
	hugeNumberOpposite->sign = !(hugeNumber2->sign);
	
	add(resultHugeNumber, hugeNumber1, hugeNumberOpposite);

	//freeSpace(&hugeNumberOpposite);（这里如果释放的话，那么就会将hugeNumberOpposite->hugeNum所指向的空间释放两次）。
}
void add(HugeNumber** resultHugeNumber, HugeNumber* hugeNumber1, HugeNumber* hugeNumber2) {
	int carry = 0;
	int number1 = 0;
	int number2 = 0;
	int* complement1 = NULL;
	int* complement2 = NULL;
	int i = 0;
	int j;
	
	applyForSpaceInAdd(resultHugeNumber);
	//两个数相加，其实是源码相加
	complement1 = fromSourceToComplement(hugeNumber1);
	
	
	complement2 = fromSourceToComplement(hugeNumber2);
	
	
	for (i = 0; i < maxCount+1; i++) {
		number1 = getOneFromHugeNumber(complement1, i, maxCount+1);
		number2 = getOneFromHugeNumber(complement2, i, maxCount+1);
		(*resultHugeNumber)->hugeNum[i] = (number1 + number2 + carry)%10000;
		carry = (number1 + number2 + carry) / 10000;
	}
	(*resultHugeNumber)->sign = judgeResultSign(hugeNumber1, hugeNumber2, carry);
	(*resultHugeNumber)->hugeNum[i] = carry;
	
	if (!(hugeNumber1->sign == 0 && hugeNumber2->sign == 0))
	{
		(*resultHugeNumber)->hugeNum[i] = 0;
		(*resultHugeNumber)->hugeNum[0] = (*resultHugeNumber)->hugeNum[0] + carry;
		if ((*resultHugeNumber)->sign == 1) {
			for (i = 0; i < maxCount + 1; i++) {
				(*resultHugeNumber)->hugeNum[i] = 9999 - (*resultHugeNumber)->hugeNum[i];

			}
		}
	}
	
	show(*resultHugeNumber);

	free(complement1);
	free(complement2);

}

int getOneFromHugeNumber(int* hugeNumber, int index, int count){
	int oneHugeNumber = 0000;
	if (index < count) {
		return hugeNumber[index];
	}
	return oneHugeNumber;
}

int getDotIndex(char* data) {
	int i;
	for (i = 0; i < strlen(data); i++) {
		if (data[i] == '.') {
			return i;
		}
	}
}
void dealDecimalPart(HugeNumber** hugeNumber, int dotCount, char* data, int* length) {
	
	int dotIndex = getDotIndex(data);
	int i;
	int j;
	for (i = 0; i < dotCount; i++) {
		if (i == 0 && ((strlen(data) - dotIndex - 1) % 4) != 0) {
			for (j = 0; j < (strlen(data) - dotIndex - 1) % 4; j++) {
				(*hugeNumber)->hugeNum[i] = (*hugeNumber)->hugeNum[i] + ((int)data[(*length) - 1] - 48)*pow(10, j);
				(*length)--;
			}
			(*hugeNumber)->hugeNum[i] = (*hugeNumber)->hugeNum[i] * pow(10, 4 - (strlen(data) - dotIndex - 1) % 4);
		}
		else {
			for (j = 0; j < 4; j++) {
				(*hugeNumber)->hugeNum[i] = (*hugeNumber)->hugeNum[i] + ((int)data[(*length) - 1] - 48)*pow(10, j);
				(*length)--;
			}
		}
	}
}

void dealIntegerPart(HugeNumber** hugeNumber, int dotCount, char* data, int* length) {
	int i;
	int j;
	for (i = dotCount; i < (*hugeNumber)->count; i++) {
		for (j = 0; j < 4; j++) {
			if (data[(*length) - 1] == '+' || data[(*length) - 1] == '-' || (*length) - 1 < 0) {
				return;
			}
			(*hugeNumber)->hugeNum[i] = (*hugeNumber)->hugeNum[i] + ((int)data[(*length) - 1] - 48)*pow(10, j);

			(*length)--;
		}
	}
}

void storageHaveDotData(HugeNumber** hugeNumber, char* data) {
	int dotIndex = getDotIndex(data);
	int length = strlen(data);
	int intCount;
	int dotCount;
	if (data[0] ==   '+'){
		intCount = (dotIndex - 1 + 3) / 4;
		dotCount = (length - dotIndex-1 + 3) / 4;
		(*hugeNumber)->sign = 0;   //0为正
		(*hugeNumber)->count = intCount + dotCount;
	}
	else if (data[0] == '-'){
		intCount = (dotIndex - 1 + 3) / 4;
		dotCount = (length - dotIndex -1+ 3) / 4;
		(*hugeNumber)->sign = 1;
		(*hugeNumber)->count = intCount + dotCount;
	} else {
		intCount = (dotIndex + 3) / 4;  //2
		dotCount = (length - dotIndex -1+ 3) / 4;  //
		(*hugeNumber)->sign = 0 ; 
		(*hugeNumber)->count = intCount + dotCount;;
	}
	(*hugeNumber)->power = intCount;
	(*hugeNumber)->hugeNum = (int*)calloc(sizeof(int), (*hugeNumber)->count);
	//处理小数
	dealDecimalPart(hugeNumber, dotCount, data, &length);
	//处理整数
	length--;//跳过小数点
	dealIntegerPart(hugeNumber, dotCount, data, &length);
}

boolean isHaveDot(char* str) {
	int i = -1;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '.') {
			return TRUE;
		}
	}
	return FALSE;
}
void show(HugeNumber* hugeNumber) {
	int i = 0;
	int* hugeNum = hugeNumber->hugeNum;
	
	for (i = 0; i < (hugeNumber->count); i++) {
				printf("%04d\n", hugeNum[i]);
	}
}

void storageData(HugeNumber** hugeNumber, char* data) {
	int length = strlen(data);
	int i = 0;
	int j;
	
	if (data[0] == '+'){
		(*hugeNumber)->sign = 0;   //0为正
		(*hugeNumber)->count = ((length-1+3) / 4);

	} else if(data[0] == '-'){
		(*hugeNumber)->sign = 1;
		(*hugeNumber)->count = ((length - 1+3) / 4);
	} else {
		(*hugeNumber)->sign = 0;   //1233这种
		(*hugeNumber)->count = ((length+3)/ 4);
	}
	(*hugeNumber)->power = (*hugeNumber)->count;
	(*hugeNumber)->hugeNum = (int*)calloc(sizeof(int), ((*hugeNumber)->count));
	dealIntegerPart(hugeNumber, 0, data, &length);
}
void readFile(HugeNumber** hugeNumber, char* fileName) {
	FILE* fpIn;
	char data[100];
	int i = 0;
	fpIn = fopen(fileName, "r");
	fgets(data, 100, fpIn);
	if (isHaveDot(data)) {
		storageHaveDotData(hugeNumber, data);
	} else {
		storageData(hugeNumber, data);
	}
	show(*hugeNumber);
	printf("\n");
	fclose(fpIn);
}

void init(HugeNumber** hugeNumber) {
	HugeNumber* space = NULL;
	if (*hugeNumber != NULL) {
		return;
	}
	space = (HugeNumber*)malloc(sizeof(HugeNumber));
	space->hugeNum = NULL;
	*hugeNumber = space;
}

void freeSpace(HugeNumber** hugeNumber) {
	if (*hugeNumber == NULL) {
		return;
	}
	
	if (((*hugeNumber)->hugeNum) != NULL)
	{
		
		free((*hugeNumber)->hugeNum);
	}
	
	free(*hugeNumber);
	*hugeNumber = NULL;
}

int main(void) {
	char* data;
	HugeNumber* hugeNumber1 = NULL;
	HugeNumber* hugeNumber2 = NULL;
	HugeNumber* resultHugeNumber = NULL;

	init(&hugeNumber1);
	init(&hugeNumber2);
	
	printf("巨大数1\n");
	readFile(&hugeNumber1, "hugeNumber1.txt");
	printf("巨大数2\n");
	readFile(&hugeNumber2, "hugeNumber2.txt");
	maxCount = getMaxCount(hugeNumber1, hugeNumber2);
	
	/*两个巨大数相加*/
	printf("巨大数相加\n");
	init(&resultHugeNumber);
	add(&resultHugeNumber, hugeNumber1, hugeNumber2);
	freeSpace(&resultHugeNumber);
	
	
	/*两个巨大数相乘*/
	printf("巨大数相乘\n");
	init(&resultHugeNumber);
	twoNumbersMultiply(hugeNumber1, hugeNumber2, &resultHugeNumber);
	freeSpace(&resultHugeNumber);

	/*两个巨大数相减*/
	printf("巨大数相减\n");
	init(&resultHugeNumber);
	sub(&resultHugeNumber, hugeNumber1, hugeNumber2);
	freeSpace(&resultHugeNumber);

	
	freeSpace(&hugeNumber1);
	freeSpace(&hugeNumber2);
	
	system("pause");
	return 0;
}
