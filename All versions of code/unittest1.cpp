#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sodoku/sudoku.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-c", "a");

			Assert::AreEqual(1, ans);
		}
		TEST_METHOD(TestMethod2)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-c", "1000001");

			Assert::AreEqual(1, ans);
		}


		TEST_METHOD(TestMethod3)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-c", "123");

			Assert::AreEqual(6, ans);

		}

		TEST_METHOD(TestMethod4)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-c", "-1");

			Assert::AreEqual(1, ans);

		}

		TEST_METHOD(TestMethod5)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-c", "");

			Assert::AreEqual(1, ans);

		}

		TEST_METHOD(TestMethod6)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-a", "123");

			Assert::AreEqual(3, ans);
		}

		TEST_METHOD(TestMethod7)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-s", "123.t");

			Assert::AreEqual(2, ans);
		}

		

		TEST_METHOD(TestMethod8)
		{
			// TODO: Your test code here
			sudoku s1;
			s1.choosecors("-s", "test2.txt");
			
			char aaa[600] = {
				"6 9 8 7 5 4 3 2 1\n"
				"3 2 1 6 9 8 7 5 4\n"
				"7 5 4 3 2 1 6 9 8\n"
				"2 1 6 9 8 7 5 4 3\n"
				"5 4 3 2 1 6 9 8 7\n"
				"9 8 7 5 4 3 2 1 6\n"
				"1 6 9 8 7 5 4 3 2\n"
				"4 3 2 1 6 9 8 7 5\n"
				"8 7 5 4 3 2 1 6 9\n\n"

				"6 9 8 7 5 4 3 2 1\n"
				"3 2 1 6 9 8 7 5 4\n"
				"7 5 4 3 2 1 6 9 8\n"
				"2 1 6 9 8 3 5 4 7\n"
				"5 4 3 2 1 7 9 8 6\n"
				"9 8 7 5 4 6 2 1 3\n"
				"1 6 9 8 7 5 4 3 2\n"
				"8 7 5 4 3 2 1 6 9\n"
				"4 3 2 1 6 9 8 7 5\n"
			};
			Assert::AreEqual(aaa,print);
			
		}

		TEST_METHOD(TestMethod9)
		{
			// TODO: Your test code here
			sudoku s1;
			int ans = s1.choosecors("-s", "test1.txt");

			Assert::AreEqual(6, ans);
		}		

		TEST_METHOD(TestMethod10)
		{
			// TODO: Your test code here
			sudoku s1;		
			s1.choosecors("-s", "test1.txt");

			char aa[300] = { "6 1 2 3 4 5 7 9 8\n"
				"3 4 5 9 7 8 6 1 2\n"
				"9 7 8 6 1 2 3 4 5\n"
				"1 8 3 4 2 9 5 7 6\n"
				"4 5 9 7 8 6 1 2 3\n"
				"7 2 6 1 5 3 4 8 9\n"
				"2 3 4 5 9 7 8 6 1\n"
				"5 9 7 8 6 1 2 3 4\n"
				"8 6 1 2 3 4 9 5 7\n"
			};

			Assert::AreEqual(aa, print);

		}

		
	};
}
