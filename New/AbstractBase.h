#pragma once

#include <AbstractClass.h>

class AbstractBase : public AbstractClass
{
public:
	AbstractBase() JMP_THIS(0x410170);
	AbstractBase(noinit_t) JMP_THIS(0x4101C0);

	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) override JMP_STD(0x410260);
	virtual ULONG __stdcall AddRef() override JMP_STD(0x410300);
	virtual ULONG __stdcall Release() override JMP_STD(0x410310);

	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) = 0;

	virtual HRESULT __stdcall IsDirty() override JMP_STD(0x410450);
	virtual HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x410380);
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x410320);

	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) override JMP_STD(0x4103E0);

	virtual ~AbstractBase() override JMP_THIS(0x4105A0);

	virtual AbstractType __stdcall What_Am_I() const override JMP_STD(0x410210);
	virtual int __stdcall Fetch_ID() const override JMP_STD(0x410220);
	virtual void __stdcall Create_ID() override JMP_STD(0x410230);

	virtual bool __stdcall INoticeSink_Unknown(DWORD dwUnknown) override JMP_STD(0x410580);

	virtual void __stdcall INoticeSource_Unknown() override JMP_STD(0x410590);

	virtual void Init() override JMP_THIS(0x410470);
	virtual void PointerExpired(AbstractClass* pAbstract, bool removed) override JMP_THIS(0x410480);
	virtual AbstractType WhatAmI() const = 0;
	virtual int Size() const = 0;
	virtual void CalculateChecksum(Checksummer& checksum) const override JMP_THIS(0x410410);
	virtual int GetOwningHouseIndex() const override JMP_THIS(0x410490);
	virtual HouseClass* GetOwningHouse() const override JMP_THIS(0x4104A0);
	virtual int GetArrayIndex() const override JMP_THIS(0x4104B0);
	virtual bool IsDead() const override JMP_THIS(0x410440);
	virtual CoordStruct* GetCoords(CoordStruct* pCrd) const override JMP_THIS(0x4104C0);
	virtual CoordStruct* GetDestination(CoordStruct* pCrd, TechnoClass* pDocker = nullptr) const override JMP_THIS(0x4104F0); // where this is moving, or a building's dock for a techno. iow, a rendez-vous point
	virtual bool IsOnFloor() const override JMP_THIS(0x410520);
	virtual bool IsInAir() const override JMP_THIS(0x410530);
	virtual CoordStruct* GetAltCoords(CoordStruct* pCrd) const override JMP_THIS(0x410540);
	virtual void Update() override JMP_THIS(0x410570);

};