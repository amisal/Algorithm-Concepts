//
//  main.cpp
//  BinarySearchTree
//
//  Created by Anish on 08/04/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//






struct BSTTreeNode {
        int srno;
        int data;
        int level;
        BSTTreeNode * leftptr;
       BSTTreeNode * rightptr;
};

class BinarySearchTree {

private:
    BSTTreeNode * rootnode;
    BSTTreeNode * temp;
    
public:
    
    int ncount;
    int count;
    int lcount;
    int rcount;
    int depth;
    
    BinarySearchTree()
    {
        ncount = count = lcount = rcount = depth = 0;
        rootnode=NULL;
        temp=NULL;
    }
    
    void insert(int key) {
        if (find(key) == NULL) {
            // first create a new node
            BSTTreeNode * newNode = new BSTTreeNode;
            temp = rootnode;
            newNode->data = key;
            newNode->leftptr = NULL;
            newNode->rightptr = NULL;
            if (rootnode == NULL)
            {
                rootnode = newNode;
                newNode->level = 0;newNode->srno = 0;
                return;
            }
            while (temp != NULL) {
                if (key < temp->data)
                {
                    if (temp->leftptr == NULL) {
                        // assign a pointer
                        temp->leftptr = newNode;
                        ncount++; lcount++;newNode->level = temp->level+1;
                        depth = temp->level + 1;newNode->srno = ncount;
                        break;
                    }
                    else
                    {
                        // move to next left pointer
                        temp = temp->leftptr;
                    }
                }
                else
                {
                    if (temp->rightptr == NULL)
                    {
                        // assign a pointer
                        temp->rightptr = newNode;
                        ncount++; rcount++;newNode->level = temp->level+1;
                        depth = temp->level + 1;newNode->srno = ncount;
                        break;
                    }
                    else
                    {
                        // move to next right pointer
                        temp = temp->rightptr;
                    }
                }
            }
        }
    }

    BSTTreeNode* find(int key)
    {
        temp = rootnode;
        while (temp != NULL) {
            if (key == temp->data) 
            {
                // return a pointer
                return temp;
            }

            else if (key < temp->data)
            {
                // move to next left pointer
                temp = temp->leftptr;
            }
            else
            {
               // move to next right pointer
               temp = temp->rightptr;
            }
        }
        return NULL;
    }

    void inOrderTraversal(BSTTreeNode * node)
    {
        if (node == NULL)
            return;
        inOrderTraversal(node->leftptr);
        cout << "| ";
        cout << node->data;
        cout << " - ";
        cout << node->srno;
        cout << "  |";
        inOrderTraversal(node->rightptr);
    }
    
    void freeNodes(BSTTreeNode * node)
    {
        
        if (node == NULL)return;
        freeNodes(node->leftptr);
        freeNodes(node->rightptr);
        delete node;
    }
    
    void printTree()
    {
        cout << "in-Order-Tree-Traversal Begin Here"<<endl;
        depth =0;
        inOrderTraversal(rootnode);
    }
    
    ~BinarySearchTree()
    {
        BSTTreeNode *node = rootnode;
        freeNodes(node);
        rootnode = NULL;
        temp = NULL;
    }
    
};//end of class BST

double InsertRunningTime(BinarySearchTree* object, const int sample_size)
 {
    const int EXP_RUNNING_TIME = 100;
    double timesum = 0;
    srand((int) time(0));
    clock_t start,end,stime;
    
    //cout << "Expected Insert Iterations = " << EXP_RUNNING_TIME << endl;
    
    for (int j = 0; j < EXP_RUNNING_TIME; j++)
    {
        //cout << "Insert Iteration no. j= " << j << "  time = " << timesum << " Sec" << endl;
        if(j != 0)
        {
            object->~BinarySearchTree();
            object = new BinarySearchTree();
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

double FindRunningTime(BinarySearchTree* object, const long sample_size)
 {
    const int EXP_RUNNING_TIME = 100;
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

void myTestCases(BinarySearchTree* bst, int i) {
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
            cout << InsertRunningTime(bst, SAMPLE_ONE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_ONE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(bst, SAMPLE_ONE_SIZE / 2);
            cout << " ms." << endl;
          
            break;

        case 2:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_TWO_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_TWO_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(bst, SAMPLE_TWO_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_TWO_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(bst, SAMPLE_TWO_SIZE / 2);
            cout << " ms." << endl;
            
            break;

        case 3:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_THREE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_THREE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(bst, SAMPLE_THREE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_THREE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(bst, SAMPLE_THREE_SIZE / 2);
            cout << " ms." << endl;
            break;
        default:
            break;
    }
}

int BSTmain() {
    // insert code here...
    BinarySearchTree *bst = new BinarySearchTree();
    cout << "Binary Search Tree: " << endl;
    myTestCases(bst,1);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    myTestCases(bst,2);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    myTestCases(bst,3);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< bst->ncount << endl;
    //cout << "Depth of Tree is = "<< bst->depth << endl;
    
    return 0;
}


