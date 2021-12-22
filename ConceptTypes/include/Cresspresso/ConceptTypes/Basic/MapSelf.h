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
///	Copyright (C) Cresspresso 2021
///	
///	[Creative Commons Attribution 3.0 New Zealand License](http://creativecommons.org/licenses/by/3.0/nz/)
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
