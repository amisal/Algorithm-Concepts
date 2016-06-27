//
//  main.cpp
//  SplayTree
//
//  Created by Anish on 08/04/15.
//  Copyright (c) 2015 Anish. All rights reserved.
//


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>

using namespace std;

struct TreeNode {
    int srno;
    int data;
    int level;
    TreeNode * leftptr;
    TreeNode * rightptr;
    TreeNode * parentNode;
};

class SplayTree {
    
public:
    TreeNode * rootnode;
    TreeNode * temp;
    

    
    int ncount;
    int count;
    int lcount;
    int rcount;
    int depth;
    
    SplayTree()
    {
        ncount = count = lcount = rcount = depth = 0;
        rootnode=NULL;
        temp=NULL;
    }
    
    void insert(int key) {
        if (find(key) == NULL) {
            // first create a new node
            
            TreeNode * newNode = new TreeNode;
            temp = rootnode;
            
            newNode->data = key;
            newNode->leftptr = NULL;
            newNode->rightptr = NULL;
            newNode->parentNode=NULL;
            
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
                        newNode->parentNode=temp;
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
                        newNode->parentNode=temp;
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
    
    TreeNode* find(int key)
    {
        temp = rootnode;
        TreeNode * result=NULL;
        
        while (temp != NULL) {
            if (key == temp->data)
            {
                // return a pointer
                result=Splay(temp);
                //cout<<"FIND KEY IS ";
                //cout<<key;
                //cout<<" "<<endl;
                //object->find((rand() % sample_size) + 1);
                //Display(rootnode,1);
                return result;
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
    
    TreeNode* Splay(TreeNode * node)
    {
        TreeNode * child;
        TreeNode * parent;
        TreeNode * grandparent;
        TreeNode * temp;
        
        child=node;
        
        
        if(child->parentNode==NULL)
        {
            return child;
        }
        else
        {
            parent=child->parentNode;
            if(parent->parentNode==NULL)
            {
                
                if(parent->leftptr==child)
                {
                    //Rotate Right
                    ZigRight(child,parent);
                }
                else
                {
                    //Rotate Left
                    ZigLeft(child,parent);
                }
            }
            else
            {
                grandparent=parent->parentNode;
                //Zig-Zig
                
                if(grandparent->rightptr==parent && parent->rightptr==child)
                    ZigzigLeft(child,parent,grandparent);
                else if(grandparent->leftptr==parent && parent->leftptr==child)
                    ZigzigRight(child,parent,grandparent);
                
                //Zig-Zag
                else if(grandparent->rightptr==parent && parent->leftptr==child)
                ZigzagLeft(child,parent,grandparent);
                else
                ZigzagRight(child,parent,grandparent);
            }
            //cout<<"KEY IS "; cout<<child->data<<endl;
            //Display(rootnode,1);
            temp=Splay(child);

        }
        return node;
    }
    
    void ZigzigLeft(TreeNode * child,TreeNode * parent,TreeNode * grandparent)
    {
        TreeNode *A, *B, *C, *D;
        TreeNode * greatgrandparent;
        
        if(grandparent->parentNode!=NULL)
            greatgrandparent=grandparent->parentNode;
        
        A=child->rightptr;
        B=child->leftptr;
        C=parent->leftptr;
        D=grandparent->leftptr;
        
        if(grandparent->parentNode!=NULL)
        {
            if(greatgrandparent->leftptr==grandparent)
                greatgrandparent->leftptr=child;
            else
                greatgrandparent->rightptr=child;
            
            child->parentNode=greatgrandparent;
        }
        else
        {
            child->parentNode=NULL;
            rootnode=child;
        }
        
        
        
        
        child->rightptr=A;
        child->leftptr=parent;
        
        parent->rightptr=B;
        parent->leftptr=grandparent;
        
        grandparent->rightptr=C;
        grandparent->leftptr=D;
        
        
    }
    void ZigzigRight(TreeNode * child,TreeNode * parent,TreeNode * grandparent)
    {
        TreeNode *A, *B, *C, *D;
        TreeNode * greatgrandparent;
        
        if(grandparent->parentNode!=NULL)
            greatgrandparent=grandparent->parentNode;
        
        A=child->leftptr;
        B=child->rightptr;
        C=parent->rightptr;
        D=grandparent->rightptr;
        
        if(grandparent->parentNode!=NULL)
        {
            if(greatgrandparent->leftptr==grandparent)
                greatgrandparent->leftptr=child;
            else
                greatgrandparent->rightptr=child;
            
            child->parentNode=greatgrandparent;
        }
        else
        {
            child->parentNode=NULL;
            rootnode->parentNode=child;
            rootnode=child;
        }
        
        
        child->parentNode=greatgrandparent;
        child->leftptr=A;
        child->rightptr=parent;
        
        parent->leftptr=B;
        parent->rightptr=grandparent;
        
        grandparent->leftptr=C;
        grandparent->rightptr=D;
    }
    
    void ZigzagLeft(TreeNode * child,TreeNode * parent,TreeNode * grandparent)
    {
        TreeNode *A, *B, *C, *D;
        TreeNode * greatgrandparent;
        
        if(grandparent->parentNode!=NULL)
            greatgrandparent=grandparent->parentNode;
        
        A=parent->rightptr;
        B=child->rightptr;
        C=child->leftptr;
        D=grandparent->leftptr;
        
        if(grandparent->parentNode!=NULL)
        {
            if(greatgrandparent->leftptr==grandparent)
                greatgrandparent->leftptr=child;
            else
                greatgrandparent->rightptr=child;
            
            child->parentNode=greatgrandparent;
        }
        else
        {
            child->parentNode=NULL;
            rootnode=child;
        }

        
        child->rightptr=parent;
        child->leftptr=grandparent;
        
        parent->rightptr=A;
        parent->leftptr=B;
        
        grandparent->rightptr=C;
        grandparent->leftptr=D;
    }
    void ZigzagRight(TreeNode * child,TreeNode * parent,TreeNode * grandparent)
    {
        TreeNode *A, *B, *C, *D;
        TreeNode * greatgrandparent;
        
        if(grandparent->parentNode!=NULL)
            greatgrandparent=grandparent->parentNode;
        
        A=parent->leftptr;
        B=child->leftptr;
        C=child->rightptr;
        D=grandparent->rightptr;
        
        if(grandparent->parentNode!=NULL)
        {
            if(greatgrandparent->leftptr==grandparent)
                greatgrandparent->leftptr=child;
            else
                greatgrandparent->rightptr=child;
            
            child->parentNode=greatgrandparent;
        }
        else
        {
            child->parentNode=NULL;
            rootnode=child;
        }
        
        child->leftptr=parent;
        child->rightptr=grandparent;
        
        parent->leftptr=A;
        parent->rightptr=B;
        
        grandparent->leftptr=C;
        grandparent->rightptr=D;

    }
    
    void ZigLeft(TreeNode * child,TreeNode * parent)
    {
        
        TreeNode *A, *B, *C;
        //TreeNode * grandparent;
        
        A=child->rightptr;
        B=child->leftptr;
        C=parent->leftptr;
        //grandparent=parent->parentNode;
        
        //child->parentNode=grandparent;
        child->rightptr=A;
        child->leftptr=parent;
        
        parent->rightptr=B;
        parent->leftptr=C;
        parent->parentNode=child;
        
        child->parentNode=NULL;
        rootnode=child;
    }
    
    void ZigRight(TreeNode * child,TreeNode * parent)
    {
        TreeNode *A, *B, *C,*temp;
        //TreeNode * grandparent;
        //temp=rootnode;
        
        A=child->leftptr;
        B=child->rightptr;
        C=parent->rightptr;
        //grandparent=parent->parentNode;
        
        //child->parentNode=grandparent;
        child->leftptr=A;
        child->rightptr=parent;
        
        parent->leftptr=B;
        parent->rightptr=C;
        parent->parentNode=child;
        
        
        child->parentNode=NULL;
        
        rootnode=child;
    }
    
    void inOrderTraversal(TreeNode * node)
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
    
    void freeNodes(TreeNode * node)
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
    
    ~SplayTree()
    {
        TreeNode *node = rootnode;
        freeNodes(node);
        rootnode = NULL;
        temp = NULL;
    }
    
    
    void Display(TreeNode *current, int indent)
    {
        if (current != NULL)
        {
            Display(current->leftptr, indent + 4);
            if (indent > 0)
                cout << setw(indent) << " ";
            cout << current->data << endl;
            Display(current->rightptr, indent + 4);
        }
    }
};//end of class BST

double InsertRunningTime(SplayTree* object, const int sample_size)
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
            object->~SplayTree();
            object = new SplayTree();
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
        //object->Display(object->rootnode, 1);
        //object.printTree(); cout << endl;
    }
    
    //timesum = timesum / EXP_RUNNING_TIME;
    
    //cout << "Total Iterations = " << EXP_RUNNING_TIME;
    //cout << "\tTotal Time =" << timesum;
    //cout << "\tAverage Time = " << timesum / EXP_RUNNING_TIME;
    //cout << endl;
    //object.printTree();
    //cout<<"Inorder Traversal for Binary Search Tree is:" << endl;
    //object->printTree();
    return timesum;
}

double FindRunningTime(SplayTree* object, const long sample_size)
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
            //cout<<"FIND KEY IS ";
            //cout<<(rand() % sample_size)+1;
            //cout<<" "<<endl;
            object->find((rand() % sample_size) + 1);
            //object->Display(object->rootnode,1);
            
        }
        end = clock();
        timesum += (int)((end - start)/(CLOCKS_PER_SEC * 0.001));
    }
    //timesum = timesum / EXP_RUNNING_TIME;
    
    // cout << "Total Iterations = " << EXP_RUNNING_TIME;
    // cout << "\tTotal Time =" << timesum;
   // cout << "\tAverage Time = " << timesum / EXP_RUNNING_TIME;
    // cout << endl;
    //object->printTree();
    //cout<<"Inorder Traversal for Binary Search Tree is:" << endl;
    //object.printTree();
    return timesum;
}

void myTestCases(SplayTree* st, int i) {
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
            cout << InsertRunningTime(st, SAMPLE_ONE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_ONE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(st, SAMPLE_ONE_SIZE / 2);
            cout << " ms." << endl;
            
            
            break;
            
        case 2:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_TWO_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_TWO_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(st, SAMPLE_TWO_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_TWO_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(st, SAMPLE_TWO_SIZE / 2);
            cout << " ms." << endl;
            
            break;
            
        case 3:
            cout << endl;
            cout << "n=";
            cout << SAMPLE_THREE_SIZE << endl;
            cout << "Insert: ";
            cout << SAMPLE_THREE_SIZE;
            cout << " nodes traversed in ";
            cout << InsertRunningTime(st, SAMPLE_THREE_SIZE);
            cout << " ms." << endl;
            cout << "Find: ";
            cout << SAMPLE_THREE_SIZE / 2;
            cout << " nodes traversed in ";
            cout << FindRunningTime(st, SAMPLE_THREE_SIZE / 2);
            cout << " ms." << endl;
            break;
        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    SplayTree *st = new SplayTree();
    cout << "Splay Tree: " << endl;
    
//    for (int i=20; i>0; i--) {
//        
//        st->insert(i);
//    }
//    
//    
//    
//    st->Display(st->rootnode, 1);
//    
//    st->find(15);
//    st->find(20);
    
    myTestCases(st,1);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< st->ncount << endl;
    //cout << "Depth of Tree is = "<< st->depth << endl;
    myTestCases(st,2);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< st->ncount << endl;
    //cout << "Depth of Tree is = "<< st->depth << endl;
    myTestCases(st,3);
    //cout << endl << "Main Function Tree " << endl;
    //cout << "Total Nodes = "<< st->ncount << endl;
    //cout << "Depth of Tree is = "<< st->depth << endl;
    //st->Display(st->rootnode, 1);

    return 0;
}


