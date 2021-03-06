/*
 * File: stbytearray.cpp
 *
 * Copyright (c) 2010-2011 Freescale Semiconductor, Inc. All rights reserved.
 * See included license file for license details.
*/
#include "stheader.h"
#include "stglobals.h"
#include "stbytearray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStByteArray::CStByteArray(size_t _size, string _name):CStArray<UCHAR>(_size, _name)
{
	
} 

CStByteArray::~CStByteArray()
{

}

ST_ERROR CStByteArray::Read(USHORT& _ush, size_t _from_offset) const
{
	if( (GetCount() - _from_offset) < sizeof(USHORT) )
	{
		return STERR_INVALID_REQUEST;
	}

	TWO_BYTE two_bytes;
	GetAt(_from_offset+0, two_bytes.Byte1);
	GetAt(_from_offset+1, two_bytes.Byte0);

	_ush = *(PUSHORT)&two_bytes;
	return STERR_NONE;
}

ST_ERROR CStByteArray::Remove(size_t from, size_t count)
{
	if(from >= GetCount())
		return STERR_INVALID_REQUEST;
	if(from + count > GetCount())
		return STERR_INVALID_REQUEST;

	memmove(m_p_t+from, m_p_t+from+count, m_count-count-from);
	m_count -= count;
	
	return STERR_NONE;
}

ST_ERROR CStByteArray::Read(ULONG& _uln, size_t _from_offset) const
{
	if( (GetCount() - _from_offset) < sizeof(ULONG) )
	{
		return STERR_INVALID_REQUEST;
	}

	FOUR_BYTE four_bytes;
	GetAt(_from_offset+0, four_bytes.Byte3);
	GetAt(_from_offset+1, four_bytes.Byte2);
	GetAt(_from_offset+2, four_bytes.Byte1);
	GetAt(_from_offset+3, four_bytes.Byte0);

	_uln = *(PULONG)&four_bytes;
	return STERR_NONE;
}

ST_ERROR CStByteArray::Read(ULONGLONG& _ulnln, size_t _from_offset) const
{
	if( (GetCount() - _from_offset) < sizeof(ULONGLONG) )
	{
		return STERR_INVALID_REQUEST;
	}

	EIGHT_BYTE eight_bytes;
	GetAt(_from_offset+0, eight_bytes.Byte7);
	GetAt(_from_offset+1, eight_bytes.Byte6);
	GetAt(_from_offset+2, eight_bytes.Byte5);
	GetAt(_from_offset+3, eight_bytes.Byte4);
	GetAt(_from_offset+4, eight_bytes.Byte3);
	GetAt(_from_offset+5, eight_bytes.Byte2);
	GetAt(_from_offset+6, eight_bytes.Byte1);
	GetAt(_from_offset+7, eight_bytes.Byte0);

	_ulnln = *(PULONGLONG)&eight_bytes;
	return STERR_NONE;
}

ST_ERROR CStByteArray::Read(ST_BOOLEAN& _bool_val, size_t _from_offset) const
{
	if( (GetCount() - _from_offset) < sizeof(UCHAR) )
	{
		return STERR_INVALID_REQUEST;
	}

	UCHAR uch;
	GetAt(_from_offset+0, uch);

	_bool_val = !(uch == 0x00);
	return STERR_NONE;
}

ST_ERROR CStByteArray::Read(void* _buf, size_t _size, size_t _from_offset) const
{
	if( (GetCount() - _from_offset) < _size ) 
	{
		return STERR_INVALID_REQUEST;
	}

	for(size_t index=0; index<_size; index ++)
	{
		GetAt(_from_offset+index, ((PUCHAR)_buf)[index]);
	}
	return STERR_NONE;
}

ST_ERROR CStByteArray::Write(USHORT _ush, size_t _from_offset)
{
	if( (GetCount() - _from_offset) < sizeof(USHORT) )
	{
		return STERR_INVALID_REQUEST;
	}

	TWO_BYTE two_bytes = *(PTWO_BYTE)&_ush;
	SetAt(_from_offset+0, two_bytes.Byte1);
	SetAt(_from_offset+1, two_bytes.Byte0);

	return STERR_NONE;
}

ST_ERROR CStByteArray::Write(ULONG _uln, size_t _from_offset)
{
	if( (GetCount() - _from_offset) < sizeof(ULONG) )
	{
		return STERR_INVALID_REQUEST;
	}

	FOUR_BYTE four_bytes = *(PFOUR_BYTE)&_uln;
	SetAt(_from_offset+0, four_bytes.Byte3);
	SetAt(_from_offset+1, four_bytes.Byte2);
	SetAt(_from_offset+2, four_bytes.Byte1);
	SetAt(_from_offset+3, four_bytes.Byte0);

	return STERR_NONE;
}

ST_ERROR CStByteArray::Write(ULONGLONG _ulnln, size_t _from_offset)
{
	if( (GetCount() - _from_offset) < sizeof(ULONGLONG) )
	{
		return STERR_INVALID_REQUEST;
	}

	EIGHT_BYTE eight_bytes = *(PEIGHT_BYTE)&_ulnln;
	SetAt(_from_offset+0, eight_bytes.Byte7);
	SetAt(_from_offset+1, eight_bytes.Byte6);
	SetAt(_from_offset+2, eight_bytes.Byte5);
	SetAt(_from_offset+3, eight_bytes.Byte4);
	SetAt(_from_offset+4, eight_bytes.Byte3);
	SetAt(_from_offset+5, eight_bytes.Byte2);
	SetAt(_from_offset+6, eight_bytes.Byte1);
	SetAt(_from_offset+7, eight_bytes.Byte0);

	return STERR_NONE;
}

ST_ERROR CStByteArray::Write(ST_BOOLEAN _bool_val, size_t _from_offset)
{
	if( (GetCount() - _from_offset) < sizeof(UCHAR) )
	{
		return STERR_INVALID_REQUEST;
	}

	UCHAR uch = ( _bool_val ) ? 0x01 : 0x00;

	SetAt(_from_offset+0, uch);

	return STERR_NONE;
}

ST_ERROR CStByteArray::Write(const void* _buf, size_t _size, size_t _from_offset)
{
	if( (GetCount() - _from_offset) < _size )
	{
		return STERR_INVALID_REQUEST;
	}

	for(size_t index=0; index<_size; index ++)
	{
		SetAt(_from_offset+index, ((PUCHAR)_buf)[index]);
	}
	return STERR_NONE;
}

wstring CStByteArray::GetAsString()
{
	wchar_t formatted_byte[7];
	wstring formatted_bytes( L"" );
	UCHAR uch=0x00;

	for(size_t index=0; index<GetCount(); index++)
	{
		GetAt(index, uch);

		if( index == GetCount()-1 )
		{
			swprintf_s(formatted_byte, 7,  L"0x%x", uch); //last byte
		}
		else
		{
			swprintf_s(formatted_byte, 7, L"0x%x, ", uch);
		}

		formatted_bytes = formatted_bytes + wstring(formatted_byte);
	}
	
	return formatted_bytes;
}

BOOL CStByteArray::operator!=(const CStByteArray& _arr) const
{
	return !(*this == _arr );
}

BOOL CStByteArray::operator==(const CStByteArray& _arr) const
{
	if( GetCount() != _arr.GetCount() )
		return FALSE;

	for(size_t index=0; index<GetCount(); index++)
	{
		UCHAR uch=0x00;
		GetAt(index, uch);

		if( uch != *(_arr.GetAt(index)) )
			return FALSE;
	}
	
	return TRUE;
}

CStArrayOfByteArrays::CStArrayOfByteArrays(size_t _size, size_t _size_of_each_bytearray, string _name):
	CStArray<CStByteArray*>(_size, _name)
{
	CStByteArray* arr;
	for(size_t index=0; index<_size; index ++)
	{
		arr = new CStByteArray(_size_of_each_bytearray);
		SetAt(index, arr);
	}
}

CStArrayOfByteArrays::~CStArrayOfByteArrays()
{
	CStByteArray* arr;
	for(size_t index=0; index<GetCount(); index ++)
	{
		arr = *GetAt(index);
		delete arr;
		SetAt(index, NULL);
	}
}

