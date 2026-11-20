/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* TODO: structure definitions */
struct TrieNode
{
  int count
  struct TrieNode *children[26];
}



/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url);

int addWordOccurrence(struct TrieNode *root, char* word, const int wordLength
		       /* TODO: other parameters you need */);

static void printTrieContents(struct TrieNode *node,char *buffer,int length,int bufsize);


int freeTrieMemory(/* TODO: any parameters you need */);

int getText(const char* srcAddr, char* buffer, const int bufSize);

int main(int argc, char** argv){
  /* TODO: write the (simple) main function

  /* argv[1] will be the URL to index, if argc > 1 */

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
void indexPage(const char* url)
{}

int addWordOccurrence(struct TrieNode *root, char* word, const int wordLength
		       /* TODO: other parameters you need */)
{
  struct TrieNode *spot = root;
  for(int i= 0; i< length;i++)
  {
    int index = word[i]- 'a';
    if(spot->children[index] == NULL)
      {
        spot->children[index] = createNode();
      }
  }
}

void printTrieContents(struct TrieNode *node,char *buffer,int length,int bufsize)
{
  if(node == NULL)
  {
    return;
  }


  if(node ->count > 0)
  {
    buffer[length] = '\0';
    printf("%s: %d\n", buffer, node -> count);
  }
  for(int i =0; i< 26;i++)
  {
    if(node -.> children[i] != NULL)
    {
      if(length +2>bufsize)
      {
        printf("the word buffer is too small\n");
        return;
      }
      buffer[length] ='a' +i;
      printf(node->children[i],buffer,length+1,bufsize)
    }
  }}

int freeTrieMemory(/* TODO: any parameters you need */)
{}

/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
