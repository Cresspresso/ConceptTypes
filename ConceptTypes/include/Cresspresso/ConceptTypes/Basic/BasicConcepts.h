#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_BasicConcepts_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_BasicConcepts_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	Include Filename: `<Cresspresso/ConceptTypes/Basic/BasicConcepts.h>`
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
	/// Used in requires expressions to indicate an expression type is usually a useful (non-void) type,
	/// but it may be void, depending on the template arguments.
	/// 
	/// For example:
	/// 
	///	template<class Self>
	///	concept example1 = requires(Self& self) {
	///		// Implies func returns void, or something to be discarded.
	///		self.func();
	///	};
	/// 
	///	template<class Self>
	///	concept example2 = requires(Self& self) {
	///		// Implies func returns a useful value, or void for certain template arguments.
	///		{ self.func() } -> is<MaybeVoid>;
	///	};
	///
	using MaybeVoid = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return true;
	}>;



	template<typename Other>
	using SameAs = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires std::same_as<Self, Other>;
		};
	}>;



	template<typename Base>
	using DerivedFrom = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::derived_from<Self, Base>;
		};
	}>;



	template<typename To>
	using ConvertibleTo = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::convertible_to<Self, To>;
		};
	}>;



	using ContextuallyConvertibleToBool = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires requires(std::add_rvalue_reference_t<Self>(&f)()) {
				f() ? 1 : 0;
			};
		};
	}>;



	using MoveConstructible = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::move_constructible<Self>;
		};
	}>;



	using CopyConstructible = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::copy_constructible<Self>;
		};
	}>;



	using Movable = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::movable<Self>;
		};
	}>;



	using Copyable = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires std::copyable<Self>;
		};
	}>;
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_BasicConcepts_h
