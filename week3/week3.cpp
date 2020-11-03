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
    auto newNode = new Node<T>(elem);
    newNode->next = *head;
    *head = newNode;
}

// pushFront with reference instead of reference pointer
template<typename T>
void pushFrontRef(Node<T> *& head, T elem)
{
    auto newNode = new Node<T>(elem);
    newNode->next = head;
    head = newNode;
}


// calls pushFront on a list of arguments
template <typename T>
void pushFrontList(Node<T> ** head, std::initializer_list<T> const& il)
{
    // iterate initializer list
    for (auto const& elem : il)
    {
        // elem is the current element from initializer list
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
    Node<T> *current = head;
    size_t count = 0;
    while (current)
    {
        if (current->data == elem)
        {
            count++;
        }
        current = current->next;
    }
    return 0;
}

// function that pops (from beginning)
// and returns the popped
// pop([1,2,3]) -> [2,3]
// pop([]) -> 0 or default object for type T
template <typename T>
T pop(Node<T> **head)
{
    if (*head == nullptr)
    {
        // empty list, return default constructor
        return T();
    }
    auto temp = *head;
    T result = temp->data;
    *head = (*head)->next;
    delete temp;
    return result;
}

/**
 * inserts a node with value @elem at position @index
 * if @index is more than the size of the list insert
 * at the end
*/
template <typename T>
void insertNth(Node<T> ** head, size_t index, T elem)
{
    Node<T> *newNode = new Node<T>(elem);
    size_t idx = 0;
    Node<T> *current = *head, *prev = nullptr;
    while (current != nullptr && idx < index)
    {
        prev = current;
        current = current->next;
        ++idx;
    }

    if (prev == nullptr)
    {
        // this means that we are inserting on index 0
        if (*head == nullptr)
        {
            // empty list
            *head = newNode;
        }
        else
        {
            // insert on front
            newNode->next = *head;
            *head = newNode;
        }
    }
    else
    {
        newNode->next = prev->next;
        prev->next = newNode;
    }
}

template <typename T>
void sortedInsert(Node<T> ** head, Node<T> * node)
{
    // assert(node != nullptr)
    // save the two nodes, between which we are going to
    // insert the new one
    Node<T> *prev = nullptr, *current = *head;
    if (*head == nullptr)
    {
        *head = node;
        return;
    }
    while (current && current->data <= node->data)
    {
        prev = current;
        current = current->next;
    }
    if (prev == nullptr)
    {
        // we are inserting on the front
        node->next = *head;
        *head = node;
    }
    else
    {
        node->next = prev->next;
        prev->next = node;
    }
}

template <typename T>
void insertionSort(Node<T> ** head)
{
    // we keep two lists: @sorted, in which
    // we insert elements keeping it sorted
    // and @rest which keeps the not-inserted
    // elements
    Node<T> * sorted = nullptr, *rest = *head;
    while (rest != nullptr)
    {
        Node<T> *temp = rest;
        rest = rest->next;
        temp->next = nullptr; // set to null, as to "leave" the other list (it is now not pointing to any element from it)
        sortedInsert(&sorted, temp);
    }
    *head = sorted;
}

/**
 * Appends @listB to @listA sets @listB to null
 */
template <typename T>
void appendList(Node<T> ** listA, Node<T> ** listB)
{
    Node<T> *current = *listA;
    if (current == nullptr)
    {
        *listA = *listB;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = *listB;
    }
    *listB = nullptr;
}

template <typename T>
void frontBackSplit(Node<T> ** head, Node<T> ** front, Node<T> ** back)
{
    if (*head == nullptr)
    {
        *front = *back = nullptr;
        return;
    }
    Node<T> *slow = *head, *fast = *head;
    while (fast != nullptr && fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = *head;
    *back = slow->next;
    slow->next = nullptr;
}

template <typename T>
void removeDuplicates(Node<T> ** head)
{
    Node<T> *current = *head, *prev = nullptr;
    while (current != nullptr)
    {
        if (prev != nullptr && prev->data == current->data)
        {
            // equal -> move just current
            Node<T> *temp = current;
            current = current->next;
            prev->next = current;
            delete temp;
        }
        else
        {
            // not equal -> move normally
            prev = current;
            current = current->next;
        }
    }
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

    // test append list
    l1 = fromVector(std::vector<int>{1,2,3});
    Node<int> *l2 = fromVector(std::vector<int>{4,5,6});
    appendList(&l1, &l2); // 1 2 3 4 5 6
    print(l1);

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
    deleteList(l1);

    l1 = fromVector(std::vector<int>{1,1,1,1,1});
    removeDuplicates(&l1);
    print(l1); // 1
    deleteList(l1);

    return 0;
}
