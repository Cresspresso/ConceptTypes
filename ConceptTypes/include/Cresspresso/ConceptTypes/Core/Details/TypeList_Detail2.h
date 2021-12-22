#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail2_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail2_h

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
///	Root Header File: <Cresspresso/ConceptTypes.h>
///	Root Include Directory: Cresspresso/ConceptTypes/
///	Root Namespace: Cresspresso::ConceptTypes
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
#include <tuple>

#include "Cresspresso/ConceptTypes/Core/Details/TypeList_Detail1.h"
#include "Cresspresso/ConceptTypes/Core/Details/forall_Detail1.h"
#include "Cresspresso/ConceptTypes/Core/Concepts.h"
#include "Cresspresso/ConceptTypes/Core/Callables.h"



namespace Cresspresso::ConceptTypes
{
	template<std::size_t i, typename T>
	struct EnumeratedIndexAndType
	{
		using index_type = std::size_t;
		inline static constexpr index_type index = i;

		using type = T;
	};



	namespace TypeListTraits
	{
		using TemplateInstance = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return requires{
				requires TypeListTraits::isTemplateInstance<Self>;
			};
		}>;



		/// \brief Equivalent to calling the default constructor like so:
		/// `TypeList<typename std::decay_t<decltype(args)>::type...>()`
		template<typename...TypeIdentityX>
		requires (
			is<std::decay_t<TypeIdentityX>, ConceptTypes::TypeIdentity>
			&& ...
			)
		constexpr TypeList<typename std::decay_t<TypeIdentityX>::type...>
			make_from_type_members(TypeIdentityX&&...) noexcept
		{
			return TypeList<typename std::decay_t<TypeIdentityX>::type...>();
		}



		template<TypeListTraits::isTemplateInstance type_list>
			requires (type_list::size > 0)
		using head = typename type_list::head;

		template<TypeListTraits::isTemplateInstance type_list>
			requires (type_list::size > 0)
		using tail = typename type_list::tail;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance...lists>
			struct Concatenate_ChoiceDetail;

			template<>
			struct Concatenate_ChoiceDetail<>
			{
				using type = TypeList<>;
			};

			template<typename...lhs_elements>
			struct Concatenate_ChoiceDetail<TypeList<lhs_elements...>>
			{
				using type = TypeList<lhs_elements...>;
			};

			template<typename...lhs_elements, typename...rhs_elements>
			struct Concatenate_ChoiceDetail<TypeList<lhs_elements...>, TypeList<rhs_elements...>>
			{
				using type = TypeList<lhs_elements..., rhs_elements...>;
			};

			template<typename...lhs_elements, typename...rhs_lists>
			struct Concatenate_ChoiceDetail<TypeList<lhs_elements...>, rhs_lists...>
			{
				using type = TypeList<lhs_elements..., typename Concatenate_ChoiceDetail<rhs_lists...>::type>;
			};
		}

		template<TypeListTraits::isTemplateInstance...lists>
		using Concatenate_MetaFunction = typename details::Concatenate_ChoiceDetail<lists...>;

		template<TypeListTraits::isTemplateInstance...lists>
		using concatenate = typename Concatenate_MetaFunction<lists...>::type;



		namespace details
		{
			template<std::size_t i, TypeListTraits::isTemplateInstance type_list>
			struct Enumerate_ChoiceDetail;

			template<std::size_t i>
			struct Enumerate_ChoiceDetail<i, TypeList<>>
			{
				using type = TypeList<>;
			};

			template<std::size_t i, typename T0>
			struct Enumerate_ChoiceDetail<i, TypeList<T0>>
			{
				using type = TypeList<EnumeratedIndexAndType<i, T0>>;
			};

			template<std::size_t i, typename T0, typename...Ts>
			struct Enumerate_ChoiceDetail<i, TypeList<T0, Ts...>>
			{
				using type = concatenate<
					TypeList<EnumeratedIndexAndType<i, T0>>,
					typename Enumerate_ChoiceDetail<i + 1, TypeList<Ts...>>::type
				>;
			};
		}

		template<TypeListTraits::isTemplateInstance type_list, std::size_t i>
		using EnumerateOffset_MetaFunction = typename details::Enumerate_ChoiceDetail<i, type_list>;

		template<TypeListTraits::isTemplateInstance type_list>
		using Enumerate_MetaFunction = typename EnumerateOffset_MetaFunction<type_list, 0>::type;

		template<TypeListTraits::isTemplateInstance type_list, std::size_t i>
		using enumerate_offset = typename EnumerateOffset_MetaFunction<type_list, i>::type;

		template<TypeListTraits::isTemplateInstance type_list>
		using enumerate = typename EnumerateOffset_MetaFunction<type_list, 0>::type;



		namespace details
		{
			template<template<typename> typename select, TypeListTraits::isTemplateInstance type_list>
			struct Map_ChoiceDetail;

			template<template<typename> typename select>
			struct Map_ChoiceDetail<select, TypeList<>>
			{
				using type = TypeList<>;
			};

			template<template<typename> typename select, typename T0>
			struct Map_ChoiceDetail<select, TypeList<T0>>
			{
				using type = TypeList<typename select<T0>::type>;
			};

			template<template<typename> typename select, typename T0, typename...Ts>
			struct Map_ChoiceDetail<select, TypeList<T0, Ts...>>
			{
				using type = concatenate<
					TypeList<typename select<T0>::type>,
					typename Map_ChoiceDetail<select, TypeList<Ts...>>::type
				>;
			};
		}

		template<TypeListTraits::isTemplateInstance type_list, template<typename> typename select>
		using Map_MetaFunction = typename details::Map_ChoiceDetail<select, type_list>;

		template<TypeListTraits::isTemplateInstance type_list, template<typename> typename select>
		using map = typename Map_MetaFunction<type_list, select>::type;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance...lists>
			struct Zip_ChoiceDetail;

			template<>
			struct Zip_ChoiceDetail<>
			{
				using type = TypeList<>;
			};

			template<typename...Ts>
			struct Zip_ChoiceDetail<TypeList<Ts...>>
			{
				using type = TypeList<TypeList<Ts>...>;
			};

			template<isTemplateInstance list0, isTemplateInstance...listX>
				requires ((list0::size == listX::size) && ...)
			struct Zip_ChoiceDetail<list0, listX...>
			{
			private:
				template<typename enumeratedIndexAndType0>
				struct select_Detail {
					using type = concatenate<
						TypeList<typename enumeratedIndexAndType0::type>,
						TypeList<at<listX, enumeratedIndexAndType0::index>...>
					>;
				};

			public:
				using type = map<
					enumerate<list0>,
					select_Detail
				>;
			};
		}

		template<TypeListTraits::isTemplateInstance...lists>
		using Zip_MetaFunction = typename details::Zip_ChoiceDetail<lists...>;

		template<TypeListTraits::isTemplateInstance...lists>
		using zip = typename Zip_MetaFunction<lists...>::type;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance type_list, template<typename...> typename meta_function>
			struct Apply_ChoiceDetail;

			template<template<typename...> typename meta_function, typename...Ts>
			struct Apply_ChoiceDetail<TypeList<Ts...>, meta_function>
			{
				using type = typename meta_function<Ts...>::type;
			};
		}

		template<TypeListTraits::isTemplateInstance type_list, template<typename...> typename meta_function>
		using Apply_MetaFunction = typename details::Apply_ChoiceDetail<type_list, meta_function>;

		template<TypeListTraits::isTemplateInstance type_list, template<typename...> typename meta_function>
		using apply = typename Apply_MetaFunction<type_list, meta_function>::type;



		template<template<typename...> typename meta_function>
		struct partial_apply
		{
			template<TypeListTraits::isTemplateInstance type_list>
			using complete_apply = apply<type_list, meta_function>;
		};



		namespace details
		{
			template<TypeListTraits::isTemplateInstance type_list>
			struct ToTuple_ChoiceDetail;

			template<typename...Ts>
			struct ToTuple_ChoiceDetail<TypeList<Ts...>>
			{
				using type = std::tuple<Ts...>;
			};
		}

		template<TypeListTraits::isTemplateInstance type_list>
		using ToTuple_MetaFunction = typename details::ToTuple_ChoiceDetail<type_list>;

		template<TypeListTraits::isTemplateInstance type_list>
		using to_tuple = typename ToTuple_MetaFunction<type_list>::type;



		namespace details
		{
			template<std::size_t n, typename Tuple_>
			struct FromTuple_ChoiceDetail
			{
				using type = concatenate<
					typename FromTuple_ChoiceDetail<n - 1, Tuple_>::type,
					TypeList<std::tuple_element_t<n - 1, Tuple_>>
				>;
			};

			template<typename Tuple_>
			struct FromTuple_ChoiceDetail<0, Tuple_>
			{
				using type = TypeList<>;
			};
		}

		template<typename Tuple_>
		using FromTuple_MetaFunction = typename details::FromTuple_ChoiceDetail<std::tuple_size_v<Tuple_>, Tuple_>;

		template<typename Tuple_>
		using from_tuple = typename FromTuple_MetaFunction<Tuple_>::type;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance TypeList_>
			struct Reverse_ChoiceDetail;

			template<>
			struct Reverse_ChoiceDetail<TypeList<>>
			{
				using type = TypeList<>;
			};

			template<typename T0, typename...Ts>
			struct Reverse_ChoiceDetail<TypeList<T0, Ts...>>
			{
				using type = concatenate<
					typename Reverse_ChoiceDetail<TypeList<Ts...>>::type,
					TypeList<T0>
				>;
			};
		}

		template<TypeListTraits::isTemplateInstance TypeList_>
		using Reverse_MetaFunction = typename details::Reverse_ChoiceDetail<TypeList_>;

		template<TypeListTraits::isTemplateInstance TypeList_>
		using reverse = typename Reverse_MetaFunction<TypeList_>::type;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance TypeListOfTypeLists_>
			struct Flatten_ChoiceDetail;

			template<TypeListTraits::isTemplateInstance...TypeLists_>
			struct Flatten_ChoiceDetail<TypeList<TypeLists_...>>
			{
				using type = TypeListTraits::concatenate<TypeLists_...>;
			};
		}

		template<TypeListTraits::isTemplateInstance TypeListOfTypeLists_>
		using Flatten_MetaFunction = typename details::Flatten_ChoiceDetail<TypeListOfTypeLists_>;

		template<TypeListTraits::isTemplateInstance TypeListOfTypeLists_>
		using flatten = typename Flatten_MetaFunction<TypeListOfTypeLists_>::type;



		namespace details
		{
			template<TypeListTraits::isTemplateInstance TypeList_>
			struct CallByArgs_ChoiceDetail;

			template<typename...Ts>
			struct CallByArgs_ChoiceDetail<TypeList<Ts...>>
			{
				template<typename Callable_, typename...Args>
					requires is<Callable_&&, ConceptTypes::details::VariadicApply_Gcc11Workaround_Detail<Callable, DefineTypeIdentity<Ts>..., Args&&...>>
				static constexpr decltype(auto)
					call(Callable_&& callable, Args&&...args)
					noexcept(noexcept(CallableTraits::call(
						std::declval<Callable_&&>(),
						DefineTypeIdentity<Ts>{}...,
						std::declval<Args&&>()...
						)))
				{
					return CallableTraits::call(
						std::forward<Callable_>(callable),
						DefineTypeIdentity<Ts>{}...,
						std::forward<Args>(args)...
					);
				}
			};
		}

		template<TypeListTraits::isTemplateInstance TypeList_, typename Callable_, typename...Args>
			requires requires(Callable_&& callable, Args&&...args) {
				details::template CallByArgs_ChoiceDetail<TypeList_>::call(
					std::forward<Callable_>(callable),
					std::forward<Args>(args)...
				);
			}
		constexpr decltype(auto)
			call_by_args(Callable_&& callable, TypeList_, Args&&...args)
			noexcept(noexcept(details::template CallByArgs_ChoiceDetail<TypeList_>::call(
				std::declval<Callable_&&>(),
				std::declval<Args&&>()...
			)))
		{
			return details::template CallByArgs_ChoiceDetail<TypeList_>::call(
				std::forward<Callable_>(callable),
				std::forward<Args>(args)...
			);
		}



		namespace details
		{
			template<is<Concept> TConcept>
			constexpr auto AllAre_LambdaDetail = []<typename...Ts>() constexpr noexcept -> bool {
				return (is<Ts, TConcept> && ...);
			};

			template<is<Concept> TConcept>
			constexpr auto AnyAre_LambdaDetail = []<typename...Ts>() constexpr noexcept -> bool {
				return (is<Ts, TConcept> || ...);
			};
		}

		// Satisfied iff `TConcept` is a `Concept`,
		// and `Self` is a `TypeList` template instance,
		// and all elements of `Self` satisfy `TConcept`.
		template<typename TConcept>
		using AllAre = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return requires{
				requires is<TConcept, Concept>;
				requires TypeListTraits::isTemplateInstance<Self>;
				requires CallableTemplateTraits::call(
					details::AllAre_LambdaDetail<TConcept>,
					Self{}
				);
			};
		}>;

		// Satisfied iff `TConcept` is a `Concept`,
		// and `Self` is a `TypeList` template instance,
		// and at least one element of `Self` satisfies `TConcept`.
		template<typename TConcept>
		using AnyAre = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return requires{
				requires is<TConcept, Concept>;
				requires TypeListTraits::isTemplateInstance<Self>;
				requires CallableTemplateTraits::call(
					details::AnyAre_LambdaDetail<TConcept>,
					Self{}
				);
			};
		}>;
	}
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_TypeList_Detail2_h
