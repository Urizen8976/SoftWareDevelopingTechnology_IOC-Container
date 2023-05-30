#include <QCoreApplication>
#include "Computer.h"
#include "IOC_Container.h"


int IOCContainer::s_nextTypeId = 115094801;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IOCContainer injector;//add IOC container
    injector.RegisterInstance<IProcessor,AMDProcessor>();// add object of AMDProcessor Class
    injector.GetObject<IProcessor>()->SetProcessor("AMD",ProcessorType::x64,5000);//initialization processor

    //TEST_1
    Computer testComputer(injector.GetObject<IProcessor>().get());//create computer by created processor
    testComputer.Info();// get info about processor

    //DATA FOR TEST_2
    injector.RegisterInstance<IProcessor,IntelProcessor>();
    injector.GetObject<IProcessor>()->SetProcessor("Intel", ProcessorType::x86,3222);

    //TEST_2
    Computer cmp(injector.GetObject<IProcessor>().get());
    cmp.Info();
}
