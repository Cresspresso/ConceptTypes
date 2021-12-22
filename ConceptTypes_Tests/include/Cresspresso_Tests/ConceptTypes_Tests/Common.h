#ifndef CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h
#define CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h

#include <type_traits>

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	template<bool value, typename...T>
	constexpr bool bool_sink = std::is_same_v<void, std::void_t<T...>> && value;

	template<typename...T>
	constexpr bool true_sink = bool_sink<true, T...>;

	template<typename...T>
	constexpr bool false_sink = bool_sink<false, T...>;
}

#endif // CRESSPRESSO_ExampleTypes_Tests_HeaderGuard_Common_h
