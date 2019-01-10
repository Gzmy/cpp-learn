#include <iostream>
#include <map>
#include <set>

void testMap() {
	std::map<std::string, std::string> m;
	m.insert(std::pair<std::string, std::string>("peach", "桃子"));

	std::cout << m.size() << std::endl;
	m.insert(std::make_pair<std::string, std::string>("banab", "香蕉"));
	std::cout << m.size() << std::endl;
	m["apple"] = "苹果";

	//m.at("waterme") = "水蜜桃";  //aborted
	m.insert(m.find("banan"), std::make_pair("waterme", "水蜜桃"));
	for( auto it = m.begin(); it != m.end(); it++ ) {
		std::cout << it->first << "==>" << it->second << std::endl;
	}

	for( auto& e : m ) {
		std::cout << e.first << "--->" << e.second << std::endl;
	}

	auto ret = m.insert(std::make_pair("peach", "桃色"));
	if(ret.second) { // ???????
		std::cout << "insert success" << std::endl;
	} else {
		std::cout << "元素已经存在:" << ret.first->first << "--->" << ret.first->second << "insert faild" << std::endl;
	}

	m.erase("apple");
	for( auto& e : m ) {
		std::cout << e.first << "-->" << e.second << std::endl;
	}

	if( 1 == m.count("apple") ) {
		std::cout << "apple have" << std::endl;
	} else {
		std::cout << "apple gone" << std::endl;
	}
	//std::map<std::string, std::string> m;
	//m["apple"] = "123";
	//std::cout << m["apple"] << std::endl;
	//m.at("banan");
	//std::cout << m.size() << std::endl;
	//std::map<std::string, std::string> m1;

	//std::map<std::string, std::string> m2{ {"apple", "苹果"}, 
	//									   {"banan", "香蕉"}, 
	//									   {"orange", "橘子"}, 
	//									   {"peach", "桃子"}, 
	//									   {"waterme", "水蜜桃"} };

	//std::cout << m2["apple"] << std::endl;
	//std::cout << m2["peach"] << std::endl;

	//std::map<std::string, std::string> m3(m2);

	//for( auto it = m2.begin(); it != m2.end(); it++ ) {
	//	std::cout << (*it).first << "----->" << it->second << std::endl;
	//}
}

void testMultimap() {
	std::multimap<int, int> m;
	for( int i = 0; i < 10; i++ ) {
		m.insert(std::pair<int, int>(i, i));
	}

	for( auto& e : m ) {
		std::cout << e.first << "-->" << e.second << std::endl;
	}
	std::cout << std::endl;

	std::multimap<int, int>::iterator it = m.lower_bound(5);
	std::cout << it->first << "-->" << it->second << std::endl;
	std::cout << std::endl;

	it = m.upper_bound(5);
	std::cout << it->first << "-->" << it->second << std::endl;

	//std::multimap<std::string, std::string> m;

	//m.insert(std::make_pair("李逵", "黑旋风"));
	//m.insert(std::make_pair("林冲", "豹子头"));
	//m.insert(std::make_pair("鲁达", "花和尚"));
	//m.insert(std::make_pair("李逵", "铁牛"));

	//std::cout << m.size() << std::endl;

	//for( auto& x : m ) {
	//	std::cout << "<" << x.first << "," << x.second << ">" << std::endl;
	//}

	//std::cout << m.count("李逵") << std::endl;
}

void testSet() {
	int arr[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
	std::set<int> s(arr, arr+sizeof(arr)/sizeof(arr[0]));
	std::cout << s.size() << std::endl;

	for( auto& e : s ) {
		std::cout << e << " ";
	}
	std::cout << std::endl;

	for( auto it = s.rbegin(); it != s.rend(); it++ ) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout << s.count(3) << std::endl;
}

void testMultiset() {
	int arr[] = { 2, 1, 3, 9, 6, 0, 5, 8, 4, 7 };

	std::multiset<int> s(arr, arr+sizeof(arr)/sizeof(arr[0]));
	for( auto& x : s ) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	s.insert(5);
	std::cout << s.count(5) << std::endl;
	for( auto& x : s ) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	s.erase(5);
	for( auto& x : s ) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

int main()
{
	//testMap();
	//testMultimap();
	//testSet();
	testMultiset();
	return 0;
}
