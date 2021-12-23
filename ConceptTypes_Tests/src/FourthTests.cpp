
///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Source File
///	Filename: FourthTests.cpp
///	
///	
///	
///	## CONTRIBUTORS
///	```json
///	[
///		{
///			"Date": "23 Dec 2021",
///			"Contributor": "Elijah Shadbolt",
///			"Email": "cresspresso@gmail.com"
///		}
///	]
///	```
///	
///	
///	
///	## PROJECT
///	
///	Title: ConceptTypes
///	Version: 1.0.0
///	
///	Language: C++
///	Standard: C++20
///	Root Include Directory: Cresspresso_Tests/ConceptTypes_Tests/
///	Root Namespace: Cresspresso_Tests::ConceptTypes_Tests
///	
///	
///	
///	### LICENSE
/// 
/// Copyright 2021 Cresspresso
/// 
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
/// 
///     http://www.apache.org/licenses/LICENSE-2.0
/// 
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissionsand
/// limitations under the License.
///	
///	
///	
///	====== ^^^^ FILE HEADER ======================================================================



#include <concepts>
#include <string>
#include <iostream>
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/FourthTests.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	namespace
	{
		using namespace Cresspresso::ConceptTypes;
		
		

		static_assert(isCallableTemplate<
			decltype([]<typename T0, std::same_as<long> T1>(char const*) {
				return 42;
			}),
			TypeList<int, long>,
			char const*
		>);

		static_assert(!isCallableTemplate<
			int,
			TypeList<int, long>,
			char const*
		>);



		static_assert(42 == CallableTemplateTraits::call(
			[]<typename T0, std::same_as<long> T1>(char const*) constexpr {
				return 42;
			},
			TypeListTraits::make<int, long>,
			"s"
		));



		static_assert(noexcept(forall([]<typename Self>() constexpr noexcept -> bool {
			return true;
		}, TypeListTraits::make<TypeList<int>>)));

		static_assert(!noexcept(forall([]<typename Self>() constexpr -> bool {
			return true;
		}, TypeListTraits::make<TypeList<int>>)));



		static_assert(isCallableTemplate<
			decltype([]<typename Self>() constexpr noexcept -> bool {
				return requires {
					requires true;
				};
			}),
			TypeList<int>
		>);

		static_assert(is<
			decltype([]<typename Self>() constexpr noexcept -> bool {
				return requires {
					requires true;
				};
			}),
			ConceptCallable
		>);
	}

	void fourth_tests()
	{
	}
}
