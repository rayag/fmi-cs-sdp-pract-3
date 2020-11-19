## Двоични дървета

Нека имаме следното представяне на възел на двоично дърво

```cpp
template <typename T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;
    
    TreeNode(T data) : data{data}, left{nullptr}, right{nullptr} { }
};
```

---


#### Зад. 1 Търсене
Да се напише функция, която търси стойност в двоично дърво.
```cpp
template <typename T>
bool search(const TreeNode<T> * root, T target) 
{
    // your code
}
```

#### Зад. 2 Брой възли
Да се напише функция, която приема двоично дърво и пресмята броя на възлите му.
```cpp
template <typename T>
size_t count(const TreeNode<T> * root)
{
    // your code
}
```

#### Зад. 3 Максимална дълбочина
Максимална дълбочина определяме като най-дългия път от корена до някое листо. Да се напише функция, която го намира.
```cpp
template <typename T>
size_t maxDepth(const TreeNode<T> *root)
{
    // your code
}
```

#### Зад. 4 Най-малък елемент
Да се напише функция, която намира най-малкия елемент в дърво.
```cpp
template <typename T>
T minValue(const TreeNode<T> *root)
{
    // your code
}
```

#### Зад. 5 Принтиране *indorder*
Да се напише функция, която приема дърво и извежда резултатът от обхождането на дървото по схемата ляво корен дясно (**ЛКД**), т.нар. *inorder traversal*.
```cpp
template <typename T>
void printInorder(const TreeNode<T> *root)
{
    // your code
}
```

#### Зад. 6 Принтиране *postorder*
Да се напише функция, която приема дърво и извежда резултатът от обхождането на дървото по схемата ляво дясно корен (**ЛДК**), т.нар. *postorder traversal*.
```cpp
template <typename T>
void printPostorder(const TreeNode<T> *root)
{
    // your code
}
```

#### Зад. 7 Използване на graphviz
Да се напише функция, която принтира дърво, така, че изпринтираното може да се види графично в [graphviz](https://graphviz.org/).

#### Зад. 8 Проверка на сума на път
Да се напише функция, която приема двоично дърво и проверява дали в него има път от корена с такава сума.
```cpp
template <typename T>
bool hasPathSum(const TreeNode<T> *root. T targetSum)
{
    // TODO
}
```

#### Зад. 9 Принтиране на пътищата
Да се напише функция, която принтира всички пътища на едно двоично дърво.
```cpp
template <typename T>
void printPaths(const TreeNode<T> *root)
{
    // TODO
}
```

#### Зад. 10 Огледално дърво
Да се напише функция, която приема дърво и го променя до неговото огледално, тоест на всяко ниво са разменени лявото и дясното поддърво.
```cpp
template <typename T>
void mirror(TreeNode<T>* root)
{
    /// TODO
}
```

#### Зад. 10 Двойно дърво
Да се напише функция, която приема дърво и за всеки възел създва негов дубликат и го вмъква като ляво дете.

#### Зад. 11 Еднакви дървета
Да се напише функция, която приема две двоични дървета и връща истина, ако те са еднакви. В противен случай връща лъжа.
```cpp
template <typename T>
bool sameTree(const TreeNode<T> *leftRoot, const TreeNode<T> *rightRoot)
{
    // TODO
}
``