#include "Body.h"

#include <Helpers/Macro.h>
#include <CellClass.h>
#include "../TechnoType/Body.h"

TechnoExt* TechnoExt::GetExtData(TechnoClass* pThis)
{
	return static_cast<TechnoExt*>(ExtensionWrapper::GetWrapper(pThis)->ExtensionObject);
}

void TechnoExt::Init(TechnoClass* pThis)
{
	auto pExt = GetExtData(pThis);
	if (auto const pType = pThis->GetTechnoType())
	{
		auto const pData = TechnoTypeExt::GetExtData(pType);

		if (pData->HasPusheen)
			pExt->Pusheen = GameCreate<PusheenManagerClass>();
	}
}

TechnoExt::TechnoExt()
{
	Pusheen = nullptr;
}

TechnoExt::~TechnoExt()
{
	if (Pusheen)
	{
		GameDelete(Pusheen);
		Pusheen = nullptr;
	}
}

size_t TechnoExt::GetSize() const
{
	return sizeof(TechnoExt);
}

HRESULT TechnoExt::Load(IStream* pStm)
{
	HRESULT hr;

	hr = SwizzleManagerClass::Instance->Swizzle((void**)&Pusheen); FAIL_CHECK(hr);

	return hr;
}

HRESULT TechnoExt::Save(IStream* pStm)
{
	return S_OK;
}

DEFINE_HOOK(0x6F3260, TechnoClass_CTOR, 0x5)
{
	GET(TechnoClass*, pItem, ESI);

	ExtensionWrapper::GetWrapper(pItem)->CreateExtensionObject<TechnoExt>();

	return 0;
}

DEFINE_HOOK(0x6F4500, TechnoClass_DTOR, 0x5)
{
	GET(TechnoClass*, pItem, ECX);

	ExtensionWrapper::GetWrapper(pItem)->DestoryExtensionObject();

	return 0;
}

DEFINE_HOOK(0x6F42F7, TechnoClass_Init, 0x5)
{
	GET(TechnoClass*, pThis, ESI);

	TechnoExt::Init(pThis);

	return 0;
}