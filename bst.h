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
		class BNode;
		BNode* root;
		int numElements;
	public:
		class iterator;
		class reverse_iterator;
		BST() : root(NULL) {}
		BST(const BST<T> & rhs) throw (const char*);
		~BST() { clear(); }
		BST<T>& operator =(const BST<T> & rhs) { return *this = copyBinaryTree(rhs, *this); } //not sure if this works
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
	private:
		deleteNode(BST<T>::BNode del, bool right); //called from erase()
		deleteBinaryTree(BST<T>BNode del); //called from clear()
		copyBinaryTree(BST<T>::BNode src, BST<T>::BNode dest); //recursive, called from operator=()
	};

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
	private:
		verifyRB(int depth); //recursive, useful for verifying property d) of a red-black tree
		verifyBST(); //Ensures that the subtree under a given node is a valid BST
		balance(); //Contains all the red-black balancing logic
	};

	template <class T>
	class BST<T>::iterator
	{
	public:
		iterator();
		iterator(BST<T>::BNode p);
		iterator(const BST<T>::iterator& rhs);
		BST<T>::iterator& operator =(const BST<T>::iterator& it);
		bool operator ==(const BST<T>::iterator& it);
		bool operator !=(const BST<T>::iterator& it);
		BST<T>::iterator operator ++();
		BST<T>::iterator operator ++(int postfix);
		BST<T>::iterator operator --();
		BST<T>::iterator operator --(int postfix);
		T operator *();
	private:
		BST<T>::BNode* p;
	};

	template <class T>
	class BST<T>::reverse_iterator
	{
	public:
		reverse_iterator();
		reverse_iterator(BST<T>::BNode p);
		reverse_iterator(const BST<T>::reverse_iterator& rhs);
		BST<T>::reverse_iterator& operator =(const BST<T>::reverse_iterator& it);
		bool operator ==(const BST<T>::reverse_iterator& it);
		bool operator !=(const BST<T>::reverse_iterator& it);
		BST<T>::reverse_iterator operator ++();
		BST<T>::reverse_iterator operator ++(int postfix);
		BST<T>::reverse_iterator operator --();
		BST<T>::reverse_iterator operator --(int postfix);
		T operator *();
	private:
		BST<T>::BNode* p;
	};
   
	/**************************************************
	 * BST ITERATOR :: DECREMENT PREFIX
	 *     advance by one. Note that this implementation uses
	 *     a stack of nodes to remember where we are. This stack
	 *     is called "nodes".
	 * Author:      Br. Helfrich
	 * Performance: O(log n) though O(1) in the common case
	 *************************************************/
	template <class T>
	typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
	{
	   // do nothing if we have nothing
	   if (NULL == pNode)
		  return *this;

	   // if there is a left node, take it
	   if (NULL != pNode->pLeft)
	   {
		  // go left
		  pNode = pNode->pLeft;

		  // jig right - there might be more right-most children
		  while (pNode->pRight)
			 pNode = pNode->pRight;
		  return *this;
	   }

	   // there are no left children, the right are done
	   assert(NULL == pNode->pLeft);
	   BNode * pSave = pNode;

	   // go up
	   pNode = pNode->pParent;

	   // if the parent is the NULL, we are done!
	   if (NULL == pNode)
		  return *this;

	   // if we are the right-child, got to the parent.
	   if (pSave == pNode->pRight)
		  return *this;

	   // we are the left-child, go up as long as we are the left child!
	   while (NULL != pNode && pSave == pNode->pLeft)
	   {
		  pSave = pNode;
		  pNode = pNode->pParent;
	   }

	   return *this;
	}

	template<class T>
	BST<T>::BST(const BST<T>& rhs) throw(const char *)
	{
		root = NULL;
		try
		{ 
			*this = rhs; 
		}
		catch (bad_alloc)
		{
			throw "ERROR: Unable to allocate a node"
		}
	}

	template<class T>
	void BST<T>::insert(const T & t) throw(const char *)
	{
		BST<T>::BNode* newb = new BST<T>::BNode(t);
		newb->
	}

} // namespace custom

#endif // BST_H
