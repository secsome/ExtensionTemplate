#include "PusheenManager.h"

#include <YRPP.h>
#include <Checksummer.h>
#include <MessageListClass.h>

#include <Helpers/Macro.h>

DynamicVectorClass<PusheenManagerClass*> PusheenManagerClass::PusheenManagers;

HRESULT PusheenManagerClass::SaveVector(IStream* pStm)
{
    HRESULT hr;

    hr = pStm->Write(&PusheenManagers.Count, sizeof(PusheenManagers.Count), nullptr); if (FAILED(hr))    return hr;
    for (auto& manager : PusheenManagers)
    {
        IPersistStream* lpStm;
        hr = manager->QueryInterface(__uuidof(IPersistStream), (void**)&lpStm); if (FAILED(hr))  return hr;
        hr = Imports::OleSaveToStream(lpStm, pStm); if (FAILED(hr))  return hr;
        hr = lpStm->Release(); if (FAILED(hr))  return hr;
    }

    return hr;
}

HRESULT PusheenManagerClass::LoadVector(IStream* pStm)
{
    HRESULT hr;

    int nCount;
    hr = pStm->Read(&nCount, sizeof(nCount), nullptr); if (FAILED(hr))   return hr;
    while (nCount--)
    {
        LPVOID ppvObj;
        hr = Imports::OleLoadFromStream(pStm, &__uuidof(IUnknown), &ppvObj); if (FAILED(hr))   return hr;
    }

    return hr;
}

PusheenManagerClass::PusheenManagerClass() : AbstractBase()
{
    PusheenManagers.AddItem(this);

    PusheenValue = 0;
}

HRESULT __stdcall PusheenManagerClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;

    *pClassID = __uuidof(this);

    return S_OK;
}

HRESULT __stdcall PusheenManagerClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractBase::Load(pStm);
    if (SUCCEEDED(hr))
    {

    }
    return hr;
}

HRESULT __stdcall PusheenManagerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractBase::Save(pStm, fClearDirty);
    if (SUCCEEDED(hr))
    {

    }
    return hr;
}

PusheenManagerClass::~PusheenManagerClass()
{
    PusheenManagers.Remove(this);
}

AbstractType PusheenManagerClass::WhatAmI() const
{
    return AbstractType(NewAbstractType::PusheenManager);
}

int PusheenManagerClass::Size() const
{
    return sizeof(PusheenManagerClass);
}

void PusheenManagerClass::CalculateChecksum(Checksummer& checksum) const
{
    AbstractBase::CalculateChecksum(checksum);

    checksum.Add(PusheenValue);
}

void PusheenManagerClass::Update()
{
    if (PusheenValue >= 10000)
        PusheenValue = 0;

    ++PusheenValue;

    wchar_t buffer[0x20];
    if (PusheenValue % 114 == 0)
    {
        swprintf_s(buffer, L"%04d", PusheenValue);
        MessageListClass::Instance->PrintMessage(buffer);
    }
}