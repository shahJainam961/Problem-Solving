#include<bits/stdc++.h>
using namespace std;

template <class T>
class Node{
    public:
        T val;
        Node<T>* next;
        
        Node(T value){
            val = value;
            next = NULL;
        }
};

template <class T>
class LinkedList{
    
    private:
        int len;
        Node<T>* head;
    public:
        LinkedList(){
            len = 0;
            head = NULL;
        }

        int size(){
            return len;
        }

        void printList(){
            Node<T>* node = head;
            while(node){
                cout<<node->val<<" ";
                node=node->next;
            }
            cout<<"Done"<<endl;
        }

        void insertAtEnd(T value){
            if(!head){
                head = new Node(value);
                len++;
                return;
            }
            Node<T>* node = head;
            while(node->next!=NULL){
                node = node->next;
            }
            node->next = new Node(value);
            len++;
            return;
        }

        void insertAtStart(T value){
            if(!head){
                head = new Node(value);
                len++;
                return;
            }
            Node<T>* node = new Node(value);
            node->next = head;
            head = node;
            len++;
            return;
        }

        void deleteAtEnd(){
            if(!head) return;
            else if(!head->next){
                head = NULL;
                len--;
                return;
            }
            Node<T>* node = head;
            while(node->next->next!=NULL){
                node = node->next;
            }
            node->next= NULL;
            len--;
            return;
        }

        void deleteAtStart(){
            if(!head) return;
            head = head->next;
            len--;
            return;
        }

};

int main(){
    LinkedList<int>* list1 = new LinkedList<int>();
    list1->insertAtEnd(10);
    list1->insertAtStart(100);
    list1->printList();
    cout<<"list size:"<<list1->size()<<endl;
    list1->insertAtEnd(0);
    list1->printList();
    cout<<"list size:"<<list1->size()<<endl;
    list1->deleteAtEnd();
    list1->printList();
    cout<<"list size:"<<list1->size()<<endl;
    list1->deleteAtStart();
    list1->deleteAtEnd();
    list1->printList();
    cout<<"list size:"<<list1->size()<<endl;
    return 0;
}