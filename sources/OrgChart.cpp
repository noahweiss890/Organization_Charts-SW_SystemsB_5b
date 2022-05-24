#include "OrgChart.hpp"
using namespace ariel;

namespace ariel {

    OrgChart& OrgChart::add_root(string root) {
        if(this->head == nullptr) {
            // Node new_guy(root);
            this->head = new Node(root);
            // cout << "head name in add_root: " << this->head->position << endl;
            return *this;
        }
        this->head->position = root;
        return *this;
    }

    OrgChart& OrgChart::add_sub(string sup, string sub) {
        if(!this->head) {
            throw invalid_argument("can't add sub before root");
        }
        queue<Node*> que;
        que.push(this->head);
        while(!que.empty()) {
            if(que.front()->position == sup) {
                que.front()->add_son(new Node(sub));
                return *this;
            }
            Node *curr_son = que.front()->eldest_son;
            while(curr_son != nullptr) {
                que.push(curr_son);
                curr_son = curr_son->right_brother;
            }
            que.pop();
        }
        throw invalid_argument("employer doesn't exist");
    }


    // level_order_iterator:

    OrgChart::level_order_iterator::level_order_iterator(Node* n) {
        this->curr = n;
        if(n) {
            this->que.push(n);
        }
    }

    bool OrgChart::level_order_iterator::operator==(const level_order_iterator &it) const {
        return this->curr == it.curr;
    }

    bool OrgChart::level_order_iterator::operator!=(const level_order_iterator &it) const {
        return !(*this == it);
    }

    string& OrgChart::level_order_iterator::operator*() const {
        return this->curr->position;
    }

    OrgChart::level_order_iterator& OrgChart::level_order_iterator::operator++() {
        Node *curr_son = this->curr->eldest_son;
        while(curr_son != nullptr) {
            this->que.push(curr_son);
            curr_son = curr_son->right_brother;
        }
        this->que.pop();
        if(que.empty()) {
            this->curr = nullptr;
        }
        else {
            this->curr = this->que.front();
        }
        return *this;
    }

    const OrgChart::level_order_iterator OrgChart::level_order_iterator::operator++(int postfix_flag) {
        OrgChart::level_order_iterator temp = *this;
        Node *curr_son = this->curr->eldest_son;
        while(curr_son != nullptr) {
            this->que.push(curr_son);
            curr_son = curr_son->right_brother;
        }
        this->que.pop();
        if(que.empty()) {
            this->curr = nullptr;
        }
        else {
            this->curr = this->que.front();
        }
        return temp;
    }

    string* OrgChart::level_order_iterator::operator->() const {
        return &this->que.front()->position;
    }

    
    // reverse_order_iterator:

    OrgChart::reverse_order_iterator::reverse_order_iterator(Node* n) {
        if(n) {
            queue<Node*> que;
            que.push(n);
            while(!que.empty()) {
                Node *curr_son = que.front()->eldest_son;
                if(curr_son) {
                    while(curr_son->right_brother != nullptr) {
                        curr_son = curr_son->right_brother;
                    }
                    while(curr_son != nullptr) {
                        que.push(curr_son);
                        curr_son = curr_son->left_brother;
                    }
                }
                this->stk.push(que.front());
                que.pop();
            }
            this->curr = this->stk.top();
            this->stk.pop();
        }
        else {
            this->curr = nullptr;
        }
    }

    bool OrgChart::reverse_order_iterator::operator==(const reverse_order_iterator &it) const {
        return this->curr == it.curr;
    }

    bool OrgChart::reverse_order_iterator::operator!=(const reverse_order_iterator &it) const {
        return !(*this == it);
    }

    string& OrgChart::reverse_order_iterator::operator*() const {
        return this->curr->position;
    }

    OrgChart::reverse_order_iterator& OrgChart::reverse_order_iterator::operator++() {
        if(stk.empty()) {
            this->curr = nullptr;
        }
        else {
            this->curr = this->stk.top();
            this->stk.pop();
        }
        return *this;
    }

    const OrgChart::reverse_order_iterator OrgChart::reverse_order_iterator::operator++(int postfix_flag) {
        OrgChart::reverse_order_iterator temp = *this;
        if(stk.empty()) {
            this->curr = nullptr;
        }
        else {
            this->curr = this->stk.top();
            this->stk.pop();
        }
        return temp;
    }

    string* OrgChart::reverse_order_iterator::operator->() {
        return &this->curr->position;
    }


    // preorder_iterator:

    OrgChart::preorder_iterator::preorder_iterator(Node* n) {
        this->curr = n;
    }

    bool OrgChart::preorder_iterator::operator==(const preorder_iterator &it) const {
        return this->curr == it.curr;
    }

    bool OrgChart::preorder_iterator::operator!=(const preorder_iterator &it) const {
        return !(*this == it);
    }

    string& OrgChart::preorder_iterator::operator*() const {
        return this->curr->position;
    }

    OrgChart::preorder_iterator& OrgChart::preorder_iterator::operator++() {
        if(this->curr->eldest_son) {
            this->curr = this->curr->eldest_son;
        }
        else if(this->curr->right_brother) {
            this->curr = this->curr->right_brother;
        }
        else {
            this->curr = this->curr->dad;
            while(this->curr != nullptr) {
                if(this->curr->right_brother) {
                    this->curr = this->curr->right_brother;
                    return *this;
                }
                this->curr = this->curr->dad;
            }
        }
        return *this;
    }

    const OrgChart::preorder_iterator OrgChart::preorder_iterator::operator++(int postfix_flag) {
        OrgChart::preorder_iterator temp = *this;
        if(this->curr->eldest_son) {
            this->curr = this->curr->eldest_son;
        }
        else if(this->curr->right_brother) {
            this->curr = this->curr->right_brother;
        }
        else {
            this->curr = this->curr->dad;
            while(this->curr != nullptr) {
                if(this->curr->right_brother) {
                    this->curr = this->curr->right_brother;
                    return temp;
                }
            }
        }
        return temp;
    }

    string* OrgChart::preorder_iterator::operator->() {
        return &this->curr->position;
    }


    // OrgChart function:

    OrgChart::level_order_iterator OrgChart::begin() {
        return begin_level_order();
    }

    OrgChart::level_order_iterator OrgChart::end() {
        return end_level_order();
    }

    OrgChart::level_order_iterator OrgChart::begin_level_order() {
        if(this->head) {
            return OrgChart::level_order_iterator(this->head);
        }
        throw invalid_argument("orgchart is empty!");
    }

    OrgChart::level_order_iterator OrgChart::end_level_order() {
        if(this->head) {
            return OrgChart::level_order_iterator();
        }
        throw invalid_argument("orgchart is empty!");
    }

    OrgChart::reverse_order_iterator OrgChart::begin_reverse_order() {
        if(this->head) {
            return OrgChart::reverse_order_iterator(this->head);
        }
        throw invalid_argument("orgchart is empty!");
    }

    OrgChart::reverse_order_iterator OrgChart::reverse_order() {
        if(this->head) {
            return OrgChart::reverse_order_iterator();
        }
        throw invalid_argument("orgchart is empty!");
    }

    OrgChart::preorder_iterator OrgChart::begin_preorder() {
        if(this->head) {
            return OrgChart::preorder_iterator(this->head);
        }
        throw invalid_argument("orgchart is empty!");
    }

    OrgChart::preorder_iterator OrgChart::end_preorder() {
        if(this->head) {
            return OrgChart::preorder_iterator();
        }
        throw invalid_argument("orgchart is empty!");
    }

    ostream& operator<<(ostream& os, const OrgChart &orgch) {
        os << "<----------OrgChart---------->" << endl << endl;;
        OrgChart::print_tree(os, orgch.head, 0);
        os << endl << "<----------OrgChart---------->" << endl;
        return os;
    }

    void OrgChart::print_tree(ostream& os, Node *head, int indent) {
        for(int i = 0; i < indent; i++) {
            os << "    ";
        }
        os << "└──";
        os << head->position << endl;
        Node *curr_son = head->eldest_son;
        while(curr_son != nullptr) {
            OrgChart::print_tree(os, curr_son, indent + 1);
            curr_son = curr_son->right_brother;
        }
    }

    bool OrgChart::operator==(const OrgChart &w) const {
        return this == &w;
    }

    bool OrgChart::operator!=(const OrgChart &w) const {
        return !(*this == w);
    }

    string OrgChart::operator*() {
        return (this->head->position);
    }
}