// 该文件写了一些测试用例
#include "list.hpp"
#include "algorithm.hpp"
#include <iostream>
using namespace std;
struct Person {
	std::string name = "张三";
	int age = 18;

	bool operator()(const Person& owner, const Person& _other) {
		return owner.age > _other.age;
	}
};

void test_sort_Pre() {
	Person p1, p2, p3;
	p1.age = 19;
	p2.age = 17;
	p3.age = 22;
	stl::list<Person> ls;
	ls.push_back(p1);
	ls.push_back(p2);
	ls.push_back(p3);
	stl::sort(ls.begin(), ls.end(), Person());

	std::cout << ls.size() << std::endl;

	for (auto& val : ls) {
		std::cout << val.age << " ";
	}
}

void test_find() {
	
	stl::list<int> ls;

	for (int i = 0; i < 20; ++i) {
		ls.push_back(i);
	}
	auto it = stl::find(ls.begin(), ls.end(), 15);
	if (it != ls.end()) {
		ls.erase(it);
	}
	for (auto& val : ls) {
		std::cout << val << " ";
	}
}

void test_sort() {
	stl::list<int> ls;
	ls.push_back(5);
	ls.push_back(10);
	ls.push_back(3);
	ls.push_back(2);
	ls.push_back(8);

	//std::cout << ls.size();

	try {
		stl::sort(ls.begin(), ls.end());
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	for (auto it = ls.begin(); it != ls.end(); ++it) {
		try {
			std::cout << *it << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void test_iterator() {
	stl::list<int> ls;

	for (int i = 0; i < 10; ++i) {
		ls.push_back(20);
	}

	stl::list<int>::iterator it = ls.begin();

	for (; it != ls.end(); it++) {
		std::cout << *it << std::endl;
	}
}

void test_const_iterator() {
	stl::list<int> ls;

	for (int i = 0; i < 10; ++i) {
		ls.push_back(20);
	}

	stl::list<int>::const_iterator const_it = ls.begin();

	for (; const_it != ls.end(); const_it++) {
		std::cout << *const_it << std::endl;
	}

	std::cout << "----------------" << std::endl;

	const stl::list<int> ls1(ls);
	for (stl::list<int>::const_iterator const_it = ls1.begin(); const_it != ls1.end(); ++const_it) {
		std::cout << *const_it << std::endl;
	}
	std::cout << "----------------" << std::endl;

	stl::list<Person> pls;
	Person p1;
	pls.push_back(p1);

	const stl::list<Person> pls1(pls);
	for (auto con_it = pls1.begin(); con_it != pls1.end(); con_it++) {
		try {
			std::cout << con_it->name  << " " << con_it->age << std::endl;
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
}

void test_reverse_iterator() {
	stl::list<int> ls;
	for (int i = 0; i < 10; ++i) {
		ls.push_back(i);
	}
	for (auto val : ls) {
		std::cout << val << std::endl;
	}
	std::cout << "-----------" << std::endl;
	for (auto reverse_it = ls.rbegin(); reverse_it != ls.rend(); reverse_it++) {
		std::cout << *reverse_it << std::endl;
	}
	std::cout << "-----------" << std::endl;
	stl::list<Person> pls;
	Person p1;
	pls.push_back(p1);
	for (auto reverse_it = pls.rbegin(); reverse_it != pls.rend(); reverse_it++) {
		std::cout << reverse_it->name << "  " << reverse_it->age << std::endl;
	}
}

void test_reverse_const_iter() {
	using namespace stl;
	using namespace std;
	list<int> ls;
	for (int i = 0; i < 10; ++i) {
		ls.push_back(i);
	}

	const list<int>con_ls(ls);

	for (auto it = con_ls.rbegin(); it != con_ls.rend(); ++it) {
		cout << *it << endl;
	}
}


int main() {
	//test_iterator();
	//test_const_iterator();
	//test_reverse_iterator();
	//test_reverse_const_iter();
	//test_find();
	//test_sort();
	test_sort_Pre();
	return 0;
}
