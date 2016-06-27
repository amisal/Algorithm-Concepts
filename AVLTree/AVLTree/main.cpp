
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
    
public:
    
    struct avlNode* rootNode;
    
    avlTree()
    {
        rootNode = NULL;
    }
    
    avlTree(avlNode* nodeptr)
    {
        rootNode = nodeptr;
    }
    
    void balance(avlNode* node)
    {
        avlNode * child;
        avlNode * parent;
        avlNode * grandparent;
        
        child=node;
        if(child != NULL)
        {
            parent=child->parentNode; 
            if(parent != NULL)grandparent=parent->parentNode;else return;
        }
        else return;
        

        while((grandparent != NULL) && (abs(grandparent->balanceFactor) < 2))
        {
            child=child->parentNode;
            if(child != NULL)
            {
                parent=child->parentNode; 
                if(parent != NULL)grandparent=parent->parentNode;else break;
            }
            else break;
            
        }
        if((parent != NULL)&&(grandparent != NULL))
        {


            if(grandparent->balanceFactor == 2)
            {
                //do balancing

                if(parent->balanceFactor == -1)
                {
                    //Left Right Case
                    RotateLeftRight(child,parent,grandparent);
                }
                //Left Left Case
                else 
                {
                    RotateLeftLeft(child,parent,grandparent);
                }

            }
            else if(grandparent->balanceFactor == -2)
            {
                if(parent->balanceFactor == 1)
                {
                    //Right Left Case
                    RotateRightLeft(child,parent,grandparent);
                }
                //Right Right Case
                else 
                {
                    RotateRightRight(child,parent,grandparent);
                }

            }
        }
        
    }
    
    void RotateLeftRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        avlNode *A,*B,*C,*D,*tmp;
        
        tmp = grandparent;
        A = parent->leftChild;
        B = child->leftChild;
        C = child->rightChild;
        D = grandparent->rightChild;
        
        parent->leftChild = A;
        parent->rightChild = B;
        grandparent->leftChild = C;
        grandparent->rightChild = D;
        
        if(tmp == rootNode) 
        {
            rootNode = child;child->parentNode = NULL;
        }
        else 
        {
            if(tmp->parentNode->nodeKey > child->nodeKey)
            {
                tmp->parentNode->leftChild = child;
            }
            else 
            {
                tmp->parentNode->rightChild = child;
            }
        
            child->parentNode = tmp->parentNode;
        }
            
        child->leftChild = parent;
        child->rightChild = grandparent;
        parent->parentNode = child;        
        grandparent->parentNode = child;  
        
        int dl=0, dr=0;
        if(grandparent->leftChild == NULL) dl =0;
        else dl=grandparent->leftDepth = grandparent->leftChild->depth+1;
        if(grandparent->rightChild == NULL) dr =0;
        else dr=grandparent->rightDepth = grandparent->rightChild->depth+1;
        grandparent->balanceFactor = dl - dr;
        grandparent->depth = (dl < dr)?dr:dl;
        
        if(parent->leftChild == NULL) dl =0;
        else dl=parent->leftDepth = parent->leftChild->depth+1;
        if(parent->rightChild == NULL) dr =0;
        else dr=parent->rightDepth = parent->rightChild->depth+1;
        parent->balanceFactor = dl - dr;
        parent->depth = (dl < dr)?dr:dl;
        
        if(child->leftChild == NULL) dl =0;
        else dl=child->leftDepth = child->leftChild->depth+1;
        if(child->rightChild == NULL) dr =0;
        else dr=child->rightDepth = child->rightChild->depth+1;
        child->balanceFactor = dl - dr;
        child->depth = (dl < dr)?dr:dl;
        
        depth(child);
    }
    void RotateLeftLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        avlNode *A,*B,*C,*D,*tmp;
        tmp = grandparent;
        A = child->leftChild;
        B = child->rightChild;
        C = parent->rightChild;
        D = grandparent->rightChild;
        
        child->leftChild = A;
        child->rightChild = B;
        grandparent->leftChild = C;
        grandparent->rightChild = D;
        
        if(tmp == rootNode) 
        {
            rootNode = parent;parent->parentNode = NULL;
        }
        else 
        {
            if(tmp->parentNode->nodeKey > parent->nodeKey)
            {
                tmp->parentNode->leftChild = parent;
            }
            else 
            {
                tmp->parentNode->rightChild = parent;
            }
        
            parent->parentNode = tmp->parentNode;           
        }
        
        parent->leftChild = child;
        parent->rightChild = grandparent;
        child->parentNode = parent;        
        grandparent->parentNode = parent;
        
        int dl=0, dr=0;
        if(grandparent->leftChild == NULL) dl =0;
        else dl=grandparent->leftDepth = grandparent->leftChild->depth+1;
        if(grandparent->rightChild == NULL) dr =0;
        else dr=grandparent->rightDepth = grandparent->rightChild->depth+1;
        grandparent->balanceFactor = dl - dr;
        grandparent->depth = (dl < dr)?dr:dl;
        
        if(child->leftChild == NULL) dl =0;
        else dl=child->leftDepth = child->leftChild->depth+1;
        if(child->rightChild == NULL) dr =0;
        else dr=child->rightDepth = child->rightChild->depth+1;
        child->balanceFactor = dl - dr;
        child->depth = (dl < dr)?dr:dl;
        
        if(parent->leftChild == NULL) dl =0;
        else dl=parent->leftDepth = parent->leftChild->depth+1;
        if(parent->rightChild == NULL) dr =0;
        else dr=parent->rightDepth = parent->rightChild->depth+1;
        parent->balanceFactor = dl - dr;
        parent->depth = (dl < dr)?dr:dl;
        
        depth(parent);
    }
    void RotateRightLeft(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        avlNode *A,*B,*C,*D,*tmp;
        tmp = grandparent;
        A = grandparent->leftChild;
        B = child->leftChild;
        C = child->rightChild;
        D = parent->rightChild;
        
        grandparent->leftChild = A;
        grandparent->rightChild = B;
        parent->leftChild = C;
        parent->rightChild = D;
        
        if(tmp == rootNode) 
        {
            rootNode = child;child->parentNode = NULL;
        }
        else 
        {
            if(tmp->parentNode->nodeKey > child->nodeKey)
            {
                tmp->parentNode->leftChild = child;
            }
            else 
            {
                tmp->parentNode->rightChild = child;
            }
        
            child->parentNode = tmp->parentNode;
        }
            
        child->leftChild = grandparent;
        child->rightChild = parent;
        parent->parentNode = child;            
        grandparent->parentNode = child;        

        int dl=0, dr=0;
        if(grandparent->leftChild == NULL) dl =0;
        else dl=grandparent->leftDepth = grandparent->leftChild->depth+1;
        if(grandparent->rightChild == NULL) dr =0;
        else dr=grandparent->rightDepth = grandparent->rightChild->depth+1;
        grandparent->balanceFactor = dl - dr;
        grandparent->depth = (dl < dr)?dr:dl;
        
        if(parent->leftChild == NULL) dl =0;
        else dl=parent->leftDepth = parent->leftChild->depth+1;
        if(parent->rightChild == NULL) dr =0;
        else dr=parent->rightDepth = parent->rightChild->depth+1;
        parent->balanceFactor = dl - dr;
        parent->depth = (dl < dr)?dr:dl;
        
        if(child->leftChild == NULL) dl =0;
        else dl=child->leftDepth = child->leftChild->depth+1;
        if(child->rightChild == NULL) dr =0;
        else dr=child->rightDepth = child->rightChild->depth+1;
        child->balanceFactor = dl - dr;
        child->depth = (dl < dr)?dr:dl;
        
        depth(child);
    }
    void RotateRightRight(avlNode* child,avlNode* parent,avlNode* grandparent)
    {
        
        avlNode *A,*B,*C,*D,*tmp;
        tmp = grandparent;
        A = grandparent->leftChild;
        B = parent->leftChild;
        C = child->leftChild;
        D = child->rightChild;
        
        grandparent->leftChild = A;
        grandparent->rightChild = B;
        child->leftChild = C;
        child->rightChild = D;
        
        tmp=tmp->parentNode;
        
        if(tmp == NULL) 
        {
            rootNode = parent;parent->parentNode = NULL;
        }
        else 
        {
            
            if(tmp->nodeKey > parent->nodeKey)
            {
                tmp->leftChild = parent;
            }
            else 
            {
                tmp->rightChild = parent;
            }
            
            parent->parentNode = tmp;
        }   
        
        parent->leftChild = grandparent;
        parent->rightChild = child;
        child->parentNode = parent;
        grandparent->parentNode = parent;

        
        
        int dl=0, dr=0;
        if(grandparent->leftChild == NULL) dl =0;
        else dl=grandparent->leftDepth = grandparent->leftChild->depth+1;
        if(grandparent->rightChild == NULL) dr =0;
        else dr=grandparent->rightDepth = grandparent->rightChild->depth+1;
        grandparent->balanceFactor = dl - dr;
        grandparent->depth = (dl < dr)?dr:dl;
        
        if(child->leftChild == NULL) dl =0;
        else dl=child->leftDepth = child->leftChild->depth+1;
        if(child->rightChild == NULL) dr =0;
        else dr=child->rightDepth = child->rightChild->depth+1;
        child->balanceFactor = dl - dr;
        child->depth = (dl < dr)?dr:dl;
        
        if(parent->leftChild == NULL) dl =0;
        else dl=parent->leftDepth = parent->leftChild->depth+1;
        if(parent->rightChild == NULL) dr =0;
        else dr=parent->rightDepth = parent->rightChild->depth+1;
        parent->balanceFactor = dl - dr;
        parent->depth = (dl < dr)?dr:dl;
        
        depth(parent);
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
    
    void depth(avlNode *node)
    {
        int dl=0, dr=0;
        if(node == NULL) return;
        else
        {
            avlNode* tmp = node;
            while(tmp != NULL)
            {
                if(tmp->leftChild == NULL) dl =0;
                else dl = tmp->leftDepth = tmp->leftChild->depth+1;
                if(tmp->rightChild == NULL) dr =0;
                else dr = tmp->rightDepth = tmp->rightChild->depth+1;
                tmp->balanceFactor = dl - dr;
                tmp->depth = (dl < dr) ? dr : dl;
                tmp = tmp->parentNode;
            }
        } 
    }
    
    void insert(avlNode* node)
    {
        //cout << "Inserting :"<<node->nodeId <<" Key:"<< node->nodeKey << endl;
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
                    else 
                    {
                        tmp->leftChild->parentNode = tmp;
                        tmp = tmp->leftChild;
                    }
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
                    else 
                    {
                        tmp->rightChild->parentNode = tmp;
                        tmp = tmp->rightChild;
                    }
                }
            }
        }
    }            
};

void Display(avlNode *current, int indent)
{
    if (current != NULL)
    {
        Display(current->leftChild, indent + 4);
        if (indent > 0)
            cout << std::setw(indent) << " ";
        cout << current->nodeKey << endl;
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
        cout << current->depth << "\\";
        cout << current->balanceFactor << endl;
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

void insertAVL(avlTree* tr, avlNode* node)
    {
        if(node != NULL)
        {
            //cout<<"Insert  Key:"<<node->nodeKey<<endl;
            tr->insert(node);
            //cout<<"Depth:"<<node->nodeLevel<<endl;
            tr->depth(node);
            //cout<<"Balance NodeId:"<<node->balanceFactor<<endl;
            tr->balance(node);
            //cout<<"Iteration:"<< node->nodeId << endl;
            //DisplayDepth(tr->rootNode,0);
        }
    }

double InsertRunningTime(const int sample_size)
{
    const int EXP_RUNNING_TIME = 100;
    double timesum = 0;
    srand((int) time(0));
    clock_t start,end,stime;
    avlTree* avlT = new avlTree();
    avlNode* avln;
    int total ;
    int factor;
    int i;

    
    //cout << "Expected Insert Iterations = " << EXP_RUNNING_TIME << endl;
    
    for (int j = 0; j < EXP_RUNNING_TIME; j++)
    {
       
        start = clock();
        for(int iter = 0 ; iter < sample_size; iter += 1)
        {
            factor = iter;
            i=0;
            //cout << "RAND_MAX = :"<< RAND_MAX << " Iter = " << iter << endl;
            //do
            //{
            avln = new avlNode();
            avln->nodeKey = rand()% sample_size;
            avln->leftChild = avln->rightChild = avln->parentNode = NULL;
            avln->nodeId = i;
            avln->leftDepth = avln->rightDepth = 0;
            if(false == avlT->exist(avln))
            {
                avlT->insert(avln);
                avlT->depth(avln);
                avlT->balance(avln);
                i++;
                //cout << "Inserted NodeID :" << i << endl;
            }
            //}while(i < iter);
            //Display(avlT->rootNode,0);
            //cout << "Depth of Tree = " << avlT->rootNode->depth << endl;
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

double FindRunningTime(const long sample_size)
{
    const int EXP_RUNNING_TIME = 100;
    double timesum = 0;
    clock_t start,end,stime;
    srand((int) time(0));
    avlTree* avlT = new avlTree();
    avlNode* avln;
    int total ;
    int factor;
    int i;


    
    //cout << "Expected Find Iterations = " << EXP_RUNNING_TIME << endl;
    
    for (int j = 0; j < EXP_RUNNING_TIME; j++)
    {
        //cout << " Find Iteration no. j= " << j << "  time = " << timesum << " ms" << endl;
        start = clock();
        for(int iter = 0 ; iter < sample_size; iter += 1)
        {
            factor = iter;
            i=0;
            //cout << "RAND_MAX = :"<< RAND_MAX << " Iter = " << iter << endl;
            //do
            //{
            
            
            avln = new avlNode();
            avln->nodeKey = rand()% sample_size;
            avln->leftChild = avln->rightChild = avln->parentNode = NULL;
            avln->nodeId = i;
            avln->leftDepth = avln->rightDepth = 0;
            if(false == avlT->exist(avln))
            {
               // avlT->insert(avln);
               // avlT->depth(avln);
               // avlT->balance(avln);
                //i++;
                //cout << "Inserted NodeID :" << i << endl;
            }
            //}while(i < iter);
            //Display(avlT->rootNode,0);
            //cout << "Depth of Tree = " << avlT->rootNode->depth << endl;
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

void myTestCases(int i) {
    const int SAMPLE_ONE_SIZE = 100;
    const int SAMPLE_TWO_SIZE = 10000;
    const int SAMPLE_THREE_SIZE = 10000000;
    
    
    
    
    switch (i) {
        case 1:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_ONE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_ONE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(SAMPLE_ONE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_ONE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(SAMPLE_ONE_SIZE / 2);
            cout << " ms." << endl;
            
            break;
            
        case 2:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_TWO_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_TWO_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(SAMPLE_TWO_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_TWO_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(SAMPLE_TWO_SIZE / 2);
            cout << " ms." << endl;
            
            break;
            
        case 3:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_THREE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_THREE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(SAMPLE_THREE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_THREE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(SAMPLE_THREE_SIZE / 2);
            cout << " ms." << endl;
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {

    cout << "AVL Tree: " << endl;
    myTestCases(1);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    myTestCases(2);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    myTestCases(3);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    
    
    return 0;
}

