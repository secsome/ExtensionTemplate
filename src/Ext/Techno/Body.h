#pragma once

#include "../Extension.h"

#include <TechnoClass.h>

#include "../../New/PusheenManager.h"

class TechnoExt final : public IExtension
{
public:
    TechnoExt();

    virtual ~TechnoExt() override final;

    // IExtension
    virtual size_t GetSize() const override final;
    virtual HRESULT Load(IStream* pStm) override final;
    virtual HRESULT Save(IStream* pStm) override final;

    // Ext helpers
    static TechnoExt* GetExtData(TechnoClass* pThis);
    static void Init(TechnoClass* pThis);

    // Other functions

    // Normal functions

    // Properties
public:
    PusheenManagerClass* Pusheen;
};