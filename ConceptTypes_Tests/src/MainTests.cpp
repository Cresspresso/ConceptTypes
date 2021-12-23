
///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Source File
///	Filename: MainTests.cpp
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



#include <iostream>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/Example2.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/OtherTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/ThirdTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/FourthTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/TypeListTests.h"

int main()
{
	Cresspresso_Tests::ConceptTypes_Tests::example2();
	Cresspresso_Tests::ConceptTypes_Tests::other_tests();
	Cresspresso_Tests::ConceptTypes_Tests::third_tests();
	Cresspresso_Tests::ConceptTypes_Tests::fourth_tests();
	Cresspresso_Tests::ConceptTypes_Tests::type_list_tests();

	std::cout << "All tests completed." << std::endl;
}
