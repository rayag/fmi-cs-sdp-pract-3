#include <iostream>
#include <vector>

template <typename T>
struct Node {
    T data;
    Node * next {nullptr};

    Node(T data) : data{data} { }
};

template <typename T>
void print(const Node<T> * head) 
{
    const Node<T> * current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
Node<T> * fromVector(std::vector<T> const& vec)
{
    Node<T> * result = nullptr;
    Node<T> * current = nullptr;

    for (T const& el : vec)
    {
        Node<T> * newNode = new Node<T>(el);
        if (result == nullptr)
        {
            // first element
            result = newNode;
            current = newNode;
        }
        else 
        {
            current->next = newNode;
            current = newNode;
        }        
    }
    return result;
}

template <typename T>
void deleteList(Node<T> *& head) // not ok, why?
{
    Node<T> * current = head;
    while (current != nullptr)
    {
        Node<T> * temp = current;
        current = current->next;
        delete temp;
    }    
    head = nullptr;
}

// Pushes @elem in the front of the list
// Hint: head should be changed as well
template <typename T>
void pushFront(Node<T> ** head, T elem)
{
    // TODO
    auto newNode = new Node<T>(elem);
    newNode->next = *head;
    *head = newNode;
}

// calls pushFront on a list of arguments
template <typename T>
void pushFrontList(Node<T> ** head, std::initializer_list<T> const& il)
{
    for (auto const& elem : il)
    {
        pushFront(head, elem);
    }
}

// how many times elem is present in the array
// count([1,6,6,3], 6) -> 2
// count([1,2,3], 9) -> 0
// count([], 7) -> 0
template <typename T>
size_t count(const Node<T> * head, T elem)
{
    // easy
    return 0;
}

// function that pops (from beginning) 
// and returns the popped
// pop([1,2,3]) -> [2,3]
// pop([]) -> 0 or default object for type T
template <typename T>
T pop(Node<T> **head)
{
    return T();
}

/** 
 * inserts a node with value @elem at position @index
 * if @index is more than the size of the list insert
 * at the end
*/
template <typename T>
void insertNth(Node<T> ** head, size_t index, T elem)
{
    // TODO
}

template <typename T>
void sortedInsert(Node<T> ** head, Node<T> * node)
{
    // TODO
}

template <typename T>
void insertionSort(Node<T> ** head)
{
    // TODO
}

/**
 * Appends @listB to @listA sets @listB to null
 */
template <typename T>
void appendList(Node<T> ** listA, Node<T> ** listB)
{
    // TODO
}

template <typename T>
void frontBackSplit(Node<T> ** head, Node<T> ** front, Node<T> ** back)
{
    // TODO
}

template <typename T>
void removeDuplicates(Node<T> ** head)
{
    // TODO
}

int main() 
{
    print(fromVector(std::vector<int>{1,2,3})); // 1 2 3
    print(fromVector(std::vector<int>{})); // 

    // test delete
    Node<int> * l = fromVector(std::vector<int>{1,2,3});
    deleteList(l);
    std::cout << l << std::endl; // should be 0, is it?

    // test pushFront
    Node<int> * l1 = nullptr;
    pushFrontList(&l1, {1,2,3});
    print(l1); // Expected: 3 2 1
    deleteList(l1);

    pushFrontList(&l1, {});
    print(l1);  // Expected: 
    deleteList(l1);

    // test pop
    pushFrontList(&l1, {1, 2, 3});
    int front = pop(&l1);
    std::cout << "front: " << front << std::endl; // Expected: front: 3
    print(l1);                                    // Expected: 2 1
    front = pop(&l1);
    std::cout << "front: " << front << std::endl; // Expected: front: 2
    print(l1);                                    // Expected: 1
    front = pop(&l1);
    std::cout << "front: " << front << std::endl; // Expected: front: 1
    print(l1);                                    // Expected: 
    front = pop(&l1);
    std::cout << "front: " << front << std::endl; // Expected: front: 0 (default constructor of int?)
    print(l1);                                    // Expected: 
    deleteList(l1);

    // test insert nth
    std::cout << "Insert tests \n";
    insertNth(&l1, 4, 3);
    print(l1); // 3
    insertNth(&l1, 0, 1);
    print(l1); // 1 3
    insertNth(&l1, 1, 2);
    print(l1); // 1 2 3
    insertNth(&l1, 3, 4);
    print(l1); // 1 2 3 4
    deleteList(l1);

    // test sortedInsert
    sortedInsert(&l1, new Node<int>(2));
    print(l1); // 2
    sortedInsert(&l1, new Node<int>(5)); // test at end
    print(l1); // 2 5
    sortedInsert(&l1, new Node<int>(3)); // test middle
    print(l1); // 2 3 5
    sortedInsert(&l1, new Node<int>(1)); // test front
    print(l1); // 1 2 3 5
    sortedInsert(&l1, new Node<int>(4));
    print(l1); // 1 2 3 4 5
    deleteList(l1);

    // test insertion sort
    l1 = fromVector(std::vector<int>{4, 1, 3, 6, 5, 2, 2});
    insertionSort(&l1);
    print(l1); // 1 2 2 3 4 5 6
    deleteList(l1);

    l1 = fromVector(std::vector<int>{5});
    insertionSort(&l1);
    print(l1);  // 5
    deleteList(l1);

    l1 = fromVector(std::vector<int>{});
    insertionSort(&l1);
    print(l1); // 
    deleteList(l1);

    // test frontBackSplit
    l1 = fromVector(std::vector<int>{1, 2, 3, 4});
    Node<int> *f, *b;
    frontBackSplit(&l1, &f, &b);
    print(f); // 1 2
    print(b); // 3 4
    deleteList(f);
    deleteList(b);

    l1 = fromVector(std::vector<int>{1, 2, 3});
    frontBackSplit(&l1, &f, &b);
    print(f); // 1
    print(b); // 2 3
    deleteList(f);
    deleteList(b);

    l1 = fromVector(std::vector<int>{1});
    frontBackSplit(&l1, &f, &b);
    print(f); // 1
    print(b); // 
    deleteList(f);
    deleteList(b);

    // test removeDuplicates
    std::cout << "Test removeDuplicates \n";
    l1 = fromVector(std::vector<int>{1,1,2,3,4});
    removeDuplicates(&l1);
    print(l1);

    return 0;
}