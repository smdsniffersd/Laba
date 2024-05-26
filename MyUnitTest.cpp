#include "pch.h"
#include <iostream>

#include "CppUnitTest.h"
#include "input_txt.h"
#include <utility>
#include "config.h"
#include "input_key.h"// ����������� ������������� ����� � ����������� �����
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;
using std::pair;
using std::endl;

namespace UnitTestProject
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // �������� �� �������
        TEST_METHOD(AllCoordinatesSame)
        {
            std::ofstream testFile("numbers.txt");
            testFile << "3 4\n3 4\n3 4\n3 4";
            testFile.close();

            auto points = input_from_txt();

            Assert::IsTrue(points.empty(), L"��������� ����� ������ ���� �������, ���� ��� ���������� ���������.");
        }
        // �������� �� double- ���������� �����
        TEST_METHOD(DoubleInput)
        {
            std::istringstream buffer("1.1\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());

            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"��������� �������� ����� ������� ��� double �����.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("������: ������� ������� �����. ����������, ������� ����� �����.") != std::string::npos,
                L"Expected error message not found.");
        }
        // �������� �� 0 �����
        TEST_METHOD(ZeroPointsInput)
        {
            std::istringstream buffer("0\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());
            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"��������� �������� ����� ����� ������� ��� ����� ������� ��������.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("���������� �������� �� ������ ������� � ����� ���������� �����.") != std::string::npos,
                L"Expected error message not found.");
        }
        // �������� �� ������������� �������� �����
        TEST_METHOD(NegativePointsInput)
        {
            std::istringstream buffer("-1\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());
            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"���������, ��� ��� ����� ������������� �������� ����� ����� �������.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("���������� �������� �� ������ ������� � ����� ���������� �����.") != std::string::npos,
                L"Expected error message not found.");
        }
        // �������� �� 1 �����
        TEST_METHOD(TestOnePointInput)
        {
            std::streambuf* orig_cin = std::cin.rdbuf();
            std::streambuf* orig_cout = std::cout.rdbuf();
            std::istringstream input("1\n");
            std::ostringstream output;
            std::cin.rdbuf(input.rdbuf());
            std::cout.rdbuf(output.rdbuf());

            auto result = input_from_console();

            std::string expected_output = "������� ����� ���������� �����:\n"
                "���������� �������� �� ������ ������� � ����� ���������� �����.\n";
            Assert::AreEqual(expected_output, output.str(), L"�������� ��������� �� ������ ��� ����� ����� �����.");
            Assert::IsTrue(result.empty(), L"������ ����� ������ ���� ������ ��� ����� ����� �����.");

            std::cin.rdbuf(orig_cin);
            std::cout.rdbuf(orig_cout);
        }
       
        // �������� �� ������� � ������ ������ �����
        TEST_METHOD(DuplicateCoordinates)
        {
            std::ofstream testFile("numbers.txt");
            testFile << "3 4\n5 6\n3 4\n5 6\n";
            testFile.close();

            std::ifstream inputFile("numbers.txt");
            std::streambuf* orig = std::cin.rdbuf(inputFile.rdbuf());

            auto points = input_from_txt();

            std::cin.rdbuf(orig);
            inputFile.close();

            Assert::IsTrue(points.empty(), L"��������� ����� ������ ���� �������, ���� ��� ���������� ���������.");
        }
        // �������� ��������� ��������
        TEST_METHOD(SearchMinPointsTest)
        {
            vector<std::pair<int, int>> testPoints = { {-10, -10}, {10, 10}, {0, 0}, {5, 5} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(testPoints);

            Assert::AreEqual(-10, result.first.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(-10, result.first.second, L"������������ y-���������� ������ �����.");
            Assert::AreEqual(10, result.second.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(10, result.second.second, L"������������ y-���������� ������ �����.");
        }
        // ������� ������� ����� ������������
        TEST_METHOD(FindOptimalPoints)
        {
            vector<pair<int, int>> points = { {INT_MAX, INT_MAX}, {INT_MIN, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(points);

            Assert::AreEqual(INT_MAX, result.first.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(INT_MAX, result.first.second, L"������������ y-���������� ������ �����.");
            Assert::AreEqual(INT_MAX, result.second.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(INT_MIN, result.second.second, L"������������ y-���������� ������ �����.");
        }
        
        // �������� �� ����� ������� �� ����� �����
        TEST_METHOD(SearchPointsOnOneLine)
        {
            vector<std::pair<int, int>> testPoints = { {0, 0}, {1, 1}, {2, 2}, {3, 3} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(testPoints);

            Assert::AreEqual(0, result.first.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(0, result.first.second, L"������������ y-���������� ������ �����.");
            Assert::AreEqual(1, result.second.first, L"������������ x-���������� ������ �����.");
            Assert::AreEqual(1, result.second.second, L"������������ y-���������� ������ �����.");
        }

        // �������� �� ������� �������� �� txt
        TEST_METHOD(TestInputFromTxtWithLargeNumbers)
        {
            std::ofstream test_file("test_numbers.txt");
            if (!test_file)
            {
                Assert::Fail(L"������ �������� ��������� �����");
                return;
            }
            test_file << "12345678901234567890 98765432109876543210" << endl;
            test_file << "98765432109876543210 12345678901234567890" << endl;
            test_file << "99999999999999999999 88888888888888888888" << endl;
            test_file << "88888888888888888888 99999999999999999999" << endl;
            test_file.close();

            vector<pair<int, int>> result = input_from_txt();

            Assert::IsTrue(result.empty(), L"��������� ������ ���������");

            remove("test_numbers.txt");
        }
        // �������� �� ������� ������������� �������� �� txt 
        TEST_METHOD(TestInputFromTxtWithMINNumbers)
        {
            std::ofstream test_file("test_numbers.txt");
            if (!test_file)
            {
                Assert::Fail(L"������ �������� ��������� �����");
                return;
            }
            test_file << "-12345678901234567890 -98765432109876543210" << endl;
            test_file << "-98765432109876543210 -12345678901234567890" << endl;
            test_file << "-99999999999999999999 -88888888888888888888" << endl;
            test_file << "-88888888888888888888 -99999999999999999999" << endl;
            test_file.close();

            vector<pair<int, int>> result = input_from_txt();
            Assert::IsTrue(result.empty(), L"��������� ������ ���������");

            remove("test_numbers.txt");
        }
        // �������� �� ������� �������� �� �������
        TEST_METHOD(TestInputFromConsoleWithLargeNumbers)
        {
            std::streambuf* orig_cin = std::cin.rdbuf();

            std::istringstream input(
                "12345678901234567890 98765432109876543210\n"
                "98765432109876543210 12345678901234567890\n"
                "99999999999999999999 88888888888888888888\n"
                "88888888888888888888 99999999999999999999\n"
            );

            std::cin.rdbuf(input.rdbuf());

            vector<pair<int, int>> result = input_from_console();

            Assert::IsTrue(result.empty(), L"��������� ������ ���������");

            std::cin.rdbuf(orig_cin);
        }
        // �������� �� ������� ������������� �������� �� �������
        TEST_METHOD(TestInputFromConsoleWithMINNumbers)
        {
            std::streambuf* orig_cin = std::cin.rdbuf();

            std::istringstream input(
                "-12345678901234567890 -98765432109876543210\n"
                "-98765432109876543210 -12345678901234567890\n"
                "-99999999999999999999 -88888888888888888888\n"
                "-88888888888888888888 -99999999999999999999\n"
            );

            std::cin.rdbuf(input.rdbuf());

            vector<pair<int, int>> result = input_from_console();
            Assert::IsTrue(result.empty(), L"��������� ������ ���������");
            std::cin.rdbuf(orig_cin);
        }

    };
}
