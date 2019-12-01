#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>

class Josephus
{
public:
    Josephus();
    ~Josephus();
    void SetInitialValue(int value);
    void SetCirculaValue(int value);
    inline int GetInitialValue(){ return initial_value;}
    inline int GetCirculaValue(){ return circulate_value;}
    inline void show(){ qDebug() << "show info.";}

    friend class MainWindow;

private:
    int initial_value;
    int circulate_value;
};

#endif // JOSEPHUS_H
