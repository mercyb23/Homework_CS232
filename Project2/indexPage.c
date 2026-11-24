/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Max size of the text we read from a web page */
#define MAX_PAGE_SIZE 300000

/* Max length of a word path while we print the trie */
#define MAX_WORD_BUF 1000

/* One node in the trie. Each node can have up to 26 children (a-z). */
typedef struct TrieNode {
  int count;                      /* how many times this word was seen */
  struct TrieNode *children[26];  /* child for each letter, or NULL */
} TrieNode;

/* Make a new empty trie node on the heap */
static TrieNode *createTrieNode(void) {
  TrieNode *node;
  int i;

  node = (TrieNode *)malloc(sizeof(TrieNode));
  if (node == NULL) {
    return NULL;
  }

  node->count = 0;
  for (i = 0; i < 26; i++) {
    node->children[i] = NULL;
  }

  return node;
}

TrieNode *indexPage(const char *url);

int addWordOccurrence(const char *word, const int wordLength, TrieNode *root);

void printTrieContents(TrieNode *node, char *wordBuf, int depth);

int freeTrieMemory(TrieNode *node);

int getText(const char *srcAddr, char *buffer, const int bufSize);

int main(int argc, char **argv) {
  TrieNode *root;

  /* Need a URL on the command line */
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <url>\n", argv[0]);
    return 1;
  }

  /* Build the trie from the web page */
  root = indexPage(argv[1]);
  if (root == NULL) {
    return 1;
  }

  /* Print all word counts in alphabetical order */
  {
    char wordBuf[MAX_WORD_BUF];
    wordBuf[0] = '\0';
    printTrieContents(root, wordBuf, 0);
  }

  /* Free all memory used by the trie */
  freeTrieMemory(root);

  return 0;
}

/* Download the page, split it into words, and put them in a trie */
TrieNode *indexPage(const char *url) {
  char *buffer;
  int bytesRead;
  int i;
  TrieNode *root;

  root = createTrieNode();
  if (root == NULL) {
    fprintf(stderr, "ERROR: could not allocate root node\n");
    return NULL;
  }

  /* Print the URL first, as required */
  printf("%s\n", url);

  buffer = (char *)malloc(MAX_PAGE_SIZE * sizeof(char));
  if (buffer == NULL) {
    fprintf(stderr, "ERROR: could not allocate page buffer\n");
    freeTrieMemory(root);
    return NULL;
  }

  bytesRead = getText(url, buffer, MAX_PAGE_SIZE);
  if (bytesRead <= 0) {
    /* Still return an empty trie so main can free it */
    free(buffer);
    return root;
  }

  /* Walk through the text and find each alphabetic word */
  i = 0;
  while (i < bytesRead) {
    /* Skip anything that is not a letter */
    while (i < bytesRead && !isalpha((unsigned char)buffer[i])) {
      i++;
    }

    if (i < bytesRead) {
      int start = i;
      char *word;
      int wordLength;
      int j;

      /* Read letters until we hit a non-letter */
      while (i < bytesRead && isalpha((unsigned char)buffer[i])) {
        i++;
      }

      wordLength = i - start;
      word = (char *)malloc((wordLength + 1) * sizeof(char));
      if (word == NULL) {
        fprintf(stderr, "ERROR: could not allocate word buffer\n");
        free(buffer);
        freeTrieMemory(root);
        return NULL;
      }

      /* Copy the word and make it lower-case */
      for (j = 0; j < wordLength; j++) {
        word[j] = (char)tolower((unsigned char)buffer[start + j]);
      }
      word[wordLength] = '\0';

      /* Print the term with a tab in front */
      printf("\t%s\n", word);

      /* Add this occurrence into the trie */
      if (addWordOccurrence(word, wordLength, root) != 0) {
        fprintf(stderr, "ERROR: could not add word to trie\n");
        free(word);
        free(buffer);
        freeTrieMemory(root);
        return NULL;
      }

      free(word);
    }
  }

  free(buffer);
  return root;
}

/* Add one more count for this word in the trie */
int addWordOccurrence(const char *word, const int wordLength, TrieNode *root) {
  TrieNode *current;
  int i;

  if (root == NULL || word == NULL || wordLength <= 0) {
    return 1;
  }

  current = root;
  for (i = 0; i < wordLength; i++) {
    int index = word[i] - 'a';

    /* Word should already be lower-case letters only */
    if (index < 0 || index > 25) {
      return 1;
    }

    /* Make a child node if we do not have one yet */
    if (current->children[index] == NULL) {
      current->children[index] = createTrieNode();
      if (current->children[index] == NULL) {
        return 1;
      }
    }

    current = current->children[index];
  }

  /* The node we end on is this word and add one to its count */
  current->count++;
  return 0;
}

/* Print all words with a non-zero count, in alphabetical order */
void printTrieContents(TrieNode *node, char *wordBuf, int depth) {
  int i;

  if (node == NULL) {
    return;
  }

  /* If this node is a real word, print it */
  if (node->count > 0 && depth > 0) {
    wordBuf[depth] = '\0';
    printf("%s: %d\n", wordBuf, node->count);
  }

  /* Visit children from a to z so output is alphabetical */
  for (i = 0; i < 26; i++) {
    if (node->children[i] != NULL) {
      if (depth + 1 >= MAX_WORD_BUF) {
        fprintf(stderr, "ERROR: word buffer is too small\n");
        return;
      }
      /* Push this letter onto the word buffer */
      wordBuf[depth] = (char)('a' + i);
      printTrieContents(node->children[i], wordBuf, depth + 1);
      
    }
  }
}

/* Free this node and all of its children */
int freeTrieMemory(TrieNode *node) {
  int i;

  if (node == NULL) {
    return 0;
  }

  for (i = 0; i < 26; i++) {
    if (node->children[i] != NULL) {
      freeTrieMemory(node->children[i]);
    }
  }

  free(node);
  return 0;
}

/* You should not need to modify this function */
int getText(const char *srcAddr, char *buffer, const int bufSize) {
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if (pipe == NULL) {
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
            buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
