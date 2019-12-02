#include "josephusthread.h"

#include <QDebug>
//#include <vector>

CircleList::CircleList() {
    head = new Node();
    head->next = head;
    head->data = 0;
    length = 0;
    v_order = new std::vector<int>;
}

CircleList::~CircleList() {
    delete(head);
}

void CircleList::createCircleList(int n) {
    length = n;
    Node *p, *q;    // p:当前节点   q:新节点
    p = head;
    for (int i = 1; i <= length; ++i) {
        q = new Node();
        q->data = i;
        p->next = q;
        p = q;
    }
    p->next = head;
}

void CircleList::traverseNode() {
    Node *p;
    p = head->next;

    while (p != head){
        p = p->next;
    }
}

void CircleList::deleteFunc(Node *p) {
    Node *q = p->next;
    p->next = q->next;
    delete q;
    length--;
}

void CircleList::deleteNode(int n) {
    Node *p;
    p = head;
    for (int i = 0; i < n; ++i)
        p = p->next;
    deleteFunc(p);
}

void CircleList::insertNode(int n, int data) {
    Node *q, *p = new Node();
    p->data = data;
    q = head;
    for (int i = 1; i < n; ++i)
        q = q->next;
    p->next = q->next;
    q->next = p;
    length++;
}

// 应改成递归
void CircleList::operation(int start, const int m) {
    Node *p = head;
    for (int i = 0; i < start; ++i)
        p = p->next;
    int count = 1;
    while (length){
        if (getStatus() != 1)
            break;
        else if (getStatus() == 1)
        {
            if ( p == head) {
                p = p->next;
                if (length != 1)
                    count++;
            }
            else if (count != m-1){
                p = p->next;
                if (p != head || length == 1) {
                    count++;
                }
            }
            else{
                count = 0;
                if (p->next == head)
                    p = head;
                // 需要删除的节点 p->next
                //                sleep(1);
                v_order->emplace_back(p->next->data);
                deleteFunc(p);
                //            traverseNode();
            }
        }
    }
}

void JosephusThread::getValue(int n, int y)
{
    qDebug() << "value: " << n << " + " << y;
    emit changeValue(n+y);
}

void JosephusThread::run()
{
    List.operation(start_value_,circulate_value_);
    emit sendpVector(List.getVector());
    emit isDone();
}


