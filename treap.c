#include <stdio.h>
#include <stdlib.h>

// Treap Node
struct Node {
    int key, priority;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->priority = rand();
    temp->left = temp->right = NULL;
    return temp;
}

// Right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Insert
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);

        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else if (key > root->key) {
        root->right = insert(root->right, key);

        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }

    return root;
}

// Search
int search(struct Node* root, int key) {
    if (root == NULL)
        return 0;

    if (root->key == key)
        return 1;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Delete node
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // Node found
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

        // Both children exist → rotate based on priority
        if (root->left->priority > root->right->priority) {
            root = rightRotate(root);
            root->right = deleteNode(root->right, key);
        }
        else {
            root = leftRotate(root);
            root->left = deleteNode(root->left, key);
        }
    }

    return root;
}

// Inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Main function (menu-driven)
int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- TREAP MENU ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Inserted!\n");
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                printf("Deleted (if existed)\n");
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Found!\n");
                else
                    printf("Not Found!\n");
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

// Steps of Code Writing
// Create node with key + random priority
// Maintain BST property (left < root < right)
// Maintain Heap property (parent priority > children)
// Use left/right rotations to balance
// Insert → BST insert + fix heap
// Delete → rotate + remove node
// Search → normal BST search
// 📌 Time Complexity
// Average: O(log n)
// Worst case: O(n)
// 📌 Applications
// Randomized search structures
// Database indexing
// Memory management
// Priority-based systems
// Competitive programming
// 📌 Viva One-Liner

// 👉 Treap is a combination of BST and Heap that uses random priorities to keep the tree balanced with average O(log n) time.