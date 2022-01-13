#include "PusheenManager.h"

// 751E0E50-1B74-DA94-C375-942B43B0A21C
HRESULT __stdcall PusheenManagerClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;

    *pClassID = __uuidof(this);

    return S_OK;
}

HRESULT __stdcall PusheenManagerClass::Load(IStream* pStm)
{
    return this->AbstractClass::Load(pStm);
}

HRESULT __stdcall PusheenManagerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return this->AbstractClass::Save(pStm, fClearDirty);
}

PusheenManagerClass::~PusheenManagerClass()
{
    
}

AbstractType PusheenManagerClass::WhatAmI() const
{
    return AbstractType();
}

int PusheenManagerClass::Size() const
{
    return 0;
}

void PusheenManagerClass::CalculateChecksum(Checksummer& checksum) const
{
}

void PusheenManagerClass::Update()
{
}