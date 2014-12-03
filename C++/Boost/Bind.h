
namespace boost_example
{
	void Bind();

	class BindTestObject
	{
	public:
		BindTestObject();
		~BindTestObject();

		void ObjectFunction(int parameter01, const wchar_t* parameter02);
	};
}