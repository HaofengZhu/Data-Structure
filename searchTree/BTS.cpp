#include <stdlib.h>
#include <vector>
#include<iostream>
#include<sstream>
#include<queue>
using namespace std;

template <typename T>
class BTS
{
private:
    struct Node
    {
        T val;
        Node *left;
        Node *right;
        Node(T v) : val(v), left(NULL), right(NULL) {}
    };

public:
    BTS() : root(NULL) {}
    ~BTS() { clear(root); }

    void insert(T val)
    {
        if (root == NULL)
        {
            root = new Node(val);
        }
        else
        {
            insert(val, root);
        }
    }

    int del(T val)
    {
        //成功返回0，失败返回-1
        Node *pParentNode = root;
        Node *pDelNode = root;
        bool isLeft = true;
        while (pDelNode != NULL)
        {
            if (pDelNode->val == val)
                break;
            pParentNode = pDelNode;
            if (val < pParentNode->val)
            {
                pDelNode = pParentNode->left;
                isLeft = true;
            }
            else
            {
                pDelNode = pParentNode->right;
                isLeft = false;
            }
        }
        if (pDelNode == NULL)
        {
            return -1;
        }
        if (pDelNode->left == NULL && pDelNode->right == NULL)
        {
            delete pDelNode;
        }
        else if (pDelNode->left == NULL)
        {
            if (isLeft)
            {
                if (pDelNode == root)
                {
                    root = pDelNode->left;
                }
                else
                {
                    pParentNode->left = pDelNode->right;
                }
            }
            else
            {
                if (pDelNode == root)
                {
                    root = pDelNode->left;
                }
                else
                {
                    pParentNode->right = pDelNode->right;
                }
            }
            delete pDelNode;
        }
        else if (pDelNode->right == NULL)
        {
            if (isLeft)
            {
                if (pDelNode == root)
                {
                    root = pDelNode->left;
                }
                else
                {
                    pParentNode->left = pDelNode->left;
                }
            }
            else
            {
                if (pDelNode == root)
                {
                    root = pDelNode->left;
                }
                else
                {
                    pParentNode->right = pDelNode->left;
                }
            }
            delete pDelNode;
        }
        else
        {
            //左右都有孩子，就把右孩子中最小的一个作为根
            Node *tmpParentNode = pDelNode;
            Node *tmpNode = pDelNode->right;
            while (tmpNode->left != NULL)
            {
                tmpParentNode = tmpNode;
                tmpNode = tmpNode->left;
            }
            tmpParentNode->left = tmpNode->right;

            tmpNode->left = pDelNode->left;
            tmpNode->right = pDelNode->right;
            if (pDelNode == root)
            {
                root = tmpNode;
            }
            else
            {
                if (isLeft)
                {
                    pParentNode->left = tmpNode;
                }
                else
                {
                    pParentNode->right = tmpNode;
                }
            }
            delete pDelNode;
        }
        return 0;
    }

    bool find(T val)
    {
        Node *tmp = root;
        while (tmp)
        {
            if (tmp->val == val)
            {
                return true;
            }
            else if (val < tmp->val)
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
        }
        return false;
    }

    void clear()
    {
        clear(root);
    }

    string PerOrder()
    {
        stringstream ss;
        queue<Node*> q;
        q.push(root);
        Node* tmp;
        ss<<"<";
        while(!q.empty()){
            tmp=q.front();
            q.pop();
            if(tmp==NULL){
                ss<<"NULL";
            }else{
                ss<<tmp->val;
                q.push(tmp->left);
                q.push(tmp->right);
            }
            ss<<",";

        }
        ss<<">";
        return ss.str();
    }


private:
    Node *root;
    void clear(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        else
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void insert(T val, Node *valNode)
    {

        while (true)
        {
            if (valNode->val < val)
            {
                if (valNode->left)
                {
                    valNode = valNode->left;
                }
                else
                {
                    valNode->left = new Node(val);
                    break;
                }
            }
            else
            {
                if (valNode->right)
                {
                    valNode = valNode->right;
                }
                else
                {
                    valNode->right = new Node(val);
                    break;
                }
            }
        }
    }
};


int main(){
    BTS<int> bts;
    bts.insert(5);
    bts.insert(2);
    bts.insert(3);
    bts.insert(7);
    bts.insert(5);
    cout<<bts.PerOrder();
    bts.del(5);
    cout<<bts.PerOrder();
}