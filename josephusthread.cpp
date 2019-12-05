#include "josephusthread.h"

#include <QTime>
#include <QCoreApplication>
#include <QDebug>

CircleList::CircleList() {
    head = new Node();
    head->next = head;
    head->data = 0;
    length = 0;
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

void CircleList::operation(int start, const int m) {

    Node *p = head;
    for (int i = 0; i < start; ++i)
        p = p->next;
    int count = 1;
    while (length){
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
            v_order.emplace_back(p->next->data);
            qDebug() << "删除： " << p->next->data;
            deleteFunc(p);
            //            traverseNode();
        }
    }
    qDebug() << "operation done and size: " << v_order.size();
}

void JosephusThread::getValue(int n, int y)
{
    qDebug() << "value: " << n << " + " << y;
    emit changeValue(n+y);
}

void JosephusThread::run()
{
    qDebug() << "thread start.";
    qDebug() << "size: " << initial_value_ << "\n";
    List.createCircleList(initial_value_);
//    while (status_ == 0)
//    {
//        qDebug() << "wait for operation() start.";
//        emit isWait();
//    }
//    qDebug() << "operation() start.";
    List.operation(start_value_,circulate_value_);

    std::vector<int> v(List.getVector());
    int value;
    for (std::vector<int>::size_type i=0; i<v.size(); ++i)
    {
        while (status_ == 0);
        if (status_ == 1){
        value = v.at(i);
        qDebug() << "send success: " << value;
        emit sendValue(value);
        QTime t;
        t.start();
        while(t.elapsed()<1000)
            QCoreApplication::processEvents();
        }
    }
    emit isDone();
}


