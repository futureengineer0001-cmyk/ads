#include <stdio.h>
#include <stdlib.h>

// Interval node
struct Node {
    int low, high;
    int max;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int low, int high) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->low = low;
    node->high = high;
    node->max = high;
    node->left = node->right = NULL;
    return node;
}

// Get max value
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Update max
void updateMax(struct Node* root) {
    if (root == NULL) return;

    root->max = root->high;

    if (root->left)
        root->max = max(root->max, root->left->max);

    if (root->right)
        root->max = max(root->max, root->right->max);
}

// Insert interval
struct Node* insert(struct Node* root, int low, int high) {
    if (root == NULL)
        return newNode(low, high);

    if (low < root->low)
        root->left = insert(root->left, low, high);
    else
        root->right = insert(root->right, low, high);

    updateMax(root);
    return root;
}

// Check overlap
int isOverlap(int l1, int h1, int l2, int h2) {
    return (l1 <= h2 && l2 <= h1);
}

// Search overlapping interval
void searchOverlap(struct Node* root, int low, int high) {
    if (root == NULL)
        return;

    if (isOverlap(root->low, root->high, low, high))
        printf("[%d, %d]\n", root->low, root->high);

    if (root->left && root->left->max >= low)
        searchOverlap(root->left, low, high);
    else
        searchOverlap(root->right, low, high);
}

// Find min node
struct Node* minValue(struct Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node
struct Node* deleteNode(struct Node* root, int low, int high) {
    if (root == NULL)
        return NULL;

    if (low < root->low)
        root->left = deleteNode(root->left, low, high);

    else if (low > root->low)
        root->right = deleteNode(root->right, low, high);

    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValue(root->right);
        root->low = temp->low;
        root->high = temp->high;
        root->right = deleteNode(root->right, temp->low, temp->high);
    }

    updateMax(root);
    return root;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d, %d] max=%d\n", root->low, root->high, root->max);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, l, h, ql, qh;

    while (1) {
        printf("\n--- INTERVAL TREE MENU ---\n");
        printf("1. Insert Interval\n");
        printf("2. Delete Interval\n");
        printf("3. Search Overlap\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter low and high: ");
                scanf("%d %d", &l, &h);
                root = insert(root, l, h);
                printf("Inserted!\n");
                break;

            case 2:
                printf("Enter low and high to delete: ");
                scanf("%d %d", &l, &h);
                root = deleteNode(root, l, h);
                printf("Deleted!\n");
                break;

            case 3:
                printf("Enter query interval (low high): ");
                scanf("%d %d", &ql, &qh);
                printf("Overlapping intervals:\n");
                searchOverlap(root, ql, qh);
                break;

            case 4:
                printf("Interval Tree (Inorder):\n");
                inorder(root);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}

// Interval Tree (Very Simple Explanation)

// An Interval Tree is a data structure used to store ranges (intervals) like:

// 👉 [10, 20], [15, 25], [30, 40]

// It helps to quickly find which intervals overlap with each other.

// Key Feature

// 👉 Each node stores:

// Start point
// End point
// Maximum end value in its subtree

// This helps to skip unnecessary checking.
    
// 📌 Steps of Code Writing
// Create node with low, high, max
// Insert interval like BST
// Update max endpoint at each node
// Check overlap using condition
// Search overlaps using pruning (max value)
// Delete node like BST + update max
// Display using inorder traversal
// 📌 Time Complexity
// Insert: O(log n) (average)
// Delete: O(log n) (average)
// Search overlap: O(log n + k)
// (k = number of overlapping intervals)
// 📌 Applications
// Calendar scheduling systems
// CPU scheduling
// Network bandwidth allocation
// Memory allocation
// Collision detection (games/graphics)
// 📌 Viva One-Liner

// 👉 Interval Tree is a BST-based structure used to efficiently find overlapping intervals in O(log n + k) time.
