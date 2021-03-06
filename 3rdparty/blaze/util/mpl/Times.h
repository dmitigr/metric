//=================================================================================================
/*!
//  \file blaze/util/mpl/Times.h
//  \brief Header file for the Times_t alias template
//
//  Copyright (C) 2012-2020 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_UTIL_MPL_TIMES_H_
#define _BLAZE_UTIL_MPL_TIMES_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include "../../util/IntegralConstant.h"
#include "../../util/typetraits/CommonType.h"


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Compile time integral multiplication.
// \ingroup mpl
//
// The Times_t alias template returns the product of the two given template arguments \a T1 and
// \a T2. In order for Times_t to be able to multiply the two types, both arguments are required
// to have a nested member \a value. The result of the multiplication can be accessed via the
// nested member \a value, the resulting type is available via the nested type \a ValueType.

   \code
   blaze::Times_t< Int_t<3> , Int_t<2>  >::value      // Results in 6
   blaze::Times_t< Long_t<3>, Int_t<2>  >::ValueType  // Results in long
   blaze::Times_t< Int_t<3> , Long_t<2> >::ValueType  // Results in long
   \endcode
*/
template< typename T1    // Type of the first compile time value
        , typename T2 >  // Type of the second compile time value
using Times_t =
   IntegralConstant< CommonType_t< typename T1::ValueType, typename T2::ValueType >
                   , ( T1::value * T2::value ) >;
//*************************************************************************************************

} // namespace blaze

#endif
