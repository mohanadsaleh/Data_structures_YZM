#include <stdio.h>
#include <stdlib.h>

struct node {
    int height;
    int data;
    struct node *left;
    struct node *right;
};
typedef struct node AVLTREE;

struct node_BTREE{
int data;
struct node_BTREE *left;
struct node_BTREE *right;
};
typedef struct node_BTREE BTREE;
AVLTREE *new_node(int x) {
    AVLTREE *node = (struct node*)malloc(sizeof(struct node));

    node->height = 0;
    node->data = x;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int height(AVLTREE *node) {
    if (node == NULL)
        return -1;
    else {
        int lheight, rheight;
        lheight = height(node->left);
        rheight = height(node->right);
        if (rheight > lheight)
            return rheight + 1;
        else
            return lheight + 1;
    }
}

int maxValue(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

/*           O z <--> sağ döndürecek (raight rotation)
            /
           O  temp
          /
         O 
         
*/
AVLTREE *R_Rotation(AVLTREE *z) { 
    AVLTREE *temp = z->left;
    z->left = temp->right; 
    temp->right = z;
    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;
}
/*       Sonuç :    
           O
          / \
         O   O
         
*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/*     O *z
        \
         O *temp
          \
           O
*/
AVLTREE *L_Rotation(AVLTREE *z) {
    AVLTREE *temp = z->right;
    z->right = temp->left;
    temp->left = z;
    z->height = maxValue(height(z->left), height(z->right)) + 1;
    temp->height = maxValue(height(temp->left), height(temp->right)) + 1;
    return temp;
}
/*       Sonuç :    
           O
          / \
         O   O
         
*/


/*--------------------------------------------RightLeft_Rotation---------------------------------------------------------*/
/*
        O 
          \
           O
          /
        O
         
 */

/*     O *z
        \
         O *temp
          \
           O
*/
AVLTREE *RightLeft_Rotation(AVLTREE *z) {
    z->right = R_Rotation(z->right);
    return L_Rotation(z);
}
/*       Sonuç :    
           O
          / \
         O   O
         
*/
/*-*--------------------------------------------------LeftRight_Rotation-----------------------------*/


/*
       O
      /
     O
      \ 
       O
*/

/*           O z <--> sağ döndürecek (raight rotation)
            /
           O  temp
          /
         O 
         
*/
AVLTREE *LeftRight_Rotation(AVLTREE *z) {
    z->left = L_Rotation(z->left);
    return R_Rotation(z);
}
/* sonuç : 
  
        O
       /  \
      O    O
  
  */

AVLTREE *insertToAVL(AVLTREE *tree, int x) {
    if (tree == NULL) {
        // If the tree is empty, create a new node
        tree = new_node(x);
    } else {
        if (x < tree->data) {
            tree->left = insertToAVL(tree->left, x);
        } else {
            tree->right = insertToAVL(tree->right, x);
        }

        // Update the height after insertion
        tree->height = maxValue(height(tree->left), height(tree->right)) + 1;

        // Check and perform rotations if necessary
        
        if ((height(tree->left) - height(tree->right)) > 1 && x < tree->left->data)
            return R_Rotation(tree);

        if ((height(tree->left) - height(tree->right)) > 1 && x > tree->left->data)
            return LeftRight_Rotation(tree);

        if ((height(tree->left) - height(tree->right)) < -1 && x > tree->right->data)
            return L_Rotation(tree);

        if ((height(tree->left) - height(tree->right)) < -1 && x < tree->right->data)
            return RightLeft_Rotation(tree);
    }

    return tree;
}

void inorder(AVLTREE *T) {
    if (T == NULL)
        return;

    inorder(T->left);
    printf("%d \t", T->data);
    inorder(T->right);
}




AVLTREE *ConvertToAvl(BTREE *root1, AVLTREE *root2) {
    if (root1 == NULL) {
        return root2;
    }

    root2 = ConvertToAvl(root1->left, root2);
    root2 = insertToAVL(root2, root1->data);
    root2 = ConvertToAvl(root1->right, root2);

    return root2;
}


    int main() {
    // Örnek bir Binary Tree oluştur
    BTREE *myBinaryTree = (struct node_BTREE *)malloc(sizeof(struct node_BTREE));
    myBinaryTree->data = 30;
    myBinaryTree->left = (struct node_BTREE *)malloc(sizeof(struct node_BTREE));
    myBinaryTree->left->data = 20;
    myBinaryTree->left->left = myBinaryTree->left->right = NULL;
    myBinaryTree->right = (struct node_BTREE *)malloc(sizeof(struct node_BTREE));
    myBinaryTree->right->data = 40;
    myBinaryTree->right->left = myBinaryTree->right->right = NULL;

    // AVL Tree'ye dönüştür
    AVLTREE *mytree = NULL;
    mytree = ConvertToAvl(myBinaryTree, mytree);

    // AVL Tree'yi inorder şekilde yazdır
    printf("AVL Tree: ");
    inorder(mytree);

    return 0;
}

   