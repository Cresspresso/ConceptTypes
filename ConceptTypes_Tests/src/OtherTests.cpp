
#include <concepts>
#include <string>
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/OtherTests.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	using ::Cresspresso::ConceptTypes::is;
	namespace CT = Cresspresso::ConceptTypes;



	constexpr auto lam = []<typename T, typename U>() constexpr noexcept -> bool {
		return std::convertible_to<T, U>;
	};

	static_assert(CT::forall(
		lam,
		CT::TypeListTraits::make<
			CT::TypeList<int*, int const*>,
			CT::TypeList<int*, void*>,
			CT::TypeList<int, long>
		>
	));

	static_assert(!CT::forall(
		lam,
		CT::TypeListTraits::make<
			CT::TypeList<int*, int const*>,
			CT::TypeList<int const*, int*>,
			CT::TypeList<int, long>
		>
	));

	static_assert(CT::is<CT::Concept, CT::Concept>);
	static_assert(CT::is<CT::TypeIdentity, CT::Concept>);
	static_assert(!CT::is<CT::Concept, CT::TypeIdentity>);
	static_assert(CT::type_argument_is<CT::TypeIdentity>(CT::Concept{}));
	static_assert(CT::argument_type_member_is(CT::DefineTypeIdentity<CT::ConceptConstant>{}, CT::Concept{}));

	static_assert(CT::is<int, CT::SameAs<int>>);
	static_assert(!CT::is<int, CT::SameAs<int const>>);
	static_assert(CT::is<bool const&, CT::ConvertibleTo<bool>>);
	static_assert(CT::is<bool const&, CT::ContextuallyConvertibleToBool>);
	static_assert(CT::is<int*, CT::ContextuallyConvertibleToBool>);

	static_assert(CT::is<
		int,
		CT::DefineMapSelfConcept<
			[]<typename Self>() constexpr noexcept -> is<CT::TypeIdentity> auto
			{
				if constexpr (CT::is<Self, CT::SameAs<int>>)
				{
					return CT::DefineTypeIdentity<long>{};
				}
				else
				{
					return CT::DefineTypeIdentity<Self>{};
				}
			},
			CT::SameAs<long>
		>
	>);

	static_assert(CT::is<
		void(*)(int),
		CT::Callable<int const&>
	>);

	static_assert(CT::is<
		decltype([]<CT::is<CT::SameAs<int>> T>(long) {}),
		CT::CallableTemplate<CT::TypeList<int>, long>
	>);

	static_assert(false == CT::is<
		decltype([]<CT::is<CT::SameAs<int>> T>(long) {}),
		CT::CallableTemplate<CT::TypeList<short>, long>
	>);

	static_assert(false == CT::is<
		decltype([]<CT::is<CT::SameAs<int>> T>(long) {}),
		CT::CallableTemplate<CT::TypeList<int>, int*>
	>);



	// constraints can disambiguate.

	template<typename T>
		requires std::unsigned_integral<T>
	constexpr int cheese(T i)
	{
		return 3;
	}

	template<typename T>
		requires std::integral<T>
	constexpr int cheese(T i)
	{
		return 5;
	}

	static_assert(cheese(2) == 5);
	static_assert(cheese(2U) == 3);



	// constrained placeholders can disambiguate.

	constexpr int yup(std::unsigned_integral auto i)
	{
		return 3;
	}

	constexpr int yup(std::integral auto i)
	{
		return 5;
	}

	static_assert(yup(2) == 5);
	static_assert(yup(2U) == 3);



	// "requires requires requires" cannot disambiguate.

	//template<typename T>
	//	requires requires{
	//	requires std::unsigned_integral<T>;
	//}
	//constexpr int pear(T i)
	//{
	//	return 3;
	//}
	//
	//template<typename T>
	//	requires requires{
	//	requires std::integral<T>;
	//}
	//constexpr int pear(T i)
	//{
	//	return 5;
	//}
	//
	//static_assert(pear(2) == 5);
	//static_assert(pear(2U) == 3);



	// CT concept type constraints cannot disambiguate.

	//constexpr int wow(CT::is < CT::DefineConcept < []<typename Self>() constexpr noexcept -> bool {
	//	return std::unsigned_integral<Self>;
	//} >> auto i)
	//{
	//	return 3;
	//}
	//
	//constexpr int wow(CT::is < CT::DefineConcept < []<typename Self>() constexpr noexcept -> bool {
	//	return std::integral<Self>;
	//} >> auto i)
	//{
	//	return 5;
	//}
	//
	//static_assert(wow(2) == 5);
	//static_assert(wow(2U) == 3);


	// You can manually disambiguate overloads with CT concept type constraints.

	using UnInt = CT::DefineConcept < []<typename Self>() constexpr noexcept -> bool {
		return std::unsigned_integral<Self>;
	}> ;
	
	template<typename T>
	requires is<T, UnInt>
	constexpr int bar(T i)
	{
		return 3;
	}

	template<typename T>
		requires (is <T, CT::DefineConcept < []<typename Self>() constexpr noexcept -> bool {
		return std::integral<Self>;
	} >>
		&& !is<T, UnInt>
		)
	constexpr int bar(T i)
	{
		return 5;
	}
	
	static_assert(bar(2) == 5);
	static_assert(bar(2U) == 3);



	void other_tests()
	{
	}
}
