// iterate_over_standard_string.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <locale>
#include <codecvt>
#include <sstream>

int main()
{
	std::cout << "EXAMPLE 1: Iterate over std::string\n";
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	std::cout << "1) range-based for loop\n";
	for (char& c : alphabet)
		std::cout << (char)toupper(c) << ' ';
	std::cout << std::endl;

	std::cout << "2) looping through the characters with an iterator\n";
	for (std::string::iterator it = alphabet.begin();
		it != alphabet.end(); ++it)
		std::cout << (char)toupper(*it) << ' ';
	std::cout << std::endl;

	std::cout << "3) looping through the characters with an old-fashioned for-loop\n";
	for (std::string::size_type i = 0;
		i <  alphabet.size(); ++i)
		std::cout << (char)toupper(alphabet[i]) << ' ';
	std::cout << std::endl;
	char szStr[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};
	char* pszStr = szStr;

	std::cout << "4) looping through the characters of a null-terminated character array\n";
	for (char* it = pszStr; *it != '\0'; ++it)
		std::cout << (char)toupper(*it) << ' ';
	std::cout << std::endl;

	std::cout << "5) using for_each (#include <algorithm>) and a lambda\n";
	std::for_each(alphabet.begin(), alphabet.end(), [](char c)
	{
		std::cout << (char)toupper(c) << ' ';
	});
	std::cout << std::endl;

	std::cout << "EXAMPLE 2: std::string to PWCHAR (via a wchar_t*)\n";
	std::cout << "A) convert to a std::wstring\n";
	std::wstring wAlphabet = std::wstring(alphabet.begin(), alphabet.end());
	std::cout << "B) assign the std::wstring to a wchar_t*,  which is PWCHAR in WIN-32\n";
	std::cout << "   a value of type \"const wchar_t*\" cannot be used to initialize an entity of \"PWCHAR\"\n";
	std::cout << "   therefore a const_cast<PWCHAR>(var.c_str()) is necessary\n";
	PWCHAR pszAlphabet = const_cast<PWCHAR>(wAlphabet.c_str());
	std::wcout << pszAlphabet << std::endl;

	std::cout << "EXAMPLE 3: char* to PWCHAR (via a wchar_t*)\n";
	const char* mbstr = pszStr;
	const size_t sizeInWords = 8;// std::strlen(pszStr) + 1;
	size_t* pReturnValue = new size_t();
	//size_t count = std::strlen(pszStr);
	size_t count = _TRUNCATE;
	wchar_t* wcstr = new wchar_t[sizeInWords];
	errno_t err = mbstowcs_s(pReturnValue
		, wcstr
		, sizeInWords
		, mbstr
		, count
	);
	if (!err)
	{
		std::cout << "pReturnValue: " << *pReturnValue << std::endl;
	}
	if (err == STRUNCATE)
		std::cout << "truncation occurred\n";
	//std::wcout << wcstr << std::endl;
	pszAlphabet = wcstr;
	std::wcout << pszAlphabet << std::endl;

	{
		std::cout << "EXAMPLE 4: PWCHAR to std::string\n";
		PWCHAR pwchar = (PWCHAR)L"abcdefghijklmnopqrstuvwxyz";
		std::wstring wstr(pwchar);
		typedef std::codecvt_utf8<wchar_t> ccvt;
		std::wstring_convert<ccvt> owstring_convert;
		std::string str = owstring_convert.to_bytes(wstr);
	}

	// a good article about string stuff, found at:
	// https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
	{
		std::cout << "EXAMPLE 5: using std::wstringstream\n";
		std::wstringstream ws_stream;
		char pch[] = { 'c', 'h', 'a', 'r', '*', '\0' };
		std::string str("narrow string");
		std::wstring wstr = L"wide string";
		wchar_t wch[] = {L'w', L'c', L'h' , L'a' , L'r' , L'_', L't', '\0' };
		PWCHAR pwchar = (PWCHAR)L"PWCHAR";
		ws_stream << pch << '\n'
			<< str.c_str() << '\n'
			<< wstr << '\n'
			<< wch << '\n'
			<< pch << '\n'
			<< pwchar << '\n';
		std::wstring all = ws_stream.str();
		std::wcout << all;
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
