#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail1_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail1_h

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



#include <cstddef>
#include <type_traits>
#include <concepts>



namespace Cresspresso::ConceptTypes
{
	namespace details
	{
		template<std::size_t i, typename T0, typename...Ts>
			requires (i < 1 + sizeof...(Ts))
		struct TypeAt_ChoiceDetail {
			using type = typename TypeAt_ChoiceDetail<i - 1, Ts...>::type;
		};

		template<typename T0, typename...Ts>
		struct TypeAt_ChoiceDetail<0, T0, Ts...> {
			using type = T0;
		};
	}

	template<std::size_t i, typename...Ts>
		requires (sizeof...(Ts) >= 1 && i < sizeof...(Ts))
	struct TypeAtIndex_MetaFunction {
		using type = typename details::TypeAt_ChoiceDetail<i, Ts...>::type;
	};

	template<std::size_t i, typename...Ts>
		requires (sizeof...(Ts) >= 1 && i < sizeof...(Ts))
	using type_at_index = typename TypeAtIndex_MetaFunction<i, Ts...>::type;



	template<typename...Ts>
	struct TypeList;

	template<>
	struct TypeList<>
	{
		inline static constexpr std::size_t size = 0;
	};

	template<typename T0>
	struct TypeList<T0>
	{
		inline static constexpr std::size_t size = 1;

		using head = T0;
		using tail = TypeList<>;

		template<std::size_t i>
			requires (i < 1)
		using at = ConceptTypes::type_at_index<i, T0>;
	};

	template<typename T0, typename...Ts>
	struct TypeList<T0, Ts...>
	{
		inline static constexpr std::size_t size = 1 + sizeof...(Ts);

		using head = T0;
		using tail = TypeList<Ts...>;

		template<std::size_t i>
			requires (i < 1 + sizeof...(Ts))
		using at = ConceptTypes::type_at_index<i, T0, Ts...>;
	};



	namespace TypeListTraits
	{
		namespace details
		{
			template<typename Self>
			struct TemplateInstance_ChoiceDetail {
				static constexpr bool value = false;
			};

			template<typename...Ts>
			struct TemplateInstance_ChoiceDetail<TypeList<Ts...>> {
				static constexpr bool value = true;
			};
		}

		template<typename Self>
		concept isTemplateInstance
			= details::TemplateInstance_ChoiceDetail<Self>::value;



		/// \brief Equivalent to calling the default constructor like so:
		/// `TypeList<types...>()`
		template<typename...types>
		constexpr TypeList<types...> make{};



		template<TypeListTraits::isTemplateInstance type_list, std::size_t i>
		using at = typename type_list::template at<i>;

		template<TypeListTraits::isTemplateInstance type_list, std::size_t i>
		struct At_MetaFunction {
			using type = at<type_list, i>;
		};
	}
}



#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail1_h
