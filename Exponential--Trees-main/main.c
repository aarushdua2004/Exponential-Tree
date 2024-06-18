/*
Group-2
Naviket Mankoo -> 2021MCB1239
Subham -> 2021MCB1248
Akshit Singh -> 2021MCB1229

Topic -Exponential Trees
Aim - Comparing the sorting time and analysis among exponential trees, binary trees and quick sort algorithm
*/
#include <stdio.h>  //importing the basic library of c
#include <stdlib.h> //importing the standard library of c
#include <string.h> //importing the string library
#include <time.h>   // importing the time library for calculating the time of functions

clock_t e_time; // intitalising the time variables for exponential tree
clock_t b_time; // intitalising the time variables for binary tree
clock_t q_time; // intitalising the time variables for quick sort

typedef struct Node node; // typedefining the node for easier use in the code

int array[5000007]; // declaring the array for quick sort
                    // the array is declared as global to increase the size constraints in local functions

struct Node // creating node for exponential tree
{
    int level;    // gives the level of the node of the exponential tree
    int count;    // number of integers present currently in the node
    node **child; // array for the children of each node pf the tree
    int data[];   // for every element in the node
};

struct node // creating node for binary tree
{
    int key;                   // the data present in the node
    struct node *left, *right; // the left and right child of the node
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node)); // allocating the memory for the node in the heap
    temp->key = item;                                               // giving the data
    temp->left = temp->right = NULL;                                // initialising the children of the node
    return temp;                                                    // returning the node
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root) // inorder
{
    if (root != NULL)
    {
        inorder(root->left);
        // printf("%d \n", root->key);
        //here the  data is not printed because we just need to calculate the time the tree takes to sort the data/
        inorder(root->right);
    }
}

/* A utility function to insert
   a new node with given key in
  BST */
struct node *insert1(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /*
    Otherwise, recur down the tree
    according to the position of the insertion of node
    */
    if (key < node->key)
        node->left = insert1(node->left, key);
    else if (key > node->key)
        node->right = insert1(node->right, key);

    /* returning the head pointer  */
    return node;
}

/* Utility funcitons  for the exponential trees*/

/*this function will be used in inserting the node in the exponential tree
it will find the correct spot for the insertion */
int binary_search(node *ptr, int element)
{
    if (ptr->count == 0) // if the node is empty then return 0
        return 0;
    if (element > ptr->data[ptr->count - 1])
        return ptr->count; // if the element is greater than the biggest element in the array then return the count of the array

    // executing binary search in the individual nodes
    int start = 0;
    int end = ptr->count - 1;
    int mid = start + (end - start) / 2;
    // we mainly divide the array into two parts and check the
    // first element of both parts of arrays and this works in a loop
    //  until you reached your element
    while (start < end)
    {
        if (element > ptr->data[mid])

            start = mid + 1; // mid is made the start
        // second part of array
        else
            end = mid; // mid is made the end of array
        // first part of array

        mid = start + (end - start) / 2;
    }

    return mid; // return the mid the ultimate answer of search
}

// funciton for creating the node of the exponential tree
// this function will be used when we have found the correct spot for insertion of the element
// then we will create the node and insert it at the position
node *createNode(const int level) // the level signifies the level from the root of the tree , root has level 1
{
    if (level <= 0)
        return NULL;

    /* Allocate node with 2**(level-1) integers */
    node *pNewNode = (node *)malloc(sizeof(node) + sizeof(int) * (1 << (level - 1))); // allocating the memory for the integer array
    memset(pNewNode->data, 0, sizeof(int) * (1 << (level - 1)));                      // this sets the data of the node elements to zero

    /* Allocate 2**level child node pointers */
    pNewNode->child = (node **)malloc(sizeof(node *) * (1 << level)); // allocating the memory for the children of the node
    memset(pNewNode->child, 0, sizeof(int) * (1 << level));

    pNewNode->count = 0; // currently the number of elements in the node is 0

    pNewNode->level = level; // setting the level to the level mentioned

    return pNewNode;
}

// function to insert the node at the position
void insert(node *root, int element)
{
    node *ptr = root; //  for not using the root
    node *parent = NULL;
    int i = 0;

    while (ptr != NULL)
    {
        int level = ptr->level;
        int count = ptr->count;
        i = binary_search(ptr, element); // finding the node in the tree

        if (count < (1 << (level - 1))) // only if the count is less than the maximum allowed size of the array
        {
            for (int j = count; j >= i + 1; --j)
                ptr->data[j] = ptr->data[j - 1]; // shifting the aray elements

            ptr->data[i] = element; // putting the element at the place
            ++ptr->count;           // increasing the count to +1
            return;
        }

        parent = ptr;
        ptr = ptr->child[i];
    }

    parent->child[i] = createNode(parent->level + 1);
    insert(parent->child[i], element);
}

void InOrderTrace(node *root) // performing the inorder trace
                              // this function only is the funcniton that essentialy performs the sorting
{

    if (root == NULL) // if null terminate
        return;

    for (int i = 0; i < root->count; ++i)
    {
        if (root->child[i])
            InOrderTrace(root->child[i]);
    }

    if (root->child[root->count])
        InOrderTrace(root->child[root->count]);
}

void swap(int *a, int *b)
{
    // swapping the elements
    int t = *a;
    // using the temporary variable
    *a = *b;
    *b = t;
}
/* partition function to help in the quick sort funciton
this function places the pivot at its correct place*/
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    // creating the last element as pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]); // swapping if condition statisfies
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); // return the partition index
}

void quickSort(int arr[], int low, int high)
{
    // performing the quick sort
    if (low < high)
    {

        int pi = partition(arr, low, high); // getting the partition

        /* recursively perfioeming the quick sort function on the left and the right side of the array around the partition*/
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// starting of main
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

    q_time = clock();
    // starting of the clock
    for (int i = 0; i < N2; i++)
    {
        fscanf(file2, "%d", &k2);
        // scanning the inputs
        array[i] = k2;
    }

    quickSort(array, 0, N2 - 1); // performing the quicksort on input file
    q_time = clock() - q_time;
    // stoping the clock
    double qui_t = (double)q_time / CLOCKS_PER_SEC;
    printf("Expo_tree time is %f\n", exp_t);
    // printing te time taken by exponential tree
    printf("Bin_tree time is %f\n", bst_t);
    // printing the time of binary tree
    printf("Quick_ time is %f\n", qui_t);
    // printing the time of quick sort algorithm
    fclose(file2);

    // closing the file at the end of the function
    return 0;
}
