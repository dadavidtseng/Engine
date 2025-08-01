//----------------------------------------------------------------------------------------------------
// IScriptableObject.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Engine/Scripting/IScriptableObject.hpp"

std::any IScriptableObject::GetProperty(std::string const& propertyName) const
{
    return std::any{};
}

bool IScriptableObject::SetProperty(const std::string& propertyName, const std::any& value)
{
    return false;
}

std::vector<std::string> IScriptableObject::GetAvailableProperties() const
{
    return {};
}

bool IScriptableObject::HasMethod(std::string const& methodName) const
{
    auto methods = GetAvailableMethods();
    for (const auto& method : methods)
    {
        if (method.name == methodName)
        {
            return true;
        }
    }
    return false;
}

bool IScriptableObject::HasProperty(const std::string& propertyName) const
{
    auto properties = GetAvailableProperties();
    for (const auto& prop : properties)
    {
        if (prop == propertyName)
        {
            return true;
        }
    }
    return false;
}
