#include <Helpers/Macro.h>

// Instances
#include "Instance/PusheenManager.h"

// Types
#include "Type/TrajectoryType.h"

namespace NewClasses
{
    void AI()
    {
        for (auto& element : PusheenManagerClass::PusheenManagers)
            element->Update();
    }

    HRESULT Put_All(IStream* pStm)
    {
        HRESULT hr;
        
        hr = PusheenManagerClass::SaveVector(pStm); if (FAILED(hr))  return hr;
        hr = TrajectoryTypeClass::SaveVector(pStm); if (FAILED(hr))  return hr;

        return hr;
    }

    HRESULT Decode_All(IStream* pStm)
    {
        HRESULT hr;

        hr = PusheenManagerClass::LoadVector(pStm); if (FAILED(hr))  return hr;
        hr = TrajectoryTypeClass::LoadVector(pStm); if (FAILED(hr))  return hr;

        return hr;
    }

    template<typename T>
    void DoRegister()
    {
        auto pFactory = GameCreate<TClassFactory<T>>();
        DWORD dwRegister;
        Imports::CoRegisterClassObject(__uuidof(T), pFactory, CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
        Game::COMClasses->AddItem(dwRegister);
    }

    void CoRegisterClasses()
    {
        DoRegister<PusheenManagerClass>();
        DoRegister<TrajectoryTypeClass>();
    }

    void Clear()
    {
        PusheenManagerClass::PusheenManagers.Clear();
        TrajectoryTypeClass::TrajectoryTypes.Clear();
    }
}

// Logics
DEFINE_HOOK(0x55B4E1, LogicClass_AI, 0x5)
{
    NewClasses::AI();

    return 0;
}

// Save Game
DEFINE_HOOK(0x67D32C, Put_All, 0x5)
{
    GET(IStream*, pStm, ESI);

    return SUCCEEDED(NewClasses::Put_All(pStm)) ? 0 : 0x67D42A;
}

// Load Game
DEFINE_HOOK(0x67E826, Decode_All, 0x6)
{
    GET(IStream*, pStm, ESI);

    return SUCCEEDED(NewClasses::Decode_All(pStm)) ? 0 : 0x67F7A3;
}

// Register classes
DEFINE_HOOK(0x6BD6B1, WinMain_CoRegisterClass, 0x5)
{
    NewClasses::CoRegisterClasses();

    return 0;
}

DEFINE_HOOK(0x685659, Clear_Scenario_PusheenManager, 0xA)
{
    NewClasses::Clear();

    return 0;
}