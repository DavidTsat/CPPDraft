#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>
#include "dexception.h"

#define DEBUG_MODE

namespace DSTL {

	/*
	forward declaration
	*/
	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	class rbtree;

	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	class rbtree {

		using K = KeyType;
		using V = ValueType;

		struct node {
			enum Color {red, black};

			node* parent;
			node* left_child;
			node* right_child;
			
			std::pair<const K, V> entry;
			Color color;

			node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const std::pair<const K, V>& entry_ = std::pair<const K, V>(), Color color_ = Color::red)
				: parent(parent_), left_child(left_child_), right_child(right_child_), entry(entry_), color(color_) {}
		};

		ComparisonPredicate compare = ComparisonPredicate();
		node* root;
		node* nil;
	public:
		
		class iterator {
			friend class const_iterator;
			node* node_;

		public:

			iterator(node* node__) : node_(node__) {}
			void operator++();
			void operator--();
			bool operator!=(const iterator&);
			std::pair<const K, V>* operator->();
			std::pair<const K, V>& operator*();
			operator node* ();
		};

		class const_iterator {
			const node* node_;
		public:
			const_iterator(iterator it_) : node_(it_.node_) {}
			const_iterator(const node* node__) : node_(node__) {}
			void operator++();
			void operator--();
			bool operator!=(const const_iterator&) const;
			const std::pair<const K, V>* operator->() const;
			const std::pair<const K, V>& operator*() const;
			operator const node* () const;
		};
		
		rbtree() {
			nil = new node(nullptr, nullptr, nullptr, std::pair<const K, V>(), node::Color::black);
			root = nil;
		}
		
		rbtree(std::initializer_list<std::pair<const K, V>>);
		rbtree(std::initializer_list<V>);

		~rbtree();

		std::pair<const K, V>& insert(const V&);
		
		std::pair<const K, V>& insert(const std::pair<const K, V>&);
		
		void inorder_traverse(node* starting_node, std::function<void(std::pair<const K, V>&)>);
		void postorder_traverse(node* starting_node, std::function<void(std::pair<const K, V>&)>);
		std::pair<const K, V>& operator[](const K&);

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

	private:
		void __insert_fixup__(node*);
		void __left_rotate__(node*);
		void __right_rotate__(node*);

		void __postorder___traverse__(node*, std::function<void(node*)>);
		node* __search__(node*, const K&);
		void __release__rbtree__(node*);
		void __transplant__(node*, node*);

		rbtree::iterator __minimum__(rbtree::iterator);
		rbtree::const_iterator __minimum__(rbtree::const_iterator) const;
		rbtree::iterator __maximum__(rbtree::iterator);
		rbtree::const_iterator __maximum__(rbtree::const_iterator) const;
		
	};

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::insert(const std::pair<const K, V>& entry_) noexcept(false) {
		node* y = nil;
		node* x = root;
		node* z = new node(nullptr, nil, nil, entry_, node::Color::red);
		while (x != nil) {
			y = x;
			if (z->entry.first < x->entry.first) {
				x = x->left_child;
			}
			else {
				x = x->right_child;
			}
		}
		z->parent = y;
		if (y == nil) {
			root = z; // tree is empty
		//	root->color = node::Color::black;
		}
		else if (z->entry.first < y->entry.first) {
			y->left_child = z;
		} 
		else {
			y->right_child = z;
		}

		/*
		if (z->parent->parent == nil) {
			return z->entry;
		}
		*/
		__insert_fixup__(z);
		return z->entry;
	}
	
	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__insert_fixup__(rbtree<K, V, C>::node* z) {
		while (z->parent->color == node::Color::red) {
			if (z->parent == z->parent->parent->left_child) {
				node* y = z->parent->parent->right_child;
				if (y->color == node::Color::red) {
					z->parent->color = node::Color::black;
					y->color = node::Color::black;
					z->parent->parent->color = node::Color::red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right_child) {
						z = z->parent;
						__left_rotate__(z);
					}
					z->parent->color = node::Color::black;
					z->parent->parent->color = node::Color::red;
					__right_rotate__(z->parent->parent);		
				}
			}
			else {
				node* y = z->parent->parent->left_child;
				if (y->color == node::Color::red) {
					z->parent->color = node::Color::black;
					y->color = node::Color::black;
					z->parent->parent->color = node::Color::red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left_child) {
						z = z->parent;
						__right_rotate__(z);
					}
					z->parent->color = node::Color::black;
					z->parent->parent->color = node::Color::red;
					__left_rotate__(z->parent->parent);
				}
			}
		}
		root->color = node::Color::black;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__left_rotate__(rbtree<K, V, C>::node * x) {
		node* y = x->right_child;
		x->right_child = y->left_child;
		if (y->left_child != nil) {
			y->left_child->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		}
		else if (x == x->parent->left_child) {
			x->parent->left_child = y;
		}
		else {
			x->parent->right_child = y;
		}
		y->left_child = x;
		x->parent = y;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__right_rotate__(rbtree<K, V, C>::node* y) {
		node* x = y->left_child;
		y->left_child = x->right_child;
		if (x->right_child != nil) {
			x->right_child->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nil) {
			root = x;
		}
		else if (y == y->parent->left_child) {
			y->parent->left_child = x;
		}
		else {
			y->parent->right_child = x;
		}
		x->right_child = y;
		y->parent = x;
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::rbtree(std::initializer_list<std::pair<const K, V>> entries) {
		for (typename std::initializer_list<std::pair<const K, V>>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
			insert(*it);
		}
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::rbtree(std::initializer_list<V> values) {
		for (typename std::initializer_list<V>::const_iterator it = values.begin(); it != values.end(); ++it) {
			insert(std::make_pair(*it, *it));
		}
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::~rbtree() {
		__release__rbtree__(root);
		delete nil;
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::insert(const V& value) {
		return insert(std::make_pair(value, value));
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__release__rbtree__(rbtree<K, V, C>::node* starting_node) {
		__postorder___traverse__(starting_node, [](node* cn) {
#ifdef DEBUG_MODE
			std::cout << "\nDeleting node with value: " << cn->entry.second;
#endif // DEBUG_MODE
			delete cn;
			});
#ifdef DEBUG_MODE
		std::cout << std::endl;
#endif // DEBUG_MODE
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::inorder_traverse(node* starting_node, std::function<void(std::pair<const K, V>&)> f) {
		if (starting_node != nullptr) {
			inorder_traverse(starting_node->left_child, f);
			f(starting_node->entry);
			inorder_traverse(starting_node->right_child, f);
		}
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::postorder_traverse(node* starting_node, std::function<void(std::pair<const K, V>&)> f) {
		if (starting_node != nullptr) {
			postorder_traverse(starting_node->left_child, f);
			postorder_traverse(starting_node->right_child, f);
			f(starting_node->entry);
		}
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__postorder___traverse__(rbtree<K, V, C>::node* starting_node, std::function<void(node*)> f) {
		if (starting_node != nil) {
			__postorder___traverse__(starting_node->left_child, f);
			__postorder___traverse__(starting_node->right_child, f);
			f(starting_node);
		}
	}

	////////////////////////////////////
	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::const_iterator rbtree<K, V, C>::begin() const {
		if (root == nullptr) {
			return root;
		}
		const typename rbtree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::const_iterator rbtree<K, V, C>::end() const {
		const typename rbtree<K, V, C>::node* max_node = __maximum__(root);
		return max_node->left_child;
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::iterator rbtree<K, V, C>::begin() {
		if (root == nullptr) {
			return root;
		}
		typename rbtree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::iterator rbtree<K, V, C>::end() {
		typename rbtree<K, V, C>::node* max_node = __maximum__(root);
		return max_node->left_child;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::const_iterator::operator++() {
		if (node_ == nullptr) {
			return;
		}

		if (node_->right_child != nullptr) {
			const typename rbtree<K, V, C>::node* right_subtree = node_->right_child;
			while (right_subtree->left_child != nullptr) {
				right_subtree = right_subtree->left_child;
			}
			node_ = right_subtree;
			return;
		}
		const typename rbtree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nullptr && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ = parent_node;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::const_iterator::operator--() {
		// TODO
	}

	template <typename K, typename V, typename C>
	bool rbtree<K, V, C>::const_iterator::operator!=(const const_iterator& rhs) const {
		return node_ != rhs.node_;
	}

	template <typename K, typename V, typename C>
	const std::pair<const K, V>* rbtree<K, V, C>::const_iterator::operator->() const {
		return &node_->entry;
	}

	template <typename K, typename V, typename C>
	const  std::pair<const K, V>& rbtree<K, V, C>::const_iterator::operator*() const {
		return node_->entry;
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::const_iterator::operator typename const rbtree<K, V, C>::node* () const {
		return node_;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::iterator::operator++() {
		if (node_ == nullptr) {
			return;
		}

		if (node_->right_child != nullptr) {
			typename rbtree<K, V, C>::node* right_subtree = node_->right_child;
			while (right_subtree->left_child != nullptr) {
				right_subtree = right_subtree->left_child;
			}
			node_ = right_subtree;
			return;
		}
		typename rbtree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nullptr && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ = parent_node;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::iterator::operator--() {
		// TODO
	}

	template <typename K, typename V, typename C>
	bool rbtree<K, V, C>::iterator::operator!=(const iterator& rhs) {
		return node_ != rhs.node_;
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>* rbtree<K, V, C>::iterator::operator->() {
		return &node_->entry;
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::iterator::operator*() {
		return node_->entry;
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::iterator::operator typename rbtree<K, V, C>::node* () {
		return node_;
	}

}