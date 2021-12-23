#ifndef CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h
#define CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	Include Filename: <Cresspresso_Tests/ConceptTypes_Tests/Common.h>
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



#include <type_traits>

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	template<bool value, typename...T>
	constexpr bool bool_sink = std::is_same_v<void, std::void_t<T...>> && value;

	template<typename...T>
	constexpr bool true_sink = bool_sink<true, T...>;

	template<typename...T>
	constexpr bool false_sink = bool_sink<false, T...>;
}

#endif // CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h
