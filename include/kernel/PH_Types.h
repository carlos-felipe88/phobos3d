/*
Phobos 3d
  version 0.0.1, January 2010

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

#ifndef PH_TYPES_H
#define PH_TYPES_H

//TODO: mudei aki
//necessario pois o size_t esta definido nele
#include <cstring>

namespace Phobos
{

#ifdef PH_WIN32
		typedef unsigned char		UInt8_t;			//u8
		typedef char				SInt8_t;			//s8
		typedef unsigned short		UInt16_t;		//u16
		typedef short				SInt16_t;		//s16
		typedef unsigned int		UInt32_t;		//u32
		typedef int					SInt32_t;		//s32
		typedef __int64				SInt64_t;		//s64
		typedef unsigned __int64	UInt64_t;		//u64
		typedef unsigned int		UInt_t;			//platform dependent type, never store or transmit (u)
  		typedef int					SInt_t;			//platform dependent type, never store or transmit (s)
  		typedef float				Float32_t;		//fp32
  		typedef double				Float64_t;		//pf64
  		typedef Float32_t			Float_t;			//platform dependent type, never store or transmit (f)
		typedef void *				Handler_t;		//platform dependent type, never store or transmit (h)
		typedef bool				Bool_t;			//b
		typedef UInt_t				ErrorHandler_t;	//platform dependent type, never store or transmit (eh)
		typedef SInt8_t				Char_t;			//ch
		typedef size_t				Size_t;			//platform dependent type, never store or transmit (sz)
		typedef UInt32_t			ObjectType_t;

#else

    //TODO:mudei aki
    //verifique para ver se tem todos os tipos necessários
    #ifdef PH_LINUX

        typedef unsigned char		UInt8_t;			//u8
		typedef char				SInt8_t;			//s8
		typedef unsigned short		UInt16_t;		//u16
		typedef short				SInt16_t;		//s16
		typedef unsigned int		UInt32_t;		//u32
		typedef int					SInt32_t;		//s32
		typedef long long   		SInt64_t;		//s64
		typedef unsigned long long	UInt64_t;		//u64
		typedef unsigned int		UInt_t;			//platform dependent type, never store or transmit (u)
  		typedef int					SInt_t;			//platform dependent type, never store or transmit (s)
  		typedef float				Float32_t;		//fp32
  		typedef double				Float64_t;		//pf64
  		typedef float   			Float_t;			//platform dependent type, never store or transmit (f)
		typedef void *				Handler_t;		//platform dependent type, never store or transmit (h)
		typedef bool				Bool_t;			//b
		typedef UInt_t				ErrorHandler_t;	//platform dependent type, never store or transmit (eh)
		typedef SInt8_t				Char_t;			//ch
		typedef size_t				Size_t;			//platform dependent type, never store or transmit (sz)
		typedef UInt32_t			ObjectType_t;

    #endif

#endif //WIN32

}

template <typename T>
struct Rect_s
{
	inline Rect_s():
		tWidth(0),
		tHeight(0)
	{
		tOrigin[0] = tOrigin[1] = 0;
	}

	inline Rect_s(const Rect_s &rhs):
		tWidth(rhs.tWidth),
		tHeight(rhs.tHeight)
	{
		tOrigin[0] = rhs.tOrigin[0];
		tOrigin[1] = rhs.tOrigin[1];
	}


	inline Rect_s &operator=(const Rect_s &other)
	{
		tOrigin[0] = other.tOrigin[0];
		tOrigin[1] = other.tOrigin[1];

		tWidth = other.tWidth;
		tHeight = other.tHeight;

		return *this;
	}

	T tOrigin[2];
	T tWidth;
	T tHeight;
};


#endif //PH_TYPES_H
