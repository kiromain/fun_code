#include <iostream>
#include <vector>

using namespace std;

class Tree
{
public:
     string name ;
     vector<Tree*> children;

     Tree(const string &name):name(name) { }

     Tree* AddSub(const string &name)
     {
          Tree *node= new Tree(name);
          children.push_back(node);
          return node;
     }


     void print(int nest)const
     {
          cout<<string(nest,'\t')<<name<<endl;
          ++nest;
          for(const Tree *node:children) node->print(nest);
     }
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
     root->print(0);
}
