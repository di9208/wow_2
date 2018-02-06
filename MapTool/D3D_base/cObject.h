#pragma once
class cObject
{
private:
	ULONG m_ulRefCount;

public:
	cObject();
	virtual ~cObject();

	virtual void AddRef();
	virtual void Release();
};

