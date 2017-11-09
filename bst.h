/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Scott Tolman, Mark Baldwin
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H
//#include ???
namespace custom
{
	template <class T>
	class BST
	{
	private:
		class BNode; //forward declaration
		BNode* root;
		int numElements;
	public:
		BST() : root(NULL) {}
		BST(const BST<T> & rhs) throw (const char*);
		~BST() { clear(); }
		BST<T>& operator =(const BST<T> & rhs);
		int size() { return numElements; }
		bool empty() { return (root == NULL); }
		void clear() { deleteBinaryTree(); }
		void insert(const T & t) throw (const char*);
		void erase(BST<T>::iterator it) { deleteNode(it); }
		BST<T>::iterator find(const T & t);
		BST<T>::iterator begin();
		BST<T>::iterator end();
		BST<T>::iterator rbegin();
		BST<T>::iterator rend();
	};

	/******************************************************
	* BNODE
	* BNode class
	******************************************************/
	template <class T>
	class BST<T>::BNode
	{
	public:
		friend class BST<T>;
		friend class iterator<T>;
		friend class reverse_iterator<T>;
		T data;
		BST<T>::BNode* pLeft;
		BST<T>::BNode* pRight;
		BST<T>::BNode* pParent;
		bool isRed;
		BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
		BNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
	};

	template<class T>
	void BST<T>::insert(const T & t) throw(const char *)
	{
		BST<T>::BNode* newb = new BST<T>::BNode(t);
		newb->
	}

} // namespace custom

#endif // BST_H
