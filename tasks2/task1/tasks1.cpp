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
     void add(T data);
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
void List< T >::add( T data )
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
     else exit(1);

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

int main()
{
     List<int> list1;

     list1.add(5);
     list1.add(6);
     list1.add(7);
     list1.add(9);
     list1.add(11);

     list1.printlist();

     cout<<"Number of elements: ";
     cout<<list1.getcounts()<<endl;

     cout<<"Size of the list in bytes: ";
     cout<<list1.getsize()<<endl;

     cout<<"Return a number from the top: ";
     list1.getfromtop();

     cout<<"Return a number from the top: ";
     list1.getfromtop();

}
