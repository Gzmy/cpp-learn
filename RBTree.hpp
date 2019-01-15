#include <iostream>

enum Color{
	RED,
	BLACK,
};

template<class K, class V>
struct RBTreeNode {
	RBTreeNode<K, V> *_left = nullptr;
	RBTreeNode<K, V> *_right = nullptr;
	RBTreeNode<K, V> *_parent = nullptr;

	std::pair<K, V> _kv;
	Color _color = RED;

	RBTreeNode() = default;
};


template<class K, class V>
class RBTree {
	typedef RBTreeNode<K, V> Node;
	public:
		RBTree() {
			_header = new Node;
			_header->_parent = nullptr;
			_header->_left = _header;
			_header->_right = _header;
		}	

		bool Insert(const std::pair<K, V>& kv) {
			if(_header->_parent == nullptr) {
				Node *root = new Node;
				root->_kv = kv;
				root->_parent = _header;
				root->_color = BLACK;
				_header->_parent = root;
				_header->_left = root;
				_header->_right = root;

				return true;
			}

			Node *root = _header->_parent;
			Node *parent = nullptr;
			Node *cur = root;
			while(cur) {
				parent = cur;
				if(cur->_kv.first < kv.first) {
					cur = cur->_right;
				} else if (cur->_kv.first > kv.first) {
					cur = cur->_left;
				} else {
					return false;
				}
			}

			cur = new Node;
			cur->_kv = kv;
			cur->_color = RED;
			if(parent->_kv.first < kv.first) {
				parent->_right = cur;
				cur->_parent = parent;
			} else {
				parent->_left = cur;
				cur->_parent = parent;
			}

			// keep red black rule
			while(cur != root && cur->_parent->_color == RED) {
				Node *parent = cur->_parent;
				Node *grandfather = cur->_parent->_parent;
				if(grandfather->_left == parent) {
					Node *uncle = grandfather->_right;
					//uncle存在且为红， 变色
					if(uncle && uncle->_color == RED) { 
						parent->_color = uncle->_color = BLACK;
						grandfather->_color = RED;
						cur = grandfather;
					} else { //uncle不在 / uncle在为黑，旋转

					}
				} else {
					Node *uncle = grandfather->_left;
				}
			}	

			root->_color = BLACK;
			_header->_left = leftMost();
			_header->_right = rightMost();
			
			return true;
		}

		Node *leftMost() {
			Node *cur = _header->_parent;
			while(cur && cur->_left != nullptr) {
				cur = cur->_left;
			}
			return cur;
		}

		Node *rightMost() {
			Node *cur = _header->_parent;
			while(cur && cur->_right != nullptr) {
				cur = cur->_right;
			}
			return cur;
		}

		bool Empty() {
			return _header->_parent == nullptr;
		}
	private:
		Node *_header; //需要迭代器
};
