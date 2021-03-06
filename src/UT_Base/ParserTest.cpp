/*
Phobos 3d
January 2010
Copyright (c) 2005-2011 Bruno Sanches  http://code.google.com/p/phobos3d

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#include <boost/test/unit_test.hpp>

#include <Phobos/Parser.h>

#include <sstream>

using namespace Phobos;

using namespace std;

BOOST_AUTO_TEST_CASE(parser_test)
{
	stringstream str;

	str << "123 abc \"string token\"";
	str << endl << "new line" << endl;
	str << "{}()//comment"<< endl;
	str << "bla" << endl << "bli" << endl;
	str << "end" << endl;
	str << "0.25" << endl;
	str << "0x01" << endl;
	str << ".." << endl;
	str << "/*multi line comment to skuip" << endl;
	str << "more comments line" << endl;
	str << "comment end */" << endl;
	str << "/bla" << endl << "id" << endl;

	Parser parser;
	parser.SetStream(&str);

	String_t token;

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_NUMBER);
	BOOST_REQUIRE(token.compare("123") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("abc") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_STRING);
	BOOST_REQUIRE(token.compare("string token") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("new") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("line") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_OPEN_BRACE);
	BOOST_REQUIRE(token.compare("{") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_CLOSE_BRACE);
	BOOST_REQUIRE(token.compare("}") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_OPEN_PAREN);
	BOOST_REQUIRE(token.compare("(") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_CLOSE_PAREN);
	BOOST_REQUIRE(token.compare(")") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("bla") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("bli") == 0);

	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("end") == 0);

	//
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_NUMBER);
	BOOST_REQUIRE(token.compare("0.25") == 0);

	//hex digit
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_NUMBER);
	BOOST_REQUIRE(token.compare("1") == 0);

	//.. line
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_DOT);
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_DOT);

	//bugged comment /bla
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ERROR);

	//bla
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("bla") == 0);

	//id
	BOOST_REQUIRE(parser.GetToken(&token) == TOKEN_ID);
	BOOST_REQUIRE(token.compare("id") == 0);
}
