#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie *createTrie();
// Trie structure
struct Trie
{
    int isWord; //1 if yes, 2 if no
    struct Trie *next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
    {
        pTrie = createTrie();
    }

    int i, idx;
    struct Trie *tmp = pTrie;
    unsigned char *text = (unsigned char *)word;
    int len = strlen(text);

    for (i = 0; i < len; i++)
    {
        idx = text[i] - 'a';
        if (tmp->next[idx] == NULL)
        {
            struct Trie* new = createTrie();
            tmp->next[idx] = new;
        }
        tmp = tmp->next[idx];
    }
    pTrie->isWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (pTrie == NULL)
        return -1;

    int i, idx, n = 0;
    struct Trie *tmp = pTrie;
    unsigned char *text = (unsigned char *)word;
    int len = strlen(text);

    if (pTrie->isWord == 1)
        n++;

    for (i = 0; i < len; i++) {
    idx = text[i] - 'a';
        if (tmp->next[idx] == NULL)
            return -1;

        tmp = tmp->next[idx];
        n++;
    }
        
    return n;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int i;
    for (i = 0; i <= 26; i++)
        if (pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
    free(pTrie);
}

// Initializes a trie structure
struct Trie *createTrie()
{
    // Create the struct, not a word.
    struct Trie *tmp;
    tmp = (struct Trie*)malloc(sizeof(struct Trie));
    tmp->isWord = 0;
    // Set each pointer to NULL.
    int i;
    for (i = 0; i < 26; i++)
        tmp->next[i] = NULL;
    // Return a pointer to the new root.
    return tmp;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n;
    FILE *ifp = fopen("dictionary.txt", "r");
    fscanf(ifp, "%d", &n);
    for (int i = 0; i < n; ++i) {
        char* word[100];
        fscanf(ifp, "%s", word);
        pInWords[i] = word;
        // printf("%s\n", pInWords[i]); testing
    }
    fclose(ifp);

    return n;
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]); 
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}