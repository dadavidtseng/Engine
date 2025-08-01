//----------------------------------------------------------------------------------------------------
// AnimationResource.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once
#include "Engine/Resource/Resource/IResource.hpp"

//----------------------------------------------------------------------------------------------------
class AnimationResource : public IResource
{
public:
    AnimationResource(String const& path, ResourceType type);
};
