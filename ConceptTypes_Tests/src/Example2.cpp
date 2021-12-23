
///	====== vvvv FILE HEADER ======================================================================
///	
///	File Type: C++ Source File
///	Filename: Example2.cpp
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
#include <cassert>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/Common.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/Example2.h"

namespace Cresspresso_Tests::ConceptTypes_Tests
{
	namespace
	{
		using namespace Cresspresso::ConceptTypes;

		using Fruit = DefineConcept<[]<typename Self>() constexpr noexcept -> bool {
			return requires {
				requires requires(Self& self) {
					{ self.seed_count() } -> is<SameAs<int>>;
				};
			};
		}>;

		struct Apple {
			int seed_count() {
				return 7;
			}
		};
		static_assert(is<Apple, Fruit>);

		static_assert(is<Fruit, Concept>);

		using G = ConvertibleTo<int>;

		template<is<Concept> TConcept>
		constexpr is<TConcept> auto make_something_that_is([[maybe_unused]] TConcept arg)
		{
			if constexpr (is<TConcept, SameAs<Fruit>>)
			{
				return Apple();
			}
			else if constexpr (is<TConcept, SameAs<G>>)
			{
				struct Fish {
					/*implicit*/ operator int() const
					{
						return 4;
					}
				};
				return Fish();
			}
			else if constexpr (is<TConcept, SameAs<Concept>>)
			{
				return Fruit{};
			}
			else if constexpr (is<TConcept, SameAs<ConceptCallable>>)
			{
				return []<typename Self>() constexpr noexcept -> bool {
					return requires{
						requires is<Self, Fruit>;
					};
				};
			}
			else
			{
				static_assert(false_sink<TConcept>, "Invalid template type argument for `TConcept`.");
			}
		}

		void example2_Detail()
		{
			is<G> auto i = make_something_that_is(G{});
			assert(static_cast<int>(i) == 4);

			is<Fruit> auto fruit = make_something_that_is(Fruit{});
			static_assert(is<decltype(fruit), SameAs<Apple>>);
			assert(fruit.seed_count() == 7);

			is<Concept> auto c = make_something_that_is(Concept{});
			static_assert(is<Apple, decltype(c)>);

			constexpr is<ConceptCallable> auto f = make_something_that_is(ConceptCallable{});
			static_assert(is<Apple, DefineConcept<f>>);
			assert(type_argument_satisfies<Apple>(f));
			assert(argument_type_member_satisfies(DefineTypeIdentity<Apple>{}, f));
		}
	}

	void example2()
	{
		example2_Detail();
	}
}
