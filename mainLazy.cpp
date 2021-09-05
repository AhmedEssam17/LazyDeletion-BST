#include <iostream>
using namespace std;
#include "LazyBST.h"

int main(int argc, const char* argv[]) 
{
    cout << "<<Constructing an empty tree>>" << endl;
    LazyBST lazyTree;
    cout << "Check if it is empty : " << endl;
    if (lazyTree.empty())
        cout << "Tree is empty" << endl;
    else
        cout << "Error in empty function" << endl;
    
    cout << endl;
    cout << "<<Now inserting 1000 random numbers>>" << endl;
    for (int i = 1; i <= 1000; i++)
    {
        int x = rand() % 1000 + 1;
        lazyTree.insert(x);
    }

    cout << endl;
    cout << "Height of BST = " << lazyTree.height() << endl;
    cout << endl;
    cout << "Size after insertion = " << lazyTree.size() << endl;
    cout << endl;
    cout << "<<Now erasing 100 random numbers>>" << endl;
    for (int i = 1; i <= 100; i++)
    {
        int x = rand() % 1000 + 1;
        lazyTree.erase(x);
    }

    cout << endl;
    cout << "Size after tagging nodes as erased : " << lazyTree.size() << endl;
    cout << endl;
    
    cout << "<<Now presenting the BST with breadh-first traversal>>" << endl;
    lazyTree.breadth_first_traversal();
    cout << endl;
    cout << endl;    
    
    cout << "<<Now checking the Front and Back of the BST>>" << endl;
    cout << "Front = " << lazyTree.front() << endl;
    cout << "Back = " << lazyTree.back() << endl;
    cout << endl;

    cout << "Size before clean : " << lazyTree.size() << endl;
    
    cout << endl;
    cout << "<<Now testing the clean function>>" << endl;
    lazyTree.clean();
    lazyTree.breadth_first_traversal();
    cout << endl;
    cout << endl;

  //  cout << "<<Graphical display of the Tree>>" << endl;
  //  lazyTree.print2D();

    cout << "Size before clear : " << lazyTree.size() << endl;

    cout << endl;
    cout << "<<And finally the clear function to delete all nodes>>" << endl;
    lazyTree.clear();
    cout << "Size after clear : " << lazyTree.size() << endl;
    cout << endl;
    cout << "Check if the tree is empty after using the clear function : " << endl;

    
    if (lazyTree.empty())
        cout << "Tree is empty" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;
    cout << endl;
    cout << "Project done" << endl;
    //Test
    
    return 0;
}