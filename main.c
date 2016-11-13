#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dict.h"

int main(int argc, char *argv[])
{
	struct WORD *word, *keyword;
	int nword;
	char *dictname = "dict.txt";
	char *binname = "dict.dat";
	char *errmsg = "./app -text\n./app -bin -r/-w\n";
	char *exitstr = "#exit";
	char usrbuf[256];

	if (strcmp(argv[1], "-text") == 0) {
		nword = word_cnt(dictname);
		word = (struct WORD*)malloc(nword * sizeof(*word));
		init_wordarray(dictname, word, nword);
		sort_wordarray(word, nword);
	} else if (strcmp(argv[1], "-bin") == 0) {
		if (strcmp(argv[2], "-w") == 0) {
			nword = word_cnt(dictname);
			word = (struct WORD *)malloc(nword * sizeof(*word));
			init_wordarray(dictname, word, nword);
			sort_wordarray(word, nword);
			creat_wordbin(word, nword, binname);
		} else if (strcmp(argv[2], "-r") == 0) {
			nword = word_bin_cnt(binname);
			word = malloc(nword * sizeof(*word));
			init_wordarry_bin(binname, word, nword);
		} else {
			printf("%s", errmsg);
			return -1;
		}
	} else {
		printf("%s", errmsg);
		return -1;
	}

	//查找模块
	while (1) {
		printf("search word:");
		fflush(stdout);
		gets(usrbuf);	
		if (strcmp(usrbuf, exitstr) == 0)
			break;
		keyword = search_word(word, nword, usrbuf);
		if (keyword == NULL)
			printf("un find\n");
		else 
			show_word(keyword);
	}
	
	free_word(word, nword);
	return 0;
}
