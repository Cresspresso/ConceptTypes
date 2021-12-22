#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail2_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail2_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	
///	This file is a private detail of the library implementation.
///	The name, path, and contents of this file may change from version to version.
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



#include <type_traits>
#include <concepts>

#include "Cresspresso/ConceptTypes/Core/Details/forall_Detail1.h"
#include "Cresspresso/ConceptTypes/Core/Concepts.h"



namespace Cresspresso::ConceptTypes
{
	template<typename TemplateArgsTypeList, typename...Args>
	using CallableTemplate = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires TypeListTraits::isTemplateInstance<TemplateArgsTypeList>;
			requires isCallableTemplate<Self, TemplateArgsTypeList, Args...>;
		};
	}>;
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail2_h
