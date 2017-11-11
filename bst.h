/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Brother Kirby, CS 235
 * Author:
 *    Scott Tolman, Mark Baldwin
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>

namespace custom
{
   template <class T>
   class BST
   {
     public:
      class iterator;
     BST() : root(NULL), numElements(0) {}
      BST(const BST<T> & rhs) throw (const char*);
      ~BST() { clear(); }
      BST<T>& operator =(const BST<T> & rhs);
      int size() { return numElements; }
      bool empty() { return (root == NULL); }
      void clear() { deleteBinaryTree(this->root); }
      void insert(const T & t) throw (const char*);
      void erase(BST<T>::iterator it) {}
	  BST<T>::iterator find(const T & t) { return iterator(); }
	  BST<T>::iterator begin();
	  BST<T>::iterator end();
      BST<T>::iterator rbegin() { return end(); }
      BST<T>::iterator rend() { return begin(); }
     private:
      class BNode;
      BNode* root;
      int numElements;

      void deleteNode(BST<T>::BNode* del, bool right){} //called from erase()
	  void deleteBinaryTree(BST<T>::BNode* del) {}  //called from clear()
      void copyBinaryTree(BST<T>::BNode* src, BST<T>::BNode* dest){} //recursive, called from operator=()
   };

   template <class T>
      class BST<T>::BNode
   {
     public:
      T data;
      BST<T>::BNode* pLeft;
      BST<T>::BNode* pRight;
      BST<T>::BNode* pParent;
      bool isRed;
     BNode() : pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
     BNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
     private:
      void verifyRB(int depth) {} //recursive, useful for verifying property d) of a red-black tree
      void verifyBST() {} //Ensures that the subtree under a given node is a valid BST
      void balance() {} //Contains all the red-black balancing logic
   };

   template <class T>
      class BST<T>::iterator
   {
     public:
     iterator() : pNode(NULL) {}
     iterator(BST<T>::BNode p) : pNode(p) {}
      iterator(const BST<T>::iterator& rhs) {}
      BST<T>::iterator& operator =(const BST<T>::iterator& it) {}
      bool operator ==(const BST<T>::iterator& it) { return (this->pNode == it.pNode); }
      bool operator !=(const BST<T>::iterator& it) { return (this->pNode != it.pNode); }
      BST<T>::iterator operator ++() { return *this; }
      BST<T>::iterator operator ++(int postfix) { return *this; }
      typename BST <T> ::iterator & operator -- ();
      BST<T>::iterator operator --(int postfix) { return *this; }
      T operator *() { return pNode->data; }
     private:
      BST<T>::BNode* pNode;
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
      typename BST <T> ::iterator & BST <T> ::iterator :: operator -- ()
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
	  numElements = 0;
      try
      {
         *this = rhs;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a node";
      }
   }

   template<class T>
      BST<T>& BST<T>::operator=(const BST<T>& rhs)
      {
         copyBinaryTree(rhs.root, this->root);
         return *this;
      }

   /*****************************************************
    * INSERT
    * creates new node with data value of t.  finds location
    * to insert node.  balances red/black tree.
    *****************************************************/
    template<class T>
    void BST<T>::insert(const T & t) throw(const char *)
    {
      BNode* newb = new BNode(t);
	  numElements++;

      if (root)
      {   
		 BNode* tmp;
         tmp = root;
         while (newb->pParent == NULL)
         {
            if (newb->data < tmp->data)
            {
               if (tmp->pLeft)
                  tmp = tmp->pLeft;
               else
               {
                  tmp->pLeft = newb;
                  newb->pParent = tmp;
               }
            }
            else
            {
               if (tmp->pRight)
                  tmp = tmp->pRight;
               else
                  tmp->pRight = newb;
               newb->pParent = tmp;
            }
         }
      }
      else if (!root)
         root = newb;
      ////still need to change colors for parts D
      //// RED / BLACK balancing this logic may all need to move to BNode::balance()
      //if (newb->pParent == NULL) //case 1
      //{
      //   newb->isRed = false;
      //   root = newb;
      //}

      //if (newb->pParent->isRed == true)								// parent is red -- case 3 and 4 
      //{
      //   if (newb->pParent->pLeft == newb)								//child left of parent
      //   {
      //      if (newb->pParent->pParent->pLeft == newb->pParent)			//parent is left of grandparent		/ shape
      //      {
      //         if (newb->pParent->pParent->pRight->isRed == true
      //             && newb->pParent->pParent->pRight)	//case 3
      //         {
      //            newb->pParent->pParent->pRight->isRed = false;
      //            newb->pParent->pParent->isRed = true;
      //            newb->pParent->isRed = false;
      //         }
      //         else if (newb->pParent->pParent->pRight->isRed == false
      //                  && newb->pParent->pParent->pRight)					//case 4a
      //         {
      //            BNode* P = newb->pParent;
      //            BNode* G = P->pParent;
      //            BNode* S = P->pRight;
      //            P->pParent = G->pParent;
      //            if (P < P->pParent)
      //               P->pParent->pLeft = P;
      //            else
      //               P->pParent->pRight = P;
      //            G->pParent = P;
      //            P->pRight = G;
      //            G->pLeft = S;
      //            S->pParent = G;
      //         }
      //      }
      //      else															//parent is right of grandparent	> shape
      //      {
      //         if (newb->pParent->pParent->pLeft->isRed == true
      //             && newb->pParent->pParent->pLeft)		//case 3
      //         {
      //            newb->pParent->pParent->pLeft->isRed = false;
      //            newb->pParent->pParent->isRed = true;
      //            newb->pParent->isRed = false;
      //         }
      //         else if (newb->pParent->pParent->pLeft->isRed == false
      //                  && newb->pParent->pParent->pLeft)						//case 4d
      //         {
      //            BNode* L = newb->pLeft;
      //            BNode* R = newb->pRight;
      //            BNode* P = newb->pParent;
      //            BNode* S = P->pRight;
      //            BNode* G = P->pParent;
      //            BNode* A = G->pRight;
      //            newb->pParent = G->pParent;
      //            if (newb < newb->pParent)
      //               newb->pParent->pLeft = newb;
      //            else
      //               newb->pParent->pRight = newb;
      //            newb->pLeft = G;
      //            newb->pRight = P;
      //            G->pLeft = A;
      //            G->pRight = L;
      //            G->pParent = newb;
      //            P->pLeft = R;
      //            P->pRight = S;
      //            P->pParent = newb;
      //            A->pParent = G;
      //            L->pParent = G;
      //            R->pParent = P;
      //            S->pParent = P;
      //         }
      //      }
      //   }
      //   else															//child right of parent
      //   {
      //      if (newb->pParent->pParent->pLeft == newb->pParent)			//parent is left of grandparent		< shape
      //      {
      //         if (newb->pParent->pParent->pRight->isRed == true
      //             && newb->pParent->pParent->pRight)//case 3
      //         {
      //            newb->pParent->pParent->pRight->isRed = false;
      //            newb->pParent->pParent->isRed = true;
      //            newb->pParent->isRed = false;
      //         }
      //         else if (newb->pParent->pParent->pRight->isRed == false
      //                  && newb->pParent->pParent->pRight)					//case 4c
      //         {
      //            BNode* L = newb->pLeft;
      //            BNode* R = newb->pRight;
      //            BNode* P = newb->pParent;
      //            BNode* S = P->pLeft;
      //            BNode* G = P->pParent;
      //            BNode* A = G->pRight;
      //            newb->pParent = G->pParent;
      //            if (newb < newb->pParent)
      //               newb->pParent->pLeft = newb;
      //            else
      //               newb->pParent->pRight = newb;
      //            newb->pLeft = P;
      //            newb->pRight = G;
      //            P->pParent = newb;
      //            P->pLeft = S;
      //            P->pRight = L;
      //            G->pParent = newb;
      //            G->pLeft = R;
      //            G->pRight = A;
      //            S->pParent = P;
      //            L->pParent = P;
      //            R->pParent = G;
      //            A->pParent = G;
      //         }
      //      }
      //      else															//parent is right of grandparent	\ shape
      //      {
      //         if (newb->pParent->pParent->pLeft->isRed == true
      //             && newb->pParent->pParent->pLeft)//case 3
      //         {
      //            newb->pParent->pParent->pLeft->isRed = false;
      //            newb->pParent->pParent->isRed = true;
      //            newb->pParent->isRed = false;
      //         }
      //         else if (newb->pParent->pParent->pLeft->isRed == false
      //                  && newb->pParent->pParent->pLeft)						//case 4b
      //         {
      //            BNode* P = newb->pParent;
      //            BNode* G = P->pParent;
      //            BNode* S = P->pRight;
      //            P->pParent = G->pParent;
      //            if (P < P->pParent)
      //               P->pParent->pLeft = P;
      //            else
      //               P->pParent->pRight = P;
      //            G->pParent = P;
      //            P->pLeft = G;
      //            G->pRight = S;
      //            S->pParent = G;
      //         }
      //      }
      //   }						// p.222 Note that we may need to do more work if the great-grandparent is red.     ???
      //}
   }
   template<class T>
   typename BST<T>::iterator BST<T>::begin()
   {
	   iterator it = new iterator();
	   it->pNode = root;
	   while (it->pNode->pLeft)
		   it->pNode = it->pNode->pLeft;
	   return it;
   }
   template<class T>
   typename BST<T>::iterator BST<T>::end()
   {
	   iterator it = new iterator();
	   it->pNode = root;
	   while (it->pNode->pRight)
		   it->pNode = it->pNode->pRight;
	   return it;
   }
};
#endif // !BST_H
