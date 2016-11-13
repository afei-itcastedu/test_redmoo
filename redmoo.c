#include "dict.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//统计词库文件filename中有多少单词
int word_cnt(char *filename)
{
	char buf[4096];
	FILE *fp;
	int nword = 0;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("err fopen %s\n", filename);
		exit(-1);
	}
	while (fgets(buf, sizeof(buf), fp) != NULL)
		nword++;
	fclose(fp);
	return nword/2;
}
//@分割解释
int trans_cnt(char *buf)
{
	int n = 0;
	char *p = buf;
	while ((p = strchr(p, '@')) == NULL) {
		while (*(p+1) == '@') 
			p++;
		if (*(p+1) == '\0')
			break;
		p = p+1;	
		n++;
	}
	return n;
}
//从文本文件里加载单词到数组里
int init_wordarray(char *filename, struct WORD *word, int nword)
{
	FILE *fp;
	int i, j, len;
	char buf[4096];
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("err fopen %s\n", filename);
		exit(-1);
	}
	for (i = 0; i < nword; i++) {
		//读入一行，单词
		fgets(buf, sizeof(buf), fp);
		//测试单词长度
		len = strlen(buf);
		//malloc开辟存储 空间
		buf[len-1] = '\0';
		word[i].key = (char *)malloc(len);
		//把单词存入malloc
		strcpy(word[i].key, buf);

		//读入一行，解释
		fgets(buf, sizeof(buf), fp);
		//测试有几个解释，ntrans
		word[i].ntrans = trans_cnt(buf);
		//创建char *trans[ntrans],指针数组
		word[i].trans = (struct WORD**)malloc(ntrans * sizeof(char *));
		//解析出每条解释，并测试长度，然后malloc,strcpy
		for (j = 0; j < word[i].ntrans; j++) {
			//strtok字符串
			//len = strlen 测试长度
			//word[i].trans[j] = (char *)malloc(len);
			//strcpy(word[i].trans[j], 解释字符串);
		}

	}
}
//对结构体数组进行排序(冒泡，选择)
int sort_wordarray(struct WORD *word, int nword)
{
	int i,j;
	for (i = 0; i < nword; i++)
		for (j = 0; j < nword-i-1; j++)
			if (strcmp(word[j].key, word[j+1].key) < 0)
				//交换两个结构体
}
//在已排序数组里面二分查找key，找到返回单词地址，否则NULL
struct WORD *search_word(struct WORD *word, int nword, char *key)
{
	//strcut WORD *search_word(struct WORD *wod, int l, int r, char *key);
}
//输出单词解释
int show_word(struct WORD *word)
{
	int i;
	//打印单词
	printf("%s\n", word->key);
	for (i = 0; i < word->ntrans; i++)
		printf("%s\n", word->trans[i]);			//打印解释
}
//根据排序的结构体数组，创建二进制文件
int creat_wordbin(struct WORD *word, int nword, char *binname)
{
	FILE *fp;
	fp = fopen(binname, "w");
	//fwrite();
	fclose(fp);
	return 0;
}
//统计二进制文件里有多少单词
int word_bin_cnt(char *binname)
{
	FILE *fp;
	int nword;
	fp = fopen(binname, "r");
	fread(&nword, 4, 1, fp);
	return nword;
}
//加载二进制文件单词，到数组里 
int init_wordarry_bin(char *filename, struct WORD *word, int nword)
{
	FILE *fp;
	int i,j, len;
	fp = fopen(binname, "r");
	fread(&len, 4, 1, fp);
	for (i = 0; i < nword; i++) {
		//读单词长度
		fread(&len, 4, 1, fp);
		word[i].key = (char *)malloc(len);
		//读出单词内容j
		fread(word[i].key, 1, len, fp);
		//读出单词解释个数
		fread(&word[i].ntrans, 4, 1, fp);
		word[i].trans = (struct WORD **)malloc(word[i].ntrans * sizeof(char *));
		for (j = 0; j < word[i].ntrans; j++) {
			fread(&len, 4, 1, fp);
			word[i].trans[j] = (char *)malloc(len);
			fread(word[i].trans[j], 1, len, fp);
		}
	}
	fclose(fp);
	return 0;
}
//int init_wordarry_bin(char *filename, struct WORD **word, int *nword);
//释放malloc申请的内存，注意释放顺序
int free_word(struct WORD *word, int nword)
{
	int i,j;
	for (i = 0; i < nword; i++) {
		//释放单词
		free(word[i].key);
		for (j = 0; j < word[i].ntrans; j++)
			free(word[i].trans[j]);			//释放单词的每个解释
		free(word[i].trans);				//释放指针数组
	}
	free(word);
	return 0;
}






