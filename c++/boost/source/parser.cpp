
#include "./Parser.h"

#include <stdio.h>
#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/bind.hpp>

using boost_example::ParserTestObject;
using boost::wformat;
using boost::spirit::qi::double_;
using boost::spirit::qi::phrase_parse;
using boost::spirit::qi::parse;
using boost::spirit::qi::int_;
using boost::spirit::ascii::space;
using boost::spirit::ascii::char_;

ParserTestObject::ParserTestObject()
{

}

ParserTestObject::~ParserTestObject()
{

}

void ParserTestObject::ParserValueMatch(double value)
{
	wprintf((wformat(L"ParserTestObject::ParserValueMatch - Value = %d\n") % value).str().c_str());
}

void ParserTestObject::ParseMatchToVector(double value, void* values_vector)
{
	std::vector<double>* values = (std::vector<double>*)values_vector;
	wprintf((wformat(L"ParserTestObject::ParseMatchToVector - Value = %d\n") % value).str().c_str());
	if (values == NULL)
		return;

	values->push_back(value);

	std::wstring message(L" ");
	for (std::vector<double>::iterator it = values->begin(); it != values->end(); ++it)
		message += (wformat(L"%d ") % *it).str();

	wprintf((wformat(L"ParserTestObject::ParseMatchToVector - Vector = [%s]\n") % message).str().c_str());
}

void ParserValueMatch(double value)
{
	wprintf((wformat(L"ParserValueMatch Function - Value = %d\n") % value).str().c_str());
}

bool GetExpression(const wchar_t* exmpression_name, const wchar_t* example, std::wstring* expression)
{
	if (expression == NULL)
		return false;

	expression->clear();
	wprintf((wformat(L"- Enter an %s expresion. E.g.: %s: ") % exmpression_name % example).str().c_str());
	std::getline(std::wcin, *expression);
	if (expression->empty())
		std::getline(std::wcin, *expression);

	return true;
}

void ConditionalMessage(const wchar_t* message, bool show_message)
{
	if (show_message)
		wprintf((wformat(L"- %s\n") % message).str().c_str());
}

void boost_example::Parser()
{
	wprintf(L"*** Boost Parser Example - Start\n");

	wprintf(L"- Parsers examples\n");
	double_; //Parse a double
	double_ >> double_; //Parse a line with 02 doubles (>> - Means followed by operator)
	*double_; //Parse that accepts 0 or more double numbers (Like a regular-expression Kleene Star considered C++ syntax)
	double_ >> *(char_(',') >> double_); //Parse a comma delimited list of numbers
	int_ | double_; //a | b - Try a if fails try b
	-double_; //match 0 or 1 time
	char_('(') >> double_ >> -(char_(',') >> double_) >> char_(')') | double_; //Complex numbers E.g.: (123, 90) or (123)

	std::wstring expression;
	expression = L"1";
	if (!parse(expression.begin(), expression.end(), 1))
		wprintf(L"Failed to evaluate that the expression could be parced to the number 1\n");

	if (parse(expression.begin(), expression.end(), 2))
		wprintf(L"Failed to evaluate that the expression could not be parced to the number 1\n");

	ParserTestObject test_object;
	std::vector<double> test_values;
	bool continue_execution = true;

	continue_execution &= GetExpression(L"curly brackets number", L"{1}", &expression);
	ConditionalMessage(L"Evaluating expression.", continue_execution);
	continue_execution &= phrase_parse(expression.begin(), expression.end(), char_('{') >> double_ >> char_('}'), space); //Parameters: StartIterator, EndIterator, Parser, SkipParser
	ConditionalMessage(L"Getting values from expressions (Functions):", continue_execution);
	continue_execution &= parse(expression.begin(), expression.end(), char_('{') >> double_[&ParserValueMatch] >> char_('}'));
	ConditionalMessage(L"Getting values from expressions (Class Functions):", continue_execution);
	continue_execution &= parse(expression.begin(), expression.end(), char_('{') >> double_[boost::bind(&ParserTestObject::ParserValueMatch, &test_object, _1)] >> char_('}'));
	continue_execution &= parse(expression.begin(), expression.end(), char_('{') >> double_[boost::bind(&ParserTestObject::ParseMatchToVector, &test_object, _1, (void*)&test_values)] >> char_('}'));

	continue_execution &= GetExpression(L"comma separated numbers", L"10,20", &expression);
	ConditionalMessage(L"Evaluating expression.", continue_execution);
	continue_execution &= phrase_parse(expression.begin(), expression.end(), double_ >> *(char_(',') >> double_), space); //Parameters: StartIterator, EndIterator, Parser, SkipParser
	ConditionalMessage(L"Getting values from expressions(Functions):", continue_execution);
	continue_execution &= parse(expression.begin(), expression.end(), double_[&ParserValueMatch] >> *(char_(',') >> double_[&ParserValueMatch]));
	ConditionalMessage(L"Getting values from expressions (Class Functions):", continue_execution);
	continue_execution &= parse(expression.begin(), expression.end(), double_[boost::bind(&ParserTestObject::ParserValueMatch, &test_object, _1)] >> *(char_(',') >> double_[boost::bind(&ParserTestObject::ParserValueMatch, &test_object, _1)]));
	continue_execution &= parse(expression.begin(), expression.end(), double_[boost::bind(&ParserTestObject::ParseMatchToVector, &test_object, _1, (void*)&test_values)] >> *(char_(',') >> double_[boost::bind(&ParserTestObject::ParseMatchToVector, &test_object, _1, (void*)&test_values)]));

	if (!continue_execution)
		wprintf((wformat(L"- Fail to parse the expression %s\n") % expression).str().c_str());

	wprintf(L"*** Boost Parser Example - End\n\n");
}
