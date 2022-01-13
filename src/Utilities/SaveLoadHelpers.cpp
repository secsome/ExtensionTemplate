#include "SaveLoadHelpers.h"

template<typename T>
inline HRESULT SaveLoadHelpers::Save(IStream* pStm, const DynamicVectorClass<T>& data)
{
    HRESULT hr;

    hr = pStm->Write(&data.Count, sizeof(data.Count), nullptr);
    if (SUCCEEDED(hr))
    {
        for (const auto& element : data)
        {
            hr = pStm->Write(&element, sizeof(element), nullptr);
            if (FAILED(hr))
                break;
        }
    }

    return hr;
}

template<typename T>
inline HRESULT SaveLoadHelpers::Load(IStream* pStm, DynamicVectorClass<T>& data)
{
    HRESULT hr;

    data.Clear();
    int nCount;
    hr = pStm->Read(&nCount, sizeof(nCount), nullptr);
    if (SUCCEEDED(hr))
    {
        while (nCount--)
        {
            T element;
            hr = pStm->Read(&element, sizeof(element), nullptr);
            if (FAILED(hr))
                break;

            data.AddItem(element);
        }
    }

    return hr;
}

template<typename T>
inline HRESULT SaveLoadHelpers::Swizzle(IStream* pStm, const DynamicVectorClass<T>& data)
{
    HRESULT hr = S_OK;
    
    for (auto& element : data)
    {
        hr = SwizzleManagerClass::Instance->Swizzle((void**)&element);
        if (FAILED(hr))
            break;
    }

    return hr;
}
