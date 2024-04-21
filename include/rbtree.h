/*
    note:
    basic rules:
        1.every node is either red or black
        2.root and leafe node must be black
            leafe node(aka:NIL,no value,but has a parent pointer)
        3.if current node is red,both of its sons should be black
        4.the number of black node on the simple path 
        from arbitrary node to leafe node should be same

    insert flow:
    1.insert new node:
        insert a node into tree like binary-tree,and colored it red
    2.check the basic rules:
        2.1 if node to be inserted is root, just color it black
        2.2 if node to be inserted's father node is black,and didn't break any basic rules,
        no operation need to be done
        2.3 if node to be inserted's father node is red,adjust red_black_tree(step 3) 
        because of breaking basic rule 3.(if current node is red,both of its sons should be black)
    3.adjust red_black_tree
    if node to be inserted's father node is red,these situation should be considered:
        3.1 father is grandpa's left child
            3.1.1 uncle is red
                3.1.1.1 color uncle and father to black(both of them was red)
                3.1.1.2 color grandpa to red
                3.1.1.3 adjust red_black_tree recursively with grandpa
            3.1.2 uncle is black or doesn't exit
                3.1.2.1 if new node was right child,change object to father,and left rotate
                3.1.2.2 color object's father(might be changed in last step) to black,color grandpa to red
                3.1.2.3 right rotate grandpa
        3.2 father is grandpa's right child
            3.2.1 uncle is red(same as 3.1.1)
                3.2.1.1 color uncle and father to black(both of them was red)
                3.2.1.2 color grandpa to red
                3.2.1.3 adjust red_black_tree recursively with grandpa
            3.2.2 uncle is black or doesn't exit(oppsite to 3.1.2)
                3.2.2.1 if new node was left child,change object to father,and right rotate
                3.2.2.2 color object's father(might be changed in last step) to black,color grandpa to red
                3.2.2.3 left rotate grandpa
    step above should execute recursively until no basic rules was broken.

    rotate operation:
        left rotate:
            node x's right child(node y) become x's father,and x now become y's left child
            if y had a left child,it would become x's right child
            x                       y
                y   ---------->x
             [c]                 [c]
        right rotate:
            oppsite to left rotate,x's left child y become x's father,x become y's right child
            if y had a right child,it would become x's left child
                x               y
            y       ---------->      x
             [c]                  [c]
    
    delete flow:
        1.locate position
        2.handle two situations:
            2.1 node to be deleted has two children.
            we find either its next node(normally its right child tree's smallest node)
            or its previous node(normally its left child tree's bigest node)
            2.2 node to be deleted has one child.
            if node to be deleted is red,no operation need
            if node to be deleted is black,adjust RBTree to make sure no basic rules is broken
        3. adjust RBTree
            if node to be deleted is black(2.2)
            3.1 if brother node is red.
            color brother to black,and father to red,rotate father(left child left rotate,right...)
            this operation activates some of situations below
            3.2 brother node is lack,and brother's two child are both black
            color brother to red,and adjust object to father
            if node's color is red now,color it to black and we are done
            3.3 brother node is black,brother's left child is red and right child is black
            color brother to red,brother's left child to black
            right rotate brother node
            come to 3.4
            3.4 brother node is black,and brother's right child is red
            color brother to father's color,father to black,brother's right child to black
            left rotate father
            done
    

    
    Why RBTree:O(log(n)) both time and space complexity
*/
#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace myStd{
enum class Color { RED,BLACK };

template <typename Key,typename Value>
class RBTree{
public:
    RBTree()
    :m_root(nullptr)
    ,m_size(0)
    ,m_NIL(new Node())
    {
        m_NIL->m_color = Color::BLACK;
    }

    ~RBTree()
    {
        if(m_size != 0){
            clear();
        }
        
    }

    void insert(const Key& key,const Value& value){
        insertNode(key,value);
    }

    void remove(const Key& key){
        Node* dood = lookup(key);
        if(dood != nullptr){
            deleteNode(dood);
            m_size--;
        }
    }

    Value* at(const Key& key){
        auto res = lookup(key);
        if(res != nullptr){
            return &res->m_value;
        }
        return nullptr;
    }

    int size(){
        return m_size;
    }

    bool empty(){
        return m_size == 0;
    }

    void clear(){
        deleteTree(m_root);
        m_size = 0;
    }

    void print(){
        inorderTraversal(m_root);
    }
private:
    struct Node{
        Key m_key;
        Value m_value;
        Color m_color;
        Node* m_left_ptr;
        Node* m_right_ptr;
        Node* m_parent_ptr;

        Node(const Key& k,const Value& v,Color c,Node* p = nullptr)
        :m_key(k)
        ,m_value(v)
        ,m_color(c)
        ,m_left_ptr(nullptr)
        ,m_right_ptr(nullptr)
        ,m_parent_ptr(p)
        {}

        Node()
        :m_color(Color::BLACK)
        ,m_left_ptr(nullptr)
        ,m_right_ptr(nullptr)
        ,m_parent_ptr(nullptr)
        {}
    };//struct Node

private:
    Node* m_root;
    size_t m_size;
    Node* m_NIL;

    // basic tools:lookup,left/right rotate
    Node* lookup(const Key& key){
        Node* cmpNode = m_root;
        
        //iteration instead of recursive
        while(cmpNode){
            if(key < cmpNode->m_key){
                cmpNode = cmpNode->m_left_ptr;
            }else if(key > cmpNode->m_key){
                cmpNode = cmpNode->m_right_ptr;
            }else{
                return cmpNode;
            }
        }//while(cmpNode)
        return cmpNode;
    }

    void rightRotate(Node* node){
        /*right rotate:
            x's left child y become x's father,x become y's right child
            if y had a right child,it would become x's left child
                x               y
            y       ---------->      x
             [c]                  [c]
        */
        
        // get current node's left son
        Node* l_son = node->m_left_ptr;

        // if l_son had a right child,it would become node's left child 
        node->m_left_ptr = l_son->m_right_ptr;//either null or node
        if(l_son->m_right_ptr){
            l_son->m_right_ptr->m_parent_ptr = node;
        }
        
        //node's left child l_son become node's father,node become l_son's right child
        l_son->m_parent_ptr = node->m_parent_ptr;
        if(!node->m_parent_ptr){
            m_root = l_son;
        }else if(node == node->m_parent_ptr->m_left_ptr){
            //if original node was it's father's left son
            node->m_parent_ptr->m_left_ptr = l_son;
        }else{
            //if original node was it's father's right son
            node->m_parent_ptr->m_right_ptr = l_son;
        }

        // new daddy!
        l_son->m_right_ptr = node;
        node->m_parent_ptr = l_son;
    }

    void leftRotate(Node* node){
        
        // see rightRotate,but on the oppsite way
        Node* r_son = node->m_right_ptr;

        node->m_right_ptr = r_son->m_left_ptr;
        if(r_son->m_left_ptr){
            r_son->m_left_ptr->m_parent_ptr = node;
        }
        
        r_son->m_parent_ptr = node->m_parent_ptr;
        if(!node->m_parent_ptr){
            m_root = r_son;
        }else if(node == node->m_parent_ptr->m_right_ptr){
            node->m_parent_ptr->m_right_ptr = r_son;
        }else{
            node->m_parent_ptr->m_left_ptr = r_son;
        }

        r_son->m_left_ptr = node;
        node->m_parent_ptr = r_son;
    }

    void insertHelper(Node* target){
        using enum Color;
        // if node to be inserted's father node is red
        while(target->m_parent_ptr && target->m_parent_ptr->m_color == RED){
            //3.1 father is grandpa's left child
            // note:why grandpa exist?because basic rule2:root and leafe node must be black
            if(target->m_parent_ptr == target->m_parent_ptr->m_parent_ptr->m_left_ptr){
                Node* uncle = target->m_parent_ptr->m_parent_ptr->m_right_ptr;
                // 3.1.1 uncle is red
                if(uncle && uncle->m_color == RED){
                    // 3.1.1.1 color uncle and father to black(both of them was red)
                    target->m_parent_ptr->m_color = BLACK;
                    uncle->m_color = BLACK;
                    // 3.1.1.2 color grandpa to red
                    target->m_parent_ptr->m_parent_ptr->m_color = RED;
                    // 3.1.1.3 adjust red_black_tree recursively with grandpa
                    target = target->m_parent_ptr->m_parent_ptr;
                }/**/ else{
                    //3.1.2 uncle is black or doesn't exit
                    // 3.1.2.1 if new node was right child,change object to father,and left rotate
                    if(target == target->m_parent_ptr->m_right_ptr){
                        target = target->m_parent_ptr;
                        leftRotate(target);
                    }
                    // 3.1.2.2 color object's father(might be changed in last step) to black,color grandpa to red
                    target->m_parent_ptr->m_color = BLACK;
                    target->m_parent_ptr->m_parent_ptr->m_color = RED;
                    rightRotate(target->m_parent_ptr->m_parent_ptr);
                }// end of 3.1.x
            } else{
                //3.2 father is grandpa's right child
                //3.2.1 uncle is red(same as 3.1.1)
                Node* uncle = target->m_parent_ptr->m_left_ptr;
                if(uncle && uncle->m_color == RED){
                    //3.2.1.1 color uncle and father to black(both of them was red)
                    uncle->m_color = BLACK;
                    target->m_parent_ptr->m_color = BLACK;
                    // 3.2.1.2 color grandpa to red
                    target->m_parent_ptr->m_parent_ptr->m_color = RED;
                    // 3.2.1.3 adjust red_black_tree recursively with grandpa
                    target = target->m_parent_ptr->m_parent_ptr;
                }else{
                    // 3.2.2 uncle is black or doesn't exit(oppsite to 3.1.2)
                    // 3.2.2.1 if new node was left child,change object to father,and right rotate
                    if(target == target->m_parent_ptr->m_left_ptr){
                        target = target->m_parent_ptr;
                        rightRotate(target);
                    }
                    // 3.2.2.2 color object's father(might be changed in last step) to black,color grandpa to red
                    target->m_parent_ptr->m_color = BLACK;
                    target->m_parent_ptr->m_parent_ptr->m_color = RED;
                    // 3.2.2.3 left rotate grandpa
                    leftRotate(target->m_parent_ptr->m_parent_ptr);
                }
            }// end of 3.x
        }
        //make sure root is black
        m_root->m_color = BLACK;
    }

    void insertNode(const Key& key,const Value& value){
        
        using enum Color;
        Node* newNode = new Node(key,value,RED);
        Node* parent{nullptr};
        Node* cmpNode = m_root;

        //locate position to insert(newNode's parent)
        while(cmpNode){
            parent = cmpNode;
            if(newNode->m_key < cmpNode->m_key){
                cmpNode = cmpNode->m_left_ptr;
            }else if(newNode->m_key > cmpNode->m_key){
                cmpNode = cmpNode->m_right_ptr;
            }else{
                // already exist,just delete
                delete newNode;
                return;
            }
        }//end of while(cmpNode)

        //increase size
        ++m_size;


        //set newNode's parent
        newNode->m_parent_ptr = parent;
        if(!parent){
            m_root = newNode;
        }else if(newNode->m_key < parent->m_key){
            parent->m_left_ptr = newNode;
        }else{
            parent->m_right_ptr = newNode;
        }

        //clean up RBTree
        insertHelper(newNode);
    }

    void inorderTraversal(Node* node) const{
        if(node){
            inorderTraversal(node->m_left_ptr);
            std::cout << node->m_key << " " << node->m_value << std::endl;
            inorderTraversal(node->m_right_ptr);
        }
    }

    //helper function,used to replace newNode with targetNode,used by delete
    void replaceNode(Node* targetNode,Node* newNode){
        if(!targetNode->m_parent_ptr){
            m_root = newNode;
        }else if(targetNode == targetNode->m_parent_ptr->m_left_ptr){
            targetNode->m_parent_ptr->m_left_ptr = newNode;
        }else{
            targetNode->m_parent_ptr->m_right_ptr = newNode;
        }

        if(newNode){
            newNode->m_parent_ptr = targetNode->m_parent_ptr;
        }
    }

    // find minest node
    Node* findMinimumNode(Node* node){
        while(node->m_left_ptr){
            node = node->m_left_ptr;
        }
        return node;
    }

    // used by remoceHelper
    Color getColor(Node* node){
        if(node == nullptr){
            return Color::BLACK;
        }
        return node->m_color;
    }
    // used by remoceHelper
    void setColor(Node *node, Color color) {
        if (node == nullptr) {
            return;
        }
        node->m_color = color;
    }

    // used to fix up RBTree,when node to be deleted is black(2.2),used by removeNode
    void removeHelper(Node* node){
        using enum Color;
        // if node is NIL and has no parent,which means it's the only node,just return
        if(node == m_NIL && node->m_parent_ptr == nullptr){
            return;
        }
        // we need to adjust RBTree from botom to top
        while(node != m_root){
            // if node is father's left child
            if(node == node->m_parent_ptr->m_left_ptr){
                // brother node
                Node* brother = node->m_parent_ptr->m_right_ptr;
                //3.1 if brother node is red.
                if(getColor(brother) == RED){
                    // color brother to black,and father to red,rotate father
                    setColor(brother,BLACK);
                    setColor(node->m_parent_ptr,RED);
                    leftRotate(node->m_parent_ptr);
                    // remember update brother after rotate
                    brother = node->m_parent_ptr->m_right_ptr;
                }
                
                //3.2 brother node is lack,and brother's two child are both black
                //after 3.1 ,now brother must be black
                if(getColor(brother->m_left_ptr) == BLACK &&
                getColor(brother->m_right_ptr) == BLACK){
                    // color brother to red,and adjust object to father
                    setColor(brother,RED);
                    node = node->m_parent_ptr;
                    // if node's color is red now,color it to black and we are done
                    if(node->m_color == RED){
                        node->m_color = BLACK;
                        node = m_root;
                    }
                }else{
                    // 3.3 brother node is black,brother's left child is red and right child is black
                    
                    if(getColor(brother->m_right_ptr) == BLACK){
                        //color brother to red,brother's left child to black
                        setColor(brother->m_left_ptr,BLACK);
                        setColor(brother,RED);
                        //right rotate brother node
                        rightRotate(brother);
                        //remember to update brother after rotate
                        brother = node->m_parent_ptr->m_right_ptr;
                    }
                    //come to 3.4 brother node is black,and brother's right child is red
                    // color brother to father's color,father to black,brother's right child to black
                    setColor(brother,getColor(node->m_parent_ptr));
                    setColor(node->m_parent_ptr,BLACK);
                    setColor(brother->m_right_ptr,BLACK);
                    // left rotate father
                    leftRotate(node->m_parent_ptr);
                    //done
                    node = m_root;
                }//end of 3.x
            }else{
                //  if node is father's left child
                // brother node
                Node* brother = node->m_parent_ptr->m_left_ptr;
                if(getColor(brother) == RED){
                    setColor(brother,BLACK);
                    setColor(node->m_parent_ptr,RED);
                    rightRotate(node->m_parent_ptr);
                    brother = node->m_parent_ptr->m_left_ptr;
                }
                
                if(getColor(brother->m_right_ptr) == BLACK &&
                getColor(brother->m_left_ptr) == BLACK){
                    setColor(brother,RED);
                    node = node->m_parent_ptr;
                    if(node->m_color == RED){
                        node->m_color = BLACK;
                        node = m_root;
                    }
                }else{                    
                    if(getColor(brother->m_left_ptr) == BLACK){
                        setColor(brother->m_right_ptr,BLACK);
                        setColor(brother,RED);
                        leftRotate(brother);
                        brother = node->m_parent_ptr->m_left_ptr;
                    }
                    setColor(brother,getColor(node->m_parent_ptr));
                    setColor(node->m_parent_ptr,BLACK);
                    setColor(brother->m_left_ptr,BLACK);
                    leftRotate(node->m_parent_ptr);
                    node = m_root;
                }//end of 3.x
            }// end of 3
        }// end of while(node != m_root)
        //make sure current node is black
        setColor(node,BLACK);
    }

    void disconnectNIL(){
        if(m_NIL == nullptr){
            return;
        }
        if(m_NIL->m_parent_ptr != nullptr){
            if(m_NIL == m_NIL->m_parent_ptr->m_left_ptr){
                m_NIL->m_parent_ptr->m_left_ptr = nullptr;
            }else{
                m_NIL->m_parent_ptr->m_right_ptr = nullptr;
            }
        }
    }

    void deleteNode(Node* deleteNode){
        using enum Color;
        Node* replace = deleteNode; // init replaceNode to deleteNode
        Node* child = nullptr;      // deleteNode's child
        Node* parentRP;             // replaceNode's parent
        Color origColor = deleteNode->m_color;  //record orignal color of deleteNode

        // 2.2 node to be deleted has one child.
        if(!deleteNode->m_left_ptr){
            replace = deleteNode->m_right_ptr;
            parentRP = deleteNode->m_parent_ptr;
            origColor = getColor(replace);
            replaceNode(deleteNode,replace);
        }else if(!deleteNode->m_right_ptr){
            replace = deleteNode->m_left_ptr;
            parentRP = deleteNode->m_parent_ptr;
            origColor = getColor(replace);
            replaceNode(deleteNode,replace);
        }else
        {
            replace = findMinimumNode(deleteNode->m_right_ptr);
            origColor = replace->m_color;
            if(replace != deleteNode->m_right_ptr){
                parentRP = replace->m_parent_ptr;
                child = replace->m_right_ptr;
                parentRP->m_left_ptr = child;
                if(child != nullptr){
                    child->m_parent_ptr = parentRP;
                }
                deleteNode->m_left_ptr->m_parent_ptr = replace;
                deleteNode->m_right_ptr->m_parent_ptr = replace;
                replace->m_left_ptr = deleteNode->m_left_ptr;
                replace->m_right_ptr = deleteNode->m_right_ptr;
                if(deleteNode->m_parent_ptr != nullptr){
                    if(deleteNode == deleteNode->m_parent_ptr->m_left_ptr){
                        deleteNode->m_parent_ptr->m_left_ptr = replace;
                        replace->m_parent_ptr = deleteNode->m_parent_ptr;
                    }else{
                        deleteNode->m_parent_ptr->m_right_ptr = replace;
                        replace->m_parent_ptr = deleteNode->m_parent_ptr;
                    }
                }else{
                    m_root = replace;
                    m_root->m_parent_ptr = nullptr;
                }
            }else{
                child = replace->m_right_ptr;
                replace->m_left_ptr = deleteNode->m_left_ptr;
                deleteNode->m_left_ptr->m_parent_ptr = replace;
                if(deleteNode->m_parent_ptr != nullptr){
                    if(deleteNode == deleteNode->m_parent_ptr->m_left_ptr){
                        deleteNode->m_parent_ptr->m_left_ptr = replace;
                        replace->m_parent_ptr = deleteNode->m_parent_ptr;
                    }else{
                        deleteNode->m_parent_ptr->m_right_ptr = replace;
                        replace->m_parent_ptr = deleteNode->m_parent_ptr;
                    }
                }else{
                    m_root = replace;
                    m_root->m_parent_ptr = nullptr;
                }
                parentRP = replace;
            }
        }

        if(replace != nullptr){
            replace->m_color = deleteNode->m_color;
        }else{
            origColor = deleteNode->m_color;
        }

        if(origColor == BLACK){
            if(child != nullptr){
                removeHelper(child);
            }else{
                m_NIL->m_parent_ptr = parentRP;
                if(parentRP != nullptr){
                    if(parentRP->m_left_ptr == nullptr){
                        parentRP->m_left_ptr = m_NIL;
                    }else{
                        parentRP->m_right_ptr = m_NIL;
                    }
                }
                removeHelper(m_NIL);
                disconnectNIL();
            }
        }

        delete deleteNode;
    }

    void deleteTree(Node *node){
        if(node){
            deleteTree(node->m_left_ptr);
            deleteTree(node->m_right_ptr);
            delete node;
            node = nullptr;
        }
    }
};//class RBTree
}//namespace myStd