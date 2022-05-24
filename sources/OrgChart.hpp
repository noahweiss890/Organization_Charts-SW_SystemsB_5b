#pragma once

#include <iostream>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
#include <string>
using namespace std;

namespace ariel {
    
    class OrgChart {
        public:
            OrgChart() { head = nullptr; }
            ~OrgChart() {
                queue<Node*> que;
                que.push(this->head);
                while(!que.empty()) {
                    Node *curr_son = que.front()->eldest_son;
                    while(curr_son != nullptr) {
                        que.push(curr_son);
                        curr_son = curr_son->right_brother;
                    }
                    Node *rem = que.front();
                    que.pop();
                    // cout << "deleting: " << rem->position << endl;
                    delete rem;
                }
            }
            OrgChart& add_root(string root);
            OrgChart& add_sub(string sup, string sub);

            friend ostream& operator<<(ostream& os, const OrgChart &orgch);
            bool operator==(const OrgChart &w) const;
            bool operator!=(const OrgChart &w) const;
            string operator*();

        private:

            struct Node {
                string position;
                Node* dad;
                Node* eldest_son;
                Node* left_brother;
                Node* right_brother;
                Node(string name) {
                    // cout << "Node ctor got name: " << name << endl;
                    this->position = name;
                    this->dad = nullptr;
                    this->eldest_son = nullptr;
                    this->left_brother = nullptr;
                    this->right_brother = nullptr;
                }
                void add_son(Node* new_guy) {
                    new_guy->dad = this;
                    if(this->eldest_son == nullptr) {
                        this->eldest_son = new_guy;
                    }
                    else {
                        Node *curr = this->eldest_son;
                        while(curr->right_brother != nullptr) {
                            curr = curr->right_brother;
                        }
                        curr->right_brother = new_guy;
                        new_guy->left_brother = curr;
                    }
                }
                friend ostream& operator<<(ostream& os, const Node &node) {
                    cout << "HERE node << :";
                    os << node.position;
                    return os;
                }
            };

            // field
            Node *head;
        
            static void print_tree(ostream& os, Node *head, int indent);

        public:

            class level_order_iterator {
                Node* curr;
                queue<Node*> que;
                public:
                    level_order_iterator(Node* n = nullptr);
                    bool operator==(const level_order_iterator &it) const;
                    bool operator!=(const level_order_iterator &it) const;
                    string& operator*() const;
                    level_order_iterator& operator++();
                    const level_order_iterator operator++(int postfix_flag);
                    string* operator->() const;
            };

            class reverse_order_iterator {
                Node* curr;
                stack<Node*> stk;
                public:
                    reverse_order_iterator(Node* n = nullptr);
                    bool operator==(const reverse_order_iterator &it) const;
                    bool operator!=(const reverse_order_iterator &it) const;
                    string& operator*() const;
                    reverse_order_iterator& operator++();
                    const reverse_order_iterator operator++(int postfix_flag);
                    string* operator->();
            };

            class preorder_iterator {
                Node *curr;
                public:
                    preorder_iterator(Node* n = nullptr);
                    bool operator==(const preorder_iterator &it) const;
                    bool operator!=(const preorder_iterator &it) const;
                    string& operator*() const;
                    preorder_iterator& operator++();
                    const preorder_iterator operator++(int postfix_flag);
                    string* operator->();
            };

            level_order_iterator begin();
            level_order_iterator end();
            level_order_iterator begin_level_order();
            level_order_iterator end_level_order();
            reverse_order_iterator begin_reverse_order();
            reverse_order_iterator reverse_order();
            preorder_iterator begin_preorder();
            preorder_iterator end_preorder();
    };
}