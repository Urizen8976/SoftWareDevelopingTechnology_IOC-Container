#ifndef IPROCESSOR_H
#define IPROCESSOR_H


#include <iostream>


enum ProcessorType                          //  Определение двух типов процессоров в перечислении
{  x86 = 86, x64 = 64  };


class IProcessor                            //  Создание абстрактного класса для процессора
{
protected:
    std::string m_version;                  //  Объявление 3-ёх нужных член-данных
    ProcessorType m_type;
    double m_speed;

public:
    virtual void SetProcessorInfo(std::string version, ProcessorType type, double speed) = 0;
    virtual void GetProcessorInfo() = 0;
    virtual ~IProcessor() = default;  //  std::cout << "destructor" << std::endl << std::endl;
};


class IntelProcessor: public IProcessor     //  Конкретный класс IntelProcessor, реализующий абстрактный класс IProcessor
{
public:
    IntelProcessor() = default;             //  Конструктор по умолчанию
    ~IntelProcessor() = default;            //  Деструктор по умолчанию
    void SetProcessorInfo(std::string version, ProcessorType type, double speed) override
    {                                       //  Сеттер
        m_version = version;
        m_type = type;
        m_speed = speed;
    }
    void GetProcessorInfo() override        //  Геттер
    {
        std::cout << "Processor for Version: " << m_version << ", Speed: " << m_speed << ", Type: x" << m_type << "\n";
    }
};


class AMDProcessor: public IProcessor       //  Конкретный класс AMDProcessor, реализующий абстрактный класс IProcessor
{
public:
    AMDProcessor() = default;               //  Конструктор по умолчанию
    ~AMDProcessor() = default;              //  Деструктор по умолчанию
    void SetProcessorInfo(std::string version, ProcessorType type, double speed) override
    {                                       //  Сеттер
        m_version = version;
        m_type = type;
        m_speed = speed;
    }
    void GetProcessorInfo() override        //  Геттер
    {
        std::cout << "Processor for Version: " << m_version << ", Speed: " << m_speed << ", Type: x" << m_type << "\n";
    }
};


#endif // IPROCESSOR_H
