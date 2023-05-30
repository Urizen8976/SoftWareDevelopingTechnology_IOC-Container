#include <QCoreApplication>
#include "Computer.h"
#include "IOC_Container.h"


int IOCContainer::s_nextTypeId = 115094801;


int main(int argc, char *argv[])
{
    /*Работа с IOC-контейнером:
    1. Создать объект IProcessor (используя актуальную реализацию);
    2. Создать объект компьютера;
    3. Внедрить объект IProcessor в компьютер;
    4. Настроить компьютер. */
    IOCContainer injector;                                                           //  Инициализация IOC-контейнера


    //---------------------Example #1-----------------------
    injector.RegisterInstance<IProcessor,AMDProcessor>();                            //  Регистрация сущности (AMD) методом RegisterInstance()
    injector.GetObject<IProcessor>()->SetProcessor("AMD", ProcessorType::x64,5000);  //  Получение из контейнера процессора и установка ему инф-ии
    Computer testComputer(injector.GetObject<IProcessor>().get());                   //  Инициализация компьютера с заданным ранее процессором
    testComputer.Info();                                                             //  Вывод информации о процессоре компьютера


    //---------------------Example #2-----------------------
    injector.RegisterInstance<IProcessor,IntelProcessor>();                          //  Регистрация сущности (Intel) методом RegisterInstance()
    injector.GetObject<IProcessor>()->SetProcessor("Intel",ProcessorType::x86,3222); //  Получение из контейнера процессора и установка ему инф-ии
    Computer cmp(injector.GetObject<IProcessor>().get());                            //  Инициализация компьютера с заданным ранее процессором
    cmp.Info();                                                                      //  Вывод информации о процессоре компьютера
}
