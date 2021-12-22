
#include <concepts>
#include <string>
#include <iostream>
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/FourthTests.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	namespace
	{
		using namespace Cresspresso::ConceptTypes;
		
		

		static_assert(isCallableTemplate<
			decltype([]<typename T0, std::same_as<long> T1>(char const*) {
				return 42;
			}),
			TypeList<int, long>,
			char const*
		>);

		static_assert(!isCallableTemplate<
			int,
			TypeList<int, long>,
			char const*
		>);



		static_assert(42 == CallableTemplateTraits::call(
			[]<typename T0, std::same_as<long> T1>(char const*) constexpr {
				return 42;
			},
			TypeListTraits::make<int, long>,
			"s"
		));



		static_assert(noexcept(forall([]<typename Self>() constexpr noexcept -> bool {
			return true;
		}, TypeListTraits::make<TypeList<int>>)));

		static_assert(!noexcept(forall([]<typename Self>() constexpr -> bool {
			return true;
		}, TypeListTraits::make<TypeList<int>>)));



		static_assert(isCallableTemplate<
			decltype([]<typename Self>() constexpr noexcept -> bool {
				return requires {
					requires true;
				};
			}),
			TypeList<int>
		>);

		static_assert(is<
			decltype([]<typename Self>() constexpr noexcept -> bool {
				return requires {
					requires true;
				};
			}),
			ConceptCallable
		>);
	}

	void fourth_tests()
	{
	}
}
