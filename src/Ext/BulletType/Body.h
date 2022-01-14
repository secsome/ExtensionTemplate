#pragma once

#include "../Extension.h"

#include <BulletTypeClass.h>

#include "../../New/Type/TrajectoryType.h"

class BulletTypeExt final : public IExtension
{
public:
    BulletTypeExt();

    virtual ~BulletTypeExt() override final;

    // IExtension
    virtual size_t GetSize() const override final;
    virtual HRESULT Load(IStream* pStm) override final;
    virtual HRESULT Save(IStream* pStm) override final;

    // Ext helpers
    static BulletTypeExt* GetExtData(BulletTypeClass* pType);
    static void LoadFromINI(BulletTypeClass* pThis, CCINIClass* const pINI);

    // Other functions

    // Normal functions

    // Properties
public:
    TrajectoryTypeClass* TrajectoryData;

};