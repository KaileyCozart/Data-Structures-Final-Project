#include "stdafx.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include "CppUnitTest.h"
#include "../Emergency Room Simulation/Read_Input_Test.h"
#include "../Emergency Room Simulation/Update_Staff_Test.h"

// Remember to Set Emergency Room Simulation to Static Library
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTester
{		
	TEST_CLASS(Emergency_Room_Tests)
	{
	public:
		
		TEST_METHOD(Random_Case1_InvalidRangeA)
		{
			auto func = []() {
				read_input("My prompt: ", 3, 1);
			};
			
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(Random_Case2_InvalidRangeB)
		{
			auto func = []() {
				read_input("My prompt: ", 6, 6);
			};

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(Random_Case3_ValidRange)
		{
			std::istringstream ss("3");
			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
			Assert::AreEqual(read_input("My prompt: ", 0, 4), 3);
			std::cin.rdbuf(orig_cin);
		}

		TEST_METHOD(Random_Case4_UpperEdgeOfRange)
		{
			std::istringstream ss("4");
			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
			Assert::AreEqual(read_input("My prompt: ", 0, 4), 4);
			std::cin.rdbuf(orig_cin);
		}

		TEST_METHOD(Random_Case5_LowerEdgeOfRange)
		{
			std::istringstream ss("0");
			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
			Assert::AreEqual(read_input("My prompt: ", 0, 4), 0);
			std::cin.rdbuf(orig_cin);
		}

		TEST_METHOD(Random_Case6_InsideOfRange)
		{
			std::istringstream ss("2");
			std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
			Assert::AreEqual(read_input("My prompt: ", 0, 4), 2);
			std::cin.rdbuf(orig_cin);
		}

		TEST_METHOD(Random_Case7_GoodRangeBadArgumentA)
		{
			auto func = []() {
				std::istringstream ss("2");
				std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
				Assert::AreEqual(read_input("My prompt: ", 1, 1), 2);
				std::cin.rdbuf(orig_cin);
			};

			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(Random_Case8_GoodRangeBadArgumentB)
		{
			auto func = []() {
				std::istringstream ss("2");
				std::streambuf *orig_cin = std::cin.rdbuf(ss.rdbuf());
				Assert::AreEqual(read_input("My prompt: ", 75, 5), 2);
				std::cin.rdbuf(orig_cin);
			};
			
			Assert::ExpectException<std::invalid_argument>(func);
		}

	};


	TEST_CLASS(Update_Staff_Tests)
	{
	public:

		TEST_METHOD(Update_Case10_ValidValues)
		{
			Assert::AreEqual(update_staff(2, 1, 1, 1), 1);
		}

		TEST_METHOD(Update_Case11_InvalidValues)
		{
			Assert::AreEqual(update_staff(2, 1, 1, 0), 0);
		}

		TEST_METHOD(Update_Case12_IfStatementNotRun)
		{
			Assert::AreEqual(update_staff(2, 7, 5, 1), 0);
		}

	};
}