#ifndef JOSEPHUSTHREAD_H
#define JOSEPHUSTHREAD_H

#include <QThread>

class Node
{
public:
    int data;
    Node *next;
};

class CircleList
{
public:
    CircleList();
    ~CircleList();
    void createCircleList(int n);
    void traverseNode();
    void deleteFunc(Node *p);
    void deleteNode(int n);
    void insertNode(int n, int data);
    inline int getLength(){ return length;}
    inline bool isEmpty(){ return head == head->next;}
    void run(int start, int m);

private:
    Node *head;
    int length;
};

//class Josephuscore
//{
//public:
//    Josephuscore(){}
//    ~Josephuscore(){}

//    inline int getL(){ return List.getLength();}

////private:
//    CircleList List;
//};



class JosephusThread : public QThread
{
    Q_OBJECT
public:
    explicit JosephusThread(QObject *parent = nullptr){
        status_ = 0;
    }
    ~JosephusThread(){}
    inline int getL() {return List.getLength();}
    CircleList List;

protected:
    void run();

signals:
    void isDone();
    void changeValue(int);

public slots:
    void getValue(int ,int);

private:
    int status_;
};

#endif // JOSEPHUSTHREAD_H
