#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26

struct TrieNode
{
    struct TrieNode *child[ALPHABET];
    int isEnd;
};

// create node
struct TrieNode* createNode()
{
    struct TrieNode *node =
        (struct TrieNode*)malloc(sizeof(struct TrieNode));

    node->isEnd = 0;

    for(int i = 0; i < ALPHABET; i++)
        node->child[i] = NULL;

    return node;
}

// insert word
void insert(struct TrieNode *root, char word[])
{
    struct TrieNode *temp = root;

    for(int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if(temp->child[index] == NULL)
            temp->child[index] = createNode();

        temp = temp->child[index];
    }

    temp->isEnd = 1;
}

// search word
int search(struct TrieNode *root, char word[])
{
    struct TrieNode *temp = root;

    for(int i = 0; word[i] != '\0'; i++)
    {
        int index = word[i] - 'a';

        if(temp->child[index] == NULL)
            return 0;

        temp = temp->child[index];
    }

    return temp->isEnd;
}

// check if node has children
int isEmpty(struct TrieNode *node)
{
    for(int i = 0; i < ALPHABET; i++)
        if(node->child[i] != NULL)
            return 0;

    return 1;
}

// print words (helper)
void printWords(struct TrieNode *root, char str[], int level)
{
    if(root->isEnd)
    {
        str[level] = '\0';
        printf("%s\n", str);
    }

    for(int i = 0; i < ALPHABET; i++)
    {
        if(root->child[i])
        {
            str[level] = i + 'a';
            printWords(root->child[i], str, level + 1);
        }
    }
}

// prefix search
void prefixSearch(struct TrieNode *root, char prefix[])
{
    struct TrieNode *temp = root;

    for(int i = 0; prefix[i] != '\0'; i++)
    {
        int index = prefix[i] - 'a';

        if(temp->child[index] == NULL)
        {
            printf("No words found\n");
            return;
        }

        temp = temp->child[index];
    }

    char str[100];
    strcpy(str, prefix);

    printf("Words with prefix:\n");
    printWords(temp, str, strlen(prefix));
}

// main
int main()
{
    struct TrieNode *root = createNode();

    int choice;
    char word[100];

    while(1)
    {
        printf("\n1.Insert Word");
        printf("\n2.Search Word");
        printf("\n3.Prefix Search");
        printf("\n4.Exit");
        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter word: ");
                scanf("%s", word);
                insert(root, word);
                break;

            case 2:
                printf("Enter word: ");
                scanf("%s", word);

                if(search(root, word))
                    printf("Found\n");
                else
                    printf("Not Found\n");

                break;

            case 3:
                printf("Enter prefix: ");
                scanf("%s", word);
                prefixSearch(root, word);
                break;

            case 4:
                exit(0);

            default:
                printf("Wrong choice\n");
        }
    }

    return 0;
}

// Time Complexity
// Insert → O(length of word)
// Search → O(length of word)
// Prefix search → O(prefix + matching words)

// 📌 Real Applications
// Auto-suggestion (Google search)
// Spell checker
// Dictionary implementation
// Word games (like Scrabble)
// IP routing tables

// Trie Code Writing Steps (Short)
// Define Trie Node Structure → array of 26 children + end-of-word flag
// Create Node Function → allocate memory and initialize all children to NULL
// Insert Function → insert each character and create nodes if needed
// Search Function → traverse character by character and check word existence
// Prefix Search Function → reach prefix node first, then explore all words
// Print Function → recursively print all words from a given node
// Main Function → menu (insert, search, prefix search, exit)