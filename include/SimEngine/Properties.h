#pragma once

#include <vector>
#include <string>
#include <map>

/**
Класс свойств объектов, описывает различные параметры, характеристики и своства различных объектов
Свойство содержит словарь double значени с соответствующими имена и\или строку - значение.
Например: свойство "координаты объекта" содержит словарь значений (1, 1, 1) с именами ("x", "y", "z")
*/
class IProperties {
public:
    /// Возвращает словарь свойства
    virtual std::map<std::string, double>& GetValues() = 0;
    /// Задает словарь для свойства
    virtual void SetValues(const std::map<std::string, double>& _map) = 0;

    /// Возвращает значение с именем name
    virtual double GetValue(std::string name) = 0;
    /// Изменяет значение с именем name
    virtual void SetValue(std::string name, double val) = 0;

    /// Возвращает имя свойства
    virtual std::string GetName() = 0;

    /// Наблюдается ли это свойство стандартным сенсором
    virtual bool IsObserved() = 0;
    /// Задает наблюдается ли это свойство стандартным сенсором
    virtual void SetIsObserved(bool _isObserved) = 0;

    /// Возвращает строковое значение свойства
    virtual std::string GetStringValue() = 0;
    /// Задает строковое значение свойства, после чего свойство становится строковым
    virtual void SetStringValue(std::string val) = 0;
};


///Класс с базовой реализациейинтерфейса свойств объектов, описывает параметры различных объектов
class TProperties : public IProperties  {
protected:
    /// словарь значений в соответствии с именами
    std::map<std::string, double> propMap;
    /// Нублюдается ли это свойство сенсорами
    bool isObserved;
    /// имя данного свойства
    std::string name;
    /// Является свойство строковым или нет
    bool isString;
    /// Строка значения свойства
    std::string stringValue;
public:
    TProperties(std::string _name = "");
    TProperties(std::map<std::string, double> _map,
        bool _isObserved = false, std::string _name = "");
    TProperties(const TProperties& properties);

    /// Возвращает словарь свойства
    virtual std::map<std::string, double>& GetValues() override { return propMap; } 
    /// Задает словарь для свойства
    virtual void SetValues(const std::map<std::string, double>& _map) override { propMap = _map; }

    /// Возвращает значение с именем name
    virtual double GetValue(std::string name) override;
    /// Изменяет значение с именем name
    virtual void SetValue(std::string name, double val) override;

    /// Возвращает имя свойства
    virtual std::string GetName() override { return name; }

    /// Наблюдается ли это свойство стандартным сенсором
    virtual bool IsObserved() override { return isObserved; }
    /// Задает наблюдается ли это свойство стандартным сенсором
    virtual void SetIsObserved(bool _isObserved) override { isObserved = _isObserved; }

    /// Возвращает строковое значение свойства
    virtual std::string GetStringValue() override;
    /// Задает строковое значение свойства, после чего свойство становится строковым
    virtual void SetStringValue(std::string val) override;
};