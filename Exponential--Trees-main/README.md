
# Exponential Trees
Sorting a set of integers has been a very common problem that has had researchers' interesets since very long time.  
In this project we have implemented the Exponential Trees that gives the bound for sorting n integers of O(n loglogn). However the original algorithm is very complex and hard to implement so we have applied the modified exponential trees in this project.  
Some properties of them are mentioned below:
* Each node at level 'k' will hold 'k' integers.
* Each node at level 'k' will have 'k+1' children.
* All the keys in any node will be sorted. 
This modified version of exponential trees is similar to binary trees with the difference that the number of children that a node can hold depends on the depth of the node increases exponentially.  


## Team Members 
Naviket Mankoo- 2021MCB1248  
Subham-2021CMCB1248  
Akshit Singh-2021MCB1229
## Deployment

To run this project in the windows terminal,
clone the repository  
(git must be installed in the machine, if not installed, then to run the code download the code zip file and then run in the terminal) and then run the following commands  
first clone the repository using the git url availaible under the code section using the following command  



```bash
git clone (git URL)
```
then go inside the directory in the "Exponential--Trees" folder and then run the following commands  
```bash
gcc ./main.c
./a.exe
```


## Input
The input is taken by a file "input.txt", so to change the input, changes have to be made in the file itself.  
The maximum size of the file can be 5000007.  

The format of the input is as follows:  
* The first number of the file is the number of integers in the file.
* The next is the N integers, that are taken as inputs and will be inserted in the trees.
## Output
The output gives the CPU run-time to sort the integers by Exponential tree, Binary Tree and using Quick Sort algorithm.  
The time taken by Exponential Tree Sorting and Quick Sort should be nearly same for smaller values of N.  
The run-time for Binary tree is always greater than the rest.
