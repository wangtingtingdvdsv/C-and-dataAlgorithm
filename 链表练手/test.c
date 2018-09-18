/*待完成任务1.用线性表
			2.初始化 销毁 尾加 查找 
			3.用void*类型。
*/
#include <stdio.h>
#include "link.h"

void main(void) {
	LinkTable* table = NULL;
	char a[10] = "yyyyyy";
	char b[10] = "eeeeeee";
	void* var;

	initLink(&table);
	printf("初始化完成\n");
	addNode(&table, a);
	printf("一个节点追加成功\n");

	addNode(&table, b);
	printf("两个节点追加成功\n");
	printf("节点显示如下\n");
	show(table);

	printf("删除功能\n");
	var = removeNode(b, &table);

	//printf("查找功能\n");
	//var = findByValue(b, table);
	//var = findByIndex(2, table);
	printf("%s\n", var);
	printf("删除之后\n");
	show(table);
	printf("\n\n");

	while (table != NULL)
	{
		destoryLink(&table);
		printf("链表摧毁完成\n");
	}
	
	system("pause");
}