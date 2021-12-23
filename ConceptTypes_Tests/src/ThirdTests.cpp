
///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Source File
///	Filename: ThirdTests.cpp
///	
///	
///	
///	## CONTRIBUTORS
///	```json
///	[
///		{
///			"Date": "23 Dec 2021",
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
///	Root Include Directory: Cresspresso_Tests/ConceptTypes_Tests/
///	Root Namespace: Cresspresso_Tests::ConceptTypes_Tests
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



#include <concepts>
#include <string>
#include <iostream>
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/ThirdTests.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	using ::Cresspresso::ConceptTypes::is;
	namespace CT = Cresspresso::ConceptTypes;



	static_assert(CT::forall(
		[]<typename T, typename U>() constexpr -> bool { return std::same_as<T, U>; },
		CT::TypeListTraits::make<
			CT::TypeList<int, int>,
			CT::TypeList<long, long>,
			CT::TypeList<char, char>
		>
	));

	static_assert(!CT::forall(
		[]<typename T, typename U>() constexpr -> bool { return std::same_as<T, U>; },
		CT::TypeListTraits::make<
			CT::TypeList<int, int>,
			CT::TypeList<long, int>,
			CT::TypeList<char, char>
		>
	));

	template<typename Self>
	concept UnitTestConcept12 = CT::forall(
		[]<typename T>() constexpr noexcept -> bool { return std::same_as<Self, T>; },
		CT::TypeListTraits::make<
			CT::TypeList<int>
		>
	);

	static_assert(UnitTestConcept12<int>);
	static_assert(!UnitTestConcept12<long>);



	static_assert(is<CT::Concept, CT::Concept>);



	template<typename Self, typename Arg>
	concept isSameAs = std::same_as<Self, Arg>;

	template<typename Arg>
	using SameAs = CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires isSameAs<Self, Arg>;
		};
	}>;

	static_assert(is<int, SameAs<int>>);
	static_assert(!is<int, SameAs<long>>);
	static_assert(is<SameAs<int>, CT::Concept>);



	static_assert(is<
		int,
		CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return std::same_as<Self, int>;
		}>
	>);

	static_assert(!is<
		long,
		CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return std::same_as<Self, int>;
		}>
	>);

	static_assert(is<
		CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return std::same_as<Self, int>;
		}>,
		CT::Concept
	>);



	using Blue = CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires true;
		};
	}>;

	using Red = CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires true;
		};
	}>;

	using Mediator = CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
		return requires{
			requires is<typename std::decay_t<Self>::Cobra, CT::Concept>;
			requires requires(Self& self)
			{
				self.cobra();
			};
		};
	}>;

	namespace MediatorTraits
	{
		template<is<Mediator> ThisMediator>
		using Cobra = typename std::decay_t<ThisMediator>::Cobra;
	}

	namespace details
	{
		using DetailWin32Cobra = CT::DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return requires{
				requires requires(Self& self)
				{
					{ self } -> is<CT::ConvertibleTo<std::string>>;
				};
			};
		}>;

		template<is<Blue> Octopus_>
		class DetailWin32Mediator {
		private:
			using Octopus = Octopus_;
	
			Octopus m_octopus;
	
		public:
			using Cobra = DetailWin32Cobra;
	
			auto octopus() const -> Octopus
			{
				return m_octopus;
			}
	
			auto set_octopus(Octopus octopus) -> void
			{
				m_octopus = octopus;
			}
	
			template<is<Red> Jaguar>
			auto mediate(Jaguar jaguar) -> void
			{
			}
	
			auto cobra()->is<DetailWin32Cobra> auto
			{
				return std::string("cobra");
			}
		};
	}

	template<is<Mediator> TMediator>
	is<MediatorTraits::Cobra<TMediator>> auto cobra(TMediator& mediator)
	{
		static_assert(std::same_as<MediatorTraits::Cobra<decltype(mediator)>, details::DetailWin32Cobra>);
		static_assert(is<decltype(mediator.cobra()), MediatorTraits::Cobra<decltype(mediator)>>);
		return mediator.cobra();
	}

	static_assert(is<int, Blue>);
	static_assert(is<int, Red>);
	static_assert(is<char const*, details::DetailWin32Cobra>);

	static_assert(is<details::DetailWin32Mediator<int>, Mediator>);

	is<Mediator> auto make_mediator()
	{
		return details::DetailWin32Mediator<int>();
	}

	void third_tests()
	{
		is<Mediator> auto mediator = make_mediator();
		is<MediatorTraits::Cobra<decltype(mediator)>> auto cobra_ = cobra(mediator);
		assert(cobra_ == std::string("cobra"));
	}
}
