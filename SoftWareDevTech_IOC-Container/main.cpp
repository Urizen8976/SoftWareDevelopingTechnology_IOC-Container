#include <QCoreApplication>
#include "Computer.h"
#include "IOC_Container.h"


int IOCContainer::s_nextTypeId = 115094801;


int main()
{
    /*Работа с IOC-контейнером:
    1. Создать объект IProcessor (используя актуальную реализацию);
    2. Создать объект компьютера;
    3. Внедрить объект IProcessor в компьютер;
    4. Настроить компьютер. */
    IOCContainer injector;                                                                //  Инициализация IOC-контейнера


    //---------------------Example #1-----------------------
    injector.RegisterInstance<IProcessor,AMDProcessor>();                                 //  Регистрация сущности (AMD) методом RegisterInstance()
    injector.GetObject<IProcessor>()->SetProcessorInfo("AMD", ProcessorType::x64,5000);   //  Получение из конт-ра процессора и установка ему инф-ии
    Computer test1Computer(injector.GetObject<IProcessor>().get());                       //  Инициализация компьютера с заданным ранее процессором
    test1Computer.GetComputerInfo();                                                      //  Вывод информации о процессоре компьютера


    //---------------------Example #2-----------------------
    injector.RegisterInstance<IProcessor,IntelProcessor>();                               //  Регистрация сущности (Intel) методом RegisterInstance()
    injector.GetObject<IProcessor>()->SetProcessorInfo("Intel",ProcessorType::x86,3222);  //  Получение из конт-ра процессора и установка ему инф-ии
    Computer test2Computer(injector.GetObject<IProcessor>().get());                       //  Инициализация компьютера с заданным ранее процессором
    test2Computer.GetComputerInfo();                                                      //  Вывод информации о процессоре компьютера
}
