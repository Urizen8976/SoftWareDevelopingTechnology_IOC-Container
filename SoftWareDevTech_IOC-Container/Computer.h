#ifndef COMPUTER_H
#define COMPUTER_H


#include <iostream>
#include <iprocessor.h>


class IntelProcessor:public IProcessor
{
};


class AMDProcessor:public IProcessor
{
};


class Computer
{
    IProcessor* Processor;// processor as attribute
public:
    Computer(IProcessor* proc)//constructor with IProcessor as argument
    {
        Processor = proc;
    }
    void SetProc(IProcessor* proc)// Set processor
    {
        Processor = proc;
    }
    void Info()// Output info about processor
    {
        Processor->GetInfo();
    }

};


//написать похожий класс для амд
//написать Iprocessor + добавить в класс компьютер как атрибут


#endif // COMPUTER_H
