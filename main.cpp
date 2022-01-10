#include <iostream>
#include <queue>
using namespace std;

template<typename T>

class BTNode{
public:

T data;
BTNode* left;
BTNode* right;

BTNode(T data){
    this->data = data;
    left = NULL;
    right = NULL;
    }
    ~BTNode(){
    delete left;
    delete right;

    }
};
/*BTNode<string>* takeInput(){ // recursive way bad
    string rootData;
    std::cout<<"Enter data"<<std::endl;
    std::cin>>rootData;

    if(rootData== "z"){ // finish
        return NULL;
    }
    BTNode<string>* root = new BTNode<string>(rootData);
    root->left = takeInput();
    root->right = takeInput();

    return root;

}*/
BTNode<string>* takeInputLevelWise(){
    string rootData;
    std::cout<<"Enter root data :"<<std::endl;
    std::cin>>rootData;
    BTNode<string>* root = new BTNode<string>(rootData);
    std::queue<BTNode<string>*> q;
    q.push(root);

    while(!q.empty()){
        BTNode<string>* f = q.front();
        q.pop();

        std::cout<<"Enter Left child of "<< f->data << std::endl;
        string leftChildData;
        std::cin>>leftChildData;
        if(leftChildData != "z"){
            BTNode<string>* child = new BTNode<string>(leftChildData);
            q.push(child);
            f->left = child;
        }
        std::cout<<"Enter Right child of "<< f->data << std::endl;
        string rightChildData;
        std::cin>>rightChildData;
        if(rightChildData != "z"){
            BTNode<string>* child = new BTNode<string>(rightChildData);
            q.push(child);
            f->right = child;
        }

    }
    return root;

}
int counNodes(BTNode<string> *root)
{
    BTNode<string> *current, *pre;

    // Initialise count of nodes as 0
    int count = 0;

    if (root == NULL)
        return count;

    current = root;
    while (current != NULL)
    {
        if (current->left == NULL)
        {
            // Count node if its left is NULL
            count++;

            // Move to its right
            current = current->right;
        }
        else
        {
            /* Find the inorder predecessor of current */
            pre = current->left;

            while (pre->right != NULL &&
                   pre->right != current)
                pre = pre->right;

            /* Make current as right child of its
               inorder predecessor */
            if(pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

                /* Revert the changes made in if part to
                   restore the original tree i.e., fix
                   the right child of predecessor */
            else
            {
                pre->right = NULL;

                // Increment count if the current
                // node is to be visited
                count++;
                current = current->right;
            } /* End of if condition pre->right == NULL */
        } /* End of if condition current->left == NULL*/
    } /* End of while */

    return count;
}
/* Function to find median in O(n) time and O(1) space
   using Morris Inorder traversal*/
string findMedian(BTNode<string> *root)
{
    if (root == NULL)
        return 0;

    int count = counNodes(root);
    int currCount = 0;
    BTNode<string> *current = root, *pre, *prev;

    while (current != NULL)
    {
        if (current->left == NULL)
        {
            // count current node
            currCount++;

            // check if current node is the median
            // Odd case
            if (count % 2 != 0 && currCount == (count+1)/2)
                return prev->data;

                // Even case
            else if (count % 2 == 0 && currCount == (count/2)+1)
                return (prev->data + current->data);

            // Update prev for even no. of nodes
            prev = current;

            //Move to the right
            current = current->right;
        }
        else
        {
            /* Find the inorder predecessor of current */
            pre = current->left;
            while (pre->right != NULL && pre->right != current)
                pre = pre->right;

            /* Make current as right child of its inorder predecessor */
            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }

                /* Revert the changes made in if part to restore the original
                  tree i.e., fix the right child of predecessor */
            else
            {
                pre->right = NULL;

                prev = pre;

                // Count current node
                currCount++;

                // Check if the current node is the median
                if (count % 2 != 0 && currCount == (count+1)/2 )
                    return current->data;

                else if (count%2==0 && currCount == (count/2)+1)
                    return (prev->data+current->data);

                // update prev node for the case of even
                // no. of nodes
                prev = current;
                current = current->right;

            } /* End of if condition pre->right == NULL */
        } /* End of if condition current->left == NULL*/
    } /* End of while */
}

void inOrder(BTNode<string> *root) {
    // Base case
    if (root == NULL) {
        return;
    }
    // Travel the left sub-tree first.
    inOrder(root->left);
    // Print the current node value
    std::cout<<root->data;
    // Travel the right sub-tree next.
    inOrder(root->right);
}
void printTree(BTNode<string>*root){ //recursive
    if(root==NULL){ /// base case
        return;
    }
    std::cout<<root->data<<":";
    if(root->left!=NULL){
        std::cout<<"L"<<root->left->data;
    }
    if(root->right!=NULL){
        std::cout<<"R"<<root->right->data;
    }
    std::cout<<std::endl;
    printTree(root->left);
    printTree(root->right);
}
string minValue(BTNode<string>* root)
{
    BTNode<string>* current = root;

/* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
    return(current->data);
}
int countNonLeafNodes(BTNode<string>* root) { // T =(n) S = o(nv )
    if (root == NULL) {
        return 0;
    }
    return countNonLeafNodes(root->left) + countNonLeafNodes(root->right) + 1;
}
int countNonleaf(BTNode<string>* root)
{
    // Base cases.
    if (root == NULL || (root->left == NULL &&
                         root->right == NULL))
        return 0;

    // If root is Not NULL and its one of its
    // child is also not NULL
    return 1 + countNonleaf(root->left) +
           countNonleaf(root->right);
}

bool searchNode(BTNode<string>* root, string key){
    if(root ==NULL){
        return false;

    }
    if(root-> data == key){
        return true;
    }

    return searchNode(root->left,key) || searchNode(root->right,key);


}
bool hasPath(BTNode<string> *root, std::vector<string>& arr, string x)
{
    // if root is NULL
    // there is no path
    if (!root)
        return false;

    // push the node's value in 'arr'
    arr.push_back(root->data);

    // if it is the required node
    // return true
    if (root->data == x)
        return true;

    // else check whether the required node lies
    // in the left subtree or right subtree of
    // the current node
    if (hasPath(root->left, arr, x) ||
        hasPath(root->right, arr, x))
        return true;

    // required node does not lie either in the
    // left or right subtree of the current node
    // Thus, remove current node's value from
    // 'arr'and then return false
    arr.pop_back();
    return false;
}
// function to print the path from root to the
// given node if the node lies in the binary tree
void printPath(BTNode<string>*root, string x)
{
    // vector to store the path
    std::vector<string> arr;

    // if required node 'x' is present
    // then print the path
    if (hasPath(root, arr, x))
    {
        for (int i=0; i<arr.size()-1; i++)
            std::cout << arr[i] << "->";
        std::cout << arr[arr.size() - 1];
    }

        // 'x' is not present in the binary tree
    else
        std::cout << "No Path";
}


//1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
// lorcan sinead faidh rory joy micheal siobha james
int main() {

   BTNode<string>* root = takeInputLevelWise();

   printTree(root);
   std::cout<<"Searching for joy:"<<std::endl;
   printPath(root, "joy");
   cout<<endl<<minValue(root)<<endl;
   cout<<endl<<countNonLeafNodes(root)<<endl;
   cout<<endl<<findMedian(root)<<endl;

   /*std::cout<<"Number of nodes in BST:"<<countNodes(root)<<std::endl;
   if(searchNode(root,8)){
       std::cout<<"found"<<std::endl;
   }else{
       std::cout<<"not found"<<std::endl;
   }*/
   delete root;
   return 0;
}



