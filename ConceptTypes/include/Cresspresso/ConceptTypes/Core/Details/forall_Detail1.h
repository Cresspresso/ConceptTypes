#ifndef CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail1_h
#define CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail1_h

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



#include <utility>
#include <type_traits>
#include <concepts>

#include "Cresspresso/ConceptTypes/Core/Details/TypeList_Detail1.h"



namespace Cresspresso::ConceptTypes
{
	namespace CallableTemplateTraits
	{
		namespace details
		{
			template<TypeListTraits::isTemplateInstance TemplateArgsTypeList>
			struct CallTemplate_ChoiceDetail;

			template<typename...TemplateArgs>
			struct CallTemplate_ChoiceDetail<TypeList<TemplateArgs...>>
			{
				template<typename TCallable, typename...Args>
					requires requires(TCallable&& callable, Args&&...args) {
					std::forward<TCallable>(callable).template operator()<TemplateArgs...>(std::forward<Args>(args)...);
				}
				static constexpr decltype(auto) call(TCallable&& callable, Args&&...args)
					noexcept(noexcept(std::declval<TCallable&&>().template operator()<TemplateArgs...>(std::declval<Args&&>()...)))
				{
					return std::forward<TCallable>(callable).template operator()<TemplateArgs...>(std::forward<Args>(args)...);
				}
			};
		}
	}

	template<typename Self, typename TemplateArgsTypeList, typename...Args>
	concept isCallableTemplate = requires{
		requires TypeListTraits::isTemplateInstance<TemplateArgsTypeList>;
		requires requires(Self&& self, Args&&...args) {
			CallableTemplateTraits::details::template CallTemplate_ChoiceDetail<TemplateArgsTypeList>::call(
				std::forward<Self>(self),
				std::forward<Args>(args)...
			);
		};
	};

	namespace CallableTemplateTraits
	{
		template<typename TCallable, TypeListTraits::isTemplateInstance TemplateArgsTypeList, typename...Args>
			requires isCallableTemplate<TCallable&&, TemplateArgsTypeList, Args&&...>
		constexpr decltype(auto)
			call(TCallable&& callable, TemplateArgsTypeList, Args&&...args)
			noexcept(noexcept(details::template CallTemplate_ChoiceDetail<TemplateArgsTypeList>::call(
				std::declval<TCallable&&>(),
				std::declval<Args&&>()...
				)))
		{
			return details::template CallTemplate_ChoiceDetail<TemplateArgsTypeList>::call(
				std::forward<TCallable>(callable),
				std::forward<Args>(args)...
			);
		}

		template<typename TCallable, TypeListTraits::isTemplateInstance TemplateArgsTypeList, typename...Args>
			requires isCallableTemplate<TCallable, TemplateArgsTypeList, Args...>
		using ResultType = decltype(CallableTemplateTraits::call(
			std::declval<TCallable>(),
			std::declval<TemplateArgsTypeList>(),
			std::declval<Args>()...
		));
	}



	/// Let `lambda` be a function object
	/// which has an instance member function template `operator()<typename...Tx>()`,
	/// where each template type argument `Tx` may or may not have constraints,
	/// and will always compile successfully when given the correct number and types of template arguments.
	/// 
	/// This `forall` bool is true iff `lambda` returns true
	/// for all possible types `Tx...`.
	/// 
	/// If the `lambda` would return false for at least one template parameter `Tx`,
	/// then `forall` should be false.
	/// 
	/// Currently this is impossible to enforce in C++,
	/// so the best we can do is manually give it an sequence of arbitrary template parameters `ExampleTypeLists`
	/// to test the lambda on each one (calling `operator()` for each `ExampleTypeList` in an arbitrary order).
	/// 
	
	template<typename TCallable, TypeListTraits::isTemplateInstance...ExampleTypeListX>
	requires ((
			isCallableTemplate<TCallable&, ExampleTypeListX>
			&& std::convertible_to<
				typename CallableTemplateTraits::template ResultType<TCallable&, ExampleTypeListX>,
				bool
			>
		) && ...)
	constexpr bool forall(TCallable&& lambda, TypeList<ExampleTypeListX...>)
		noexcept((
			noexcept(static_cast<bool>(CallableTemplateTraits::call(std::declval<TCallable&>(), ExampleTypeListX{})))
			&& ...
			)) // For some reason this needs the extra pair of parentheses.
	{
		return ((
			static_cast<bool>(CallableTemplateTraits::call( (lambda), ExampleTypeListX{} ))
		) && ...);
	}
}

#endif // CRESSPRESSO_ConceptTypes_HeaderGuard_forall_Detail1_h
