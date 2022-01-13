#pragma once

#include "AbstractBase.h"
#include <YRPP.h>

class __declspec(uuid("751E0E50-1B74-DA94-C375-942B43B0A21C")) PusheenManagerClass : public AbstractBase
{
public:
    static DynamicVectorClass<PusheenManagerClass*> PusheenManagers;

    static HRESULT SaveVector(IStream* pStm);
    static HRESULT LoadVector(IStream* pStm);

    PusheenManagerClass();

    //IPersist
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override;
    
    //IPersistStream
    virtual HRESULT __stdcall Load(IStream* pStm) override;
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override;

    //Destructor
    virtual ~PusheenManagerClass() override;

    // AbstractClass
    virtual AbstractType WhatAmI() const override;
    virtual int Size() const override;
    virtual void CalculateChecksum(Checksummer& checksum) const override;
    virtual void Update() override;

private:
    int PusheenValue;
};

template<>
class TClassFactory<PusheenManagerClass> : public IClassFactory
{
public:
    TClassFactory<PusheenManagerClass>()
    {
        this->nRefCount = 0;
    }

    virtual HRESULT __stdcall QueryInterface(const IID& riid, void** ppvObject) override final
    {
        if (!ppvObject)
            return E_POINTER;

        *ppvObject = nullptr;

        if (riid == __uuidof(IUnknown) || riid == __uuidof(IClassFactory))
            *ppvObject = this;

        if (!ppvObject)
            return E_NOINTERFACE;

        this->AddRef();

        return S_OK;
    }

    virtual ULONG __stdcall AddRef() override final
    {
        return Imports::InterlockedIncrement(&this->nRefCount);
    }

    virtual ULONG __stdcall Release() override final
    {
        int nNewRef = Imports::InterlockedIncrement(&this->nRefCount);
        if (!nNewRef)
            GameDelete(this);
        return nNewRef;
    }

    virtual HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, const IID& riid, void** ppvObject) override final
    {
        if (!ppvObject)
            return E_INVALIDARG;

        *ppvObject = nullptr;
        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;

        PusheenManagerClass* pThis = GameCreate<PusheenManagerClass>();
        if (!pThis)
            return E_OUTOFMEMORY;

        HRESULT hr = pThis->QueryInterface(riid, ppvObject);

        if (FAILED(hr))
            GameDelete(pThis);

        return hr;
    }

    virtual HRESULT __stdcall LockServer(BOOL fLock) override final
    {
        this->nRefCount += fLock ? 1 : -1;

        return S_OK;
    }

private:
    int nRefCount;
};