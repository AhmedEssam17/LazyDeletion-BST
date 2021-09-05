#include "LazyBST.h"
#include <iostream>
#include<queue>
#include<list>
#include<cstdlib>
#define COUNT 10
using namespace std;

LazyBST::LazyBST() : root(0), mySize(0), taggedSize(0)
{
    //Empty constructor
}

bool LazyBST::empty()
{
    return mySize == 0;
}

int LazyBST::size()
{
    return mySize - taggedSize;
}

int LazyBST::height()
{
    return heightPriv(root);
}

int LazyBST::heightPriv(NodePointer root)
{
    int h;
    LazyBST::NodePointer tree = root;
    if (tree == 0)
        return 0;
    int leftH = heightPriv(tree->L);
    int rightH = heightPriv(tree->R);
    if (leftH > rightH)
        h = leftH + 1;
    else
        h = rightH + 1;
    return h;
}

bool LazyBST::member(ElementType const& item)
{
    bool found = false;
    NodePointer tree = root;
    NodePointer parent = NULL;
    search(item, found, tree, parent);

    if (found)          //found
    {
        if (tree->tagged)          //tagged
            return false;
        else                       //untagged
            return true;
    }
    return false;       //not found
}

ElementType LazyBST::front()
{
    LazyBST::NodePointer tree = root;
    int frontItem = 0;
    while (tree != NULL)
    {
        if (!(tree->tagged))
            frontItem = tree->data;
        tree = tree->L;
    }
    return frontItem;
}

ElementType LazyBST::back()
{
    LazyBST::NodePointer tree = root;
    int backItem = 0;
    while (tree != NULL)
    {
        if (!(tree->tagged))
            backItem = tree->data;
        tree = tree->R;
    }
    return backItem;
}

void LazyBST::breadth_first_traversal()
{
    if (root == NULL)
        return;
    queue <NodePointer> q;
    q.push(root);
    while (!q.empty()) {
        NodePointer temp = q.front();

        if (temp->tagged == false)
            cout << temp->data << " ";
        else
            cout << temp->data << "x" << " ";

        if (temp->L != NULL)
            q.push(temp->L);

        if (temp->R != NULL)
            q.push(temp->R);
        q.pop();
    }
}

void LazyBST::search(ElementType item, bool& found, NodePointer& tree, NodePointer& parent)
{
    tree = root;
    parent = 0;
    found = false;
    while (!found && tree != 0)
    {
        if (item < tree->data)         //Drop to the left of the tree
        {
            parent = tree;
            tree = tree->L;
        }
        else if (tree->data < item)    //Drop to the right of the tree
        {
            parent = tree;
            tree = tree->R;
        }
        else                           //found
            found = true;
    }
}

bool LazyBST::insert(ElementType item)
{
    bool found = false;
    NodePointer tree = root;
    NodePointer parent = NULL;

    //Check if it is an empty tree
    if (tree == NULL)
    {
        root = new Node(item);
        mySize++;
        return true;
    }

    //Check if the item is found tagged or not untagged
    search(item, found, tree, parent);
    if (found)          //found
    {
        if (tree->tagged)                        //tagged
        {
            tree->tagged = 0;
            taggedSize--;
            //Remove from the deleted list
            std::list<NodePointer>::iterator it = std::find(deleted.begin(), deleted.end(), tree);
            deleted.erase(it);
            return true;
        }
        else                                    //untagged
            return false;
    }

    //Not found >> New insertion
    if (item < parent->data)           //insert in left
    {
        parent->L = new Node(item);
        mySize++;
        return true;
    }
    else if (item > parent->data)      //insert in right
    {
        parent->R = new Node(item);
        mySize++;
        return true;
    }
}

bool LazyBST::erase(ElementType item)
{
    bool found = false;
    NodePointer tree = root;
    NodePointer parent = NULL;

    //Check if it is an empty tree
    if (tree == NULL)
    {
        return false;
    }

    //Check if the item is found tagged or not untagged
    search(item, found, tree, parent);
    if (found)          //found
    {
        if (tree->tagged)                        //tagged
        {
            return false;
        }
        else                                    //untagged
        {
            tree->tagged = true;
            taggedSize++;
            //Add to the deleted list
            deleted.push_front(tree);
            return true;
        }
    }
    //Not found >> Do nothing
    if (!found)
        return false;
}

void LazyBST::clear()
{
    clearPriv(root);
}

void LazyBST::clearPriv(NodePointer ptr)
{
    if (ptr == NULL)
        return;
    clearPriv(ptr->L);
    clearPriv(ptr->R);
    if (ptr->tagged)
        taggedSize--;
    mySize--;
    delete ptr;
}

void LazyBST::clean()
{
    cleanPriv(root);
}

void LazyBST::cleanPriv(NodePointer ptr)
{
    while (deleted.size() != 0)
    {
        NodePointer ptr = deleted.front();
        remove(ptr->data);
        deleted.pop_front();
    }
}

void LazyBST::remove(ElementType item)
{
    bool found = false;
    NodePointer tree = new Node();
    NodePointer parent = new Node();
    search(item, found, tree, parent);

    //Not found >> Do nothing
    if (!found)
    {
        return;
    }

    //Check if it has 2 children >> Convert it to Case Leaf node or 1 child
    if (tree->L != 0 && tree->R != 0)
    {
        NodePointer xTree = tree->R;
        parent = tree;
        while (xTree->L != 0)
        {
            parent = xTree;
            xTree = xTree->L;
        }
        if (xTree->tagged == false)
            tree->tagged = 0;
        tree->data = xTree->data;
        tree = xTree;
    }

    //Perform the normal way of Leaf node or 1 child deletion
    NodePointer subtree = tree->L;
    if (subtree == 0)
        subtree = tree->R;
    if (parent == 0)
        root = subtree;
    else if (parent->L == tree)
        parent->L = subtree;
    else
        parent->R = subtree;
    delete tree;
    taggedSize--;
    mySize--;
}

void LazyBST::print2D()
{
    // Pass initial space count as 0  
    print2DPriv(root, 0);
}

void LazyBST::print2DPriv(Node* root, int space)
{
    // Base case  
    if (root == NULL)
        return;

    // Increase distance between levels  
    space += COUNT;

    // Process right child first  
    print2DPriv(root->R, space);

    // Print current node after space  
    // count  
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    // Process left child  
    print2DPriv(root->L, space);
}