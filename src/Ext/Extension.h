#pragma once

#include <YRPP.h>

// All ext classes should derive from this class
class IExtension
{
public:
    virtual ~IExtension() {};

    virtual size_t GetSize() const = 0;
    virtual HRESULT Load(IStream* pStm) = 0;
    virtual HRESULT Save(IStream* pStm) = 0;

#define FAIL_CHECK(hr) if(FAILED(hr)) return hr;
};

// This class is just a wrapper to replace 
class ExtensionWrapper
{
public:
    ExtensionWrapper()
    {
        this->FlagDirty = FALSE;
        this->ExtensionObject = nullptr;
    }

    ~ExtensionWrapper()
    {
        if (this->ExtensionObject)
            GameDelete(this->ExtensionObject);
    }

    size_t GetSize() const
    {
        if (this->ExtensionObject)
            return this->ExtensionObject->GetSize();

        return 0;
    }

    inline static ExtensionWrapper*& GetWrapper(void* pThis)
    {
        return *reinterpret_cast<ExtensionWrapper**>((int)pThis + 0x20);
    }

    inline void DestoryExtensionObject()
    {
        GameDelete(this->ExtensionObject);
        this->ExtensionObject = nullptr;
    }

    template<typename TExt>
    inline void CreateExtensionObject()
    {
        this->DestoryExtensionObject();
        this->ExtensionObject = GameCreate<TExt>();
    }

    HRESULT Load(IStream* pStm) const
    {
        if (auto pExtData = this->ExtensionObject)
        {
            HRESULT hr = pStm->Read(pExtData, pExtData->GetSize(), nullptr);

            if (SUCCEEDED(hr))
                return pExtData->Load(pStm);

            return hr;
        }

        return S_OK;
    }

    HRESULT Save(IStream* pStm) const
    {
        if (auto pExtData = this->ExtensionObject)
        {
            HRESULT hr = pStm->Write(pExtData, pExtData->GetSize(), nullptr);
            
            if (SUCCEEDED(hr))
                return pExtData->Save(pStm);
            
            return hr;
        }

        return S_OK;
    }

    bool IsDirty() const
    {
        return this->FlagDirty;
    };

    inline void SetDirtyFlag(bool fDirty)
    {
        this->FlagDirty = fDirty;
    }

private:
    bool FlagDirty;

public:
    IExtension* ExtensionObject;
};

template<class T>
class HelperClass : public T
{
public:
    inline static HelperClass* GetHelperClass(T* pSrc)
    {
        return static_cast<HelperClass*>(pSrc);
    }

    template<typename TAs>
    inline TAs* As() const
    {
        return (TAs*)this;
    }

    template<typename TAs>
    inline HelperClass<TAs>* AsHelper() const
    {
        return (HelperClass<TAs>*)this;
    }
};