
#include "./Bind.h"

#include <stdio.h>
#include <string.h>
#include <vector>
#include <boost/format.hpp>
#include <boost/bind.hpp>

using boost_example::BindTestObject;
using boost::wformat;
using boost::bind;
using std::wstring;
using std::vector;

BindTestObject::BindTestObject()
{

}

BindTestObject::~BindTestObject()
{

}

void BindTestObject::ObjectFunction(int parameter01, const wchar_t* parameter02)
{
	wprintf((wformat(L"ObjectFunction - Parameter 01 = %d ; Parameter 02 = %s\n") % parameter01 % parameter02).str().c_str());
}


void Function01()
{
	wprintf(L"Function01\n");
}

void Function02(int parameter01, const wchar_t* parameter02)
{
	wprintf((wformat(L"Function02 - Parameter 01 = %d ; Parameter 02 = %s\n") % parameter01 % parameter02).str().c_str());
}

void Function03(int parameter01, void* parameter02A)
{
	vector<int>* parameter02 = (vector<int>*)parameter02A;
	wprintf((wformat(L"Function03 - Parameter 01 = %d\n") % parameter01).str().c_str());
	if (parameter02 == NULL)
		return;

	parameter02->push_back(parameter01);

	std::wstring message(L" ");
	for (std::vector<int>::iterator it = parameter02->begin(); it != parameter02->end(); ++it)
		message += (wformat(L"%d ") % *it).str();

	wprintf((wformat(L"Function03 - Vector = [%s]\n") % message).str().c_str());
}

void boost_example::Bind()
{
	wprintf(L"*** Boost Bind Example - Start\n");
	
	bind(&Function01)();
	bind(&Function02, 43, L"String")();

	vector<int> parameter02;
	bind(&Function03, 1, (void*)&parameter02)();
	bind(&Function03, 2, _1)((void*)&parameter02);

	BindTestObject object;
	bind(&BindTestObject::ObjectFunction, &object, 88, L"Class Function String")();

	wprintf(L"*** Boost Bind Example - End\n\n");
}
