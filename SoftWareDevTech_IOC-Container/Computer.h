#ifndef COMPUTER_H
#define COMPUTER_H


#include <iostream>
#include <IProcessor.h>


class Computer                                //  Класс компьютера, включающего в себя процессор
{
protected:
    IProcessor* m_processor;

public:
    Computer(IProcessor* processor)           //  Конструктор
    {
        m_processor = processor;
    }
    void SetProcessor(IProcessor* processor)  //  Сеттер для определения процессора
    {
        m_processor = processor;
    }
    void GetComputerInfo()                    //  Геттер для вывода инф-ии о компьютере (его процессоре)
    {
        m_processor->GetProcessorInfo();
    }
};


#endif // COMPUTER_H
