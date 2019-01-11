#include <iostream>

template<class T>
struct ListNode {
	ListNode(const T& val = T()) : _pPre(nullptr), _pNext(nullptr), _val(val){
	}

	ListNode<T> *_pPre;
	ListNode<T> *_pNext;
	T _val;
};

template<class T, class Ref, class Ptr>
class ListIterator {
	typedef ListNode<T>* PNode;
	typedef ListIterator<T, Ref, Ptr> Self;
	
	public:
		PNode _pNode;
		ListIterator(PNode pNode = nullptr) : _pNode(pNode) {}
		ListIterator(const Self& l) : _pNode(l._pNode) {}

		T& operator*() {
			return _pNode->_val;
		}

		T* operator->() { //?????????
			return &(operator*());
		}

		Self& operator++() {
			_pNode = _pNode->_pNext;
			return *this;
		}

		Self operator++(int) {
			Self temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}

		bool operator!=(const Self& l) {
			return _pNode != l._pNode;
		}

		bool operator==(const Self& l) {
			return _pNode == l._pNode;
		}
};


template<class T, class Ref, class Ptr, class Iterator>
class ListReverseIterator {
	typedef ListReverseIterator<T, Ref, Ptr, Iterator> Self;
	Iterator _it;
	public:
		ListReverseIterator(const Iterator& it) : _it(it) {}
		ListReverseIterator(const Self& s) : _it(s._it) {}

		Ref operator*() {
			Iterator temp = _it;
			return *(--temp);
		}

		Ptr operator->() {
			return &operator*();
		}

		Self& operator++() {
			--_it;
			return *this;
		}

		Self& operator++(int) {
			Iterator temp(_it);
			--_it;
			return temp;
		}

		Self& operator--() {
			++_it;
			return *this;
		}

		Self operator--(int) {
			Iterator temp(_it);
			++_it;
			return temp;
		}

		bool operator==(const Self& s) {
			return _it == s._it;
		}

		bool operator!=(const Self& s) {
			return _it != s._it;
		}
};

template<class T>
class List {
	typedef ListNode<T> Node;
	typedef Node* PNode;

	public:
		typedef ListIterator<T, T&, T*> Iterator;
		typedef ListIterator<T, const T&, const T*> ConstIterator;
		typedef ListReverseIterator<T, T&, T*, Iterator> ReverseIterator;
		typedef ListReverseIterator<T, const T&, const T*, ConstIterator> ConstReverseIterator;

	public:
		List() {
			createHead();
		}

		List(int n, const T& value = T()) {
			createHead();
			for(int i = 0; i < n; i++) {
				PushBack(value);
			}
		}

		template<class Iterator>
		List(Iterator first, Iterator last) {
			createHead();
			while(first != last) {
				PushBack(*first);
				++first;
			}
		}

		List(const List<T>& l) {
			createHead();
			List<T> temp(l.CBegin(), l.CEnd());
			this->Swap(temp);
		}

		List<T>& operator=(const List<T>& l) {
			if(this != &l) {
				List<T> temp(l);
				this->Swap(temp);
			}
			return *this;
		}

		~List(){
			Clear();
			delete _pHead;
			_pHead = nullptr;
		}

		/////////////////////////////////
		//Iterator
		Iterator Begin(){
			return Iterator(_pHead->_pNext);
		}
		Iterator End() {
			return Iterator(_pHead);
		}

		ReverseIterator RBegin() {
			return ReverseIterator(End());
		}

		ReverseIterator REnd() {
			return ReverseIterator(Begin());
		}
		ConstIterator CBegin() const {
			return ConstIterator(_pHead->_pNext);
		}

		ConstIterator CEnd() const {
			return ConstIterator(_pHead);
		}

		ConstReverseIterator CRBegin() const {
			return ConstReverseIterator(CEnd());
		}

		ConstReverseIterator CREnd() const {
			return ConstReverseIterator(CBegin());
		}


		/////////////////////////////
		//capacity
		size_t Size() const{
			size_t count = 0;
			PNode pCur = _pHead->_pNext;
			while(pCur != _pHead){
				count++;
				pCur = pCur->_pNext;
			}

			return count;
		}

		bool Empty()const {
			return _pHead->_pNext == _pHead;
		}
	private:
		void createHead() {
			_pHead = new Node;
			_pHead->_pPre = _pHead;
			_pHead->_pNext = _pHead;
		}
	private:
		PNode _pHead;
};
