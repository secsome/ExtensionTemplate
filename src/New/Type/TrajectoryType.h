#pragma once

#include "AbstractTypeBase.h"

enum class TrajectoryType
{
    Invalid = -1,
    Straight = 0,
    Bombard = 1,
};

class TrajectoryClass;

class __declspec(uuid("293F5424-F297-409C-AD97-70108F28B089"))
    TrajectoryTypeClass : public AbstractTypeBase
{
public:
    static DynamicVectorClass<TrajectoryTypeClass*> TrajectoryTypes;

    static HRESULT SaveVector(IStream* pStm);
    static HRESULT LoadVector(IStream* pStm);

    TrajectoryTypeClass();

    //IPersist
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override;

    //IPersistStream
    virtual HRESULT __stdcall Load(IStream* pStm) override;
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override;

    //Destructor
    virtual ~TrajectoryTypeClass() override;

    // AbstractClass
    virtual AbstractType WhatAmI() const override;
    virtual int Size() const override;
    virtual void CalculateChecksum(Checksummer& checksum) const override;

    // AbstractTypeClass
    virtual bool LoadFromINI(CCINIClass* pINI) override;
    virtual bool SaveToINI(CCINIClass* pINI) override;

    TrajectoryClass* CreateInstance() const;

private:
    TrajectoryType Type;
};

#include <ObjectTypeClass.h>