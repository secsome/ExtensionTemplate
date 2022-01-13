#pragma once

#include <YRPP.h>
#include <ArrayClasses.h>

// Westwood style save & load helper
// Westwood like such kind of things

namespace SaveLoadHelpers
{
    template<typename T>
    HRESULT Save(IStream* pStm, const DynamicVectorClass<T>& data);

    template<typename T>
    HRESULT Load(IStream* pStm, DynamicVectorClass<T>& data);

    template<typename T>
    HRESULT Swizzle(IStream* pStm, const DynamicVectorClass<T>& data);
}