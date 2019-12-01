#include "josephus.h"

Josephus::Josephus(): initial_value(0), circulate_value(0)
{
}

Josephus::~Josephus()
{
}

void Josephus::SetInitialValue(int value)
{
    initial_value = value;
}

void Josephus::SetCirculaValue(int value)
{
    circulate_value = value;
}

