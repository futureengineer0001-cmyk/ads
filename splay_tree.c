#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Right rotate
struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotate
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay function
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key) {
        if (root->left == NULL) return root;

        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }
    else {
        if (root->right == NULL) return root;

        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    struct Node* node = newNode(key);

    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = NULL;
    } else {
        node->left = root;
        node->right = root->right;
        root->right = NULL;
    }

    return node;
}

// Search
struct Node* search(struct Node* root, int key) {
    root = splay(root, key);

    if (root && root->key == key)
        printf("Key Found!\n");
    else
        printf("Key Not Found!\n");

    return root;
}

// Inorder display
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Main (MENU DRIVEN)
int main() {
    struct Node* root = NULL;
    int choice, key, n;

    while (1) {
        printf("\n--- SPLAY TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("After insertion (root changed by splay)\n");
                inorder(root);
                printf("\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &key);
                root = search(root, key);
                printf("After search (splayed result): ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Tree (Inorder): ");
                inorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Steps to Write Code
// Create node (key, left, right)
// Implement rotations (left, right)
// Write splay function (zig, zig-zig, zig-zag)
// Implement insert, search, delete (with splaying)
// Display tree using inorder traversal
// 📌 Time Complexity
// Amortized: O(log n)
// Worst case: O(n)
// 📌 Applications
// Cache systems
// Memory management (OS)
// Compilers (symbol tables)
// Network routing
// Frequently accessed data optimization