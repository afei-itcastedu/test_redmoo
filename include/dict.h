#ifndef _DICT_H_
#define _DICT_H_
struct WORD {
	char *key;		//单词
	int n_trans;	//单词解释个数
	char **trans;	//单词解释
};

int word_cnt(char *filename);
int init_wordarray(char *filename, struct WORD *word, int nword);
int sort_wordarray(struct WORD *word, int nword);
struct WORD *search_word(struct WORD *word, int nword, char *key);
int show_word(struct WORD *word);
int creat_wordbin(struct WORD *word, int nword, char *binname);
int word_bin_cnt(char *binname);
int init_wordarry_bin(char *filename, struct WORD *word, int nword);
int free_word(struct WORD *word, int nword);

#endif





