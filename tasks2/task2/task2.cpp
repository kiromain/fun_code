#include <iostream>

using namespace std;

template <class T> class Node
{
public:
     T data;
     Node *next;
};

template <class T> class List
{
public:
     void printlist();
     void addLIFO(T data);
     int getcounts();
     T getfromtop();
     int getsize();

     Node< T > *head, *tail;

     List()
     {
          head = NULL;
          tail = NULL;
     }
};

template <class T>
void List< T >::addLIFO( T data )
{
     Node <T> *p = new Node<T>;
     p->data = data;

     if(head == NULL){
          head  = new Node<T>;
          head = p;
          tail = head;
     }else{
          p->next = NULL;
          tail->next = p;
          tail = tail->next;
     }
}

template <class T>
void List< T >::printlist()
{
     Node<T> *current;

     current = head;
     cout<<"Inserted elements: ";
     if ( current == NULL ) return;
     while(current != NULL){
          cout<<current->data<<" ";
          current = current->next;
     }
     cout<<endl;
}

template <class T>
T List< T >::getfromtop()
{
     Node<T> *current = head;

     while(current->next->next!=NULL) current=current->next;

     if(current->next!=NULL) cout<<current->next->data<<endl;

     if(head!=NULL){
          if(head->next == NULL){
               head = NULL;
          }else{
               Node<T> *temp = head;
               while(temp->next->next != NULL){
                    temp = temp->next;
               }
               Node<T> *lastnode = temp->next;
               temp->next = NULL;
               delete lastnode;
          }
     }
}

template <class T>
int List< T >::getcounts()
{
     Node<T> *current;

     current = head;
     int counts = 0;

     while(current != NULL){
          counts++;
          current = current->next;
     }

     return counts;
}

template <class T>
int List< T >::getsize()
{
     Node<T> *current;
     current = head;

     int sizeinbytes=0;
     while(current != NULL){
          sizeinbytes += sizeof(current);
          current = current->next;
     }
     return sizeinbytes;
}

// zadanie 2
template <class T>
class Inher : public List<T>
{
public:

     T getfrombottom()
     {
          Node<T> *current;
          current = this->head;

          if(current!=NULL) cout<<current->data<<endl;
          else exit(1);

          Node<T> *temp = this->head;
          this->head = this->head->next;

          delete temp;
     }

     T getfromanywhere(int x)
     {
          Node<T> *current = this->head;
          if(this->head == NULL) cout<<"List is empty"<<endl;

          if(x == 0)
          {
               cout<<current->data;
               this->head = current->next;
               delete current;
          }

          for(int i=0;current != NULL && i < x-2; i++) current = current->next;

          cout<<current->next->data<<endl;

          Node<T> *next = current->next->next;
          delete current->next;

          current->next = next;
     }

     void addmiddle(T data,int x)
     {
          Node<T> *new_ele = new Node<T>();
          new_ele->data = data;
          new_ele->next = NULL;

          if(x == 1)
          {
               new_ele->next = this->head;
               this->head = new_ele;
          }else{
               Node<T> *temp = this->head;

               while(--x > 1) temp = temp->next;

               new_ele->next = temp->next;
               temp->next = new_ele;

          }
     }

};


int main()
{
     List<int> list1;

     /*list1.addLIFO(5);
     list1.addLIFO(6);
     list1.addLIFO(7);
     list1.addLIFO(9);
     list1.addLIFO(11);

     list1.printlist();

     cout<<"Number of elements: ";
     cout<<list1.getcounts()<<endl;

     cout<<"Return a number from the top: ";
     list1.getfromtop();

     cout<<"Return a number from the top: ";
     list1.getfromtop();

     cout<<"Size of the list in bytes: ";
     cout<<list1.getsize()<<endl;*/

     //zadanie 2
     Inher<int> inher;

     inher.addLIFO(5);
     inher.addLIFO(6);
     inher.addLIFO(7);
     inher.addLIFO(9);
     inher.addLIFO(11);

     inher.printlist();

     int x;
     cout<<"Choose a position from 1 to "<<inher.getcounts()<<" you want to return: ";
     cin>>x;

     if(x>inher.getcounts()) cout<<"The number is to big"<<endl;
     else if(x<1) cout<<"The number is invalid"<<endl;
     else{
          cout<<"The number from "<<x<<" position is: ";
          inher.getfromanywhere(x);
     }
     inher.printlist();

     int y;
     cout<<"Choose a position from 1 to "<<inher.getcounts()<<" you want to insert a data: ";
     cin>>y;

     if(y>inher.getcounts()) cout<<"The number is to big"<<endl;
     else if(y<1) cout<<"The number is invalid"<<endl;
     else inher.addmiddle(15,y);
     inher.printlist();

     cout<<"Return a number from the bottom: ";
     inher.getfrombottom();
     inher.printlist();

}
