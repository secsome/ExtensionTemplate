#include "Body.h"

#include <Helpers/Macro.h>

#include <CCINIClass.h>
#include <FootClass.h>

BulletTypeExt* BulletTypeExt::GetExtData(BulletTypeClass* pType)
{
	return static_cast<BulletTypeExt*>(ExtensionWrapper::GetWrapper(pType)->ExtensionObject);
}

void BulletTypeExt::LoadFromINI(BulletTypeClass* pThis, CCINIClass* const pINI)
{
	auto pExt = BulletTypeExt::GetExtData(pThis);
	auto const lpSection = pThis->ID;

	if (!pINI->GetSection(lpSection))
		return;

	pExt->TrajectoryData = GameCreate<TrajectoryTypeClass>();
	strcpy(pExt->TrajectoryData->ID, pThis->ID);
	pExt->TrajectoryData->LoadFromINI(pINI);
}

BulletTypeExt::BulletTypeExt()
{
	TrajectoryData = nullptr;
}

BulletTypeExt::~BulletTypeExt()
{
	if (TrajectoryData)
	{
		GameDelete(TrajectoryData);
		TrajectoryData = nullptr;
	}
}

size_t BulletTypeExt::GetSize() const
{
	return sizeof(BulletTypeExt);
}

HRESULT BulletTypeExt::Load(IStream* pStm)
{
	HRESULT hr = S_OK;

	hr = SwizzleManagerClass::Instance->Swizzle((void**)&TrajectoryData); FAIL_CHECK(hr);

	return hr;
}

HRESULT BulletTypeExt::Save(IStream* pStm)
{
	HRESULT hr = S_OK;

	// No extra thing to write

	return hr;
}


DEFINE_HOOK(0x46BDD9, BulletTypeClass_CTOR, 0x5)
{
	GET(BulletTypeClass*, pItem, ESI);

	ExtensionWrapper::GetWrapper(pItem)->CreateExtensionObject<BulletTypeExt>();

	return 0;
}

DEFINE_HOOK(0x46C8B6, BulletTypeClass_SDDTOR, 0x6)
{
	GET(BulletTypeClass*, pItem, ECX);

	ExtensionWrapper::GetWrapper(pItem)->DestoryExtensionObject();

	return 0;
}

DEFINE_HOOK_AGAIN(0x46C429, BulletTypeClass_LoadFromINI, 0xA)
DEFINE_HOOK(0x46C41C, BulletTypeClass_LoadFromINI, 0xA)
{
	GET(BulletTypeClass*, pItem, ESI);
	GET_STACK(CCINIClass*, pINI, 0x90);

	BulletTypeExt::LoadFromINI(pItem, pINI);

	return 0;
}