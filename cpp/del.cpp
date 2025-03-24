#include <iostream>
#include <sstream>
using namespace std;
typedef struct Num {
  int data;
  struct Num *next;
} Num,*Nums;
typedef struct Node {
  Nums head;
  Nums tail;
  int length=0;
} Node,*Nodes;
int init(Nodes &node) {
  node->head=new Num;
  node->head->next=nullptr;
  node->tail=node->head;
  return 0;
}
int TailInsert(Nodes &node,int num) {
  node->tail->next=new Num;
  node->tail=node->tail->next;
  node->tail->data=num;
  node->tail->next=nullptr;
  node->length++;
  return 0;
}
int del(Nodes &node) {
  Nums current=node->head->next;
  while(current&&current->next) {
    if(current->data==current->next->data) {
      if(current->next==node->tail) {
        node->tail=current;
      }
      Nums t=current->next;
      current->next=t->next;
      delete t;
      node->length--;
    }
    else current=current->next;
  }
  return 0;
}
/*int print(Nodes &node) {
  Nums current=node->head->next;
  while(current) {
    cout<<current->data<<" ";
    current=current->next;
  }
  return 0;
}*/
int des(Nodes &node) {
  Nums current=node->head;
  while(current) {
    Nums t=current;
    current=current->next;
    delete t;
  }
  return 0;
}
int main() {
  Nodes node=new Node;
  init(node);
  int num;
  string line;
  if(getline(cin,line)) {
    istringstream iss(line);
    while(iss>>num) {
      TailInsert(node,num);
    }
  }
  del(node);
  //print(node);
  cout<<node->length;
  des(node);
  delete node;
  return 0;
}