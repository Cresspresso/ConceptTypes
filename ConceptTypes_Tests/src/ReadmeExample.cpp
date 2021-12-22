
// Concept Types

// Types that act like concepts (or vice versa).

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



// You can differentiate overloads constrained with CT concept types by manually constraining them further.

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
