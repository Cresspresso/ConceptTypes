#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_Callables_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_Callables_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	Include Filename: `<Cresspresso/ConceptTypes/Basic/Callables.h>`
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
	namespace details
	{
		template<template<typename...> typename K, typename...Args>
		struct VariadicApply_Gcc11Workaround_MetaFunction_Detail {
			using type = K<Args...>;
		};

		template<template<typename...> typename K, typename...Args>
		using VariadicApply_Gcc11Workaround_Detail = typename VariadicApply_Gcc11Workaround_MetaFunction_Detail<K, Args...>::type;
	}

	template<typename...Args>
	using Callable = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires {
			requires requires(Self&& self, Args&&...args) {
				std::forward<Self>(self)(std::forward<Args>(args)...);
			};
		};
	}>;

	namespace CallableTraits
	{
		static_assert(is<int(*&&)(int, long), Callable<int, long>>);

		template<typename TCallable, typename...Args>
			requires is<TCallable&&, ConceptTypes::details::VariadicApply_Gcc11Workaround_Detail<Callable, Args&&...>>
		constexpr decltype(auto)
			call(TCallable&& callable, Args&&...args)
			noexcept(noexcept(std::declval<TCallable&&>()(std::declval<Args&&>()...)))
		{
			return std::forward<TCallable>(callable)(std::forward<Args>(args)...);
		}

		template<typename TCallable, typename...Args>
			requires is<TCallable, details::VariadicApply_Gcc11Workaround_Detail<Callable, Args...>>
		using ResultType = decltype(CallableTraits::call(std::declval<TCallable>(), std::declval<Args>()...));
	}
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_Callables_h
