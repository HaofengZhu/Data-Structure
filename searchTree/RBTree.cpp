#include<stdlib.h>
#include<iostream>
#include <iomanip>
#include"RBTree.h"

template<typename T>
void RBTree<T>::leftRotate(RBTNode<T>* &root,RBTNode<T>* x){
    RBTNode<T> *y=x->right;

    x->right=y->left;
    if(y->left!=NULL){
        y->left->parent=x;
    }
    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }

    y->parent=x->parent;
    if(x->parent==NULL){
        root=y;
    }else
    {
        if (x->parent->left == x)
            x->parent->left = y;    
        else
            x->parent->right = y;   
    }
    
    y->left = x;
    x->parent = y;
}

template <class T>
void RBTree<T>::setChild(RBTNode<T>* parent,childDirection direction,RBTNode<T>* child){
    if(direction==childDirection::LEFT){
        parent->left=child;
    }else{
        parent->right=child;
    }
    if(child){
        child->parent=parent;
    }
}

template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
    RBTNode<T> *x = y->left;

    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        root = x;           
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;   
        else
            y->parent->left = x;   
    }

    x->right = y;
    y->parent = x;
}


template<typename T>
void RBTree<T>::insert(T key){
    RBTNode<T> *z=NULL;
    if ((z=new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
        return ;

    insert(mRoot, z);
}

template<typename T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node){
    RBTree<T> *y=NULL;
    RBTree<T> *x=root;

    while(x!=NULL){
        y=x;
        if(node->key<x->key){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    node->parent=y;
    if (y!=NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    node->color = RED;

    insertFixUp(root,node);
}


template <typename T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *parent,*gparent;

    //如果父节点存在且为红色
    while((parent=node->parent)!=NULL&&parent->color==RED){
        gparent=parent->parent;

        //情景1:叔叔节点存在且是红色
        {
            RBTNode<T> *uncle=gparent->right;
            if(uncle&&uncle->color==RED){
                uncle->color=BLACK;
                parent->color=BLACK;
                gparent->color=RED;
                node=gparent;
                continue;
            }
        }

        if(parent==gparent->left){
            //情景3：叔叔节点是黑色（或者不存在），且当前节点是其父节点的右孩子，父节点是其祖父节点的左孩子
            if(parent->right==node){
                RBTNode<T>* tmp;
                leftRotate(root,parent);
                tmp=parent;
                parent=node;
                node=tmp;
            }
            //情景3后半段和情景2：当前节点是其父节点的左孩子，父节点是其祖父节点的左孩子
            parent->color=BLACK;
            gparent->color=RED;
            rightRotate(root,gparent);
            }else{
            //情景4：叔叔节点是黑色（或者不存在），且当前节点是其父节点的左孩子，父节点是其祖父节点的右孩子
            if(parent->left==node){
                RBTNode<T>* tmp;
                rightRotate(root,parent);
                tmp=parent;
                parent=node;
                node=tmp;
            }
            //情景4后半段和情景5：当前节点是其父节点的右孩子，父节点是其祖父节点的右孩子
            parent->color=BLACK;
            gparent->color=RED;
            leftRotate(root,gparent);
        }
    }
    root->color=BLACK;
}

template<typename T>
void RBTree<T>::remove(T key){
    RBTNode<T> *node;
    if((node==search(mRoot,key))!=NULL){
        remove(mRoot,node);
    }
}

template<typename T>
void RBTree<T>::remove(RBTNode<T>* & root,RBTNode<T>* node){
    RBTNode<T> *child,*parent;
    RBTColor color;

    if(node->left!=NULL&&node->right!=NULL){
        //用后继节点替换
        RBTNode<T> *replace=node->right;
        while (replace->left!=NULL)
        {
            replace=replace->left;
        }
        if(node->parent!=NULL){
            //不是根节点
            if(node->parent->left==node)
                node->parent->left=replace;
            else
                node->parent->right=replace;
        }else{
            root=replace;
        }

        //调整被取代的节点,用replace的右节点替代（replace一定没有左孩子）
        child = replace->right;
        parent = replace->parent;
        if(parent==node){
            //特殊情况，如果replace就是node的右节点，因为node要被替换 ，这里parent要修改为replace
            parent=replace;
            //这里拼接到replace右节点的节点本身就是replace的右节点，因此不需要操作
        }else{
            //replace被拿走
            //需要将parent->left设置为child
            setChild(parent,LEFT,child);
            //node被替换，需要将node的右孩子作为replace的右孩子
            setChild(replace,RIGHT,node->right);
        }
        // 保存"取代节点"的颜色
        color = replace->color;
        replace->color=node->color;
        replace->parent=node->parent;

        //设置node的左节点为replace的左结点
        setChild(replace,LEFT,node->left);

        //如果被替换的节点是黑色，则需要特殊的操作来自平衡
        if(color==BLACK)
            removeFixUp(root,child,parent);
        delete node;
        return;
    }
    
    if(node->left!=NULL){
        child=node->left;
    }else{
        child=node->right;
    }
    parent=node->parent;
    color=node->color;
    if(child){
        child->parent=parent;
    }
    if(parent){
        //node不是根节点
        if(parent->left==node){
            parent->left=child;
        }else{
            parent->right=child;
        }
    }else{
        root=child;
    }

    //删除情景1，替换节点是红色，仍然符合红黑树性质，不需要fixup
    if(color==BLACK){
        //其余情景
        removeFixUp(root,child,parent);
    }
    delete node;
}


template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *brother;

    while ((!node || node->color==BLACK) && node != root)
    {
        if (parent->left == node)
        {
            //删除情景2.1：替换结点是其父结点的左子结点
            brother = parent->right;
            if (brother->color==RED)
            {
                // 删除情景2.1.1：替换结点的兄弟结点是红结点  
                brother->color=BLACK;
                parent->color=RED;
                leftRotate(root, parent);
                brother = parent->right;
                //进行情景2.1.2.3的处理
            }
            if ((!brother->left || brother->left->color==BLACK) &&
                (!brother->right || brother->right->color==BLACK))
            {
                // 删除情景2.1.2.3：替换结点的兄弟结点的子结点都为黑结点  
                brother->color=RED;
                node = parent;
                parent = node->parent;
                //继续循环，把parent作为新的替换结点，重新进行删除结点情景处理
            }
            else
            {
                if (!brother->right || brother->right==BLACK)
                {
                    // 删除情景2.1.2.2：替换结点的兄弟结点的右子结点为黑结点，左子结点为红结点  
                    brother->left->color=BLACK;
                    brother->color=RED;
                    rightRotate(root, brother);
                    brother = parent->right;
                    //进行情景2.1.2.1的处理
                }
                // 删除情景2.1.2.1：替换结点的兄弟结点的右子结点是红结点，左子结点任意颜色
                brother->color=parent->color;
                parent->color=BLACK;
                brother->right=BLACK;
                leftRotate(root, parent);
                node = root;
                break;
                //处理完成，出循环
            }
        }
        else
        {
            brother = parent->left;
            if (brother->color==RED)
            {
                brother->color=BLACK;
                parent->color=RED;
                rightRotate(root, parent);
                brother = parent->left;
            }
            if ((!brother->left || rb_is_black(brother->left)) &&
                (!brother->right || rb_is_black(brother->right)))
            {
                brother->color=RED;
                node = parent;
                parent=node->parent;
            }
            else
            {
                if (!brother->left || rb_is_black(brother->left))
                {
                    brother->right->color=BLACK;
                    brother->color=RED;
                    leftRotate(root, brother);
                    brother = parent->left;
                }
                brother->color=parent->color;
                parent->color=BLACK;
                brother->left->color=BLACK;
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            std::cout << std::setw(2) << tree->key << "(B) is root" << std::endl;
        else                // tree是分支节点
            std::cout << std::setw(2) << tree->key <<  (rb_is_red(tree)?"(R)":"(B)") << " is " << std::setw(2) << key << "'s "  << std::setw(12) << (direction==1?"right child" : "left child") << std::endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void RBTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}
