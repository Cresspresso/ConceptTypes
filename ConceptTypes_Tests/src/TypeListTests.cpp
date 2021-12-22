
#include <utility>
#include <concepts>
#include <string>
#include <tuple>
#include <iostream>
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/TypeListTests.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	namespace
	{
		using namespace Cresspresso::ConceptTypes;



		static_assert(std::same_as<
			TypeListTraits::zip<
				TypeList<int, long, char>,
				TypeList<int const, long const, char const>,
				TypeList<int*, long*, char*>
			>,
			TypeList<
				TypeList<int, int const, int*>,
				TypeList<long, long const, long*>,
				TypeList<char, char const, char*>
			>
		>);



		static_assert(std::same_as<
			TypeListTraits::to_tuple<TypeList<int, long&>>,
			std::tuple<int, long&>
		>);



		static_assert(std::same_as<
			TypeListTraits::from_tuple<std::tuple<char, short&>>,
			TypeList<char, short&>
		>);



		static_assert(std::same_as<
			TypeListTraits::reverse<TypeList<int, char, long, char const*>>,
			TypeList<char const*, long, char, int>
		>);



		static_assert(std::same_as<
			TypeListTraits::flatten<TypeList<
				TypeList<int, char>,
				TypeList<long, char const*, int>
			>>,
			TypeList<int, char, long, char const*, int>
		>);




		static_assert(TypeListTraits::isTemplateInstance<std::decay_t<decltype(TypeListTraits::make<int, int>)>>);



		static_assert(CallableTemplateTraits::call(
			[]<typename Self, typename To>() constexpr noexcept -> bool {
				return std::same_as<Self, To>;
			},
			TypeListTraits::make<int, int>
		));


		static_assert(!CallableTemplateTraits::call(
			[]<typename Self, typename To>() constexpr noexcept -> bool {
				return std::same_as<Self, To>;
			},
			TypeListTraits::make<int, long>
		));


		static_assert(is<DefineTypeIdentity<int>, TypeIdentity>);

		static_assert(is<
			decltype(([](is<TypeIdentity> auto t0, is<TypeIdentity> auto t1){})),
			Callable<
				DefineTypeIdentity<int>,
				DefineTypeIdentity<long>
			>
		>);

		static_assert(5 == TypeListTraits::call_by_args(
			[](is<TypeIdentity> auto t0, is<TypeIdentity> auto t1, int x, char const*) constexpr noexcept -> int {
				static_assert(std::same_as<typename TypeIdentityTraits::template type<decltype(t0)>, int>);
				static_assert(std::same_as<typename TypeIdentityTraits::template type<decltype(t1)>, char>);
				return x + 1;
			},
			TypeListTraits::make<int, char>,
			4,
			"hi"
		));

		static_assert(CallableTemplateTraits::call(
			[]<typename...Ts>() constexpr noexcept -> bool
			{
				return (std::same_as<Ts, int> && ...);
			},
			TypeListTraits::make<
				int,
				int,
				int
			>
			));

		static_assert(!CallableTemplateTraits::call(
			[]<typename...Ts>() constexpr noexcept -> bool
			{
				return (std::same_as<Ts, int> && ...);
			},
			TypeListTraits::make<
				int,
				long,
				int
			>
			));



		static_assert(is<
			TypeList<int, int, int>,
			TypeListTraits::AllAre<SameAs<int>>
		>);

		static_assert(!is<
			TypeList<int, long, int>,
			TypeListTraits::AllAre<SameAs<int>>
		>);



		static_assert(is<
			TypeList<int, int, int>,
			TypeListTraits::AnyAre<SameAs<int>>
		>);

		static_assert(is<
			TypeList<int, long, int>,
			TypeListTraits::AnyAre<SameAs<int>>
		>);

		static_assert(!is<
			TypeList<short, long, int*>,
			TypeListTraits::AnyAre<SameAs<int>>
		>);



		static_assert(is<
			TypeList<
				TypeList<int, long>,
				TypeList<char, short>,
				TypeList<int, long long, long>
			>,
			TypeListTraits::AllAre<DefineConcept<[]<typename TypeList_>() constexpr noexcept -> bool {
				return requires{
					requires TypeListTraits::isTemplateInstance<TypeList_>;
					requires is< TypeList_, TypeListTraits::AllAre<ConvertibleTo<int>> >;
				};
			}>>
		>);



		static_assert(/*IIFE*/[]() constexpr -> bool
		{
			auto lambda = []<typename T>(int x) constexpr -> int
			{
				if constexpr (std::same_as<T, int>) {
					return x + 1;
				}
				else if constexpr (std::same_as<T, long>) {
					return x + 2;
				}
				else if constexpr (std::same_as<T, char>) {
					return x + 3;
				}
				else {
					return x;
				}
			};

			auto lambda2 = [&lambda]<typename...Ts>(int x) constexpr
			{
				return std::make_tuple(
					CallableTemplateTraits::call(lambda, TypeListTraits::make<Ts>, x)
					...
				);
			};
		
			std::tuple<int, int, int> tuple = CallableTemplateTraits::call(
				lambda2,
				TypeListTraits::make<int, long, char>,
				10
			);
		
			auto const& [a, b, c] = tuple;
			return a == 11
				&& b == 12
				&& c == 13;
		}());
	}

	void type_list_tests()
	{
	}
}
