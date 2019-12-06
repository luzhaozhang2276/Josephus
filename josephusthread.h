#ifndef JOSEPHUSTHREAD_H
#define JOSEPHUSTHREAD_H

#include <QThread>
#include <vector>

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
//    inline int getStatus() { return status_;}
//    inline bool setStatus(int flag) {
//        status_ = flag;
//        return true;
//    }
    inline std::vector<int> getVector() {return v_order;}
    void operation(int start, int m);

private:
    Node *head;
    int length;
    int status_;
    std::vector<int> v_order;
};

class JosephusThread : public QThread
{
    Q_OBJECT
public:
    explicit JosephusThread(QObject *){}
    ~JosephusThread(){}
    inline int getL() {return List.getLength();}
//    inline bool getInitialFlag() {return initial_flag_;}
    inline bool getStop() {return stop_;}
    inline bool getStatus() {return status_;}
    inline int getInitialValue() {return initial_value_;}
    inline int getCircluaValue() {return circulate_value_;}
    inline int getStartValue() {return start_value_;}
//    inline void setInitialFlag(bool value) {initial_flag_ = value;}
    inline void setStop(bool value) {stop_ = value;}
    inline void setStatus(bool value) {status_ = value;}
    inline void setInitialValue(int value) {initial_value_ = value;}
    inline void setCirculaValue(int value) {circulate_value_ = value;}
    inline void setStartValue(int value) {start_value_ = value;}
    inline void setSpeedValue(int value) {speed_value_ = value;}
    inline void setRemainValue(std::vector<int>::size_type value) {remain_value_ = value;}

    CircleList List;

protected:
    void run();

signals:
    void isDone();
    void isWait();
    void changeValue(int);
    void sendValue(int);

public slots:
    void getValue(int ,int);

private:
    bool stop_{0};
    bool status_{0};            // 运行状态(标志位)
    int initial_value_{9};     // 初始人数
    int circulate_value_{3};   // 循环参数(报数次数)
    int start_value_{1};       // 开始序号
    int speed_value_{0};
    std::vector<int>::size_type remain_value_{0};
};

#endif // JOSEPHUSTHREAD_H
