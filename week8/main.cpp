#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>
#include <limits>

template <typename T>
struct TreeNode {
    T data;
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};

//    TreeNode(T data) : data{data}, left{nullptr}, right{nullptr} { }
};

template <typename T>
bool search(const TreeNode<T> * root, T target)
{
    if (root == nullptr)
        return false;

    return root->data == target || search(root->left, target) || search(root->right, target);
}

template <typename T>
size_t count(const TreeNode<T> * root)
{
    if (root == nullptr)
        return 0;
    return 1 + count(root->left) + count(root->right);
}

template <typename T>
size_t maxDepth(const TreeNode<T> *root)
{
    if (root == nullptr)
        return 0;

    size_t leftDepth = maxDepth(root->left);
    size_t rightDepth = maxDepth(root->right);

    return 1 + ( leftDepth > rightDepth ? leftDepth : rightDepth);
}

template <typename T>
bool isLeaf(const TreeNode<T> *node)
{
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}

template <typename T>
T minValue(const TreeNode<T> *const root)
{
    if (root == nullptr)
        return T();

    if (isLeaf(root))
        return root->data;

    // min { root->data, minValue(left), minValue(right) }
    return std::min(root->data, std::min(minValue(root->left), minValue(root->right)));
}

template <typename T>
void printInorder(const TreeNode<T> *root)
{
    // left root right
    if (root != nullptr)
    {
        printInorder(root->left);
        std::cout << root->data << " ";
        printInorder(root->right);
    }
}

template <typename T>
void printPostorder(const TreeNode<T> *root)
{
    // left right root
    if (root != nullptr)
    {
        printPostorder(root->left);
        printPostorder(root->right);
        std::cout << root->data << " ";
    }
}

template <typename T>
bool hasPathSumHelp(const TreeNode<T> *root, T targetSum, T currentSum)
{
    if (root == nullptr) return false;
    if (isLeaf(root))
        return (root->data + currentSum) == targetSum;

    return hasPathSum(root->left, targetSum, currentSum + root->data) || hasPathSum(root->right, targetSum, currentSum + root->data);
}

template <typename T>
bool hasPathSum(const TreeNode<T> *root, T targetSum)
{
    hasPathSumHelp(root, targetSum, 0);
}


template <typename T>
void printPaths(const TreeNode<T> *root, std::vector<T> vec)
{
    if (root == nullptr) return;

    if (isLeaf(root))
    {
        vec.push_back(root->data);
        for ( T const& el : vec)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        vec.push_back(root->data);
        printPaths(root->left, vec);
        printPaths(root->right, vec);
    }

}

template <typename T>
void mirror(TreeNode<T>* root)
{
    if (root == nullptr)
        return;

    mirror(root->left);
    mirror(root->right);

    auto temp = root->left;
    root->left = root->right;
    root->right = temp;
}

template <typename T>
bool sameTree(const TreeNode<T> *leftRoot, const TreeNode<T> *rightRoot)
{
    if (leftRoot == nullptr)
        return rightRoot == nullptr;
    if (rightRoot == nullptr)
        return leftRoot == nullptr;

    return leftRoot->data == rightRoot->data && sameTree(leftRoot->left, rightRoot->left) && sameTree(leftRoot->right, rightRoot->right);
}

// x + 0 = x
// x && true = x
template <typename T>
bool isBSTHelper(const TreeNode<T> *root, T min, T max)
{
    if (root == nullptr)
        return true;

    return (root->left == nullptr || (root->left->data < root->data && root->left->data > min && isBSTHelper(root->left, min, root->data))) &&
            (root->right == nullptr || (root->right->data > root->data && root->right->data < max && isBSTHelper(root->right, root->data, max)));
}

bool isBST(const TreeNode<int> *root)
{
    return isBSTHelper(root, INT_MIN, INT_MAX);
}

// concepts - T

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
bool isBST(const TreeNode<double> *root)
{
    return isBSTHelper(root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
TreeNode<T> *bstFromSortedArrayHelper(std::vector<T> const& vec, size_t start, size_t end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    TreeNode<T> *root = new TreeNode<T>(vec[mid]);
    if (mid > 0)
        root->left = bstFromSortedArray(vec, start, mid - 1);
    root->right = bstFromSortedArray(vec, mid + 1, end);
}

template <typename T>
TreeNode<T>* bstFromSortedArray(std::vector<T> const& vec)
{
    return bstFromSortedArrayHelper(vec, 0, vec.size() - 1);
}

template <typename T>
int search(std::vector<T> const& vec, T elem, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        if (vec[i] == elem)
            return i;
    }
    return -1;
}

// storage duration - static -> static variables, global variables
// data
int v;
template <typename T>
TreeNode<T>* buildTreeHelper(std::vector<T> const &inorder, std::vector<T> const& preorder, size_t inStart, size_t inEnd, size_t& pIndex)
{
    T rootValue = preorder[pIndex];
    pIndex++;
    static int x;
    if (inStart > inEnd)
        return nullptr;

    TreeNode<T> *root = new TreeNode<T>{rootValue};
    if (inStart == inEnd)
        return root;

    int idx = search(inorder, rootValue, inStart, inEnd);
    if (idx != -1)
    {
        if (idx > 0)
            root->left = buildTreeHelper(inorder, preorder, inStart, idx - 1, pIndex);
        root->right = buildTreeHelper(inorder, preorder, idx + 1, inEnd, pIndex);
    }
}

template<typename T>
void bfs(const TreeNode<T> *root)
{

}

template <typename T>
void printGv(const TreeNode<T> *root)
{
    if (root)
    {
        if (root->left) {
            std::cout << root->data << " -> " << root->left->data << std::endl;
            printGv(root->left);
        }
        if (root->right) {
            std::cout << root->data << " -> " << root->right->data << std::endl;
            printGv(root->right);
        }
    }
}

template <typename T>
void printTreeLevels(const TreeNode<T> *root)
{
    // TODO
}

template<typename T>
void zigZag(TreeNode<T> *root)
{

}

int main() {
    TreeNode<int> t5{5};
    TreeNode<int> t4{4};
    TreeNode<int> t3{3};
    TreeNode<int> t2{2, &t4, &t5};
    TreeNode<int> t1{1, &t2, &t3};
//    zigZag(&t1);
    size_t x = 0;
    TreeNode<int> *t = buildTreeHelper(std::vector<int>{8, 3, 9, 1, 5, 2, 4}, std::vector<int>{1, 3, 8, 9, 2, 5, 4}, 0, 6, x);
    printGv(t);
//    std::cout << search(&t1, 7) << std::endl;
//    std::cout << search(&t1, 3) << std::endl;
//    std::cout << minValue(nullptr);
//    printInorder(&t1);
//    printPostorder(&t1);
    return 0;
}
