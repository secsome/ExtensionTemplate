#pragma once

#include "AbstractBase.h"

class BulletClass;
class TrajectoryTypeClass;

class TrajectoryClass : public AbstractBase
{
public:
    static DynamicVectorClass<TrajectoryClass*> Trajectories;

    static HRESULT SaveVector(IStream* pStm);
    static HRESULT LoadVector(IStream* pStm);

    TrajectoryClass();

    //IPersist
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override;

    //IPersistStream
    virtual HRESULT __stdcall Load(IStream* pStm) override;
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override;

    //Destructor
    virtual ~TrajectoryClass() override;

    // AbstractClass
    virtual AbstractType WhatAmI() const override;
    virtual int Size() const override;
    virtual void CalculateChecksum(Checksummer& checksum) const override;
    virtual void Update() override;


private:
    BulletClass* OwnerObject;
    TrajectoryTypeClass* Type;
};