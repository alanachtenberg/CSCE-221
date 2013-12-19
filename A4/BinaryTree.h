
#include <iostream>
#include "BinaryNode.h"

using namespace std;
class BinaryTree
{

private:
    BinaryNode *root;
    void deleteTree(BinaryNode *root);
public:
    BinaryTree()
    {
        root=NULL;
    }
    BinaryTree(int el)
    {
        root=new BinaryNode(el);
    }
    ~BinaryTree()
    {
        deleteTree(root);
        root=NULL;
    }


    //functions

    BinaryNode*   find(int x, BinaryNode* t);
    BinaryNode* removeMin(BinaryNode* t);
    BinaryNode* findMin(BinaryNode* t);

    BinaryNode *get_Root()
    {
        return root;
    }



    bool isEmpty()
    {
        return root==NULL;
    }


    int size()
    {
        return (root== NULL) ? 0 : root->size(root);
    }

    int height ()
    {
        return (root==NULL) ? 0 : root->height(root);
    }

    BinaryNode* insert( int x, BinaryNode * t, int* counter=new int(0))
    {
        if (t == NULL){
            t = new BinaryNode(x);
            t->SearchCost=*counter+1;
            if (root==NULL)
                root=t;
        }
        else if
        (x < t->element){
            *counter+=1;
            t->left = insert(x, t->left, counter);}
        else if
        (x > t->element){
            *counter+=1;
            t->right = insert(x, t->right, counter);
            }
 //   if(t->SearchCost<t->height(t))
        return t;
    }

    BinaryNode* remove(int x, BinaryNode* t, int* counter=new int(0))
// private function
{
    if
    (t == NULL)
        cout<<"item not found\n";
    if
    (x < t->element){
        *counter+=1;
        t->left = remove(x, t->left, counter);
        }
    else if
    (x > t->element){
        *counter+=1;
        t->right = remove(x, t->right, counter);
        }
    else if
    (t->left != NULL && t->right != NULL)  // item x is found; t has two children
    {
        t->element = findMin(t->right)->element;
        t->right = removeMin(t->right);
    }
    else  //t has only one child
    {
        BinaryNode* node = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete node;
    }


    return t;
}



    void insert(int x)
    {
    insert(x, root);
    }

    void remove(int x)
    {
    remove(x, root);
    }

    BinaryNode* find(int x)
    {
        return find(x, root);
    }



    void copy (BinaryTree& rhs)
    {
        if (this!=&rhs)
        {
            deleteTree(root); //make tree empty
            if (rhs.root != NULL)
                root=rhs.root->copy();
        }
    }


    void merge (int rootItem, BinaryTree& t1, BinaryTree& t2);


};
BinaryNode* BinaryTree::findMin(BinaryNode* t)
{
    if (t == NULL)
        std::cout<<"tree full\n";
    while (t->left != NULL)
        t = t->left;
    return t;
}

BinaryNode* BinaryTree::find(int x, BinaryNode* t)
{
while (t != NULL)
if (x < t->element)
    t = t->left;
else if (x > t->element)
    t = t->right;

else return t;
}

BinaryNode * BinaryTree::removeMin(BinaryNode* t)
{
    if
    (t == NULL)
        cout<<"item not found";
    if (t->left != NULL)
        t->left = removeMin(t->left);
    else
    {
        BinaryNode* node = t;
        t = t->right;
        delete node;
    }
    return t;
}




void BinaryTree::merge(int rootItem, BinaryTree& t1, BinaryTree& t2)
{

    if (t1.root == t2.root && t1.root != NULL)
    {
        cerr << "Left tree == right tree; "
            << " merge aborted" << endl;
        return;
    }

    if (this != &t1 && this != &t2)
        deleteTree(root);

    root = new BinaryNode(rootItem, t1.root, t2.root);

    //remove aliases
    if (this != &t1) t1.root = NULL;
    if (this != &t2) t2.root = NULL;

}

void BinaryTree::deleteTree(BinaryNode *root) // postorder traversal
{
    if (root == NULL) return; // nothing to delete
    if (root->left != NULL)
        deleteTree(root->left);
    if (root->right != NULL)
        deleteTree(root->right);
    delete root;
}


