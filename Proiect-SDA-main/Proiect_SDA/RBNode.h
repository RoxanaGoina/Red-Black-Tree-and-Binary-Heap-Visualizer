#ifndef RBNODE_H_
#define RBNODE_H_
#include<string.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;


struct RBNode
{
    int key;       // key
    RBNode *p;     // pointer to parent
    RBNode *left;  // pointer to left child
    RBNode *right; // pointer to right child
    enum color {RED=0, BLACK=1};
    color col;

    static RBNode* Nil; // sentinel leaf node

    RBNode(int k, RBNode *l = Nil, RBNode *r = Nil, RBNode *parent = Nil, color c = RBNode::BLACK) :
        key(k), p(parent), left(l), right(r), col(c) { }

    string toString()
    {
        ostringstream os;
        os << key << ((col == RBNode::RED) ? ":RED" : ":BLACK");
        return os.str();
    }

    ~RBNode()
    {
        if (this != Nil)
        {
            if(left != Nil)
                delete left;
            if(right != Nil)
                delete right;
        }
    }

};

RBNode* RBNode::Nil = new RBNode(0);

struct RBTree
{
    RBNode* root;

    void LeftRotate(RBNode* x)
    {
        // Set y
        RBNode* y = x->right;
        // Turn y's left subtree into x's right subtree
        x->right = y->left;
        if (y->left != RBNode::Nil)
            y->left->p = x;
        // link x's parent to y
        y->p = x->p;
        if (x->p == RBNode::Nil)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
        // Put x on y's left
        y->left = x;
        x->p = y;
    }

    /**
     * RightRotate(y) also assumes that y is the right child of
     * an RBNode x
     */

    void RightRotate(RBNode* y)
    {
        // Set x
        RBNode* x = y->left;
        // Turn x's right subtree into y's left subtree
        y->left = x->right;
        if (x->right != RBNode::Nil)
            x->right->p = y;
        // link y's parent to x
        x->p = y->p;
        if (y->p == RBNode::Nil)
            root = x;
        else if (y == y->p->left)
            y->p->left = x;
        else
            y->p->right = x;
        // Put y on x's right
        x->right = y;
        y->p = x;
    }

    RBTree()
    {
        root = RBNode::Nil;
    }
    ~RBTree()
    {
        delete root;
    }

    RBNode* createNode(int key)
    {
        return new RBNode(key);
    }

    bool isNil(RBNode* n)
    {
        return (n == RBNode::Nil);
    }

    RBNode* search(RBNode* w, int key)
    {
        if (isNil(w) || w->key == key)
            return w;
        return search( (key < w->key) ? w->left : w->right, key);
    }

    /**
     * maximum(w) returns the node with maximum key in the
     * RB-tree with root node w
     */
    RBNode* maximum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->right))
            x = x->right;
        return x;
    }

    /**
     * minimum(w) returns the node with minimum key in the
     * RB-tree with root node w
     */
    RBNode* minimum(RBNode* w)
    {
        RBNode* x = w;
        while (!isNil(x->left))
            x = x->left;
        return x;
    }

    /**
     * successor(w) returns the successor of node w in the
     * RB-tree to which node w belongs
     */
    RBNode* successor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->right))
            return minimum(x->right);
        RBNode* y = x->p;
        while (!isNil(y) && x == y->right)
        {
            x = y;
            y = x->p;
        }
        return y;
    }

    RBNode* predecessor(RBNode* w)
    {
        if(isNil(w)) return w;
        RBNode* x = w;
        if (!isNil(x->left))
            return maximum(x->left);
        RBNode* y = x->p;
        while (!isNil(y) && x == y->left)
        {
            x = y;
            y = x->p;
        }
        return y;
    }


    /**
     * RBInsert(z) inserts node z in this RB-tree
     */
    void RBInsert(RBNode* z)
    {
        // insert like in a binary search tree
        RBNode *y = RBNode::Nil;
        RBNode *x = root;
        while (!isNil(x))
        {
            y = x;
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->p = y;
        if (isNil(y))
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        z->left = z->right = RBNode::Nil;
        z->col = RBNode::RED;
        RBInsertFixup(z);
    }

    RBNode* del(RBNode* z)
    {
        RBNode *y = (isNil(z->left) || isNil(z->right)) ? z : successor(z);
        RBNode *x = !isNil(y->left) ? y->left : y->right;
        x->p = y->p;
        if(isNil(y->p))
        {
            root = x;
        }
        else
        {
            if (y == y->p->left)
                y->p->left = x;
            else
                y->p->right = x;//y->right=z;
        }
        if (y != z)
        {
            z->key = y->key;
            // copy y's satellite data into z
        }
        if (y->col == RBNode::BLACK)
            RBDeleteFixup(x);
        return y;
    }

    void RBDeleteFixup(RBNode* x)
    {
        RBNode* w;
        while ((x != root) && (x->col == RBNode::BLACK))
        {
            if (x == x->p->left)
            {
                w = x->p->right;
                if(w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->p->col = RBNode::RED;
                    LeftRotate(x->p);
                    w = x->p->right;
                }
                if((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->p;
                }
                else
                {
                    if(w->right->col == RBNode::BLACK)
                    {
                        w->left->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        RightRotate(w);
                        w = x->p->right;
                    }
                    w->col = x->p->col;
                    x->p->col = RBNode::BLACK;
                    w->right->col = RBNode::BLACK;
                    LeftRotate(x->p);
                    x = root;
                }
            }
            else
            {
                // same as 'then' clause with 'right' and 'left' exchanged
                w = x->p->left;
                if(w->col == RBNode::RED)
                {
                    w->col = RBNode::BLACK;
                    x->p->col = RBNode::RED;
                    RightRotate(x->p);
                    w = x->p->left;
                }
                if((w->left->col == RBNode::BLACK) && (w->right->col == RBNode::BLACK))
                {
                    w->col = RBNode::RED;
                    x = x->p;
                }
                else
                {
                    if(w->left->col == RBNode::BLACK)
                    {
                        w->right->col = RBNode::BLACK;
                        w->col = RBNode::RED;
                        LeftRotate(w);
                        w = x->p->left;
                    }
                    w->col = x->p->col;
                    x->p->col = RBNode::BLACK;
                    w->left->col = RBNode::BLACK;
                    RightRotate(x->p);
                    x = root;
                }
            }
        }
        x->col = RBNode::BLACK;
    }

    void RBInsertFixup(RBNode* z)
    {
        while(z->p->col == RBNode::RED)
            if (z->p == z->p->p->left)
            {
                RBNode* y = z->p->p->right;
                if (y->col == RBNode::RED)
                {
                    z->p->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                }
                else
                {
                    if (z==z->p->right)
                    {
                        z = z->p;
                        LeftRotate(z);
                    }
                    z->p->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                    RightRotate(z->p->p);
                }
            }
            else
            {
                /* same as 'then' clause,
                 * with 'left' and 'right' exchanged */
                RBNode* y = z->p->p->left;
                if (y->col == RBNode::RED)
                {
                    z->p->col = RBNode::BLACK;
                    y->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                    //z=z->p->p;
                }
                else
                {
                    if (z==z->p->left)
                    {
                        z = z->p;
                        RightRotate(z);
                    }
                    z->p->col = RBNode::BLACK;
                    z->p->p->col = RBNode::RED;
                    LeftRotate(z->p->p);
                }
            }
        root->col = RBNode::BLACK;
    }

    void inorder(RBNode* T)
    {
        if (!isNil(T))
        {
            inorder(T->left);
            cout << T->toString() << ' ';
            inorder(T->right);
        }
    }

    void inorder()
    {
        if (isNil(root))
        {
            cout << "empty";
        }
        else
            inorder(root);
    }

    void display(RBNode* w, string indent,bool ok)
    {
        if (!isNil(w))
        {
            cout << indent;
            if (ok)
            {
                cout << "R->";
                indent += "   ";
            }
            else
            {
                cout << "L->";
                indent +="    ";
            }
            string culoare;
            if(w->col==0)
            {
                culoare="RED";

            }
            else culoare="BLACK";

            cout << w->key << "----->" << culoare<< endl;
            display(w->right, indent, true);

            display(w->left, indent, false);

        }
    }

    void indentedDisplay()
    {
        if (isNil(root))
            cout << "The RB tree is empty" <<endl;
        else
        {
            cout << "The RB tree is" <<endl;
            display(root,"",false );
        }
    }

    // auxiliary method
    //int bh(RBNode* x)
    //{
    //  return (isNil(x) ? 0 : countBlacks(x->left));
    //}

    // auxiliary method
    int countBlacks(RBNode* x)
    {
        int contor=0;
        if(isNil(x))
            return 0;
        while(!isNil(x))
        {
            if(x->col==RBNode::BLACK)
            {
                contor++;
            }
            x=x->left;
        }
        return contor;

        return 0;
    }

    /**
     * Compute the black-height of this red-black tree
     */
    int bh(RBNode *x)
    {
        // TODO
        int contor=0;
        while(!isNil(x))
        {
            if(x->col==RBNode::BLACK)
            {
                contor++;

            }
            x=x->left;
        }
        return contor;

    }

    // compute the depth of the tree with root *x
    int depth(RBNode* x)
    {
        if (isNil(x))
        {
            return -1;
        }
        else
        {
            int lDepth = depth(x->left);
            int rDepth = depth(x->right);
            return (lDepth<rDepth ? rDepth : lDepth)+1;
        }
    }

    /**
     * Compute the depth of this red-black tree
     */
    int depth()
    {
        return depth(root);
    }

    /* return the maximum key of black nodes.
     * If the tree is empty, return -1000 */
    int maxBlackKey(RBNode *x)
    {
        int cheie;
        if(isNil(x->right) || isNil(x->left))
            return -1000;
        else
        {
            while(!isNil(x))
            {
                if(x->col==RBNode::BLACK)
                    cheie=x->key;
                x=x->right;
            }

            //}
            return cheie;
        }
    }

    int maxRedKey()
    {
        if(isNil(root))
            return -1000;
        RBNode* x = root;
        while(!isNil(x->right))
            x = x->right;
        if(x->col == RBNode::BLACK)
            x = x->left;
        else x->p;
        return x->key;

    }
};

#endif /* RBNODE_H_ */
