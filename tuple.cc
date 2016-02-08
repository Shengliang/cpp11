

#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>


std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

int main()
{
    std::vector< std::tuple<double, char, std::string> > arr;
    auto student0 = get_student(0);

    arr.emplace_back(get_student(0));
    arr.emplace_back(get_student(1));
    arr.emplace_back(get_student(2));

    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';

    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';
    int i = 0;

    for(auto & e : arr) {
       std::cout << "ID: " << i++ << ", "
              << "GPA: " << std::get<0>(e) << ", "
              << "grade: " << std::get<1>(e) << ", "
              << "name: " << std::get<2>(e) << '\n';
    }

     return 0;
}
