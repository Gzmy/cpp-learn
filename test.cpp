#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void printVector(const vector<int>& vec)
{
    vector<int>::const_iterator it = vec.begin();
    while(it != vec.end()){
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

int main()
{
    //迭代器失效
    vector<int> vec = {1, 2 ,3, 4};
    vector<int>::iterator pos = find(vec.begin(), vec.end(), 3);

    vec.erase(pos);
    cout << *pos << endl;

    //operator[]+index  && for+auto
    //vector<int> vec = {1, 2, 3, 4};

    //vec[0] = 10;
    //cout << vec[0] << endl;

    //for(size_t i = 0; i < vec.size(); i++){
    //    cout << vec[i] << " ";
    //}
    //cout << endl;

    //vector<int> swapv;
    //swapv.swap(vec);

    //cout << "vec data:";
    //for(size_t i = 0; i < vec.size(); i++){
    //    cout << vec[i] << " ";
    //}
    //cout << endl << "swapv data : ";
    //for(size_t i = 0; i < swapv.size(); i++){
    //    cout << swapv[i] << " ";
    //}
    //cout << endl;

    //find  / insert  / erase
    //vector<int> vec = {1, 2, 3, 4};
    //
    //vector<int>::iterator pos = find(vec.begin(), vec.end(), 3);
    //vec.insert(pos, 30);
    //
    //vector<int>::iterator it = vec.begin();
    //while(it != vec.end()){
    //    cout << *it << " ";
    //    it++;
    //}
    //cout << endl;

    //pos = find(vec.begin(), vec.end(), 3);
    //vec.erase(pos);

    //it = vec.begin();
    //while(it != vec.end()){
    //    cout << *it << " ";
    //    it++;
    //}
    //cout << endl;

    //push_back and pop_back
    //int a[] = {1, 2, 3 , 4};
    //vector<int> vec(a, a+sizeof(a)/sizeof(int));

    //vector<int>::iterator it = vec.begin();

    //while(it != vec.end()){
    //    cout << *it << " ";
    //    it++;
    //}
    //cout << endl;

    //vec.pop_back();
    //vec.pop_back();

    //it = vec.begin();
    //while(it != vec.end()){
    //    cout << *it << " ";
    //    it++;
    //}
    //cout << endl;

    //capacity
    //size_t sz;
    //vector<int> bar;
    //sz = bar.capacity();
    //bar.reserve(100);
    //cout << "making bar grow!" << '\n';
    //for(int i = 0; i < 100; i++){
    //    bar.push_back(i);
    //    if(sz != bar.capacity()){
    //        sz = bar.capacity();
    //        cout << "capacity changed : " <<sz << endl;
    //    }
    //}
    //size_t sz;
    //std::vector<int> foo;
    //sz = foo.capacity();
    //cout << "making foo grow:\n";
    //for(int i = 0; i < 100; ++i){
    //    foo.push_back(i);
    //    if(sz != foo.capacity()){
    //        sz = foo.capacity();
    //        cout << "capacity changed : " << sz << '\n';
    //    }
    //}

    //vector的插入及打印
    //vector<int> vec;
    //vec.push_back(1);
    //vec.push_back(2);
    //vec.push_back(3);
    //vec.push_back(4);
    //vec.push_back(5);
    //
    //vector<int>::iterator it = vec.begin();
    //while(it != vec.end()){
    //    cout << *it << " ";
    //    it++;
    //}
    //cout << endl;

    //it = vec.begin();
    //while(it != vec.end()){
    //    *it *= 2;
    //    it++;
    //}
    //for(auto id : vec){
    //    cout << id << endl;
    //}
    //
    //vector<int>::reverse_iterator rit = vec.rbegin();
    //while(rit != vec.rend()){
    //    cout << *rit << " ";
    //    ++rit;
    //}
    //cout << endl;

    //printVector(vec);

    //实例化vector
    //std::vector<int> first;
    //std::vector<int> second(4, 100);
    //for(auto it : second){
    //    cout << it << endl;
    //}
    //std::vector<int> third (second.begin(), second.end());
    //for(auto id : third){
    //    cout << id << endl;
    //}
    //std::vector<int> fourth(third);
    //for(auto ie : fourth){
    //    cout << ie << endl;
    //}

    return 0;
}
