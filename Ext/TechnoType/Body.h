#pragma once

#include "../Extension.h"

#include <TechnoTypeClass.h>

class TechnoTypeExt final : public IExtension
{
public:
    TechnoTypeExt() :
        HideHealthBar{ false }
    {}

    ~TechnoTypeExt() = default;

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

};

class TechnoTypeHelper : public HelperClass<TechnoTypeClass>
{
public:
    bool HasMoney() const
    {
        return this->Cost > 0;
    }
};

class InfantryTypeHelper : public HelperClass<InfantryClass>
{
public:
    bool HasBaseMoney() const
    {
        return this->As<TechnoTypeHelper>()->HasMoney();
    }
};