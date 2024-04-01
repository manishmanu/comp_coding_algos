#include <iostream>
#include <string>
#include <tuple>    // C++-11

/*
    Structured bindings help with returning multiple values from a method.

    Concept: Why create a type only for one-time use case ? Often we end up
    creating struct type just to handle multiple return values from a method.

    Using std::tie along with std::tuple solves the problem but still makes
    code messy as you need to declare each of the return variable.

    structured bindings are designed to auto decompose return values and assign
    to variables (also handles type).
*/

struct Person {
    std::string name;
    int age;
};

Person createPerson1(){
    return { "John Doe", 27 };
}

std::tuple<std::string, int> createPerson2(){
    return { "John Doe", 27 };
}

int main() {
    Person person1 = createPerson1();
    std::cout << "Struct: name = " << person1.name << ", age = " << person1.age << std::endl;

    auto person2 = createPerson2();
    std::cout << "Tuple: name = " << std::get<0>(person2) << ", age = "
              << std::get<1>(person2) << std::endl;

    std::string name;
    int age;
    std::tie(name, age) = createPerson2();
    std::cout << "Tie: name = " << name << ", age = " << age << std::endl;

    // Only supported from C++-17
    // Also works for more than 2 return values.
    auto[name2, age2] = createPerson2();
    std::cout << "Structued binding: name = " << name2 << ", age = " << age2 << std::endl;
}

