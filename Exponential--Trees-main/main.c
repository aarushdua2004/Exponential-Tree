#include <stdio.h>  // Importing the basic library of C
#include <stdlib.h> // Importing the standard library of C
#include <string.h> // Importing the string library
#include <time.h>   // Importing the time library for calculating the time of functions

clock_t e_time; // Initializing the time variables for exponential tree
clock_t b_time; // Initializing the time variables for binary tree
clock_t m_time; // Initializing the time variables for merge sort

typedef struct Node node; // Typedefining the node for easier use in the code

int array[5000007]; // Declaring the array for merge sort
                    // The array is declared as global to increase the size constraints in local functions

struct Node // Creating node for exponential tree
{
    int level;    // Gives the level of the node of the exponential tree
    int count;    // Number of integers present currently in the node
    node **child; // Array for the children of each node of the tree
    int data[];   // For every element in the node
};

struct node // Creating node for binary tree
{
    int key;                   // The data present in the node
    struct node *left, *right; // The left and right child of the node
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // Allocating the memory for the node in the heap
    temp->key = item;                                               // Giving the data
    temp->left = temp->right = NULL;                                // Initializing the children of the node
    return temp;                                                    // Returning the node
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root) // Inorder
{
    if (root != NULL)
    {
        inorder(root->left);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given key in BST */
struct node *insert1(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree according to the position of the insertion of node */
    if (key < node->key)
        node->left = insert1(node->left, key);
    else if (key > node->key)
        node->right = insert1(node->right, key);

    /* Returning the head pointer */
    return node;
}

/* Utility functions for the exponential trees */

/* This function will be used in inserting the node in the exponential tree
   It will find the correct spot for the insertion */
int binary_search(node *ptr, int element)
{
    if (ptr->count == 0) // If the node is empty then return 0
        return 0;
    if (element > ptr->data[ptr->count - 1])
        return ptr->count; // If the element is greater than the biggest element in the array then return the count of the array

    // Executing binary search in the individual nodes
    int start = 0;
    int end = ptr->count - 1;
    int mid = start + (end - start) / 2;
    // We mainly divide the array into two parts and check the
    // first element of both parts of arrays and this works in a loop
    // until you reached your element
    while (start < end)
    {
        if (element > ptr->data[mid])
            start = mid + 1; // Mid is made the start (second part of array)
        else
            end = mid; // Mid is made the end of array (first part of array)

        mid = start + (end - start) / 2;
    }

    return mid; // Return the mid, the ultimate answer of search
}

// Function for creating the node of the exponential tree
// This function will be used when we have found the correct spot for insertion of the element
// Then we will create the node and insert it at the position
node *createNode(const int level) // The level signifies the level from the root of the tree, root has level 1
{
    if (level <= 0)
        return NULL;

    /* Allocate node with 2**(level-1) integers */
    node *pNewNode = (node *)malloc(sizeof(node) + sizeof(int) * (1 << (level - 1))); // Allocating the memory for the integer array
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1)));                      // This sets the data of the node elements to zero

    /* Allocate 2**level child node pointers */
    pNewNode->child = (node **)malloc(sizeof(node *) * (1 << level)); // Allocating the memory for the children of the node
    memset(pNewNode->child, 0, sizeof(int) * (1 << level));

    pNewNode->count = 0; // Currently the number of elements in the node is 0
    pNewNode->level = level; // Setting the level to the level mentioned

    return pNewNode;
}

// Function to insert the node at the position
void insert(node *root, int element)
{
    node *ptr = root; // For not using the root
    node *parent = NULL;
    int i = 0;

    while (ptr != NULL)
    {
        int level = ptr->level;
        int count = ptr->count;
        i = binary_search(ptr, element); // Finding the node in the tree

        if (count < (1 << (level - 1))) // Only if the count is less than the maximum allowed size of the array
        {
            for (int j = count; j >= i + 1; --j)
                ptr->data[j] = ptr->data[j - 1]; // Shifting the array elements

            ptr->data[i] = element; // Putting the element at the place
            ++ptr->count;           // Increasing the count to +1
            return;
        }

        parent = ptr;
        ptr = ptr->child[i];
    }

    parent->child[i] = createNode(parent->level + 1);
    insert(parent->child[i], element);
}

void InOrderTrace(node *root) // Performing the inorder trace
{
    if (root == NULL) // If null terminate
        return;

    for (int i = 0; i < root->count; ++i)
    {
        if (root->child[i])
            InOrderTrace(root->child[i]);
    }

    if (root->child[root->count])
        InOrderTrace(root->child[root->count]);
}

// Merge function to merge the sorted halves
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* Create temp arrays */
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r] */
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    FILE *file;
    // declaring the file
    file = fopen("input.txt", "r");
    // opening the file

    node *pRoot = createNode(1);
    // creation of node

    struct node *root = NULL;
    // creating the binary tree node

    root = insert1(root, 1);
    // creating thr root for binary tree

    if (file == NULL)
    {
        // checking the file whether null or not

        return 0;
        // if file is empty then printing 0
    }

    int N; // the size of the array in the file
    /* the inputs are taken in a file just to ensure that the set of numbers for both the exponential and the binary tree is same and
    and also to perform the quick sort, we need to store the elements in the array*/

    fscanf(file, "%d", &N);
    // scannig the first number which is number of inputs for the array

    int k;
    e_time = clock(); // starting the clock to measure the time

    for (int i = 0; i < N; i++)
    {
        // scanning the file integer by integer
        // and storing it in the variable k
        fscanf(file, "%d", &k);

        insert(pRoot, k);
        // inserting the k in both trees
    }

    InOrderTrace(pRoot); // sorting by exponential tree calling function

    e_time = clock() - e_time;
    double exp_t = (double)e_time / CLOCKS_PER_SEC;

    fclose(file); // closing the file

    FILE *file1; // opening the file
    file1 = fopen("file1", "r");
    int N1;
    int k1;
    b_time = clock();         // opening the clock
    fscanf(file1, "%d", &N1); // scanning the first integer the size

    for (int i = 0; i < N; i++)
    {
        // reading the file
        fscanf(file1, "%d", &k1);

        insert1(root, k);
        // inserting thr data of file int the tree
    }

    inorder(root);
    // inorder traversal
    b_time = clock() - b_time;
    // calculating the time
    double bst_t = (double)b_time / CLOCKS_PER_SEC;

    fclose(file1);
    // closing the file
    FILE *file2;
    file2 = fopen("input.txt", "r");
    // opening the file to scan
    int N2;
    fscanf(file2, "%d", &N2);
    // scanning the file
    //  int arr[N2];
    int k2;

    m_time = clock();
    // starting of the clock
    for (int i = 0; i < N2; i++)
    {
        fscanf(file2, "%d", &k2);
        // scanning the inputs
        array[i] = k2;
    }

    mergeSort(array, 0, N2 - 1); // performing the mergesort on input file
    m_time = clock() - m_time;
    // stoping the clock
    double mer_t = (double)m_time / CLOCKS_PER_SEC;
    printf("Expo_tree time is %f\n", exp_t);
    printf("Bin_tree time is %f\n", bst_t);
    printf("Merge_sort time is %f\n", mer_t);

    return 0;
}
