#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Tree
{
private:
     string name;
     vector<shared_ptr<Tree>> children;
public:
     Tree(const string &name):name(name) { }

     shared_ptr<Tree> AddSub(const string &name)
     {
          shared_ptr<Tree> node=make_shared<Tree>(name);
          children.push_back(node);
          return node;
     }
     void print(int nesting=0)const
     {
          cout<<string(nesting,'\t')<<name<<endl;
          ++nesting;
          for(const shared_ptr<Tree> node:children) node->print(nesting);
     }
};

int main()
{
     shared_ptr<Tree> root=make_shared<Tree>("nazwa drzewa");
     shared_ptr<Tree> galaz1 = root->AddSub("galaz 1");
     shared_ptr<Tree> galaz2 = root->AddSub("galaz 2");
     shared_ptr<Tree> galaz3 = root->AddSub("galaz 3");
     shared_ptr<Tree> galaz1_1 = galaz1->AddSub("galaz 1.1");
     shared_ptr<Tree> galaz2_1 = galaz2->AddSub("galaz 2.1");
     shared_ptr<Tree> galaz2_2 = galaz2->AddSub("galaz 2.2");
     shared_ptr<Tree> galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.2");
     root->print();
     return 0;
}
