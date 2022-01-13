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
    return this->AbstractBase::Load(pStm);
}

HRESULT __stdcall PusheenManagerClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return this->AbstractBase::Save(pStm, fClearDirty);
}

PusheenManagerClass::~PusheenManagerClass()
{
    PusheenManagers.Remove(this);
}

AbstractType PusheenManagerClass::WhatAmI() const
{
    return AbstractType(74);
}

int PusheenManagerClass::Size() const
{
    return sizeof(PusheenManagerClass);
}

void PusheenManagerClass::CalculateChecksum(Checksummer& checksum) const
{
    checksum.Add(PusheenValue);
    AbstractBase::CalculateChecksum(checksum);
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

DEFINE_HOOK(0x55B4E1, LogicClass_AI, 0x5)
{
    for (auto& pusheen : PusheenManagerClass::PusheenManagers)
        pusheen->Update();

    return 0;
}

DEFINE_HOOK(0x67D32C, Put_All_PusheenManagers, 0x5)
{
    GET(IStream*, pStm, ESI);

    HRESULT hr = PusheenManagerClass::SaveVector(pStm);
    
    return SUCCEEDED(hr) ? 0 : 0x67D42A;
}

DEFINE_HOOK(0x67E826, Decode_All_PusheenManagers, 0x6)
{
    GET(IStream*, pStm, ESI);

    HRESULT hr = PusheenManagerClass::LoadVector(pStm);

    return SUCCEEDED(hr) ? 0 : 0x67F7A3;
}

DEFINE_HOOK(0x6BD6B1, WinMain_CoRegisterClass_PusheenManager, 0x5)
{
    auto pFactory = GameCreate<TClassFactory<PusheenManagerClass>>();
    DWORD dwRegister;
    Imports::CoRegisterClassObject(
        __uuidof(PusheenManagerClass), pFactory, CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &dwRegister
    );
    Game::COMClasses->AddItem(dwRegister);

    return 0;
}

DEFINE_HOOK(0x685659, Clear_Scenario_PusheenManager, 0xA)
{
    PusheenManagerClass::PusheenManagers.Clear();

    return 0;
}