
#include "./Serialization.h"

#include <stdio.h>
#include <string.h>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::wformat;
using boost::property_tree::json_parser::write_json;
using boost::property_tree::json_parser::read_json;
using boost::property_tree::json_parser::json_parser_error;
using boost::property_tree::wptree;
using boost::filesystem::current_path;
using boost::filesystem::path;
using std::wstring;

void boost_example::Serialization()
{
	wprintf(L"*** Boost Serialization Example - Start\n");

	wprintf(L"Building property tree\n");

	wptree property_tree;
	property_tree.add<int>(L"Property_01", 1);
	property_tree.add<int>(L"Property_02", 2);
	property_tree.add<int>(L"Property_03", 3);
	property_tree.add<int>(L"Property_04", 4);
	property_tree.add<int>(L"Property_05", 5);
	property_tree.add<int>(L"Node1.Node2.Node3.Property_06", 6);

	wprintf(L"Saving to a file\n");

	path file_path(current_path().c_str());
	file_path /= L"JsonTest.txt";
	wprintf((wformat(L"File Path: %s\n") % file_path.generic_wstring()).str().c_str());

	std::wofstream file(file_path.generic_wstring().c_str());
	if (!file.is_open())
	{
		wprintf(L"Could not create the file\n");
		return;
	}

	try
	{
		write_json(file, property_tree);
	}
	catch (json_parser_error)
	{
		wprintf(L"Could not write Json to the file\n");
	}

	file.close();

	wprintf(L"Loading from the file\n");
	wprintf((wformat(L"File Path: %s\n") % file_path.generic_wstring()).str().c_str());

	std::wifstream read_file(file_path.generic_wstring().c_str());
	if (!read_file.is_open())
	{
		wprintf(L"Could not load the file\n");
		return;
	}

	std::wstringstream temp_stream;
	temp_stream << read_file.rdbuf();
	wprintf(L"Json file content:\n");
	wprintf(temp_stream.str().c_str());
	wprintf(L"\n");

	wptree read_property_tree;
	try
	{
		read_property_tree.clear();
		read_json(temp_stream, read_property_tree);
	}
	catch (json_parser_error)
	{
		wprintf(L"Could not read Json to the file\n");
		return;
	}

	wprintf(L"Read property tree content:\n");
	wprintf((wformat(L"\t Property_01 = %d\n") % read_property_tree.get<int>(L"Property_01", 0)).str().c_str());
	wprintf((wformat(L"\t Property_02 = %d\n") % read_property_tree.get<int>(L"Property_02", 0)).str().c_str());
	wprintf((wformat(L"\t Property_03 = %d\n") % read_property_tree.get<int>(L"Property_03", 0)).str().c_str());
	wprintf((wformat(L"\t Property_04 = %d\n") % read_property_tree.get<int>(L"Property_04", 0)).str().c_str());
	wprintf((wformat(L"\t Property_05 = %d\n") % read_property_tree.get<int>(L"Property_05", 0)).str().c_str());
	wprintf((wformat(L"\t Property_06 = %d\n") % read_property_tree.get<int>(L"Node1.Node2.Node3.Property_06", 0)).str().c_str());

	wprintf(L"*** Boost Serialization Example - End\n\n");
}