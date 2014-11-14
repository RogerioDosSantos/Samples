
#ifdef __cplusplus

namespace code_interoperability
{
	class CppEntryPoint
	{
	public:
		CppEntryPoint();
		~CppEntryPoint();
		bool Run();
	};
}

#endif //__cplusplus

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	void* CreateCppEntryPoint();
	void DestroyCppEntryPoint(void* entry_point);
	void RunCppEntryPoint(void* entry_point);

#ifdef __cplusplus
}
#endif //__cplusplus
