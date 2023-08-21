#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    int val;
    Node* next;
    Node* prev;
    Node(int value){
        val = value;
        next = NULL;
        prev = NULL;
    }
};

class DLL{
    int len;
    Node* head;
    Node* tail;
public:
    DLL(){
        len = 0;
        head = NULL;
        tail = NULL;
    }

    void insertAtStart(int value){
        len++;
        Node* node = new Node(value);
        if(!head){
            head = node;
            tail = node;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }

    void insertAtEnd(int value){
        len++;
        Node* node = new Node(value);
        if(!head){
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
        return;
    }

    void deleteAtStart(){
        if(!head and !tail) return;
        if(!head->next){
            len--;
            head = NULL;
            tail = NULL;
            return;
        }
        len--;
        Node* tmp = head;
        head = head->next;
        tmp->next = NULL;
        return;
    }

    void deleteAtEnd(){
        if(!head and !tail) return;
        if(!head->next){
            len--;
            head = NULL;
            tail = NULL;
            return;
        }
        len--;
        Node* tmp = tail;
        tail = tail->prev;
        tmp->prev = NULL;
        tail->next = NULL;
        return;
    }

};