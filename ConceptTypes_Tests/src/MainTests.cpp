
#include <iostream>

#include <Cresspresso/ConceptTypes.h>

#include "Cresspresso_Tests/ConceptTypes_Tests/Example2.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/OtherTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/ThirdTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/FourthTests.h"
#include "Cresspresso_Tests/ConceptTypes_Tests/TypeListTests.h"

int main()
{
	Cresspresso_Tests::ConceptTypes_Tests::example2();
	Cresspresso_Tests::ConceptTypes_Tests::other_tests();
	Cresspresso_Tests::ConceptTypes_Tests::third_tests();
	Cresspresso_Tests::ConceptTypes_Tests::fourth_tests();
	Cresspresso_Tests::ConceptTypes_Tests::type_list_tests();

	std::cout << "All tests completed." << std::endl;
}
