#include "./CodeInteroperability.h"

#include <stdio.h>

using  code_interoperability::CppEntryPoint;

CppEntryPoint::CppEntryPoint()
{
}

CppEntryPoint::~CppEntryPoint()
{
}

bool  CppEntryPoint::Run()
{
	wprintf(L"Hello to my C++ program!");
	return true;
}


void* CreateCppEntryPoint()
{
	CppEntryPoint* entry_point = new  CppEntryPoint();
	return (void *)entry_point;
}

void DestroyCppEntryPoint(void* entry_point)
{
	delete (CppEntryPoint*)entry_point;
	entry_point = NULL;
}

void RunCppEntryPoint(void* entry_point)
{
	if (!((CppEntryPoint*)entry_point)->Run())
		wprintf(L"Could not execute C++ code properly!");
}
