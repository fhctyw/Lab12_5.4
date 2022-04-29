#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_5.4\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
			Assert::AreEqual((int)getSign(2, 2), 10);
		}
	};
}
