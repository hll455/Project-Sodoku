#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sodoku/sodoku.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sodokuTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
	//	
	//	TEST_METHOD(Testtrue)
	//	{
	//		// TODO: Your test code here


	///*		sodoku s1;
	//		s1.choosecors("-c", "10");
	//		bool judge();*/
	//	}
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			sodoku* s2=new sodoku();
			char ans[] = "6 1 2 3 4 5 7 8 9 3 4 5 7 8 9 6 1 2 7 8 9 6 1 2 3 4 5 1 2 3 4 5 7 8 9 6 4 5 7 8 9 6 1 2 3 8 9 6 1 2 3 4 5 7 2 3 4 5 7 8 9 6 1 5 7 8 9 6 1 2 3 4 6 1 2 3 4 5 7 8";
			s2->choosecors("-s", "test1.txt");
			
			/*FILE* da1;
			da1 = fopen("123.txt", "r");
			while (!feof(da1)) 
			fgets(ans,100,da1);
			fclose(da1);*/
			Assert::AreEqual(ans, print);
		}

		//TEST_METHOD(TestMethod1)
		//{
		//	// TODO: Your test code here
		//}
	};
}