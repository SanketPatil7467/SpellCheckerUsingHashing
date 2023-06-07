#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 50
#define HASH_TABLE_SIZE 1000

typedef struct HashNode
{
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct
{
    HashNode **nodes;
    int size;
} HashMap;

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HASH_TABLE_SIZE;
}

HashMap *createHashMap(int size)
{
    HashMap *map = malloc(sizeof(HashMap));
    map->nodes = calloc(size, sizeof(HashNode *));
    map->size = size;

    return map;
}

void put(HashMap *map, const char *key, int value)
{
    unsigned long hashValue = hash(key) % map->size;

    HashNode *node = map->nodes[hashValue];

    while (node != NULL && strcmp(node->key, key) != 0)
    {
        node = node->next;
    }

    if (node == NULL)
    {
        node = malloc(sizeof(HashNode));
        node->key = strdup(key);
        node->value = value;
        node->next = map->nodes[hashValue];
        map->nodes[hashValue] = node;
    }
    else
    {
        node->value = value;
    }
}

int get(HashMap *map, const char *key)
{
    unsigned long hashValue = hash(key) % map->size;

    HashNode *node = map->nodes[hashValue];

    while (node != NULL && strcmp(node->key, key) != 0)
    {
        node = node->next;
    }

    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return node->value;
    }
}

int cmpfunc(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

int missingCharacter(char input[])
{
    FILE *words;
    char line[100], Xinput[100], Tinput[100], Tline[100], Xline[100];
    int found = 0;
    words = fopen("words.txt", "r");
    if (words)
    {
        while (fgets(line, sizeof(line), words))
        {
            line[strcspn(line, "\n")] = 0;
            for (int i = 0; i < 26; i++)
            {
                int len = strlen(input), flen = strlen(line);
                strcpy(Xinput, input);
                strcpy(Xline, line);
                Xinput[len] = 'a' + i;
                len++;
                Xinput[len] = '\0';
                char Ninput[100], Nline[100];
                if (len == flen)
                {
                    for (int j = 1; j <= len; j++)
                        Ninput[j - 1] = Xinput[j];
                    for (int j = 1; j <= flen; j++)
                        Nline[j - 1] = Xline[j];
                    Ninput[len - 1] = '\0';
                    Nline[flen - 1] = '\0';
                    Xinput[1] = '\0';
                    Xline[1] = '\0';
                    qsort(Nline, strlen(Nline), sizeof(char), cmpfunc);
                    qsort(Ninput, strlen(Ninput), sizeof(char), cmpfunc);
                    strcpy(Tinput, Xinput);
                    strcat(Tinput, Ninput);
                    strcpy(Tline, Xline);
                    strcat(Tline, Nline);
                    if (strcmp(Tinput, Tline) == 0)
                    {
                        found = 1;
                        printf("%s\n", line);
                        break;
                    }
                }
                if (found == 1)
                    break;
            }
            if (found == 1)
                break;
        }
        fclose(words);
    }
    else
    {
        printf("\nUnexpected error occurred\n");
    }
    return found;
}

int mixedExtraMissing(char input[])
{
    FILE *words;
    char line[100], Xinput[100], Xline[100];
    int found = 0;
    words = fopen("words.txt", "r");
    if (words)
    {
        while (fgets(line, sizeof(line), words))
        {
            line[strcspn(line, "\n")] = 0;
            int len = strlen(input), flen = strlen(line);
            if (len == flen)
            {
                for (int i = 1; i < len; i++)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        strcpy(Xinput, input);
                        strcpy(Xline, line);
                        memmove(&Xinput[i], &Xinput[i + 1], strlen(Xinput) - i);
                        Xinput[len - 1] = 'a' + j;
                        qsort(Xinput + 1, strlen(Xinput) - 1, sizeof(char), cmpfunc);
                        qsort(Xline + 1, strlen(Xline) - 1, sizeof(char), cmpfunc);
                        if (strcmp(Xinput, Xline) == 0)
                        {
                            found = 1;
                            printf("%s\n", line);
                            break;
                        }
                    }
                    if (found == 1)
                        break;
                }
                if (found == 1)
                    break;
            }
        }
        fclose(words);
    }
    return found;
}

int incorrectArrangement(char input[])
{
    FILE *words;
    char line[100], Ninput[100], Nline[100];
    int found = 0;
    words = fopen("words.txt", "r");
    if (words)
    {
        while (fgets(line, sizeof(line), words))
        {
            line[strcspn(line, "\n")] = 0;
            int len = strlen(input), flen = strlen(line);
            if (len == flen)
            {
                for (int i = 1; i <= len; i++)
                    Ninput[i - 1] = input[i];
                for (int i = 1; i <= flen; i++)
                    Nline[i - 1] = line[i];
                Ninput[len - 1] = '\0';
                Nline[flen - 1] = '\0';
                qsort(Nline, strlen(Nline), sizeof(char), cmpfunc);
                qsort(Ninput, strlen(Ninput), sizeof(char), cmpfunc);
                if (strcmp(Ninput, Nline) == 0)
                {
                    found = 1;
                    printf("%s\n", line);
                    break;
                }
            }
        }
        fclose(words);
    }
    return found;
}

int exchangedCharacters(char input[])
{
    FILE *words;
    char line[100], Xinput[100];
    int found = 0;
    words = fopen("words.txt", "r");
    if (words)
    {
        while (fgets(line, sizeof(line), words))
        {
            line[strcspn(line, "\n")] = 0;
            int len = strlen(input), flen = strlen(line);
            if (len == flen)
            {
                for (int i = len - 1; i >= 0; i--)
                {
                    strcpy(Xinput, input);
                    Xinput[i] = 'a';
                    for (int j = 0; j < 26; j++)
                    {
                        if (strcmp(Xinput, line) == 0)
                        {
                            found = 1;
                            printf("%s\n", line);
                            break;
                        }
                        Xinput[i] = 'a' + j;
                    }
                    if (found == 1)
                        break;
                }
            }
        }
        fclose(words);
    }
    else
        printf("\nUnexpected error occurred\n");
    return found;
}

int main()
{
    char word[MAX_WORD_LENGTH];
    FILE *fp = fopen("words.txt", "r");
    HashMap *map = createHashMap(HASH_TABLE_SIZE);

    if (fp == NULL)
    {
        fprintf(stderr, "Error: cannot open file\n");
        return EXIT_FAILURE;
    }

    while (fscanf(fp, "%s", word) == 1)
    {
        // Convert word to lowercase
        for (size_t i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }

        // Insert word into hashmap
        put(map, word, 1);
    }

    fclose(fp);

    while (1)
    {
        // Retrieve words from hashmap
        printf("Enter a word to check: ");
        scanf("%s", word);

        // Convert input word to lowercase
        for (size_t i = 0; word[i]; i++)
        {
            word[i] = tolower(word[i]);
        }

        if (get(map, word) == 1)
        {
            printf("'%s' is in the dictionary\n", word);
        }
        else
        {
            printf("'%s' is not in the dictionary\n", word);
            int missing = 0, extra = 0, mixed = 0, incorrect = 0, exchanged = 0;
            printf("\nSpelling is wrong. Possible right spellings are given below:- \n\n");
            missing = missingCharacter(word);
            mixed = mixedExtraMissing(word);
            incorrect = incorrectArrangement(word);
            exchanged = exchangedCharacters(word);
            if (missing == 0 && extra == 0 && mixed == 0 && incorrect == 0 && exchanged == 0)
            {
                printf("\nNo such word exist\n");
            }
        }
    }

    return EXIT_SUCCESS;
}
