#pragma once

#include "../Extension.h"

#include <BulletClass.h>

#include "../../New/Instance/PusheenManager.h"

class BulletExt final : public IExtension
{
public:
    BulletExt();

    virtual ~BulletExt() override final;

    // IExtension
    virtual size_t GetSize() const override final;
    virtual HRESULT Load(IStream* pStm) override final;
    virtual HRESULT Save(IStream* pStm) override final;

    // Ext helpers
    static BulletExt* GetExtData(BulletClass* pThis);
    static void Init(BulletClass* pThis);

    // Other functions

    // Normal functions

    // Properties
public:
    
};