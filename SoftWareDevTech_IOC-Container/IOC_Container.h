#ifndef IOC_CONTAINER_H
#define IOC_CONTAINER_H


#include <functional>
#include <iostream>
#include <memory>
#include <map>
#include <string>
using namespace std;


class IOCContainer
{
    static int s_nextTypeId;                     //  Статическая переменная, указывающая на идентификатор следующего типа, который будет выделен
    template<typename T>
    static int GetTypeID()                       //  Шаблонная функция для определенного типа T, возвращающая значение идентификатора типа
    {
        static int typeId = s_nextTypeId++;      //  Экземпляр статической локальной переменной для каждого типа
        return typeId;
    }

public:
    class FactoryRoot                            //  Абстрактный базовый класс для всех фабрик, предоставляющих способы создания объектов
    {  public: virtual ~FactoryRoot() {}  };


    std::map<int, std::shared_ptr<FactoryRoot>> m_factories;   //  Коллекция фабрик для определенных типов объектов


    template<typename T>
    class CFactory : public FactoryRoot                        //  Фабрика определенного типа T, реализующая абстрактный класс FactoryRoot
    {
        std::function<std::shared_ptr<T>()> m_functor;         //  Функтор для создания и возврата объекта - объект, вызываемый как функция
    public:                                                    //  (Пустой шаблонный класс)
        ~CFactory() {}
        CFactory(std::function<std::shared_ptr<T>()> functor): m_functor(functor) {}
        std::shared_ptr<T> GetObject() {  return m_functor();  }
    };


    template<typename T> std::shared_ptr<T> GetObject()                     //  Метод получения экземпляра из контейнера
    {
        auto typeId = GetTypeID<T>();                                       //  Получение typeId фабрики
        auto factoryBase = m_factories[typeId];                             //  Получение необходимой нам фабрики
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);  //  Приведение указателя к типу конкретной фабрики
        return factory->GetObject();                                        //  Возвращение объекта, созданного заданным функтором фабрики
    }


    //Регистрация экземпляров класса (ЭК)
    // Самая простая реализация - регистрация функтора (принимает интерфейсный тип и переменное число аргументов)
    template<typename TInterface, typename... TS>                 //  Регистрация функтора в IoC-К для создания объектов типа TInterface
    void RegisterFunctor( std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)> functor)
    {
        m_factories[GetTypeID<TInterface>()]                      //  Обращение к map'у фабрик для фабрики типа TInterface
        =  std::make_shared<CFactory<TInterface>>(                //  Создание ЭК CFactory<TInterface> с помощью make_shared
        [ = ] { return functor(GetObject<TS>()...); });           // Регистрация функтора лямбда-выражением, передавая ему все объекты из фабрик TS
    }


    template<typename TInterface>                                 //  Регистрация одного экземпляра объекта (ЭО)
    void RegisterInstance(std::shared_ptr<TInterface> t)          // Метод - аналогичный RegisterFunctor, но регистрирует только лишь один ЭО
    {
        m_factories[GetTypeID<TInterface>()]
        =  std::make_shared<CFactory<TInterface>>(
        [ = ] { return t; });
    }


    template<typename TInterface, typename... TS>                 //  Перегрузка функции RegisterFunctor, вызов по указателю на functor
    void RegisterFunctor(std::shared_ptr<TInterface> (*functor)(std::shared_ptr<TS>... ts))
    {
        RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)>(functor));
    }


    template<typename TInterface, typename TConcrete, typename... TArguments> //  Фабрика, вызывающая конструктор, для каждого экземпляра
    void RegisterFactory()                                                    //  Регистрация фабрики создания объектов с TInterface-ом - интерфейс
    {                                               //TConcrete  - конк. реал. интерфейса, TArguments - набор параметров для конструктора TConcrete
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments>... ts)>(
                [](std::shared_ptr<TArguments>... arguments) -> std::shared_ptr<TInterface>
                {
                    return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
                }
            )
        );
    }


    template<typename TInterface, typename TConcrete, typename... TArguments>  //  Перегрузка функции RegisterInstance, классы нижнего уровня
    void RegisterInstance() {                                                  //  (и аргументы) передаются по другому
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }
};


#endif // IOC_CONTAINER_H
