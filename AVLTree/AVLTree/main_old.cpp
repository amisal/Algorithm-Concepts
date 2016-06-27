/*
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on April 16, 2015, 1:39 PM
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))


/*
 *
 */
struct avlNode {
    struct avlNode* parentNode;
    struct avlNode* leftChild;
    struct avlNode* rightChild;
    int nodeKey;
    int nodeId;
    int nodeLevel;
    int balanceFactor;
    int leftDepth;
    int rightDepth;
    int depth;
};
class avlTree {
    
public:
    
    struct avlNode* rootNode;
    
    avlTree(){
        rootNode = NULL;
    }
    avlTree(avlNode* nodeptr)
    {
        rootNode = nodeptr;
    }
    void balance(avlNode* node)
    {
        if(node->parentNode==NULL)
        {
            return;
        }
        else if (node->parentNode->parentNode==NULL)
        {
            
            return;
        }
        else
        {
            avlNode * child=node;
            avlNode * parent=node->parentNode;
            avlNode * grandparent=parent->parentNode;
            if(calBalanceFactor(grandparent)==2)
            {
                //do balancing
                
                if(calBalanceFactor(parent)==-1)
                {
                    //Left Right Case
                    RotateLeftRight(child,parent,grandparent);
                }
                //Left Left Case
                RotateLeftLeft(child,parent,grandparent);
                
            }
            else if(calBalanceFactor(grandparent)==-2)
            {
                if(calBalanceFactor(parent)==1)
                {
                    //Right Left Case
                    RotateRightLeft(child,parent,grandparent);
                }
                //Right Right Case
                RotateRightRight(child,parent,grandparent);
                
            }
        }

    }
    
    void RotateLeftRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        
        avlNode * temp=child;
        
        parent->rightChild=child->leftChild;
        parent->parentNode=temp;
        grandparent->leftChild=temp;
        
        grandparent->rightChild=NULL;
        parent->leftChild=NULL;
        parent->rightChild=NULL;
        temp->rightChild=NULL;
        
    }
    void RotateLeftLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        
        if(grandparent->parentNode==NULL)
            rootNode=parent;
        
        parent->parentNode=grandparent->parentNode;
        parent->rightChild=grandparent;
        
        grandparent->leftChild=NULL;
        grandparent->rightChild=NULL;
        
        child->leftChild=NULL;
        child->rightChild=NULL;
        
    }
    void RotateRightLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        parent->leftChild=child->rightChild;
        parent->parentNode=child;
        grandparent->rightChild=child;
        
        avlNode * temp=child;
        
        parent->leftChild=child->rightChild;
        parent->parentNode=temp;
        grandparent->rightChild=temp;
        
        grandparent->leftChild=NULL;
        parent->rightChild=NULL;
        parent->leftChild=NULL;
        temp->leftChild=NULL;
    }
    void RotateRightRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        if(grandparent->parentNode==NULL)
            rootNode=parent;
        
        parent->parentNode=grandparent->parentNode;
        parent->leftChild=grandparent;
        
        grandparent->leftChild=NULL;
        grandparent->rightChild=NULL;
        
        child->leftChild=NULL;
        child->rightChild=NULL;
        
    }
    
    int calBalanceFactor(avlNode* node)
    {
        
        int balanceFactor=0;
        balanceFactor=(depth(node->leftChild)-depth(node->rightChild));
        return balanceFactor;
    }
    
    bool exist(avlNode* node)
    {
        avlNode* tmp = rootNode;
        if(tmp == NULL) return false;
        else
        {
            do{
                if(tmp->nodeKey == node->nodeKey)return true;
                else if(node->nodeKey < tmp->nodeKey) tmp = tmp->leftChild;
                else tmp = tmp->rightChild;
            }while(tmp != NULL);
        }
        return false;
    }
    int depth(avlNode *node)
    {
        if(node == NULL) return 0;
        else
        {
            node->leftDepth = depth(node->leftChild)+1;
            node->rightDepth = depth(node->rightChild)+1;
            node->depth = MAX(node->leftDepth, node->rightDepth);
        }
        return node->depth;
    }
    void insert(avlNode* node)
    {
        std::cout << "Insert " << node->nodeId << ":" ;
        std::cout << " Key : " << node->nodeKey << endl;
        if(rootNode == NULL)
            rootNode = node;
        else
        {
            avlNode * tmp = rootNode;
            while(tmp != NULL)
            {
                if(node->nodeKey < tmp->nodeKey )
                {
                    if(tmp->leftChild == NULL)
                    {
                        tmp->leftChild = node;
                        node->parentNode = tmp;
                        tmp->leftDepth += 1;
                        tmp = NULL;
                    }
                    else tmp = tmp->leftChild;
                }
                else
                {
                    if(tmp->rightChild == NULL)
                    {
                        tmp->rightChild = node;
                        node->parentNode = tmp;
                        tmp->rightDepth += 1;
                        tmp = NULL;
                    }
                    else tmp = tmp->rightChild;
                }
            }
        }
        depth(rootNode);
    }
    
    
    
};

void Display(avlNode *current, int indent)
{
    if (current != NULL)
    {
        if (indent > 0)
            cout << std::setw(indent) << " ";
        cout << current->nodeKey << endl;

        Display(current->leftChild, indent + 4);
    
        Display(current->rightChild, indent + 4);
    }
}
void DisplayDepth(avlNode *current, int indent)
{
    if (current != NULL)
    {
        DisplayDepth(current->leftChild, indent + 4);
        if (indent > 0)
        cout << std::setw(indent) << " ";
        cout << current->depth << endl;
        DisplayDepth(current->rightChild, indent + 4);
    }
}

void inOrderTraversal(avlNode * node)
{
    if (node == NULL)
        return;
    inOrderTraversal(node->leftChild);
    cout << "| ";
    cout << node->nodeKey;
    //cout << " - ";
    //cout << node->srno;
    cout << "  |";
    inOrderTraversal(node->rightChild);
}
void preTraversal(avlNode* node)
{
    if (node == NULL)
        return;
    
    cout << "| ";
    cout << node->nodeKey;
   // cout << " - ";
   // cout << node->srno;
    cout << "  |";
    
    preTraversal(node->leftChild);
    preTraversal(node->rightChild);;
}
void insertAVL(avlTree* tr, avlNode* node)
{
    if(node != NULL)
    {
        tr->insert(node);
        tr->balance(node);
        cout << " Tree Traversal Preorder " << endl;
        cout << tr->calBalanceFactor(node)<< endl;
        preTraversal(tr->rootNode);
        cout << endl;
        Display(tr->rootNode,0);
        //DisplayDepth(tr->rootNode,0);
        
    }
}
int main(int argc, char** argv) {
    
    avlTree* avlT = new avlTree();
    avlNode* avln;
    srand(time(0));
    int i=0;
    int keys[3]={8,10,12};
    
    //while(i < 20)
    //{
    for(int i=0;i<3;i++)
    {
        avln = new avlNode();
        //avln->nodeKey = rand()% 100;
        avln->nodeKey = keys[i];
        avln->leftChild = avln->rightChild = avln->parentNode = NULL;
        avln->nodeId = i;
        avln->leftDepth = avln->rightDepth = 0;
        if(false == avlT->exist(avln))
        {
            insertAVL(avlT,avln);
            //i++;
        }
    }
    cout<<endl;
    cout<<avlT->rootNode;
   // preTraversal(avlT->rootNode);
    return 0;
}