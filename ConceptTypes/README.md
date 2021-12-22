
# Concept Types

Types that act like concepts (or vice versa).

They can be used to declare concepts inside of classes, template specializations, and anywhere that you can use a type.

## Installation

This is a header only library with multiple header files.

1. Add the `ConceptTypes/include` directory to your own project's includes so that your build system detects it. (Copy the `Cresspresso` folder to your project.)
2. `#include <Cresspresso/ConceptTypes.h>`

## Examples

```cpp
#include <utility>
#include <concepts>
#include <Cresspresso/ConceptTypes.h>

using Cresspresso::ConceptTypes::DefineConcept;

template<typename To>
using ConvertibleTo = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
	return requires{
		requires std::convertible_to<Self, To>;
		requires requires(Self&& self) {
			static_cast<To>(std::forward<Self>(self));
		};
	};
}>;

// The `is` concept lets you use them as a regular concept/constraint.

using Cresspresso::ConceptTypes::is;

static_assert(is<int, ConvertibleTo<int>>);

is<ConvertibleTo<int>> auto my_var = 42;

// CT concept types can be aliased (typedef/using) and partially applied.

using ConvertibleToInt = ConvertibleTo<int>;
static_assert(is<int, ConvertibleToInt>);

// They can also be used as template type parameters.

using Cresspresso::ConceptTypes::Concept;

template<typename C>
requires is<C, Concept>
constexpr is<C> auto make_something() {
	if constexpr (std::same_as<C, ConvertibleTo<int>>) {
		return 42;
	}
	else {
		constexpr bool false_ = !std::is_same_v<void, std::void_t<C>>;
		static_assert(false_, "Invalid template type argument.");
	}
}

static_assert(42 == static_cast<int>(make_something<ConvertibleTo<int>>()));

// They can be instantiated as concrete objects.

ConvertibleTo<int> my_variable{};
static_assert(is<int, std::decay_t<decltype(my_variable)>>);

constexpr auto foo(is<Concept> auto arg) {
	if constexpr (std::same_as<decltype(arg), ConvertibleTo<int>>) {
		return 1;
	}
	else {
		return "";
	}
}
static_assert(1 == foo(ConvertibleTo<int>{}));

// A type alias for a CT concept type can exist as a complete non-template type.

using Fruit = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
	return requires{
		requires requires(Self const& self) {
			{ self.get_seed_count() } -> is<ConvertibleTo<int>>;
		};
	};
}>;

struct Apple {
	int get_seed_count() const {
		return 7;
	}
};
static_assert(is<Apple, Fruit>);

// CT concept types can be written inline as a type expression.

static_assert(is<
	int,
	DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires std::same_as<Self, int>;
		};
	}>
>);
```

## Limitations

Standard concepts can disambiguate overloads by checking for mutually exclusive constraints,
and constraints that are a superset or subset of another overload's constraints
(the more tightly constrained overload is chosen).
For example, given the function argument `3U`, the `std::unsigned_integral` overload is chosen over `std::integral`.

This library's CT concept types cannot disambiguate overloads in this fashion.
Worthy of mention, `requires{ requires superset<T>; }` expressions also suffer from this limitation.
As a workaround, you can differentiate overloads constrained with CT concept types by manually constraining them further.

```cpp
using UnsignedIntegral = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
	return std::unsigned_integral<Self>;
}>;

using Integral = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
	return std::integral<Self>;
}>;

template<typename T>
	requires is<T, UnsignedIntegral>
constexpr T over(T i) {
	return i;
}

template<typename T>
	requires is<T, Integral>
	&& (!is<T, UnsignedIntegral>) // needs the extra `&& !subset` for disambiguation.
constexpr T over(T i) {
	return i + 1;
}

static_assert(3 == over(3U));
static_assert(4 == over(3));
```

## Version

Version: 1.0.0

## Testing

This library aims to be cross-platform by only using standard C++20 features (and STL) and no other dependencies.
However, clang currently (as of 22 Dec 2021) does not provide all the necessary standard C++20 features.

22 Dec 2021. Version 1.0.0 was tested on:

* ✅ MSVC, Visual Studio Community 2022, Windows 10, `/std:c++latest`.
* ✅ GCC (g++11), Windows Subsystem for Linux, Ubuntu 20.04, `-std=c++20`.
* ❌ Clang 13 failed to build this library. We will have to wait for them to implement "lambdas in unevaluated contexts" (std C++20).
