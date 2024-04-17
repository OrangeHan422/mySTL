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
        
    
    Why RBTree:O(log(n)) both time and space complexity
*/

#include <iostream>
#include <sstream>
#include <string>

namespace myStd{
enum class Color { RED,BLACK };

template <typename Key,typename Value>
class RBTree{

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
            l_son->m_right_ptr->parent = node;
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
            r_son->m_left_ptr->parent = node;
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
                    target->m_parent_ptr->m_parent_ptr = RED;
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
        Node* newNode(key,value,Red);
        Node* parent{nullptr};
        Node* cmpNode = root;

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
        if(parent){
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

    void removeHelper(Node* node){

    }
};//class RBTree
}//namespace myStd