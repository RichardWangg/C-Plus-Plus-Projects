#include <iostream>

class Node {
 public:
 Node *get_next() const;
 void set_next(Node *next_node);
 private:
 Node *p_next_node_;
};
class Linked_list {
public:
void interleave( Linked_list &param_list );
 private:
 Node *p_list_head_;
};

void Linked_list::interleave( Linked_list &param_list ) {
    while (p_list_head_ != nullptr) {
        param_list.p_list_head_;
    }

}



int main() {




}