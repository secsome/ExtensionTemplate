#include "Body.h"

#include <Helpers/Macro.h>

#include "../BulletType/Body.h"

BulletExt* BulletExt::GetExtData(BulletClass* pThis)
{
	return static_cast<BulletExt*>(ExtensionWrapper::GetWrapper(pThis)->ExtensionObject);
}

void BulletExt::Init(BulletClass* pThis)
{
	auto pExt = GetExtData(pThis);
	if (auto const pType = pThis->Type)
	{
		auto const pData = BulletTypeExt::GetExtData(pType);
		
	}
}

BulletExt::BulletExt()
{
}

BulletExt::~BulletExt()
{
}

size_t BulletExt::GetSize() const
{
    return sizeof(BulletExt);
}

HRESULT BulletExt::Load(IStream* pStm)
{
    return S_OK;
}

HRESULT BulletExt::Save(IStream* pStm)
{
    return S_OK;
}

DEFINE_HOOK(0x4664BA, BulletClass_CTOR, 0x5)
{
	GET(BulletClass*, pItem, ESI);

	ExtensionWrapper::GetWrapper(pItem)->CreateExtensionObject<BulletExt>();

	return 0;
}

DEFINE_HOOK(0x4665E9, BulletClass_DTOR, 0xA)
{
	GET(BulletClass*, pItem, ESI);

	ExtensionWrapper::GetWrapper(pItem)->DestoryExtensionObject();

	return 0;
}

DEFINE_HOOK(0x466556, BulletClass_Init, 0xA)
{
	GET(BulletClass*, pThis, ECX);
	pThis->SpawnNextAnim = false;

	BulletExt::Init(pThis);

	return 0;
}