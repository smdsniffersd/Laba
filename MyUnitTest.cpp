#include "pch.h"
#include <iostream>

#include "CppUnitTest.h"
#include "input_txt.h"
#include <utility>
#include "config.h"
#include "input_key.h"// Подключение заголовочного файла с тестируемым кодом
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

        // Проверка на повторы
        TEST_METHOD(AllCoordinatesSame)
        {
            std::ofstream testFile("numbers.txt");
            testFile << "3 4\n3 4\n3 4\n3 4";
            testFile.close();

            auto points = input_from_txt();

            Assert::IsTrue(points.empty(), L"Ожидаемые точки должны быть пустыми, если все координаты совпадают.");
        }
        // Проверка на double- количество точек
        TEST_METHOD(DoubleInput)
        {
            std::istringstream buffer("1.1\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());

            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"Ожидаемые значения будут пустыми при double вводе.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("Ошибка: введено нецелое число. Пожалуйста, введите целое число.") != std::string::npos,
                L"Expected error message not found.");
        }
        // Проверка на 0 точек
        TEST_METHOD(ZeroPointsInput)
        {
            std::istringstream buffer("0\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());
            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();
            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"Ожидаемые значения точек будут пустыми при вводе нулевых значений.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("Невозможно провести ни одного отрезка в таком количестве точек.") != std::string::npos,
                L"Expected error message not found.");
        }
        // Проверка на отрицательное значение точек
        TEST_METHOD(NegativePointsInput)
        {
            std::istringstream buffer("-1\n");
            std::streambuf* oldCin = std::cin.rdbuf(buffer.rdbuf());
            std::stringstream outputBuffer;
            std::streambuf* oldCout = std::cout.rdbuf(outputBuffer.rdbuf());

            auto points = input_from_console();

            std::cin.rdbuf(oldCin);
            std::cout.rdbuf(oldCout);

            Assert::IsTrue(points.empty(), L"Ожидается, что при вводе отрицательных значений баллы будут пустыми.");

            std::string output = outputBuffer.str();
            Assert::IsTrue(output.find("Невозможно провести ни одного отрезка в таком количестве точек.") != std::string::npos,
                L"Expected error message not found.");
        }
        // Проверка на 1 точку
        TEST_METHOD(TestOnePointInput)
        {
            std::streambuf* orig_cin = std::cin.rdbuf();
            std::streambuf* orig_cout = std::cout.rdbuf();
            std::istringstream input("1\n");
            std::ostringstream output;
            std::cin.rdbuf(input.rdbuf());
            std::cout.rdbuf(output.rdbuf());

            auto result = input_from_console();

            std::string expected_output = "Введите общее количество точек:\n"
                "Невозможно провести ни одного отрезка в таком количестве точек.\n";
            Assert::AreEqual(expected_output, output.str(), L"Неверное сообщение об ошибке при вводе одной точки.");
            Assert::IsTrue(result.empty(), L"Вектор точек должен быть пустым при вводе одной точки.");

            std::cin.rdbuf(orig_cin);
            std::cout.rdbuf(orig_cout);
        }
       
        // Проверка на повторы в разных местах ввода
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

            Assert::IsTrue(points.empty(), L"Ожидаемые точки должны быть пустыми, если все координаты совпадают.");
        }
        // Проверка случайных значений
        TEST_METHOD(SearchMinPointsTest)
        {
            vector<std::pair<int, int>> testPoints = { {-10, -10}, {10, 10}, {0, 0}, {5, 5} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(testPoints);

            Assert::AreEqual(-10, result.first.first, L"Некорректная x-координата первой точки.");
            Assert::AreEqual(-10, result.first.second, L"Некорректная y-координата первой точки.");
            Assert::AreEqual(10, result.second.first, L"Некорректная x-координата второй точки.");
            Assert::AreEqual(10, result.second.second, L"Некорректная y-координата второй точки.");
        }
        // Большая разница между координатами
        TEST_METHOD(FindOptimalPoints)
        {
            vector<pair<int, int>> points = { {INT_MAX, INT_MAX}, {INT_MIN, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(points);

            Assert::AreEqual(INT_MAX, result.first.first, L"Некорректная x-координата первой точки.");
            Assert::AreEqual(INT_MAX, result.first.second, L"Некорректная y-координата первой точки.");
            Assert::AreEqual(INT_MAX, result.second.first, L"Некорректная x-координата второй точки.");
            Assert::AreEqual(INT_MIN, result.second.second, L"Некорректная y-координата второй точки.");
        }
        
        // Проверка на точки лежащие на одной линии
        TEST_METHOD(SearchPointsOnOneLine)
        {
            vector<std::pair<int, int>> testPoints = { {0, 0}, {1, 1}, {2, 2}, {3, 3} };

            pair<pair<int, int>, pair<int, int>> result = search_min_points(testPoints);

            Assert::AreEqual(0, result.first.first, L"Некорректная x-координата первой точки.");
            Assert::AreEqual(0, result.first.second, L"Некорректная y-координата первой точки.");
            Assert::AreEqual(1, result.second.first, L"Некорректная x-координата второй точки.");
            Assert::AreEqual(1, result.second.second, L"Некорректная y-координата второй точки.");
        }

        // Проверка на большие значения из txt
        TEST_METHOD(TestInputFromTxtWithLargeNumbers)
        {
            std::ofstream test_file("test_numbers.txt");
            if (!test_file)
            {
                Assert::Fail(L"Ошибка создания тестового файла");
                return;
            }
            test_file << "12345678901234567890 98765432109876543210" << endl;
            test_file << "98765432109876543210 12345678901234567890" << endl;
            test_file << "99999999999999999999 88888888888888888888" << endl;
            test_file << "88888888888888888888 99999999999999999999" << endl;
            test_file.close();

            vector<pair<int, int>> result = input_from_txt();

            Assert::IsTrue(result.empty(), L"Ожидается пустой результат");

            remove("test_numbers.txt");
        }
        // Проверка на большие отрицательные значения из txt 
        TEST_METHOD(TestInputFromTxtWithMINNumbers)
        {
            std::ofstream test_file("test_numbers.txt");
            if (!test_file)
            {
                Assert::Fail(L"Ошибка создания тестового файла");
                return;
            }
            test_file << "-12345678901234567890 -98765432109876543210" << endl;
            test_file << "-98765432109876543210 -12345678901234567890" << endl;
            test_file << "-99999999999999999999 -88888888888888888888" << endl;
            test_file << "-88888888888888888888 -99999999999999999999" << endl;
            test_file.close();

            vector<pair<int, int>> result = input_from_txt();
            Assert::IsTrue(result.empty(), L"Ожидается пустой результат");

            remove("test_numbers.txt");
        }
        // Проверка на большие значения из консоли
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

            Assert::IsTrue(result.empty(), L"Ожидается пустой результат");

            std::cin.rdbuf(orig_cin);
        }
        // Проверка на большие отрицательные значения из консоли
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
            Assert::IsTrue(result.empty(), L"Ожидается пустой результат");
            std::cin.rdbuf(orig_cin);
        }

    };
}
