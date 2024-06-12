// Given a binary tree, print the inorder traversal of the binary tree
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

struct node
{
  int val;
  node *left;
  node *right;
  node(int val) : val(val), left(nullptr), right(nullptr) {}
  node(int val, node *left, node *right) : val(val), left(left), right(right) {}
};

vector<int> inorderRec(node *root)
{
  if (root == nullptr)
  {
    return vector<int>();
  }

  auto left = inorderRec(root->left);
  int val = root->val;
  auto right = inorderRec(root->right);

  left.push_back(val);
  left.insert(left.end(), right.begin(), right.end());
  return left;
}

vector<int> inorderWithoutRec(node *root)
{
  if (root == NULL)
  {
    return vector<int>();
  }

  vector<int> inorder;
  stack<node *> s;
  while (root != nullptr)
  {
    s.push(root);
    root = root->left;
  }

  while (!s.empty())
  {
    auto tnode = s.top();
    inorder.push_back(tnode->val);
    s.pop();
    if (tnode->right != nullptr)
    {
      s.push(tnode->right);
      tnode = tnode->right;
      while (tnode->left != nullptr)
      {
        s.push(tnode->left);
        tnode = tnode->left;
        continue;
      }
    }
  }

  return inorder;
}

void printVec(vector<int> arr)
{
  for (int i = 0; i < arr.size(); i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int main()
{
  auto tree = new node(1, new node(2), new node(3));
  auto inorderRecArr = inorderRec(tree);
  auto inorderArr = inorderWithoutRec(tree);
  printVec(inorderArr);
}