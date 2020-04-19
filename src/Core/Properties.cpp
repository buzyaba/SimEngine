#include <stdexcept>
#include "Core/Properties.h"

TProperties::TProperties(std::string _name) : name(_name),
    isString(false), stringValue(""), isObserved(false) {}

TProperties::TProperties(std::map<std::string, double> _map,
    bool _isObserved, std::string _name) :
    isObserved(_isObserved), name(_name), isString(false), stringValue(""), propMap(_map) {}

TProperties::TProperties(const TProperties& properties) :
    propMap(properties.propMap), isObserved(properties.isObserved),
    name(properties.name), isString(properties.isString),
    stringValue(properties.stringValue) {}

void TProperties::SetValue(std::string name, double val) {
    auto iter = propMap.find(name);
    if (iter != propMap.end())
        iter->second = val;
    else throw std::runtime_error("No property with this name");
}

double TProperties::GetValue(std::string name) {
    auto iter = propMap.find(name);
    if (iter != propMap.end())
        return iter->second;
    else throw std::runtime_error("No property with this name");
}

std::string TProperties::GetStringValue()
{
    if (!isString)
    {
        stringValue = "";
        for(const auto& elem : propMap)
            stringValue += std::to_string(elem.second) + "_";
        stringValue.pop_back();
    }
    return stringValue;
}

void TProperties::SetStringValue(std::string val)
{
    stringValue = val;
    isString = true;
}
