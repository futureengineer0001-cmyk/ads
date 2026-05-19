#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Node structure
struct Node {
    struct Node *child[256];
    int isEnd;
};

// Create new node
struct Node* newNode() {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->isEnd = 0;

    for (int i = 0; i < 256; i++)
        node->child[i] = NULL;

    return node;
}

// Insert suffix into tree
void insert(struct Node* root, char *suffix) {
    struct Node* curr = root;

    for (int i = 0; suffix[i] != '\0'; i++) {
        if (curr->child[(int)suffix[i]] == NULL)
            curr->child[(int)suffix[i]] = newNode();

        curr = curr->child[(int)suffix[i]];
    }
    curr->isEnd = 1;
}

// Build suffix tree
void buildSuffixTree(struct Node* root, char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        insert(root, &text[i]);
    }
}

// Search pattern
int search(struct Node* root, char *pattern) {
    struct Node* curr = root;

    for (int i = 0; pattern[i] != '\0'; i++) {
        if (curr->child[(int)pattern[i]] == NULL)
            return 0;

        curr = curr->child[(int)pattern[i]];
    }
    return 1;
}

// Print all suffixes
void printSuffixes(struct Node* root, char *buffer, int level) {
    if (root->isEnd) {
        buffer[level] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < 256; i++) {
        if (root->child[i]) {
            buffer[level] = (char)i;
            printSuffixes(root->child[i], buffer, level + 1);
        }
    }
}

// Find longest repeated substring (basic)
void longestRepeated(struct Node* root, char *buffer, int level, char *result) {
    int children = 0;

    for (int i = 0; i < 256; i++) {
        if (root->child[i]) {
            children++;
            buffer[level] = (char)i;
            longestRepeated(root->child[i], buffer, level + 1, result);
        }
    }

    if (children > 1) {
        buffer[level] = '\0';
        strcpy(result, buffer);
    }
}

// Main function
int main() {
    char text[MAX];
    struct Node* root = newNode();

    printf("Enter string: ");
    scanf("%s", text);

    buildSuffixTree(root, text);

    printf("\nSuffix Tree Built Successfully!\n");

    // Search pattern
    char pattern[MAX];
    printf("\nEnter pattern to search: ");
    scanf("%s", pattern);

    if (search(root, pattern))
        printf("Pattern FOUND\n");
    else
        printf("Pattern NOT FOUND\n");

    // Print suffixes
    char buffer[MAX];
    printf("\nAll suffixes:\n");
    printSuffixes(root, buffer, 0);

    // Longest repeated substring
    char result[MAX] = "";
    longestRepeated(root, buffer, 0, result);

    printf("\nLongest Repeated Substring (approx): %s\n", result);

    return 0;
}

// Suffix tree is a compressed trie of all suffixes of a string used for fast pattern matching in O(m) time.
// 📌 Suffix Tree
// ✅ Steps of Code Writing
// Create node with 256 child pointers + end marker
// Insert all suffixes of the string into tree
// Build tree using text[i], text[i+1], ...
// Search pattern by traversing characters
// Print all suffixes using DFS traversal
// Find longest repeated substring using shared paths
// 📌 Time Complexity
// Construction: O(n²)
// Search: O(m) (m = pattern length)
// Traversal: O(n²)
// 📌 Applications
// DNA sequence matching
// Plagiarism detection
// Pattern matching in text editors
// Data compression
// Bioinformatics