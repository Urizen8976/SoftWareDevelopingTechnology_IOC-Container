#ifndef IPROCESSOR_H
#define IPROCESSOR_H


#include <iostream>


enum ProcessorType  //enumeration for type of processor (84 and 64 for correct output couse its enum)
{ x86 = 86,
  x64 = 64
};


//abstract class of Processor
class IProcessor
{
protected:
    std::string Version;
    ProcessorType Type;
    double Speed;

public:
    IProcessor(){}// default constructor

    //Setter
    void SetProcessor(std::string version, ProcessorType type, double speed)
    {
        Version = version;
        Type = type;
        Speed = speed;
    }

    //Getter
    void GetInfo()
    {
        std::cout << "Processor for " << Version << " Speed: " << Speed << " Type: x" << Type << "\n";
    }
    virtual ~IProcessor(){}
};


#endif // IPROCESSOR_H
