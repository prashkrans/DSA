#include<iostream>
using namespace std;

struct node{
    int data;
    node* next;
};
//  You are not able to trace back the previous node in a singly linked list. So you have to store not only the current node
//  but also the previous node. This is different in a doubly linked list which we will cover in the later chapter.

struct listNode {									//	Modern way of defining a structure for a linked list node using modern constructors
	int val;
	listNode *next;
	listNode() : val(0), next(NULL) {}				//	Modern way of using constructors
	listNode(int val_) : val(val_), next(NULL) {}
};

// 1a. Iterate Down a List (While loop)
int length(node* head){
    int count = 0;
    //if (head==NULL) return count;
    node* curr = head;
    while(curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

// 1b. Iterate Down a List (For loop)
int lengthForLoop(node* head){
    int count = 0;
    node* curr;
    for(curr = head; curr!=NULL; curr = curr->next) count++;
    return count;
}

// 2a. Returnable Push at head (stack)
node* pushAtHead(node* head, int data){
    node* newNode = new node; // Can also use struct node* newNode = malloc(sizeof(struct node)); instead of new but avoid it
    newNode->data = data;
    newNode->next = head;
    head = newNode;
    return head;
}

// 2b. Void Push at head (stack) - IMPORTANT// It works for any node pointer Eg. voidPushAtHead(anyPtr, data) or voidpushAtHead(curr->next, data)
void voidPushAtHead(node*& head, int data){ // Note in the void function we pass head as node*& head instead of node* head to make changes in the original head
    node* newNode = new node;               // Use node*&  head only when
    newNode->data = data;                   // a. the function is void type, and
    newNode->next = head;                   // b. head is being modified
    head = newNode;
}


// 3a. Returnable Push at end (queue)
node* pushAtEnd(node* head, int data){        // Need to look for two cases a. If the llist is empty or b. The llist is not empty
    node* newNode = new node;
    newNode->data = data;
    newNode->next = NULL;
    node* curr = head;
    if(curr==NULL){                           // Here the base case is not covered in the loop itself therefore needs to be explicitly mentioned
        head = newNode;                       // i.e. if the llist is empty the first element will be the head
        return head;                          // No need to go any further
    }
    while(curr->next!=NULL)                   // Note the end condition is curr->next!=0 and not curr->!=0
        curr=curr->next;                      // i.e. we have to stop at the last element of the linked list
    curr->next = newNode;
    return head;                              // Note - we need to return head and not the curr
}

// 3b. Void Push at end (queue)               // Need to look for two cases a. If the llist is empty or b. The llist is not empty
void voidPushAtEnd(node*& head, int data){    // Note the function is void type and changes head too thus the need of node*& head
    node* newNode = new node;
    newNode->data = data;
    newNode->next = 0;
    node* curr = head;
    if(curr==0){                              // Here the base case is not covered in the loop itself therefore needs to be explicitly mentioned
        head = newNode;                       // i.e. if the list in empty the first element will be the head
        return;                               // No need to go any further
    }
    while(curr->next!=0){                     // Note the end condition is curr->next!=0 and not curr->!=0
        curr = curr->next;                    // i.e. we have to stop at the last element of the linked list
    }
    curr->next = newNode;
}



// 4a. Iterative - Print all the elements of the linked list from head to end
void print(node* head){
    if(head == NULL) cout<<"The given linked list is empty \n";
    else{
        // cout<<"Printing elements of the linked list iteratively from head to end"<<"\n";
        node* curr = head;
        while(curr!=0) { // or while(curr!=NULL)
            cout<<curr->data<<" ";
            curr = curr->next;
        }
        cout<<"\n";
    }
}

// 4b. Recursive - Print all the elements of the linked list from head to end
void printRecursive(node* head){
    if(head == NULL) return;
    cout<<head->data<<" ";              // Notice the order of cout<<head->data<<" "; i.e. before recursive call
    printRecursive(head->next);
}

// 5a. Recursive - Print all the elements of the linked list from end to head (#IMP)
void printRecEndToHead(node* head){
    if(head == NULL) return;
    printRecEndToHead(head->next);
    cout<<head->data<<" ";             // Notice the order of cout<<head->data<<" "; i.e. after recursive call
}

// 5b. Iterative - Print all the elements of the linked list from end to head
void printEndToHead(node* head){
    int size = length(head);
    int array[size];
    int i = size-1;
    node* curr = head;
    while(curr!=NULL){
        array[i--] = curr->data;        // Notice the use of an array
        curr=curr->next;
    }
    for(int i=0;i<size;i++) cout<<array[i]<<" ";
}

// 6. Write a count() function that counts the number of times a given int occurs in a list.
int count(node* head, int item){
    int countItem=0;
    node* curr = head;
    while(curr!=NULL){                  // Can use a for loop for a shorter code
        if (curr->data == item) countItem++;
        curr=curr->next;
    }
    return countItem;
}

// 7. Write a getNth() function that takes a linked list and an integer index (O to size -1) and
//   returns the value stored in the node at that index position
int getNth(node* head, int index){
    node* curr = head;
    int len = length(head);
    if (index<0||index>=len) return -1;  // -1 represents that the index was out of bounds
    for(int i=0; i<index; i++) curr=curr->next;
    return curr->data;
}

// 8. Write a function deleteList() that takes a list, deallocates all of its memory and sets its
//   head pointer to NULL (the empty list). (Write the function as a void type)
void deleteList(node*& head){           // new and delete are operators in C++
    if (head == NULL) return;           // while malloc(sizeof()) and free(pointerName) are functions in C & C++
    node* curr = head;
    node* currNext = NULL;
    while(curr!=NULL){
        currNext=curr->next;
        delete curr;                    // This is generally used along with new operators
        //free(curr);                   // This is generally used along with malloc() function
        curr = currNext;
    }
    head = NULL;
    cout<<"The length of the linked list after deletion is = "<<length(head)<<" as expected\n";
}

// 9. Write a popAtHead() function that is the inverse of Push(). Pop() takes a non-empty list, deletes
//   the head node, and returns the head node's data. If all you ever used were Push() & Pop() (both at head),
//   then our linked list would really look like a stack. (Write the function as a void type)
void popAtHead(node*& head){
    node* curr = head;
    if(head==NULL) {
        cout<<"The given linked list is already empty \n";
        return;
    }
    cout<<"The element at head being popped is = "<<head->data<<"\n";
    head = head->next;
    delete curr;                                    // or free(curr) would also work
    cout<<"The current length of the linked list after popAtHead is = "<<length(head)<<"\n";
}

// 10. Write a function insertNth() which can insert a new node at any index within a list.
//     Any given index in the range [0..length], and the new node to be inserted at that index.
//     (Write the function as a void type)
// 10a. Without the use of the function pushAtHead() - IMPORTANT
void insertNth(node*& head, int index, int data){
    int len = length(head);
    if(index<0||index>len){            // If head==NULL => len = 0 => only works when index = 0
        cout<<"Index out of bounds \n";
        return;
    }
    node* newNode = new node;
    newNode->data = data;
    if(index>0&&index<=len){            // All valid indices except 0
        node* curr = head;
        node* prev = head;
        for(int i=0; i<index; i++){
            prev = curr;
            curr = curr->next;
        }
        prev->next = newNode;
        newNode->next = curr;
    }
    if(index==0){                      // For index = 0 i.e. similar to pushAtHead()
        newNode->next = head;          // index = 0 is a special case
        head = newNode;                // Covers head==NULL case too
    }
}

// 10b. With the help of the function pushAtHead() - IMPORTANT
void insertNthWithPush(node*& head, int index, int data){
    int len = length(head);
    if(index<0||index>len){
        cout<<"Index out of bounds \n";
        return;
    }
    if(index>0&&index<=len){            // All valid indices except 0
        node* curr = head;              // Note - curr traverses till index-1 and i till index-2
        for(int i=0; i<index-1; i++){   //
            curr = curr->next;
        }
        // curr->next = pushAtHead(curr->next, data);
        // pushAtHead(anyPtr, data) => Decln newN; newN->data=data; newN->next=anyPtr; anyPtr=newNode;
        // Tricky use of pushAtHead and it works for any node pointer
        voidPushAtHead(curr->next, data); // Notice that curr is not used instead curr->next is used as it is a part of a node of the list
    }
    if(index==0) {
        //head = pushAtHead(head, data); // index = 0 is a special case
        voidPushAtHead(head, data);
    }
}

// 11. Write a sortedInsert() function which given a list that is sorted in increasing order, and a
//     single node, inserts the node into the correct sorted position in the list. While Push()
//     allocates a new node to add to the list, SortedInsert() takes an existing node, and just
//     rearranges pointers to insert it into the list. (Write the function as a void type)
/*void sortedInsert(node*& head, node* singleNode){// My code
    if(head==NULL||head->data>=singleNode->data){// When the list is empty or sN->data is the smallest i.e. at index = 0
        singleNode->next = head;
        head = singleNode;
        return;
    }
    node* curr = head;
    while(curr->next!=NULL){                    // When sN->data fits in the middle i.e. index 1 to size-1
        if(curr->next->data>=singleNode->data){ // Locates the node whose next node->data is greater than sN->data
            singleNode->next = curr->next;      // i.e. locate the node before the point of insertion
            curr->next = singleNode;
            break;
        }
        curr=curr->next;
    }
    if(curr->next==NULL){                       // When sN->data is the largest i.e. index = size
        curr->next = singleNode;
        singleNode->next = NULL;
    }
}*/

// 11b. Shorter version of the same code as above.
void sortedInsert(node*& head, node* newNode){ // Lecture Code
    if(head==NULL||head->data>=newNode->data){
        newNode->next = head;
        head = newNode;
    }
    else {
        node* current = head;
        while(current->next!=NULL && current->next->data < newNode->data){ // Takes care of both insertion at the end and the middle
            current = current->next;            // Locates the node before the point of insertion
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 12. Write an insertSort() function which given a list, rearranges its nodes so they are sorted in
//     increasing order. It should use sortedInsert().(Write the function as a void type) #IMPORTANT - Learn it
void insertSort(node*& head){
    node* resultHead = NULL;            // Temporary empty linked list created to build the answer
    node* curr = head;                  // Iterates over the original llist
    node* currNext;                     // Note the use of currNext which stores the next node of the original llist
    while(curr!=NULL){
        currNext = curr->next;          // # IMP - Notes the next node before curr gets changed in the sortedInsert() function
        sortedInsert(resultHead, curr); // Calling the sortedInsert function
        curr = currNext;                // Shifting to the next node
    }
    head = resultHead;                  // Finally copy back the sorted llist in the original llist
}                                       // No need of the base case i.e. head==NULL will give the ans head=NULL

// 14. Write an append() function that takes two lists, 'a' and 'b', appends 'b' onto the end of 'a',
//     and then sets 'b' to NULL (since it is now trailing off the end of 'a'). (Write the function as a void type)
void append(node*& aHead, node*& bHead){
    if(aHead==NULL) aHead=bHead;                    // Special case if llist a is empty
    else{
        node* aCurr = aHead;
        while(aCurr->next!=NULL) aCurr=aCurr->next; // Finding the last node of llist a
        aCurr->next = bHead;                        // Appends b after the last node of llist a
    }
    bHead = NULL;                                   // Empties the llist b
}

// 15. Write a funtion frontBackSplit() that splits the nodes of the given list into front and back halves, and return
//     the two lists using the reference parameters. If the length is odd, the extra node should go in the front list.
//     So frontBackSplit() on the list {2, 3, 5, 7, 11} should yield the two lists {2, 3, 5} and {7,11}
//     Another method -  uses two pointers to traverse the list. A "slow" pointer advances one node at a time, while
//     the "fast" pointer goes two nodes at a time. When the fast pointer reaches the end, the slow pointer will be about
//     half way. (Write the function as a void type)

// 15a. My Code (inefficient) - using pushAtEnd() function.
//      Actually there is no need to use pushAtEnd() function at all. We just need to cut the source llist at the right posn
void frontBackSplit(node*& head, node*& head1, node*& head2){
    int len = length(head);
    int len1, len2;
    if (len%2==0) {
        len1=len/2;
        len2=len1;
    }
    else {
        len1=len/2+1;
        len2=len-len1;
    }
    node* curr = head;
    head1 = NULL;
    for(int i=1; i<=len1; i++){
        voidPushAtEnd(head1, curr->data);
        curr = curr->next;
    }
    head2 = NULL;
    for(int i=1; i<=len2; i++){
        voidPushAtEnd(head2, curr->data);
        curr = curr->next;
    }
}

// 15b. Better code - without using pushAtEnd() function.
void frontBackSplitBetter(node*& head, node*& head1, node*& head2){
    int len = length(head);
    int mid = (len-1)/2;    // Eg. Odd - len = 5 then mid is 2 and Even - len = 6 then mid is 2 (same for both odd & even)
    if(len<2){              // i.e if head==NULL (len == 0) or head->next==NULL (len == 1) => head2 = NULL and head1 = head
        head1 = head;
        head2 = NULL;
    }
    else {
        node* curr = head;                          // i iterates from 0 to mid-1
        for(int i=0; i<mid; i++) curr=curr->next;   // while curr iterates from 0 to mid
        head1 = head;
        head2 = curr->next;                         // as second list starts from mid->next
        curr->next = NULL;                          // # IMP - cutting the first half at current
    }
}

// [# IMPORTANT]
// 15c. Uses the fast/slow pointer strategy. In this strategy there is no need to calculate the length of the llist.
//      i.e. without using the length() function 
void frontBackSplitFastSlowptr(node*& head, node*& head1, node*& head2){
    if(head==NULL || head->next==NULL){             // Takes care of cases with length < 2 without using the length func
        head1 = head;
        head2 = NULL;
    }
    else {
        node* slow = head;                          // slow begins at i = 0
        node* fast = head->next;                    // fast begins at i = 1
        while(fast!=NULL){
            fast = fast->next;                      // this index of fast is always even
            if(fast!=NULL){
                slow = slow->next;                  // for each 2 advances of fast slow advances once. (Eventually fast becomes null and slow = (len-1)/2
                fast = fast->next;                  // this index of fast is always odd & if fast -> x times slow -> x/2 times
            }                                       // i.e. if len or n = 6 then (n-1)/2 = 2 & if n = 5 then (n-1)/2 = 2
        }                                           // now 'slow' is before the midpoint in the list (i.e. before 2.5 or 3 is 2)
        head1 = head;                               // first list starts from the head of the source llist
        head2 = slow->next;                         // as second list starts from slow->next
        slow->next = NULL;                          // # IMP - cutting the first half at slow
    }
}

// 16.  Write a removeDuplicates() function which takes a list sorted in increasing order and deletes any duplicate nodes
//      from the list. Ideally, the list should only be traversed once. (Write the function as a void type) i.e. O(n)
void removeDuplicates(node*& head){ // The linked list should already be sorted or use an insertSort() function
    insertSort(head);
    if (head==NULL||head->next==NULL) return;       // since there are no duplicates
    node* curr = head;
    while(curr->next!=NULL){
        if (curr->data == curr->next->data) {
            node* temp = curr->next;
            curr->next = curr->next->next;          // or curr->next = temp->next;
            delete temp;
        }
        else curr = curr->next;                     // move to the next node only if consecutive duplicates not found
    }
}

// 17.  Write a function moveNode() which is a variant on Push(). Instead of creating a new node and pushing it onto the given
//      list, moveNode() takes two lists, removes the front node from the second list and pushes it onto the front of the first.
//      (Write the function as a void type)
// 17a. Using the pushAtHead() function - (My Code)
void moveNodeWithPush(node*& head1, node*& head2){
    if(head2==NULL) return;
    else{
        voidPushAtHead(head1, head2->data);
        head2 = head2->next;
    }
}

// 17b. Without using pushAtHead() function.
void moveNode(node*& destHead, node*& sourceHead){  // Please make sure to use *& and not just * as this problem
    if(sourceHead == NULL) return;                  // just wasted half an hour of life just because I did not use *&, lol.
    else {
        node* newNode = sourceHead;         // the head of the source llist is copied in a newNode
        sourceHead = sourceHead->next;      // the head of the source llist is shifted by one posn
        newNode->next = destHead;           // newNode is appended with head of the destination llist
        destHead = newNode;                 // the head of the destination llist now points at the newNode
    }
}

// 18.  Write a function alternatingSplit() that given a source list, splits its nodes into two shorter lists.
//      If we number the elements 0, 1, 2, ... then all the even elements should go in the first list, and
//      all the odd elements in the second. The elements in the new lists may be in any order.
//      (Write the function as a void type)

// 18a. Using pushAtEnd() function. (My Code)
void alternatingSplit(node* head, node*& evenHead, node*& oddHead){
    evenHead = NULL;
    oddHead = NULL;
    if (head==NULL) return;                                     // Does nothing when the source list itself is empty
    else{
        node* curr = head;
        int index = 0;
        while(curr!=NULL){
            if(index%2==0) voidPushAtEnd(evenHead, curr->data); // pushAtEnd() gives the same order to sublists as the source list
            else voidPushAtEnd(oddHead, curr->data);
            index++;
            curr = curr->next;
        }
    }
}
// 18b. Using moveNode() function.
void alternatingSplitWithMoveNode(node* sourceHead, node*& eHead, node*& oHead){
    eHead = NULL;
    oHead = NULL;
    if (sourceHead==NULL) return;                               // Does nothing when the source list itself is empty
    else {
        node* curr = sourceHead;
        // method b -  node* currNext = NULL;
        int index = 0;
        while(curr!=NULL){
            // method b -  currNext = curr->next;
            if(index%2==0) moveNode(eHead, curr);               // moveNode() gives the opposite order to sublists as compared to the source list
            else moveNode(oHead, curr);                         // also moveNode() automatically advances curr to its next node
            index++;                                            // so, there is no need to have a currNext pointer
            //method b -  curr = currNext;
        }
    }
}

// 19.  Given two lists, merge their nodes together to make one list, taking nodes alternately between the two lists.
//      So shuffleMerge() with {1, 2, 3} and {7, 13, 1} should yield {1, 7, 2, 13, 3, 1}. If either list runs out,
//      all the nodes should be taken from the other list. You may want to use MoveNode() as a helper. Overall, many
//      techniques are possible: dummy node, local reference, or recursion. Using this function and FrontBackSplit(),
//      you could simulate the shuffling of cards.
// 19a. shuffleMerge() using recursion - (My Code)
node* shuffleMerge(node* head1, node* head2){               // recursive shuffleMerge() having 3 base cases
if(head1==NULL&&head2==NULL) return NULL;                   // 1. both the lists are empty
if(head1!=NULL&&head2==NULL) return head1;                  // 2. list 1 is empty while list 2 is not
if(head1==NULL&&head2!=NULL) return head2;                  // 3. list 2 is empty while list 1 is not
node* newNode1 = new node;                                  // creates two nodes newNode1 and newNode2
node* newNode2 = new node;
newNode1->data = head1->data;                               // [newNode1] -> [newNode2] -> recursively returned list
newNode1->next = newNode2;
newNode2->data = head2->data;
newNode2->next = shuffleMerge(head1->next, head2->next);    // # IMP - note the recusion call inside newNode->next
return newNode1;                                            // returns the head of the current list in recursion
}
// 19b. shuffleMerge() using recursion (more efficient as does not need temporary storage) - (Lecture Code)
node* shuffleMergeBetter(node* a, node* b){
node* result;
node* recCall;
if(a==NULL) return b;                                       // the two cases already consider the case when both a & b are empty lists
else if(b==NULL) return a;
else{                                                       //it turns out to be convenient to do the recursive call first --
    recCall = shuffleMerge(a->next, b->next);               // otherwise a->next and b->next need temporary storage.
    result = a;                                             // one node from a. Don't confuse that all the nodes of a goes in result
    result->next = b;                                       // as result->next = b i.e. second node from b
    b->next = recCall;                                      // then the rest of the nodes from recursion
    return result;
}
}

// 20.  Write a sortedMerge() function that takes two lists, each of which is sorted in increasing order, and merges the two
//      together into one list which is in increasing order and return the new list. The new list should be made by splicing
//      together the nodes of the first two lists (May use moveNode()). Ideally, sortedMerge() should only make one pass
//      through each list.
// 20a. Iteratively without using any function - (My Code)
node* sortedMergeIter(node* aHead, node* bHead){ // moveNode() acts as pushAtHead so, the order gets reversed (ascg becomes descg)
    if (aHead==NULL) return bHead;
    else if (bHead==NULL) return aHead;
    node* aCurr = aHead;
    node* bCurr = bHead;
    node* resultHead = NULL;                    // Points the first node of the result list
    node* resultCurr = NULL;                    // Points to the last node of the result list
    while(aCurr!=NULL&&bCurr!=NULL){
        node* newNode = new node;
        newNode->next = NULL;
        if(aCurr->data<=bCurr->data){
            newNode->data = aCurr->data;
            aCurr = aCurr->next;                // Advances the list from which an element is taken - here A
        }
        else if(aCurr->data>bCurr->data){
            newNode->data = bCurr->data;
            bCurr = bCurr->next;                // Advances the list from which an element is taken - here B
        }
        if(resultHead==NULL) {                  // Builds the result list
                resultHead = newNode;           // Base Case of appending if list is empty
                resultCurr = resultHead;        // This is basically pushAtEnd()
            }
            else {
                resultCurr->next = newNode;     // Appends if the list is not empty
                resultCurr = resultCurr->next;  // Advances to the last node
            }
    }
    if(aCurr==NULL) resultCurr->next = bCurr;
    else if (bCurr==NULL) resultCurr->next = aCurr;
    return resultHead;
}

// 20b. Recursively without using any function - (My Code)
//      It is shorter than the iterative. Probably wouldn't want to use the recursive version for production code
//      however, because it will use stack space which is proportional to the length of the lists.
node* sortedMergeRec(node* a, node* b){
    if(a==NULL) return b;                               // Base Cases
    else if(b==NULL) return a;
    node* newNode = new node;                           // or node* resultHead = NULL;
    if(a->data<=b->data){
        newNode->data = a->data;                        // or resultHead = a;
        newNode->next = sortedMergeRec(a->next, b);     // or resultHead->next = sortedMergeRec(a->next, b);
    }
    else if (a->data>b->data){
        newNode->data = b->data;                        // or resultHead = a;
        newNode->next = sortedMergeRec(a, b->next);     // or resultHead->next = sortedMergeRec(a->next, b);
    }
    return newNode;
}

// 21.  mergeSort() - (This problem requires recursion) Given FrontBackSplit() and sortedMerge(), it's pretty easy to write a
//      classic recursive MergeSort(): split the list into two smaller lists, recursively sort those lists, and finally merge
//      the two sorted lists together into a single sorted list.
//      Ironically, this problem is easier than either frontBackSplit() or sortedMerge().
node* mergeSort(node* head){                        // mergeSort() as well as quickSort() are implemented recursively
    if(head==NULL||head->next==NULL) return head;   // Steps -  1. Base cases 2. Recursive call on each halves
    node* firstHead = NULL;                         //          3. Small calcn => merge the sorted halves
    node* secondHead = NULL;
    frontBackSplit(head, firstHead, secondHead);    // splits the given list into two sublists - all 3 pointers passed by reference
    firstHead = mergeSort(firstHead);               // recursive call on the first half
    secondHead = mergeSort(secondHead);             // recursive call on the second half
    head = sortedMergeIter(firstHead, secondHead);  // merges the sorted sublists in ascending order
    return head;
}

// 22.  Write a function sortedIntersect() that given two lists sorted in increasing order, creates and returns a new list
//      representing the intersection of the two lists. The new list should be made with its own memory � the original lists
//      should not be changed. In other words, this should be Push() list building, not MoveNode(). (leetcode)
//      # Ideally, each list should only be traversed once.
//      This problem along with Union() and Difference() form a family of clever algorithms that exploit the constraint that
//      the lists are sorted to find common nodes efficiently.
//      The strategy is to advance up both lists and build the result list as we go. When the current point in both lists are
//      the same, add a node to the result. Otherwise, advance the list which has the lesser value of currData
node* sortedIntersect(node* aHead, node* bHead){
    if(aHead==NULL||bHead==NULL) return NULL;       // Base Case i.e. if either of the list is empty return NULL
    int len1 = length(aHead);
    int len2 = length(bHead);
    node* larger = NULL;
    node* smaller = NULL;
    if(len1>=len2) {                                // finding smaller and larger can be taken care before
        larger = aHead;                             // calling the function thus making the function concise
        smaller = bHead;
    }
    else {
        larger = bHead;
        smaller = aHead;
    }
    node* resultHead = NULL;
    node* resultCurr = NULL;
    while(larger!=NULL&&smaller!=NULL){             // 3 check conditions within the loops
        if(smaller->data == larger->data){          // 1. if both elements are same copy in result and advance both
            node* newNode = new node;               // 2. if elem of the smaller list is smaller than the elem of the larger list, advance the
            newNode->data = smaller->data;          // 3. if elem of the larger list is smaller than the elem of the smaller list, advance the smaller list
            newNode->next = NULL;                   // these three conditions + both already sorted allow to traverse both the lists only once larger list
            if(resultHead==NULL) {
                resultHead = newNode;
                resultCurr = resultHead;
            }
            else {
                resultCurr->next = newNode;
                resultCurr = resultCurr->next;
            }
            smaller = smaller->next;
            larger = larger->next;
        }
        else if(smaller->data<larger->data) smaller = smaller->next;    // #IMP condition
        else larger = larger->next;
    }
    return resultHead;
}

// 23.  Write an iterative reverse() function that reverses a list by rearranging all the .next pointers and the head pointer.
//      Ideally, Reverse() should only need to make one pass of the list. The iterative solution is moderately complex.
//      (Write the function as a void type) (#IMP - Remember only the solutions 23b and 24b)

// 23a. Iterative without using any function i.e. using three pointers. This method does not create any new nodes.
//      Instead of running a single "current" pointer down the list, run three pointers (front, middle, back) down the list
//      in order: front is on one node, middle is just behind it, and back in turn is one behind middle. Add code to reverse
//      the .next pointer of the middle node during the iteration. Add code to take care of the empty list and to adjust the head pointer itself.
void reverseIterWith3Ptrs(node*& head){
    if(head==NULL||head->next==NULL) return;
    node* currNext = head->next;    // The initialisation is important for all the three pointers
    node* curr = head;              // prev = NULL; curr = head; currNext = head->next;
    node* prev = NULL;
    while(curr!=NULL){              // Loop stops when the last node is made the first node
        curr->next = prev;          // Builds the reversed list
        prev = curr;                                    // The next three lines advances the three pointers
        curr = currNext;
        if(currNext!=NULL) currNext = currNext->next;   // If currNext is already NULL currNext->next is not valid hence the if condition
    }
    head = prev;                    // The first node of the reversed list is stored at prev which is now made as the head
}

// [#IMPORTANT] I have added another iterative method refer LC#206
// 23b. # IMP - Iterative reverse() without  using moveNode() function. This does not involve creating new nodes but a temp pointer is used
//      to modify the given list itself. # IMP - Learn this for iterative reverse()
void reverseIterative(node*& head){						// Note the use of *& here as we are modifying the head itself
    if(head==NULL||head->next==NULL) return;
    node* resultHead = NULL;                            // Here the resultHead itself keeps moving in the original list itself
    node* curr = head;                                  // hence, the original list itself is reveresed
    node* currNext = NULL;
    while(curr!=NULL){
        currNext = curr->next;
        curr->next = resultHead;                        // This works for base case too i.e. when resultHead = NULL;
        resultHead = curr;                              // Similar to what moveHead() does
        curr = currNext;
    }
    head = resultHead;
}

// 23c. Iterative using moveNode() function. moveNode() involves creating new nodes not just pointer rearrangement.
void reverseIterWithMoveNode(node*& head){
    if(head==NULL||head->next==NULL) return;
    node* resultHead = NULL;
    node* curr = head;
    while(curr!=NULL) moveNode(resultHead, curr);         // Automatically advances curr;
    deleteList(head->next);                               // OPTIONAL deleteList(head->next) deletes all the elements after head except head
    head = resultHead;
}

// 24.  Write an recursive reverse() function that reverses a list. There is a short and efficient recursive solution to this problem.
//      As before, the code should only make a single pass over the list. Doing it with multiple passes is easier but very slow (24a.)
// 24a. Recursive without using any function() - (My Code)
//      But this code is inefficent as O(n^2)
//      This inefficient solution is reverses the last n-1 elements of the list, and then iterates all the way down to the new tail
//      and put the old head node there. That solution is very slow compared to the 24b. which gets the head node in the right place
//      without extra iteration.
node* reverseRecursiveSlower(node* head){                   //  Don't learn this
    if(head==NULL||head->next==NULL) return head;
    node* recCall = reverseRecursiveSlower(head->next);     // Recursive call on the second node of the current list
    node* curr = recCall;
    while(curr->next!=NULL) curr = curr->next;      // Advances curr to the last node => while loop is not required in second method
    curr->next = head;                              // Appends head node to the last node
    curr->next->next = NULL;                        // Makes the last node point to NULL
    return recCall;                                 // Returns the head i.e. recCall of the reversed list
}

// [#IMPORTANT]
// 24b. Recursive without any function() - (Modified My Code - to make O(n)) - Learn this method ### IMPORTANT
//      Probably the hardest part is accepting the concept that the reverseRecursive(head->next) does in fact reverses the rest.
node* reverseRecursive(node* head){
    if(head==NULL||head->next==NULL) return head;   // Base Case makes recCall the head of the reversed list
    node* recCall = reverseRecursive(head->next);   // Recursion after the first node. After recn we have rvrsd all excpt the first and stored in recCall
    head->next->next = head;                        // head->next->next = head; head->next = NULL as it now the last node
    head->next = NULL;
    return recCall;                                 // Returns the first node i.e. recCall of the reversed list
}

// 24c. Exactly same as 24b. but is a void type function and uses first and second pointers.
void reverseRec(node*& head){
    if(head==NULL||head->next==NULL) return;        // Base cases - head remains unchanged if len = 0 or 1
    node* first = head;                             // Points to the first node in the current list - eg. {1, 2, 3}
    node* second = first->next;                     // Points to the second node in the current list - eg. {2, 3}
    reverseRec(second);                             // Recursion on all the nodes after the first node
    first->next->next = first;                      // Assuming after recursion we have reversed all the nodes except the first and stored them in second
    first->next = NULL;                             // first->next->next = first; first->next = NULL as it now the last node
    head = second;                                  // Fixes head at beginning of the reversed list
}

// 25. (LC#24) Write a function swapPairs() to swap pairs in a given linked list as demonstrated. (Recursive) Eg. {1, 2, 3, 4, 5} becomes {2, 1, 4, 3, 5}
node* swapPairs(node* head) {			//	Here, the links are swapped instead of the values (Prefer this method)
    if (head==NULL||head->next==NULL) return head;
    node* curr = head->next;
    node* prev = head;
    node* temp = curr->next;
    curr->next = prev;
    prev->next = swapPairs(temp);
    return curr;
}
/* 25b. Exactly same as 25 but without the use a redundant variable temp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL || head->next==NULL) return head;
        ListNode *prev = head->next;
        head->next = head->next->next;
        prev->next = head;
        head->next = swapPairs(head->next);
        return prev;
        //or head = prev; return head;
    }
};
*/

/*  25c. It swaps node values instead of nodes itself, recursive
class Solution {
public:
    void swap(int &a, int &b) {
        int temp = b;
        b = a;
        a = temp;
    }
    ListNode* swapPairs(ListNode* h) {
        if(h==NULL || h->next==NULL) return h;
        swap(h->val, h->next->val);
        h->next->next = swapPairs(h->next->next);
        return h;

    }
};
*/

// 26. Write a funcntion isPalindrome() to check whether a given linked list is a palindrome or not. Eg. {2, 10, 1, 99, 7, 99, 1, 10, 2} => True
// 26a. Method 1. Using getLength() or getSize() function to get the size of the linked list and defining mid = (len-1)/2 then get a pointer to mid
//		Prefer method 2 over method 1 as method 1 tends to get a bit lengthier than method 2

// 26b. Method 2. Using slow and fast pointers to get the pointer to the mid of the list 
//      # IMP - Best solution - Reverse the second half of the list and using slow and fast pointers as the slow will give the mid point
//      of the list. Then compare the reversed second half with first half.
//      If all the elements are equal return true else false. #IMPORTANT
bool isListPalindrome(node* head) {
        if(head==NULL||head->next==NULL) return 1;
        node* slow = head;                          // Using slow and fast to get the midpoint without calculating the length of the list
        node* fast = head->next;
        while(fast!=NULL){
            fast = fast->next;
            if(fast!=NULL){
                slow = slow->next;
                fast = fast->next;
            }
        }                                           // Eg. {1, 2, 2, 1} or {1, 2, 3, 2, 1}
        node* slowNext = slow->next;                // slowNext points to the node after the node at the middle i.e second 2 or second 2
        slow->next = NULL;                          // slow points to the node at the middle i.e first 2 or 3
        slowNext = reverseRecursive(slowNext);      // reveres the second half
        node* curr1 = head;                         // two pointers for iterating the first half and the second half
        node* curr2 = slowNext;
        bool ans = 1;
        while(curr2!=NULL){                         // using curr2 in the break condition as size of second half <= size of the first half
            if(curr1->data != curr2->data){
                ans = 0; break;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return ans;
    }

// 27.  You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order,
//      and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
//      You may assume the two numbers do not contain any leading zero, except the number 0 itself.
//      Eg. Input: a = [2,4,3], b = [5,6,4] => 342 + 465 = 807 => Output: [7,0,8]
node* addTwoNumbers(node* l1, node* l2) {
        int len1 = length(l1); int len2 = length(l2); int len;
        node* larger = NULL;
        node* smaller = NULL;
        if(len1>=len2){
            larger = l1; smaller = l2; len = len1;
        }
        else{
            larger = l2; smaller = l1; len = len2;
        }
        int sum, rem, carry, s, l;
        carry = 0;
        node* resultHead = NULL;
        node* rCurr = NULL;
        while(larger!=NULL){                    // Loop ends when the larger list is used up
            sum = 0;
            sum += carry;                       // Carrying over 1 or 0
            if(smaller==NULL) s=0;              // If the smaller loop ends make its elemens 0
            else s = smaller->data;
            l = larger->data;
            sum += s + l;                       // sum = sum + s + l for implementing the carry step
            rem = sum%10;                       // rem is value that is to be appended in the result list
            carry = sum/10;                     // carry can be 0 or 1 only as each node consists of a single digit number
            node* newNode = new node;
            newNode->data = rem;
            newNode->next = NULL;
            if(resultHead==NULL){               // First entry in the result list
                //ListNode* newNode = new ListNode(rem, NULL);    // calling constructors while using the new operator on structs with functions
                resultHead = newNode;
                rCurr = resultHead;
            }
            else{
                //ListNode* newNode = new ListNode(rem, NULL);
                rCurr->next = newNode;                          // Building the result list
                rCurr = rCurr->next;
            }
            larger = larger->next;                              // Advancing the larger and smaller pointers
            if(smaller!=NULL) smaller = smaller->next;          // If the smaller list is alread emptied, no need to advance it
        }
        if(carry == 1){                                         // If there is a carry over for the last addition need to append digit 1 at the end
                node* newNode = new node;
                newNode->data = 1;
                newNode->next = NULL;
                rCurr->next = newNode;
                rCurr = rCurr->next;
            }
        return resultHead;                                      // Check its input from user in int main()
    }

// 28.  Write a function hasCycle() to check whether the given linked list has a cycle. (leetCode problem - LC#141)
//      This problem uses the two pointer technique (slow and fast) or Floyd's Cycle Finding Algorithm.
//      Floyd's Cycle Finding Algorithm -
//      The space complexity can be reduced to O(1) by considering two pointers at different speed -
//      a slow pointer and a fast pointer. The slow pointer moves one step at a time while the fast pointer
//      moves two steps at a time. There can be two cases :
//      Case I - If there is no cycle in the list, the fast pointer will eventually reach the end and we can
//      return false in this case.
//      Case II - Now consider a cyclic list and imagine the slow and fast pointers are two runners racing around
//      a circle track. The fast runner will eventually meet the slow runner. Why?
//      Consider this case (we name it case IIA) - The fast runner is just one step behind the slow runner. In the
//      next iteration, they both increment one and two steps respectively and meet each other.
//      How about other cases? For example, we have not considered cases where the fast runner is two or three steps
//      behind the slow runner yet. This is simple, because in the next or next's next iteration, this case will be reduced to
//      case IIA mentioned above, as in each iteration if fast is behind slow pointer the gap between them reduces by 1.
bool hasCycle(node* head){                          // My Code
    if(head==NULL||head->next==NULL) return false;  // The only base case here is head==NULL as head->next gets covered by fast.
    bool ans = false;
    node* slow = head;
    node* fast = head;
    while(fast!=NULL){
        fast=fast->next;
        if(fast!=NULL){
            if(slow==fast){
                ans = true;
                break;
            }
            else{
                slow = slow->next;
                fast = fast->next;
            }
        }
    }
    return ans;
}

/* Prefer this solution
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==NULL || head->next==NULL) return false;
        ListNode *slow = head;
        ListNode *fast = head->next;
        while(fast!=NULL) {
            fast = fast->next;
            if(fast!=NULL) {
                if(slow==fast) return true;
                slow = slow->next;
                fast = fast->next;
            }
        }
        return false;        
    }
};
*/ 

// or
bool hasCycle2(node* head){              // LeetCode solution
    if(head==NULL) return false;
    node* slow = head;
    node* fast = head->next;
    while(slow!=fast){
        if(fast==NULL||fast->next==NULL) return false;
        else {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
    return true;    // The program only reaches here as the while loop ends i.e. slow==fast
}                   // therefore a cycle exists.

// 29.  Write a function detectCycle() s.t. given the head of a linked list, it returns the node where the cycle begins. If there is no
//		cycle, return null. (LC#142 - Linked List Cycle II)
// 29a. O(n) - Efficient - (leetCode soln)
//      1. Using the two pointer technique (Floyd's Cycle Algorigtm) and
//      2. m+k = (y-2x)*n i.e. m+k is a multiple of n
node* detectCycle(node* head){
        if(head==NULL||head->next==NULL) return NULL;
        node* slow = head;
        node* fast = head;
        slow = slow->next;                      //  Note - slow = slow->next and fast = fast->next->next is really important
        fast = fast->next->next;                //  for this algo to run properly
        while(slow!=fast){
            if(fast==NULL||fast->next==NULL) return NULL;
            else {
                slow = slow->next;
                fast = fast->next->next;
            }
        }
        slow = head;            // If the program reaches here => the list has a cycle thus slow is made to point to head
        while(slow!=fast){      // Until slow == fast both pointers are advanced one step a time
            slow=slow->next;
            fast=fast->next;

        }
        return slow;            // It is already proved that slow and fast pointer would meet at the first node in the cycle
}

/* 29. Leetcode (LC#142) - Detect a cycle in linked list II
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL || head->next==NULL) return NULL;
        ListNode *slow = head;
        ListNode *fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
			if(slow==fast) break;
        }
        if(fast && fast->next) {
            slow = head;
            while(slow!=fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
        return NULL;
    }
};
*/

// 29b. O(n^2) - Inefficient
/*  int distBetween(ListNode* node1, ListNode* node2){
        cout<<"distBetween "<<node1->val<<" & "<<node2->val<<" = ";
        if(node1==node2) return 0;
        else {
            int count = 0;
            while(node1!=node2){
                count++;
                node1 = node1->next;
            }
            return count;
        }
    }

    ListNode *detectCycle(ListNode* head) {
        if(head==NULL||head->next==NULL) return NULL;
        vector<int> distance;
        int currDist = -1;
        bool hasCycle = 0;
        ListNode* curr = head;
        while(curr!=NULL){
            currDist = distBetween(head, curr);
            distance.push_back(currDist);
            cout<<"Current Distance = "<<currDist<<"\n";
            for(int i=0; i<distance.size()-1; i++){
                if(distance[i]==currDist){
                    hasCycle = 1;
                    break;
                }
            }
            if(hasCycle==1) break;
            curr = curr->next;
        }
        if(hasCycle==1) {
            ListNode* firstNodeInLoop = head;
            for(int i=0; i<currDist; i++) firstNodeInLoop = firstNodeInLoop->next;
            return firstNodeInLoop;
        }
        else return NULL;
    }
*/
// 30.  Write a program to find the node at which the intersection of two singly linked lists begins.
//      If the two linked lists have no intersection at all, return null.
//      The linked lists must retain their original structure after the function returns.
//      You may assume there are no cycles anywhere in the entire linked structure.
//      Your code should preferably run in O(n) time and use only O(1) memory.
//      Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
//      Output: null
//      Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
//      Output: Reference of the node with value = 8
//  30a. My Code - O(n) i.e. O(m+n) time and O(1) memory.
node *getIntersectionNode(node *headA, node *headB) {
        int sizeA = 0;
        int sizeB = 0;
        node* currA = headA;
        node* currB = headB;
        while(currA!=NULL){             // Get the size of both lists
            sizeA++;
            currA=currA->next;
        }
        while(currB!=NULL){
            sizeB++;
            currB=currB->next;
        }
        int diff = abs(sizeA-sizeB);    // The bigger list must be made shorter from the left end
        if(sizeA>sizeB){
            currA = headA;
            currB = headB;
            while(diff--) currA=currA->next;
        }
        else if(sizeB>sizeA){
            currA = headA;
            currB = headB;
            while(diff--) currB=currB->next;
        }
        else {
            currA = headA;              // If both the lists have the same size, both currs begin from the respective heads
            currB = headB;
        }
        while(currA!=NULL){
            if(currA==currB){           // Note - Don't compare value i.e. currA->data == currB->data is incorrect
                return currA;
            }
            else{
                currA = currA->next;
                currB = currB->next;
            }
        }
        return NULL;                    // If the program reaches here => there is no intersection
    }
// 30b. Shorter version of 30a.
/*ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *pA = headA;
        ListNode *pB = headB;
        while (pA != pB) {
            pA = (pA == NULL) ? headB : pA->next;
            pB = (pB == NULL) ? headA : pB->next;
        }
        return pA;
*/
//########################################################################################################################################################################

int main(){
node* head = NULL;
for (int i=1; i<=10; i++){              // Creates a ll as head -> {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}
    if (i<6) head = pushAtHead(head, i);
    else voidPushAtHead(head, i);
}
//head = NULL;                          // Checks all the fucntions for head == NULL
cout<<"The length of the linked list is "<<length(head)<<" or "<<lengthForLoop(head)<<"\n";
print(head);
cout<<"Printing elements of the linked list recursively from head to end \n";
printRecursive(head);
cout<<"\n";
cout<<"Printing elements of the linked list recursively from end to head \n";
printRecEndToHead(head);
cout<<"\nPrinting elements of the linked list iteratively from end to head \n";
printEndToHead(head);
cout<<"\n";
node* head2 = 0;
for (int i=10; i<=100; i=i+10){            // Creates a second llist as head2 -> {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}
    if (i<60) head2 = pushAtEnd(head2, i);
    else voidPushAtEnd(head2, i);
}
cout<<"The length of the second linked list is "<<length(head2)<<" or "<<lengthForLoop(head2)<<"\n";
print(head2);
cout<<"Printing elements of the second linked list recursively from head to end \n";
printRecursive(head2);
cout<<"\n";
cout<<"Printing elements of the second linked list recursively from end to head \n";
printRecEndToHead(head2);
cout<<"\nPrinting elements of the second linked list iteratively from end to head \n";
printEndToHead(head2);
cout<<"\n";
int item=0;
node* head3 = NULL;
for(int i=0; i<10; i++){                   // Creates a third llist as head3 -> {5, 5, 5, 5, 5, 5, 1, 1, 1, 1}
    if (i<6) head3 = pushAtHead(head3, 5);
    else head3 = pushAtEnd(head3,1);
}
cout<<"Printing elements of the third linked list recursively from head to end \n";
printRecursive(head3);
cout<<"\n";
node* head4 = NULL;
for(int i=5; i<=50; i=i+5) head4 = pushAtEnd(head4, i); // Creates a fourth list with a cycle
cout<<"Printing elements of the fourth linked list recursively from head to end \n";
printRecursive(head4);
cout<<"\n";
cout<<"Creating a cycle in the fourth linked list \n";
node* curr4 = head4;
while(curr4->next!=NULL){
    curr4 = curr4->next;
}
curr4->next = head4->next; // i.e. the last element now points to the second element thus creating a cycle
node* head5 = NULL;
for(int i=100; i<=1200; i=i+100) head5 = pushAtEnd(head5, i); // Creates a fifth list with a cycle
cout<<"Printing elements of the fifth linked list recursively from head to end \n";
printRecursive(head5);
cout<<"\n";
cout<<"Creating a cycle in the fifth linked list \n";
node* curr5 = head5;
while(curr5->next!=NULL){
    curr5 = curr5->next;
}
//curr5->next = head5;    // i.e. the last element now points to the first element thus creating a cycle
curr5->next = head5->next->next->next->next;    // i.e. the last element now points to the fifth element thus creating a cycle

char input;
bool boolAns;
int value;
/* Deleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeete this /*
cout<<"Wanna use the count() function? (y/n) = ";
cin>>input;
while(input=='y'){
    cout<<"Enter the number to be found in the third linked list = ";
    cin>>item;
    int countItem = count(head3, item);
    if (countItem==0) cout<<"The number is not present in the third linked list \n";
    else cout<<"The number "<<item<<" is present in the third linked list, "<<countItem<<" time(s) \n";
    cout<<"Wanna continue? => count() (y/n) = ";
    cin>>input;
}

cout<<"Wanna use the getNth() function? (y/n) = ";
cin>>input;
while(input=='y'){
    cout<<"Enter the value of the index = ";
    int index = -1;
    cin>>index;
    int dataAtIndex = getNth(head, index);
    if(dataAtIndex == -1) cout<<"Index out of bounds \n";
    else cout<<"The data at index "<<index<<" is "<<dataAtIndex<<"\n";
    cout<<"Wanna continue? => getNth() (y/n) = ";
    cin>>input;
}
cout<<"Wanna delete a list? (y/n) = ";
cin>>input;
while(input=='y'){
if(input == 'y')cout<<"Which one? 1, 2 or 3? ";
int listNo;
cin>>listNo;
switch(listNo){
    case 1: deleteList(head); break;
    case 2: deleteList(head2); break;
    case 3: deleteList(head3); break;
    default: cout<<"Incorrect linked list number"; break;
}
cout<<"Wanna delete another? (y/n) = ";
cin>>input;
}

cout<<"Wanna use popAtHead() func on the second linked list? (y/n) = ";
cin>>input;
while(input=='y'){
    popAtHead(head2);
    cout<<"Wanna continue? => popAtHead() (y/n) - ";
    cin>>input;
}

cout<<"Wanna use insertNth() function on the third list? (y/n) = ";
cin>>input; int flag = 0;
while(input=='y'){
    int index, data;
    cout<<"Input index and data to be addded = ";
    cin>>index>>data; flag = 1;
    insertNth(head3, index, data);
    cout<<"Wanna continue? => insertNth() (y/n) = ";
    cin>>input;
}
if(flag == 1){
    cout<<"The updated third linked list after insertNth() is = \n";
    print(head3);
}

cout<<"Wanna use insertNthWithPush() function on the second list? (y/n) = ";
cin>>input;
flag = 0;
while(input=='y'){
    int index, data;
    cout<<"Input index and data to be addded = ";
    cin>>index>>data; flag = 1;
    insertNthWithPush(head2, index, data);
    cout<<"Wanna continue? => insertNthWithPush() (y/n) = ";
    cin>>input;
}
if(flag==1){
    cout<<"The updated second linked list after insertNthWithPush() is = \n";
    print(head2);
}

cout<<"Wanna use sortedInsert() function on the second list? (y/n) = ";
cin>>input;
while(input=='y'){
    node* singleNode = new node;
    cout<<"Enter the data to be inserted in the sorted linked list i.e. second linked list = ";
    int data;
    cin>>data;
    singleNode->data = data;
    singleNode->next = NULL;
    sortedInsert(head2, singleNode);
    cout<<"The updated second linked list after sortedInsert() is = \n";
    print(head2);
    cout<<"Wanna continue? => sortedInsert() (y/n) = ";
    cin>>input;
}

cout<<"Wanna use insertSort() function on the first list? (y/n) = ";
cin>>input;
if(input=='y'){
    cout<<"Printing the unsorted version\n";
    print(head);
    insertSort(head);
    cout<<"Printing the sorted version\n";
    print(head);
}

cout<<"Wanna use append() function on the first list and second list? (y/n) = ";
cin>>input;
if(input=='y'){
    append(head, head2);
    cout<<"The first list after append() = \n";
    print(head);
    cout<<"The second list after append() = \n";
    print(head2);
}

node* half1Head = NULL;
node* half2Head = NULL;
//head = NULL; head2 = NULL; head3 = NULL;      //To test the fbsplit() for len < 2
voidPushAtHead(head, 1); print (head);
voidPushAtHead(head2, 2); print (head2);
voidPushAtHead(head3, 3); print (head3);
cout<<"Wanna use frontBackSplit() function on the first lis?t (y/n) = ";
cin>>input;
if(input=='y'){
    cout<<"Original llist = ";
    print(head);
    frontBackSplit(head, half1Head, half2Head);
    cout<<"The first half = ";
    print(half1Head);
    cout<<"The second half = ";
    print(half2Head);
    deleteList(half1Head);
    deleteList(half2Head);
}

cout<<"Wanna use frontBackSplitBetter() function on the second list? (y/n) = ";
cin>>input;
if(input=='y'){
    cout<<"Original llist = ";
    print(head2);
    frontBackSplitBetter(head2, half1Head, half2Head);
    cout<<"The first half = ";
    print(half1Head);
    cout<<"The second half = ";
    print(half2Head);
    deleteList(half1Head);
    deleteList(half2Head);
}

cout<<"Wanna use frontBackSplitFastSlowptr() function on the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    cout<<"Original llist = ";
    print(head3);
    frontBackSplitFastSlowptr(head3, half1Head, half2Head);
    cout<<"The first half = ";
    print(half1Head);
    cout<<"The second half = ";
    print(half2Head);
    deleteList(half1Head);
    deleteList(half2Head);
}

cout<<"Wanna use removeDuplicates() function on the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    cout<<"Original llist = ";
    print(head3);
    cout<<"The third llist after removing duplicates = ";
    removeDuplicates(head3);
    print(head3);
}

cout<<"Wanna use moveNodeWithPush() function on the first and the second lists? (y/n) = ";
cin>>input;
flag = 0;
while(input=='y'){
    flag = 1;
    if(input=='y') moveNodeWithPush(head, head2);
    cout<<"Wanna continue? => moveNodeWithPush() (y/n) = ";
    cin>>input;
}
if (flag==1){
    cout<<"The updated first list is = ";
    print(head);
    cout<<"The updated second list is = ";
    print(head2);
}

cout<<"Wanna use moveNode() function on the second and the third lists? (y/n) = ";
cin>>input;
flag = 0;
while(input=='y'){
    flag = 1;
    if(input=='y') moveNodeWithPush(head2, head3);
    cout<<"Wanna continue? => moveNodeWithPush() (y/n) = ";
    cin>>input;
}
if (flag==1){
    cout<<"The updated second list is = ";
    print(head2);
    cout<<"The updated third list is = ";
    print(head3);
}


cout<<"Wanna use alternatingSplit() function on the second list? (y/n) = ";
cin>>input;
if(input=='y'){
    node* eHead = NULL;
    node* oHead = NULL;
    cout<<"Original llist = ";
    print(head2);
    alternatingSplit(head2, eHead, oHead);
    cout<<"The sublists of alternatingSplit() are = \n";
    print(eHead);
    print(oHead);
}

cout<<"Wanna use alternatingSplitWithMoveNode() function on the first list? (y/n) = ";
cin>>input;
if(input=='y'){
    node* eHead = NULL;
    node* oHead = NULL;
    cout<<"Original llist = ";
    print(head);
    alternatingSplitWithMoveNode(head, eHead, oHead);
    cout<<"The sublists of alternatingSplit() are = \n";
    print(eHead);
    print(oHead);
}


cout<<"Wanna use shuffleMerge() function on the second and the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    node* sMergeHead = shuffleMerge(head2, head3);
    cout<<"The shuffle merged list is = \n";
    print(sMergeHead);
}

cout<<"Wanna use shuffleMergeBetter() function on the first and the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    node* sMergeHead = shuffleMergeBetter(head, head3);
    cout<<"The shuffle merged list is = \n";
    print(sMergeHead);
}

cout<<"Wanna use sortedMergeIter() function on the first and the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; head3 = NULL; voidPushAtHead(head3, 5); voidPushAtHead(head, 2); voidPushAtHead(head, 1);
    insertSort(head); insertSort(head3); // Sorting in ascending order both the lists before merging
    print(head); print(head3);
    cout<<"The iteratively merged list is = \n";
    node* sMergeHead = sortedMergeIter(head, head3);
    print(sMergeHead);
}

cout<<"Wanna use sortedMergeRec() function on the first and the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; head3 = NULL; voidPushAtHead(head3, 5); voidPushAtHead(head, 2); voidPushAtHead(head, 1);
    insertSort(head); insertSort(head3); // Sorting in ascending order both the lists before merging
    print(head); print(head3);
    cout<<"The recursively merged list is = \n";
    node* sMergeHead = sortedMergeRec(head, head3);
    print(sMergeHead);
}

cout<<"Wanna use mergeSort() function on the first list? (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; voidPushAtEnd(head, 1); voidPushAtHead(head, 2);
    cout<<"Original llist = \n";
    print(head);
    node* mergeSortHead = mergeSort(head);
    cout<<"The sorted llist using mergeSort() function is = \n";
    print(mergeSortHead);
}

cout<<"Wanna use sortedIntersect() function on the first list and the third list? (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; head3 = NULL; voidPushAtHead(head, 1); voidPushAtHead(head3, 1);
    head = mergeSort(head); head3 = mergeSort(head3);       // Sorting the two lists before intersection
    print(head); print(head3);
    node* intsecHead = sortedIntersect(head, head3);
    cout<<"The intersection between first and the third list is = \n";
    print(intsecHead);
}

cout<<"Wanna use reverseIterWithMoveNode() function on the first list (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; voidPushAtHead(head, 1); voidPushAtHead(head, 2); voidPushAtEnd(head, 0);
    cout<<"Original llist = \n";
    print(head);
    reverseIterWithMoveNode(head);
    cout<<"The reversed llist = \n";
    print(head);
}

cout<<"Wanna use reverseRecursive() function on the second list (y/n) = ";
cin>>input;
if(input=='y'){
    //head2 = NULL; voidPushAtHead(head2, 1); voidPushAtHead(head2, 2); voidPushAtEnd(head2, 0);
    cout<<"Original llist = \n";
    print(head2);
    head2 = reverseRecursive(head2);
    cout<<"The reversed llist = \n";
    print(head2);
}

cout<<"Wanna use reverseRecursiveSlower() function on the first list (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; voidPushAtHead(head, 1); voidPushAtHead(head, 2); voidPushAtEnd(head, 0);
    cout<<"Original llist = \n";
    print(head);
    head = reverseRecursiveSlower(head);
    cout<<"The reversed llist = \n";
    print(head);
}

cout<<"Wanna use void reverseRec() function on the first list (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; voidPushAtHead(head, 1); voidPushAtHead(head, 2); voidPushAtEnd(head, 0);
    cout<<"Original llist = \n";
    print(head);
    reverseRec(head);
    cout<<"The reversed llist = \n";
    print(head);
}

cout<<"Wanna use void reverseIterative() function on the third list (y/n) = ";
cin>>input;
if(input=='y'){
    head3 = NULL; voidPushAtHead(head3, 1); voidPushAtHead(head3, 2); voidPushAtEnd(head3, 0);
    cout<<"Original llist = \n";
    print(head3);
    reverseIterative(head3);
    cout<<"The reversed llist = \n";
    print(head3);
}

cout<<"Wanna use void reverseIterWith3Ptrs() function on the first list (y/n) = ";
cin>>input;
if(input=='y'){
    //head = NULL; voidPushAtHead(head, 1); voidPushAtHead(head, 2); voidPushAtEnd(head, 0);
    cout<<"Original llist = \n";
    print(head);
    reverseIterWith3Ptrs(head);
    cout<<"The reversed llist = \n";
    print(head);
}

cout<<"Wanna use void swapPairs() function on the second list (y/n) = ";
cin>>input;
while(input=='y'){
    //head2 = NULL; voidPushAtHead(head2, 1); voidPushAtHead(head2, 2); voidPushAtEnd(head2, 0);
    cout<<"Original llist = \n";
    print(head2);
    head2 = swapPairs(head2);
    cout<<"The pair swapped llist = \n";
    print(head2);
    cout<<"Wanna continue? => swapPairs() (y/n) = ";
    cin>>input;
}


cout<<"Wanna use isListPalindrome() function on the first list (y/n) = ";
cin>>input;
if(input=='y'){
    head = NULL; voidPushAtHead(head, 100); voidPushAtHead(head, 26);  voidPushAtHead(head, 15); voidPushAtHead(head, 26); voidPushAtHead(head, 100);
    cout<<"Original llist = \n";
    print(head);
    bool palin = isListPalindrome(head);
    if(palin==1) cout<<"The given list is a palindrome\n";
    else cout<<"The given list is not a palindrome\n";
}
 Deleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeete this*/
cout<<"Wanna use addTwoNumbers() function (y/n) = ";
cin>>input;
if(input=='y'){
    node* a = NULL; node*b = NULL;
    int len; int dig;
    cout<<"Enter the length followed by digits of the list 1 = ";
    cin>>len;
    for(int i=0; i<len; i++){
        cin>>dig;
        voidPushAtHead(a, dig);
    }
    cout<<"Enter the length followed by digits of the list 2 = ";
    cin>>len;
    for(int i=0; i<len; i++){
        cin>>dig;
        voidPushAtHead(b, dig);
    }
    cout<<"Stored as reversed as = \n"; print(a); print(b);
    cout<<"Adding the two numbers\n";
    node* c = addTwoNumbers(a, b);
    //print(c);
    cout<<"The sum of the two numbers are = ";
    printEndToHead(c);
}

cout<<"Wanna use hasCycle() function (y/n) = ";
cin>>input;
while(input=='y'){
    cout<<"Input the list number (1-5) to be checked for a cycle = \n";
    cin>>value;
    int fl = 1;
    node* current = NULL;
    switch(value){
        case 1 :
            current = head;
            break;
        case 2 :
            current = head2;
            break;
        case 3 :
            current = head3;
            break;
        case 4 :
            current = head4;
            break;
        case 5 :
            current = head5;
            break;
        default :
            fl = 0;
    }
    if(fl){
        boolAns = hasCycle2(current); // boolAns = hasCycle(current);
        if(boolAns==1) cout<<"The list ("<<value<<") has a cycle\n";
        else cout<<"The list ("<<value<<") has no cycle\n";
    }
    else cout<<"Invalid input\n";
    cout<<"Wanna continue? => hasCycle() (y/n) = ";
    cin>>input;
}
cout<<"Wanna use detectCycle() function (y/n) = ";
cin>>input;
while(input=='y'){
    cout<<"Input the list number (1-5) to be checked for a cycle = \n";
    cin>>value;
    int fl = 1;
    node* current = NULL;
    switch(value){
        case 1 :
            current = head;
            break;
        case 2 :
            current = head2;
            break;
        case 3 :
            current = head3;
            break;
        case 4 :
            current = head4;
            break;
        case 5 :
            current = head5;
            break;
        default :
            fl = 0;
    }
    if(fl){
        node* cycleHead = detectCycle(current);
        if(cycleHead!=NULL) cout<<"The list ("<<value<<") has a cycle which begins form the node = "<<cycleHead->data<<"\n";
        else cout<<"The list ("<<value<<") has no cycle\n";
    }
    else cout<<"Invalid input\n";
    cout<<"Wanna continue? => detectCycle() (y/n) = ";
    cin>>input;
}

cout<<"Wanna use getIntersectionNode() function (y/n) = ";
cin>>input;
if(input=='y'){
    node* headA = NULL;
    node* headB = NULL;
    headA = pushAtEnd(headA, 1); headA = pushAtEnd(headA, 3); headA = pushAtEnd(headA, 5); headA = pushAtEnd(headA, 7); headA = pushAtEnd(headA, 8); headA = pushAtEnd(headA, 9);
    headB = pushAtEnd(headB, 2); headB = pushAtEnd(headB, 4); headB = pushAtEnd(headB, 6);
    headB->next->next->next = headA->next->next->next; // To create an intersection. If removed they won't intersect.
    cout<<"Printing list A = ";
    print(headA);
    cout<<"Printing list B = ";
    print(headB);
    node* intersectedNode = getIntersectionNode(headA, headB);
    if(intersectedNode) cout<<"List A and list B intersect at the node with value = "<<intersectedNode->data<<"\n";
    else cout<<"List A and list B don't intersect \n";
}
cout<<"Ending the program";
return 0;
}
