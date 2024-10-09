//Adamska-Shalansaska IX/XII/MMXX

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

typedef struct Tweet Tweet_Impl;
typedef std::vector<Tweet_Impl> twitter;

Tweet tweetRead();

void menu(); 
void read();
void tweetWrite();
void sort();
void write();
void trend();
void presence();
void charPop();

int binarySearch();
int findPos();

bool contest();
bool hashtag();

std::string slice();

std::vector<std::string> insertHashtags();
std::vector<std::string> insertHashtagsR();
std::vector<std::string> insertMentions();
std::vector<int> conteggio();

twitter built();

#endif