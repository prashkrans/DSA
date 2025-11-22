/*
https://appdividend.com/2019/06/12/cpp-list-tutorial-with-example-list-in-c-standard-template-library-stl/
listName.push_back(int val);
listName.push_front(int val);
listName.front();
listName.back();
listName.pop_front();
listName.pop_back();
empty() – Returns whether the list is empty(1) or not(0).
insert(itr pos, int noOfE, int value) – Inserts new elements in the list before the element at a specified position.
    Parameters: This function takes in three parameters:
    pos: Position in the container where the new elements are inserted.
    noOfE: Number of elements to insert. Each element is initialized to a copy of val.
    value: Value to be copied (or moved) to the inserted elements.
    insert(itr pos, int value) i.e. if only two param given, first is pos, second is value
    Return Value: This function returns an iterator that points to the first of the newly inserted elements.
assign() – Assigns new elements to list by replacing current elements and resizes the list.
    The list::assign() is a built-in function in C++ STL which is used to assign values to a list. It can
    also be used to copy elements from one list to another.
    a. To assign elements to a list.
    Syntax: list_name.assign(int count, int/dataTaype value)
    Parameters: This function accepts two mandatory parameters as shown in the above syntax and described below:
    count: The number of values needed to be assigned to the list with name list_name.
    value: This is the value that will be assigned count number of times starting from the first element. If the
    list already contains some elements then those elements will be replaced by the element specified in the parameter value.
    The data type of this parameter must be of the same type as that of list_name.
    Return Value: This function assigns the element specified in the value parameter count number of times starting from the
    first element in the list list_name. The return type of this function is void and it does not returns any value.
    b. To copy elements from an existing list to a new list.
    Syntax: first_list.assign(second_list.begin(), second_list.end());
erase(itr pos) or erase(iterator it_start, it_end) – Removes a single element or a range of elements from the list given the position as an iterator.
remove(int value) – Removes all the elements from the list, which are equal to given element value.
    Syntax: list_name.remove(int val)
remove_if() in C++ STL– Used to remove all the values from the list that correspond true to the predicate or condition given as parameter to the function.
reverse() – Reverses the list.
size() – Returns the number of elements in the list.
resize(int newSize)function in C++ STL– Used to resize a list container.
sort() – Sorts the list in increasing order.
unique() – Removes all duplicate consecutive elements from the list.
clear() - Removes all the elements of the list container, thus making it size 0.
merge() -  Merges two sorted lists into one
           Syntax1: list1_name.merge(list2_name)
           The list::merge() is an inbuilt function in C++ STL which merges two sorted lists into one.
           The lists should be sorted in ascending order. If no comparator is passed in parameter, then
           it merges two sorted lists into a single sorted list. If a comparator is passed in the parameter,
           then it merges the list accordingly doing internal comparisons.
           Parameters: The function accepts a single mandatory parameter list2_name which specifies the list to be merged into list1.
           Return value: The function does not returns anything

           Syntax2: list1_name.merge(list2_name, comparator)
*/

#include<iostream>
#include<list>
using namespace std;

void printList(list<int> l) {
    list<int>::iterator it;
    for(it = l.begin(); it!=l.end(); it++) cout<<(*it)<<" ";
    cout<<"\n";
}

void printListUsingAuto(list<int> l) {
    for(auto i : l) cout<<i<<" ";
    cout<<"\n";
}

int main(){
    list<int> l;
    l.push_back(5);    l.push_front(1);
    cout<<l.front()<<" "<<l.back()<<"\n";
    cout<<l.size()<<"\n";
    l.pop_back();
    l.pop_front();
    if(l.empty()) cout<<"The linked list is empty\n";
    else cout<<"The linked list is not empty\n";
    l.push_back(2);    l.push_back(3);    l.push_back(4);    l.push_back(5);
    l.push_front(1);
    list<int> l2(l);
    list<int>::iterator it;
    printList(l);
    printListUsingAuto(l2);
    l.merge(l2);
    printList(l);
    l.reverse();
    printListUsingAuto(l);
    l.reverse();
    it = l.begin();
    advance(it, 4); //   i.e. it = it + 4 but it doesn't work
    l.insert(it, 3, 7);
    printList(l);
    advance(it, 3);
    l.insert(it, 8);
    printList(l);
    list<int> l3(l);
    l.assign(2, 9);
    printList(l);
    l2.assign(l.begin(), l.end());
    printListUsingAuto(l2);
    printList(l3);
    l3.unique();
    printList(l3);
    l3.sort();
    printList(l3);
    cout<<"Size of l3 = "<<l3.size()<<"\n";
    l3.push_front(7);
    printList(l3);
    l3.remove(7);
    printList(l3);
    return 0;
}
