#include <iostream>
#include <vector>

using namespace std;

class TreeNode
{
public:
     string name;
     TreeNode *child1;
     TreeNode *child2;
     TreeNode *child3;
     TreeNode *next;
};

class Tree
{
public:
     TreeNode *node;
     vector<TreeNode*> children;

     Tree()
     {
          node = new TreeNode;
          node->child1 = node->child2 = node->child3 = node->next = NULL;
     }

     Tree AddSub(const string &name1)
     {
          TreeNode *p = new TreeNode;
          p->name = name1;

          if(node == NULL)
          {
               node = p;
               p->next = NULL;
               children.push_back(node);
          }else{
               node->next = p;
               p->next = NULL;
               children.push_back(node);
          }

          return node;
     }

     /*
     void print(int nest)const
     {
          cout<<string(nest,'\t')<<name<<endl;
          ++nest;
          for(const Tree *node:children) node->print(nest);
     }*/
};

int main()
{
     Tree* root = new Tree("tree name");
     Tree* galaz1 = root->AddSub("galaz 1"); // this function creates a child Tree object and returns pointer to it
     Tree* galaz2 = root->AddSub("galaz 2");
     Tree* galaz3 = root->AddSub("galaz 3");
     Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");
     Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");
     Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");
     Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.2");
     // after execution
     //root->print(0);
}
