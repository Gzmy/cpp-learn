#pragma once

#include <iostream>
#include <assert.h>
#include <stdlib.h>

/*
template<class T>
struct AVLTreeNode {
	AVLTreeNode<T> *_pLeft;
	AVLTreeNode<T> *_pRight;
	AVLTreeNode<T> *_pParent;
	T _data;
	int _bf; //平衡因子

	AVLTreeNode(const T& data = T()) : _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr), _data(data), _bf(0)
	{}
};

template<class T>
class AVLTree {
	public:
		typedef AVLTreeNode<T> Node;
		typedef Node* pNode;
	private:
		pNode _pRoot;
	public:
		bool insert(const T& data) {
			if(_pRoot == nullptr) {
				_pRoot = new Node(data);
				return true;
			}

			pNode pCur = _pRoot;
			pNode pParent = nullptr;
			while(pCur) {
				pParent = pCur;
				if(data < pCur->_data) {
					pCur = pCur->_pLeft;
				} else if(data > pCur->_data) {
					pCur = pCur->_pRight;
				} else {
					return false;
				}
			}


		}
};
*/

template<class K, class V>
struct AVLTreeNode {
	std::pair<K, V> _kv;
	AVLTreeNode<K, V> *_left = nullptr;
	AVLTreeNode<K, V> *_right = nullptr;
	AVLTreeNode<K, V> *_parent = nullptr;
	int _bf = 0;
};

template<class K, class V>
class AVLTree {
	typedef AVLTreeNode<K, V> Node;
	public:
		//std::pair<iterator, bool> Insert(const std::pair<K, V>& kv);
		bool Insert(const std::pair<K, V>& kv) {
			if(_root == nullptr) {
				_root = new Node;
				_root->_kv = kv;
				return true;
			}

			Node *cur = _root;
			Node *parent = nullptr;
			while(cur) {
				parent = cur;
				if(cur->_kv.first < kv.first) {
					cur = cur->_right;
				} else if(cur->_kv.first > kv.first) {
					cur = cur->_left;
				} else {
					return false;
				}
			}

			cur = new Node;
			cur->_kv = kv;
			if(parent->_kv.first < kv.first) {
				parent->_right = cur;
			} else {
				parent->_left = cur;
			}
			cur->_parent = parent;

			//1.调整平衡因子 
			//		左边高度变了，parent --bf
			//		右边高度变了，parent ++bf
			//		parent |bf| == 1， 之前是0高度改变，继续调整
			//		parent |bf| == 0   高度不变，调整完成
			//		parent |bf| == 2   进行旋转
			
			while(parent) {
				if(parent->_left == cur) {
					--parent->_bf;
				} else {
					++parent->_bf;
				}

				if(abs(parent->_bf) == 1) {
					cur = cur->_parent;
					parent = parent->_parent;
				} else if(parent->_bf == 0) {
					return true;
				} else if(abs(parent->_bf) == 2) { //Adjust
					if(parent->_bf == -2 && cur->_bf == -1){ //right only
						RotateR(parent);
					} else if (parent->_bf == 2 && cur->_bf == 1){ // left only
						RotateL(parent);
					} else if (parent->_bf == -2 && cur->_bf == 1){ //left right
						Node *subL = parent->_left; // adjust bf
						Node *subLR = subL->_right;
						int bf = subLR->_bf;

						RotateL(parent->_left);
						RotateR(parent);

						subLR->_bf = 0;
						if(bf == 1) {
							parent->_bf = 0;
							subL->_bf = -1;
						} else if(bf == -1) {
							parent->_bf = 1;
							subL->_bf = 0;
						}
					} else if (parent->_bf == 2 && cur->_bf == -1){ //right left
						Node *subR = parent->_right;
						Node *subRL = subR->_left;
						int bf = subRL->_bf;

						RotateR(parent->_right);
						RotateL(parent);

						subRL->_bf = 0;
						if(bf == 1) {
							parent->_bf = -1;
							subR->_bf = 0;
						} else if(bf == -1) {
							parent->_bf = 0;
							subR->_bf = 1;
						}
					}
					break;
				} else {
					//assert(false);
				}
			}
			return true;
		}

		void InOrder() {
			_InOrder(_root);
			std::cout << std::endl;
		}

		bool isBalance() {
			return _isBalance(_root);
		}

	private:
		Node *_root = nullptr;
	private:
		void RotateR(Node* parent) {
			Node *subL = parent->_left;
			Node *subLR = subL->_right;

			parent->_left = subLR;
			if(subLR)
				subLR->_parent = parent;

			subL->_right = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subL;

			if(parent == _root) {
				_root = subL;
				subL->_parent = nullptr;
			} else {
				if(ppNode->_left == parent) {
					ppNode->_left = subL;
				} else {
					ppNode->_right = subL;
				}

				subL->_parent = ppNode;
			}

			subL->_bf = parent->_bf = 0;
		}

		void RotateL(Node* parent) {
			Node *subR = parent->_right;
			Node *subRL = subR->_left;
			Node *ppNode = parent->_parent;

			parent->_right = subRL;
			if(subRL) {
				subRL->_parent = parent;
			}

			subR->_left = parent;
			parent->_parent = subR;

			if(parent == _root) {
				_root = subR;
				subR->_parent = nullptr;
			} else {
				if(ppNode->_left == parent) {
					ppNode->_left = subR;
				} else {
					ppNode->_right = subR;
				}

				subR->_parent = ppNode;
			}

			subR->_bf = parent->_bf = 0;
		}
		
		void _InOrder(Node *root) {
			if(root == nullptr) {
				return;
			}

			_InOrder(root->_left);
			std::cout << root->_kv.first << " ";
			_InOrder(root->_right);
		}

		int _getHeight(Node *root) {
			if(root == nullptr){
				return 0;
			}

			int leftHeight = _getHeight(root->_left);
			int rightHeight = _getHeight(root->_right);

			return leftHeight > rightHeight ? (leftHeight+1) : (rightHeight+1);
		}

		bool _isBalance(Node* root) {
			if(root == nullptr) {
				return true;
			}

			int leftHeight = _getHeight(root->_left);
			int rightHeight = _getHeight(root->_right);

			if(rightHeight-leftHeight != root->_bf) {
				std::cout << root->_kv.first << "error" << std::endl;
			}
			return abs(leftHeight-rightHeight) < 2 &&
				   _isBalance(root->_left) &&
				   _isBalance(root->_right);
		}
};


void testAVLTree() {
	//int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	int arr[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};

	AVLTree<int, int> t;
	for(auto e : arr) {
		t.Insert(std::make_pair(e, 0));
	}

	t.InOrder();
	if(t.isBalance()) {
		std::cout << "balance" << std::endl;
	}
}

