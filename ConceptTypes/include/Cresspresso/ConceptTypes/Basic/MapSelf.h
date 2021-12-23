#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_MapSelf_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_MapSelf_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	Include Filename: `<Cresspresso/ConceptTypes/Basic/MapSelf.h>`
///	
///	
///	
///	## CONTRIBUTORS
///	```json
///	[
///		{
///			"Date": "22 Dec 2021",
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
///	Root Header File: `<Cresspresso/ConceptTypes.h>`
///	Root Include Directory: `Cresspresso/ConceptTypes/`
///	Root Namespace: `Cresspresso::ConceptTypes`
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



#include <utility>
#include <type_traits>
#include <concepts>

#include "Cresspresso/ConceptTypes/Core/Concepts.h"



namespace Cresspresso::ConceptTypes
{
	template<auto select, typename TheConcept>
	using DefineMapSelfConcept = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires isConcept<TheConcept>;
			requires is<
				typename decltype(CallableTemplateTraits::call(select, TypeListTraits::make<Self>))::type,
				TheConcept
			>;
		};
	}>;
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_MapSelf_h
