#include "Body.h"

#include <Helpers/Macro.h>

#include <CCINIClass.h>
#include <FootClass.h>

TechnoTypeExt* TechnoTypeExt::GetExtData(TechnoTypeClass* pType)
{
	return static_cast<TechnoTypeExt*>(ExtensionWrapper::GetWrapper(pType)->ExtensionObject);
}

void TechnoTypeExt::LoadFromINI(TechnoTypeClass* pThis, CCINIClass* const pINI)
{
	auto pExt = TechnoTypeExt::GetExtData(pThis);
	auto const lpSection = pThis->ID;

	if (!pINI->GetSection(lpSection))
		return;

	pExt->HideHealthBar = pINI->ReadBool(lpSection, "HideHealthBar", pExt->HideHealthBar);
}

size_t TechnoTypeExt::GetSize() const
{
	return
		sizeof(HideHealthBar)
		;
}

HRESULT TechnoTypeExt::Load(IStream* pStm)
{
	HRESULT hr;
	
	hr = this->Read(pStm, this->HideHealthBar); FAIL_CHECK(hr);

    return hr;
}

HRESULT TechnoTypeExt::Save(IStream* pStm)
{
	HRESULT hr;
	
	hr = this->Write(pStm, this->HideHealthBar); FAIL_CHECK(hr);

    return hr;
}

DEFINE_HOOK(0x711835, TechnoTypeClass_CTOR, 0x5)
{
	GET(TechnoTypeClass*, pItem, ESI);

    ExtensionWrapper::GetWrapper(pItem)->CreateExtensionObject<TechnoTypeExt>();

	return 0;
}

DEFINE_HOOK(0x711AE0, TechnoTypeClass_DTOR, 0x5)
{
	GET(TechnoTypeClass*, pItem, ECX);

    ExtensionWrapper::GetWrapper(pItem)->DestoryExtensionObject();

	return 0;
}

DEFINE_HOOK_AGAIN(0x716132, TechnoTypeClass_LoadFromINI, 0x5)
DEFINE_HOOK(0x716123, TechnoTypeClass_LoadFromINI, 0x5)
{
	GET(TechnoTypeClass*, pItem, EBP);
	GET_STACK(CCINIClass*, pINI, 0x380);

	TechnoTypeExt::LoadFromINI(pItem, pINI);

	return 0;
}

DEFINE_HOOK(0x6F64A9, TechnoClass_DrawHealthBar_Hide, 0x5)
{
	GET(TechnoClass* const, pThis, ECX);

	auto const pData = TechnoTypeExt::GetExtData(pThis->GetTechnoType());
	
	return pData->HideHealthBar ? 0x6F6AB6 : 0;
}
