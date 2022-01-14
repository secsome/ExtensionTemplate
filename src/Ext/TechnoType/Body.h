#pragma once

#include "../Extension.h"

#include <TechnoTypeClass.h>

class TechnoTypeExt final : public IExtension
{
public:
    TechnoTypeExt();

    virtual ~TechnoTypeExt() override final;

    // IExtension
    virtual size_t GetSize() const override final;
    virtual HRESULT Load(IStream* pStm) override final;
    virtual HRESULT Save(IStream* pStm) override final;

    // Ext helpers
    static TechnoTypeExt* GetExtData(TechnoTypeClass* pType);
    static void LoadFromINI(TechnoTypeClass* pThis, CCINIClass* const pINI);
    
    // Other functions

    // Normal functions

    // Properties
public:
    bool HideHealthBar;
    bool HasPusheen;

};

class TechnoTypeHelper : public HelperClass<TechnoTypeClass>
{
    
};