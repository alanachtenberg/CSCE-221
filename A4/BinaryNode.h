
#include <cstddef> // to define NULL
class BinaryNode {
private:
friend class BinaryTree;
int element;
int SearchCost;
BinaryNode *left, *right;
public:
BinaryNode(int el = 0, BinaryNode *lt = NULL,
BinaryNode *rt = NULL) :
//constructor
element(el), left(lt), right(rt), SearchCost(-1) { }
// functions
BinaryNode *getLeft() { return left; }
BinaryNode *getRight() { return right; }
int getElem() { return element; }
int getSearchCost() { return SearchCost;}
int size(BinaryNode *t);
int height(BinaryNode *t);
BinaryNode *copy();
};

int BinaryNode::size(BinaryNode *t) { //recursive
if (t == NULL)
return 0;

return 1 + size(t->left) + size(t->right);
}

int BinaryNode::height(BinaryNode *t) { //recursive
if (t == NULL)
return 0;
else {
int hlf = height(t->left), hrt = height(t->right);
return (hlf > hrt) ? 1+hlf : 1+hrt; // 1+max(hlf,hrt)
}
}

BinaryNode *BinaryNode::copy( ) { // recursive
BinaryNode *root = new BinaryNode(element);
if (left != NULL)
root->left = left->copy();
if (right != NULL)
root->right = right->copy();
return root;
}

