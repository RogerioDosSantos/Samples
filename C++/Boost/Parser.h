#include <vector>

namespace boost_example
{
	void Parser();

	class ParserTestObject
	{
	public:
		ParserTestObject();
		~ParserTestObject();

		void ParserValueMatch(double value);
		void ParseMatchToVector(double value, void* values_vector);
	};

}