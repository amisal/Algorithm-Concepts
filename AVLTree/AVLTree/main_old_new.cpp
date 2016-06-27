#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>

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
    
private:
    avlNode *temp;
    
public:
    
    struct avlNode* rootNode;
    
    avlTree()
    {
        rootNode = NULL;
    }
    
    avlTree(avlNode* nodeptr)
    {
        rootNode = nodeptr;
        temp=NULL;
    }
    
    void balance(avlNode* node)
    {
        
        avlNode * child;
        avlNode * parent;
        avlNode * grandparent;
        
        if((node->parentNode != NULL)&&(node->parentNode->parentNode != NULL))
        {
            child=node;
            parent=node->parentNode;
            grandparent=parent->parentNode;
            
            //grandparent->balanceFactor=calBalanceFactor(grandparent);
            //parent->balanceFactor=calBalanceFactor(parent);
            
            while (grandparent->parentNode!=NULL || (abs(calBalanceFactor(grandparent))==2)) {
                
                
                if(calBalanceFactor(grandparent) == 2)
                {
                    //do balancing
                    
                    if(calBalanceFactor(parent) == -1)
                    {
                        //Left Right Case
                        RotateLeftRight(child,parent,grandparent);
                    }
                    //Left Left Case
                    else RotateLeftLeft(child,parent,grandparent);
                    
                }
                else if(calBalanceFactor(grandparent) == -2)
                {
                    if(calBalanceFactor(parent) == 1)
                    {
                        //Right Left Case
                        RotateRightLeft(child,parent,grandparent);
                    }
                    //Right Right Case
                    else RotateRightRight(child,parent,grandparent);
                    
                }
                
                grandparent=grandparent->parentNode;
                parent=parent->parentNode;
                child=child->parentNode;
                
            }
            
        }
        
    }
    
    void RotateLeftRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        
        avlNode *A,*B,*C,*D;
        A = parent->leftChild;
        B = child->leftChild;
        C = child->rightChild;
        D = grandparent->rightChild;
        
        child->leftChild = parent;
        child->rightChild = grandparent;
        
        child->parentNode=grandparent->parentNode;
        grandparent->parentNode=child;
        parent->parentNode=child;
        
        
        parent->leftChild = A;
        parent->rightChild = B;
        grandparent->leftChild = C;
        grandparent->rightChild = D;
        
        if(child->parentNode == NULL) rootNode = child;
        
        else if(child->parentNode->leftChild == grandparent)
            child->parentNode->leftChild = child;
        else    child->parentNode->rightChild = child;
        
        
    }
    void RotateLeftLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        
        
        
        avlNode *A,*B,*C,*D;
        A = child->leftChild;
        B = child->rightChild;
        C = parent->rightChild;
        D = grandparent->rightChild;
        
        parent->leftChild = child;
        parent->rightChild = grandparent;
        
        parent->parentNode=grandparent->parentNode;
        grandparent->parentNode=parent;
        child->parentNode=parent;
        
        child->leftChild = A;
        child->rightChild = B;
        grandparent->leftChild = C;
        grandparent->rightChild = D;
        
        if(parent->parentNode == NULL) rootNode = parent;
        
        else if(parent->parentNode->leftChild == grandparent)
            parent->parentNode->leftChild = parent;
        else    parent->parentNode->rightChild = parent;
        
        
    }
    void RotateRightLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        avlNode *A,*B,*C,*D;
        A = grandparent->leftChild;
        B = child->leftChild;
        C = child->rightChild;
        D = parent->rightChild;
        
        child->leftChild = grandparent;
        child->rightChild = parent;
        
        child->parentNode=grandparent->parentNode;
        grandparent->parentNode=child;
        parent->parentNode=child;
        
        
        grandparent->leftChild = A;
        grandparent->rightChild = B;
        parent->leftChild = C;
        parent->rightChild = D;
        
        if(child->parentNode == NULL) rootNode = child;
        
        else if(child->parentNode->leftChild == grandparent)
            child->parentNode->leftChild = child;
        else child->parentNode->rightChild = child;
        
    }
    void RotateRightRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        avlNode *A,*B,*C,*D;
        A = grandparent->leftChild;
        B = parent->leftChild;
        C = child->leftChild;
        D = child->rightChild;
        
        parent->leftChild = grandparent;
        parent->rightChild = child;
        
        parent->parentNode=grandparent->parentNode;
        grandparent->parentNode=parent;
        child->parentNode=parent;
        
        grandparent->leftChild = A;
        grandparent->rightChild = B;
        child->leftChild = C;
        child->rightChild = D;
        
        if(parent->parentNode == NULL) rootNode = parent;
        
        else if(parent->parentNode->leftChild == grandparent)
            parent->parentNode->leftChild = parent;
        else    parent->parentNode->rightChild = parent;
        
        
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
            node->balanceFactor = node->leftDepth - node->rightDepth;
            node->depth = MAX(node->leftDepth, node->rightDepth);
        }
        
        return node->depth;
    }
    
    avlNode* find(int key)
    {
        temp = rootNode;
        while (temp != NULL) {
            if (key == temp->nodeKey)
            {
                // return a pointer
                return temp;
            }
            
            else if (key < temp->nodeKey)
            {
                // move to next left pointer
                temp = temp->leftChild;
            }
            else
            {
                // move to next right pointer
                temp = temp->rightChild;
            }
        }
        return NULL;
    }
    
    void insert(int key) {
        
        if (find(key) == NULL)
        {
            // first create a new node
            avlNode * node = new avlNode;
            
            temp = rootNode;
            
            node->nodeKey = key;
            node->leftChild = NULL;
            node->rightChild = NULL;
            node->parentNode=NULL;
            node->leftDepth=0;
            node->rightDepth=0;
            node->nodeId=0;
            
            if (rootNode == NULL)
            {
                rootNode = node;
                node->nodeLevel = 0;node->nodeId = 0;
                return;
            }
            while(temp != NULL)
            {
                if(node->nodeKey < temp->nodeKey )
                {
                    if(temp->leftChild == NULL)
                    {
                        temp->leftChild = node;
                        node->parentNode = temp;
                        temp->leftDepth += 1;
                        temp = NULL;
                    }
                    else temp = temp->leftChild;
                }
                else
                {
                    if(temp->rightChild == NULL)
                    {
                        temp->rightChild = node;
                        node->parentNode = temp;
                        temp->rightDepth += 1;
                        temp = NULL;
                    }
                    else temp = temp->rightChild;
                }
            }
            
            balance(node);
            
        }
        
    }
    
    
    void insert1(avlNode* node)
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
        //depth(rootNode);
    }
    
    void displayTree(avlNode *ptr, int level)
    {
        int i;
        if (ptr!=NULL)
        {
            displayTree(ptr->rightChild, level + 1);
            printf("\n");
            if (ptr == rootNode)
                cout<<"Root -> ";
            for (i = 0; i < level && ptr != rootNode; i++)
                cout<<"        ";
            cout<<ptr->nodeKey;
            cout<<" (";cout<<calBalanceFactor(ptr);cout<<")";
            displayTree(ptr->leftChild, level + 1);
        }
    }
    
};

void Display(avlNode *current, int indent)
{
    if (current != NULL)
    {
        
        //if (indent > 0)
        cout << setw(indent) << " ";
        cout << current->nodeKey << endl;
        Display(current->leftChild, indent + 4);
        
        Display(current->rightChild, indent + 4);
    }
}

void DisplayDepth(avlNode *current, int indent)
{
    if (current != NULL)
    {
        
        if (indent > 0)
            cout << setw(indent) << " ";
        cout << current->depth << "\\";
        cout << current->balanceFactor << endl;
        DisplayDepth(current->leftChild, indent + 4);
        
        DisplayDepth(current->rightChild, indent + 4);
    }
}

void preTraversal(avlNode* pn)
{
    if(pn == NULL) return;
    cout << pn->nodeKey << "-";
    preTraversal(pn->leftChild);
    preTraversal(pn->rightChild);
}

void insertAVL(avlTree* tr, int key)
{
    //if(node != NULL)
    //{
    tr->insert(key);
    // tr->depth(tr->rootNode);
    
    //tr->depth(tr->rootNode);
    // cout << endl;
    //cout << " Tree Traversal Preorder " << endl;
    // preTraversal(tr->rootNode);
    cout << endl;
    //tr->displayTree(tr->rootNode,1);
    cout << endl;
    cout << "---------------------------------------";
    // DisplayDepth(tr->rootNode,0);
    //}
}

double InsertRunningTime(avlTree* object, const int sample_size)
{
    const int EXP_RUNNING_TIME = 1;
    double timesum = 0;
    srand((int) time(0));
    clock_t start,end,stime;
    
    //cout << "Expected Insert Iterations = " << EXP_RUNNING_TIME << endl;
    
    for (int j = 0; j < EXP_RUNNING_TIME; j++)
    {
        //cout << "Insert Iteration no. j= " << j << "  time = " << timesum << " Sec" << endl;
        if(j != 0)
        {
            object->~avlTree();
            object = new avlTree();
        }
        start = clock();
        for (int i = 0; i < sample_size; i++)
        {
            //cout<<" ";
            //cout<<(rand() % sample_size)+1;
            //cout<<" ";
            object->insert((rand() % (((sample_size*10) < RAND_MAX) ? (sample_size*10):RAND_MAX) ) + 1);
        }
        end = clock();
        timesum += (int)((end - start)/(CLOCKS_PER_SEC * 0.001));
        //object.printTree(); cout << endl;
    }
    
    timesum = timesum / EXP_RUNNING_TIME;
    
    //cout << "Total Iterations = " << EXP_RUNNING_TIME;
    //cout << "\tTotal Time =" << timesum;
    //cout << "\tAverage Time = " << timesum / EXP_RUNNING_TIME;
    //cout << endl;
    //object.printTree();
    //cout<<"Inorder Traversal for Binary Search Tree is:" << endl;
    //object->printTree();
    return timesum;
}

double FindRunningTime(avlTree* object, const long sample_size)
{
    const int EXP_RUNNING_TIME = 1;
    double timesum = 0;
    clock_t start,end,stime;
    srand((int) time(0));
    
    //cout << "Expected Find Iterations = " << EXP_RUNNING_TIME << endl;
    
    for (int j = 0; j < EXP_RUNNING_TIME; j++)
    {
        //cout << " Find Iteration no. j= " << j << "  time = " << timesum << " ms" << endl;
        start = clock();
        for (long i = 0; i < sample_size; i++)
        {
            //cout<<" ";
            //cout<<(rand() % sample_size)+1;
            //cout<<" ";
            object->find((rand() % sample_size) + 1);
        }
        end = clock();
        timesum += (int)((end - start)/(CLOCKS_PER_SEC * 0.001));
    }
    timesum = timesum / EXP_RUNNING_TIME;
    
    // cout << "Total Iterations = " << EXP_RUNNING_TIME;
    // cout << "\tTotal Time =" << timesum;
    //cout << "\tAverage Time = " << timesum / EXP_RUNNING_TIME;
    // cout << endl;
    //object->printTree();
    //cout<<"Inorder Traversal for Binary Search Tree is:" << endl;
    //object.printTree();
    return timesum;
}

void myTestCases(avlTree* avl, int i) {
    const int SAMPLE_ONE_SIZE = 10;
    const int SAMPLE_TWO_SIZE = 50;
    const int SAMPLE_THREE_SIZE = 100;
    
    switch (i) {
        case 1:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_ONE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_ONE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(avl, SAMPLE_ONE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_ONE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(avl, SAMPLE_ONE_SIZE / 2);
            cout << " ms." << endl;
            
            
            break;
            
        case 2:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_TWO_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_TWO_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(avl, SAMPLE_TWO_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_TWO_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(avl, SAMPLE_TWO_SIZE / 2);
            cout << " ms." << endl;
            
            break;
            
        case 3:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_THREE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_THREE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(avl, SAMPLE_THREE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_THREE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(avl, SAMPLE_THREE_SIZE / 2);
            cout << " ms." << endl;
            break;
        default:
            break;
    }
}


int main(int argc, char** argv) {
    
    avlTree* avlT = new avlTree();
    avlNode* avln;
    //srand((int)time(0));
    //int i=0;
    //int keys[6]={4,3,6,9,8,10};
    //int key=0;
    
    //while(i < 100)
    //{
        //for(int i=0;i<6;i++)
        //{
        
      //  key = rand()% 100;
        
        //if(avlT->find(key)==NULL)
        //{
        //insertAVL(avlT,key);
        //i++;
        //}
    //}
    //cout<<endl;
    //cout<<avlT->rootNode;
    // preTraversal(avlT->rootNode);
    
    cout << "AVL Tree: " << endl;
    myTestCases(avlT,1);
    myTestCases(avlT,2);
    myTestCases(avlT,3);
    
    avlT->displayTree(avlT->rootNode, 1);
    return 0;
}