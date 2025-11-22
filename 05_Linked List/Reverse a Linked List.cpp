//  Reverse a linked list a. iterative b. recursive
//  Running time: O(n) for each method
//  Auxiliary space: O(1) for iterative but O(n) for recursive because of the recursion stack

#include<iostream>
using namespace std;

struct node{
    int val;
    node *next;
    node(int v) : val(v), next(nullptr) {}
};

void reverseIter(node* &head) { // passing head by reference i.e &head used here, since its a void function that returns nothing
    if(head==nullptr || head->next==nullptr) return;
    node *curr = head, *currNext = nullptr, *resultHead = nullptr;
    while(curr!=nullptr) {
        currNext = curr->next;
        curr->next = resultHead;
        resultHead = curr;
        curr = currNext;
    }
    head = resultHead;
}

void reverseIter2(node* &head) { // Since its a void function we need to pass head by reference
    if(head == NULL || head->next == NULL) return;
    node* curr = head;
    node* currNext = curr->next;
    node* currNextNext = NULL;
    while(currNext != NULL) {
        currNextNext = currNext->next;
        currNext->next = curr;
        curr = currNext;
        currNext = currNextNext;
    }
    head->next = NULL;
    head = curr;
}

node *reverseRec(node *head) {
    if(head==nullptr || head->next==nullptr) return head;
    node *second = reverseRec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return second;
}

void print(node *head) {
    node* curr = head;
    while(curr!=nullptr) {
        cout<<curr->val<<" ";
        curr = curr->next;
    }
    cout<<"\n";
}

int main() {
    node* head = new node(1);
    head->next = new node(2);
    head->next->next = new node(3);
    head->next->next->next = new node(4);
    head->next->next->next->next = new node(5);
    print(head);
    reverseIter(head);
    print(head);
    cout<<"##########"<<endl;
    print(head);
    reverseIter2(head);
    print(head);
    cout<<"##########"<<endl;
    print(head);
    head = reverseRec(head);
    print(head);
    return 0;
}
