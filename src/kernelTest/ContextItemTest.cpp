/*
Phobos 3d
  March 2010

  Copyright (C) 2005-2010 Bruno Crivelari Sanches

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Bruno Crivelari Sanches bcsanches@gmail.com
*/

#include <boost/test/unit_test.hpp>

#include <PH_ContextItem.h>

using namespace Phobos;

BOOST_AUTO_TEST_CASE(contextItem_basic)
{
	ContextItem_c a("test"), b("before");

	BOOST_REQUIRE(a.GetName().compare("test") == 0);
	BOOST_REQUIRE(b.GetName().compare("before") == 0);

	BOOST_REQUIRE(b < a);
	BOOST_REQUIRE(!(a < b));

	ContextItem_c c("test");
	BOOST_REQUIRE(!(a < c));
}
