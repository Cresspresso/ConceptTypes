#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_Concepts_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_Concepts_h

///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Header File
///	Include Filename: `<Cresspresso/ConceptTypes/Core/Concepts.h>`
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

#include "Cresspresso/ConceptTypes/Core/Details/TypeList_Detail1.h"
#include "Cresspresso/ConceptTypes/Core/Details/forall_Detail1.h"



namespace Cresspresso::ConceptTypes
{
	namespace details
	{
		template<typename Self>
		concept isReturnBool_Detail = requires{
			requires std::same_as<std::remove_cvref_t<Self>, bool>;
		};
	}

	template<typename Self>
	concept isConceptConstant = requires{
		{ Self::value } -> details::isReturnBool_Detail;
	};

	template<bool value_>
	struct DefineConceptConstant {
		static constexpr bool value = value_;
	};



	template<typename Self>
	concept isConcept
		= forall(
			[]<typename InputSelf>() constexpr noexcept -> bool {
				return requires {
					requires isConceptConstant<typename Self::template Constant<InputSelf>>;
				};
			},
			TypeListTraits::make<
				TypeList<void>,
				TypeList<int>,
				TypeList<char const*>,
				TypeList<long&>,
				TypeList<int(*)(int, int, int)>,
				TypeList<int(&)[10]>,
				TypeList<decltype([]<typename>(){})>
			>
		);



	template<typename Self>
	concept isConceptCallable
		= forall(
			[]<typename InputSelf>() constexpr noexcept -> bool {
				return requires{
					requires isCallableTemplate<Self const&, TypeList<InputSelf>>;
					requires std::convertible_to<
						CallableTemplateTraits::ResultType<Self const&, TypeList<InputSelf>>,
						bool
					>;
					requires noexcept(static_cast<bool>(CallableTemplateTraits::call(
						std::declval<Self const&>(),
						TypeListTraits::make<InputSelf>
					)));
				};
			},
			TypeListTraits::make<
				TypeList<void>,
				TypeList<int>,
				TypeList<char const*>,
				TypeList<long&>,
				TypeList<int(*)(int, int, int)>,
				TypeList<int(&)[10]>,
				TypeList<decltype([]<typename>() {}) >
			>
		);



	template<auto lambda>
	struct DefineConcept {
		template<typename Self>
		using Constant = DefineConceptConstant < requires{
			requires isConceptCallable<decltype(lambda)>;
			requires CallableTemplateTraits::call(lambda, TypeListTraits::make<Self>);
		} > ;
	};

	using Concept = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires isConcept<Self>;
		};
	}>;



	using ConceptConstant = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires isConceptConstant<Self>;
		};
	}>;



	template<typename Self, typename TheConcept>
	concept is = isConcept<TheConcept>
		&& TheConcept::template Constant<Self>::value; // `Self` must satisfy `TheConcept`.



	using ConceptCallable = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires isConceptCallable<Self>;
		};
	}>;



	template<typename Self, typename TheConcept>
		requires isConcept<std::decay_t<TheConcept>>
	constexpr bool type_argument_is(TheConcept&&) noexcept
	{
		return is<Self, std::decay_t<TheConcept>>;
	}



	template<typename Self, typename TheConceptCallable>
		requires is<TheConceptCallable&&, ConceptCallable>
	constexpr bool type_argument_satisfies(TheConceptCallable&& callable) noexcept
	{
		return static_cast<bool>(CallableTemplateTraits::call(
			std::forward<TheConceptCallable>(callable),
			TypeListTraits::make<Self>
		));
	}



	using TypeIdentity = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			typename Self::type;
		};
	}>;

	namespace TypeIdentityTraits
	{
		template<is<TypeIdentity> TheTypeIdentity>
		using type = typename TheTypeIdentity::type;
	}

	template<typename T>
	struct DefineTypeIdentity {
		using type = T;
	};



	template<typename SelfMetaFunction, typename TheConcept>
		requires is<std::decay_t<SelfMetaFunction>, TypeIdentity>
			&& is<std::decay_t<TheConcept>, Concept>
	constexpr bool argument_type_member_is(SelfMetaFunction&&, TheConcept&&) noexcept
	{
		return is<typename std::decay_t<SelfMetaFunction>::type, std::decay_t<TheConcept>>;
	}



	template<typename SelfMetaFunction, typename TheConceptCallable>
		requires is<std::decay_t<SelfMetaFunction>, TypeIdentity>
			&& is<TheConceptCallable&&, ConceptCallable>
	constexpr bool argument_type_member_satisfies(SelfMetaFunction&&, TheConceptCallable&& callable) noexcept
	{
		return type_argument_satisfies<typename std::decay_t<SelfMetaFunction>::type>(std::forward<TheConceptCallable>(callable));
	}
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_Concepts_h
