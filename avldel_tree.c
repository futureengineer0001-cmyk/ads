#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left, *right;
    int height;
};

// Get height
int height(struct node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}

// Maximum value
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Create node
struct node *newNode(int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));

    temp->data = data;
    temp->left = temp->right = NULL;
    temp->height = 1;

    return temp;
}

// Right rotation
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Balance factor
int getBalance(struct node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// Insert node
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);

    else if (data > root->data)
        root->right = insert(root->right, data);

    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Rotation
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    // RR Rotation
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    // LR Rotation
    if (balance > 1 && data > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Rotation
    if (balance < -1 && data < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum value node
struct node *minValue(struct node *root)
{
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Delete node
struct node *deleteNode(struct node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else
    {
        // One child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        struct node *temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main()
{
    struct node *root = NULL;
    int choice, value;

    do
    {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;

        case 3:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 4:
            printf("Exit");
            break;

        default:
            printf("Invalid choice");
        }

    } while (choice != 4);

    return 0;
}



// AVL TREE

// Definition:
// AVL Tree is a self-balancing Binary Search Tree (BST).
// The height difference between left and right subtree
// (balance factor) should be -1, 0, or +1.

// Operations:
// 1. Insertion  -> Add node and balance tree
// 2. Deletion   -> Remove node and rebalance
// 3. Traversal  -> Display tree (Inorder)

// Balance Factor:
// BF = Height(Left Subtree) - Height(Right Subtree)

// Conditions for Rotation:
// 1. LL (Left Left)  -> Right Rotation
// 2. RR (Right Right) -> Left Rotation
// 3. LR (Left Right) -> Left + Right Rotation
// 4. RL (Right Left) -> Right + Left Rotation

// Time Complexity:
// Insertion -> O(log n)
// Deletion  -> O(log n)
// Search    -> O(log n)
// Traversal -> O(n)

// Advantages:
// - Fast searching
// - Automatically balanced
// - Better than normal BST

// Applications:
// - Database indexing
// - Searching large data
// - Dictionary / Phonebook
// - Memory management

// // 