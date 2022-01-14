#include "TrajectoryType.h"

#include <YRPP.h>
#include <Checksummer.h>

DynamicVectorClass<TrajectoryTypeClass*> TrajectoryTypeClass::TrajectoryTypes;

HRESULT TrajectoryTypeClass::SaveVector(IStream* pStm)
{
    HRESULT hr;

    hr = pStm->Write(&TrajectoryTypes.Count, sizeof(TrajectoryTypes.Count), nullptr); if (FAILED(hr))    return hr;
    for (auto& manager : TrajectoryTypes)
    {
        IPersistStream* lpStm;
        hr = manager->QueryInterface(__uuidof(IPersistStream), (void**)&lpStm); if (FAILED(hr))  return hr;
        hr = Imports::OleSaveToStream(lpStm, pStm); if (FAILED(hr))  return hr;
        hr = lpStm->Release(); if (FAILED(hr))  return hr;
    }

    return hr;
}

HRESULT TrajectoryTypeClass::LoadVector(IStream* pStm)
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

TrajectoryTypeClass::TrajectoryTypeClass() : AbstractTypeBase()
{
    TrajectoryTypes.AddItem(this);

    Type = TrajectoryType::Invalid;
}

HRESULT __stdcall TrajectoryTypeClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;

    *pClassID = __uuidof(this);

    return S_OK;
}

HRESULT __stdcall TrajectoryTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractTypeBase::Load(pStm);
    if (SUCCEEDED(hr))
    {

    }
    return hr;
}

HRESULT __stdcall TrajectoryTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractTypeBase::Save(pStm, fClearDirty);
    if (SUCCEEDED(hr))
    {

    }
    return hr;
}

TrajectoryTypeClass::~TrajectoryTypeClass()
{
    TrajectoryTypes.Remove(this);
}

AbstractType TrajectoryTypeClass::WhatAmI() const
{
    return AbstractType(NewAbstractType::TrajectoryType);
}

int TrajectoryTypeClass::Size() const
{
    return sizeof(TrajectoryTypeClass);
}

void TrajectoryTypeClass::CalculateChecksum(Checksummer& checksum) const
{
    AbstractTypeBase::CalculateChecksum(checksum);
    
    checksum.Add(Type);
}

bool TrajectoryTypeClass::LoadFromINI(CCINIClass* pINI)
{
    if (!AbstractTypeBase::LoadFromINI(pINI))
        return false;

    char readBuffer[0x400];

    pINI->ReadString(this->ID, "Trajectory", "Invalid", readBuffer);
    if (_strcmpi(readBuffer, "Straight") == 0)
        Type = TrajectoryType::Straight;
    else if (_strcmpi(readBuffer, "Bombard") == 0)
        Type = TrajectoryType::Bombard;
    else
        Type = TrajectoryType::Invalid;

    return true;
}

bool TrajectoryTypeClass::SaveToINI(CCINIClass* pINI)
{
    if (!AbstractTypeBase::SaveToINI(pINI))
        return false;

    const char* pValue;
    switch (Type)
    {
    case TrajectoryType::Invalid:
    default:
        pValue = nullptr;
        break;

    case TrajectoryType::Straight:
        pValue = "Straight";
        break;

    case TrajectoryType::Bombard:
        pValue = "Bombard";
        break;
    }
    if (pValue)
        pINI->WriteString(ID, "Trajectory", pValue);

    return true;
}

TrajectoryClass* TrajectoryTypeClass::CreateInstance() const
{
    return nullptr;
}
