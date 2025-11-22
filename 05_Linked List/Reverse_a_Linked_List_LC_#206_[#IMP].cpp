/**
LC#206. Reverse Linked List
Given the head of a singly linked list, reverse the list, and return the reversed list.

E.g. 1:
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

E.g. 2: // Covered by the base case #2 if(head->next == NULL) return head;
Input: head = [1] 
Output: [1]

E.g. 3: // Covered by the base case #1 if(head== NULL) return head;
Input: head = NULL
Output: NULL

Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?
**/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
        ListNode* reverseWithRecursion(ListNode* head) {
            if(head == NULL || head->next == NULL) return head;
            ListNode* recCall = reverseWithRecursion(head->next);
            head->next->next = head;
            head->next = NULL;
            return recCall;
        }
    
        void reverseWithIteration(ListNode* &head) { // Since its a void function we need to pass head by reference
            if(head == NULL || head->next == NULL) return;
            ListNode* curr = head;
            ListNode* currNext = curr->next;
            ListNode* currNextNext = NULL;
            while(currNext != NULL) {
                currNextNext = currNext->next;
                currNext->next = curr;
                curr = currNext;
                currNext = currNextNext;
            }
            head->next = NULL;
            head = curr;
        }

        void reverseWithIteration2(ListNode* &head) { // Since its a void function we need to pass head by reference
            if(head == NULL || head->next == NULL) return;
            node *curr = head, *currNext = nullptr, *resultHead = nullptr;
            while(curr!=nullptr) {
                currNext = curr->next;
                curr->next = resultHead;
                resultHead = curr;
                curr = currNext;
            }
            head = resultHead;
        }
        
    
        ListNode* reverseList(ListNode* head) {
            // return reverseWithRecursion(head);
            // reverseWithIteration(head);
            reverseWithIteration2(head);
            return head;
        }
    };