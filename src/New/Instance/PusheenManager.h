#pragma once

#include "AbstractBase.h"
#include <YRPP.h>

class __declspec(uuid("751E0E50-1B74-DA94-C375-942B43B0A21C")) 
    PusheenManagerClass : public AbstractBase
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