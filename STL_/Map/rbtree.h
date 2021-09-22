#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include "dexception.h"

#define DEBUG_MODE

namespace DSTL {

	/*
	forward declaration
	*/
	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	class rbtree;

	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	void swap(rbtree<KeyType, ValueType, ComparisonPredicate>&, rbtree<KeyType, ValueType, ComparisonPredicate>&) noexcept;

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
		std::size_t height;
		std::size_t size;
	public:
		
		class iterator {
			friend class const_iterator;
			node* node_;
			const node* nil_;
		public:

			iterator(node* node__, const node* nil__) : node_(node__), nil_(nil__) {}
			iterator& operator++();
			void operator--();
			bool operator!=(const iterator&);
			std::pair<const K, V>* operator->();
			std::pair<const K, V>& operator*();
			operator node* ();
		};

		class const_iterator {
			const node* node_;
			const node* nil_;
		public:
			const_iterator(iterator it_) : node_(it_.node_), nil_(it_.nil_) {}
			const_iterator(const node* node__, const node* nil__) : node_(node__), nil_(nil__) {}
			const_iterator& operator++();
			void operator--();
			bool operator!=(const const_iterator&) const;
			const std::pair<const K, V>* operator->() const;
			const std::pair<const K, V>& operator*() const;
			operator const node* () const;
		};
		
		rbtree() : height(0), size(0) {
			nil = new node(nullptr, nullptr, nullptr, std::pair<const K, V>(), node::Color::black);
			root = nil;
		}
		
		rbtree(const rbtree&);
		rbtree(rbtree&&) noexcept;
		
		rbtree& operator=(const rbtree&);
		rbtree& operator=(rbtree&&) noexcept;

		rbtree(std::initializer_list<std::pair<const K, V>>);
		rbtree(std::initializer_list<V>);

		void delete_entry(const K&);

		~rbtree();

		std::pair<const K, V>& insert(const V&);
		
		std::pair<const K, V>& insert(const std::pair<const K, V>&);
		
		void inorder_traverse(std::function<void(std::pair<const K, V>&)>);
		void postorder_traverse(std::function<void(std::pair<const K, V>&)>);
		std::pair<const K, V>& operator[](const K&);
		std::size_t get_height() const;
		std::size_t get_size() const;

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

#ifdef DEBUG_MODE
		bool check_rbtree_properties();
#endif // DEBUG_MODE

		friend void swap<>(rbtree&, rbtree&) noexcept;
	private:
		void __insert_fixup__(node*);
		void __left_rotate__(node*);
		void __right_rotate__(node*);

		void __postorder___traverse__(node*, std::function<void(node*)>, node* nil_);
		void __postorder___traverse__(node*, std::function<void(std::pair<const K, V>&)>, node* nil_);
		void __inorder___traverse__(node*, std::function<void(std::pair<const K, V>&)>, node* nil_);

		node* __search__(node*, const K&);
		void __release__rbtree__(node*);
		void __rb__transplant__(node*, node*);
		void __rb__delete_entry__(node*);
		void __rb__delete_fixup__(node*);

		node* __minimum__(node*);
		const node* __minimum__(const node*) const;
		node* __maximum__(node*);
		const node* __maximum__(const node*) const;
		
	};

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::insert(const std::pair<const K, V>& entry_) noexcept(false) {
		std::size_t height_counter = 1;
		node* y = nil;
		node* x = root;
	
		while (x != nil) {
			y = x;

			if (entry_.first == x->entry.first) {
			//	__release__rbtree__(root); TODO
				throw repeated_key_exception();
			}

			if (compare(entry_.first, x->entry.first)) {
				x = x->left_child;
			}
			else {
				x = x->right_child;
			}
			++height_counter;
		}
		node* z = new node(nullptr, nil, nil, entry_, node::Color::red);
		z->parent = y;
		if (y == nil) {
			root = z; // tree is empty
		}
		else if (z->entry.first < y->entry.first) {
			y->left_child = z;
		} 
		else {
			y->right_child = z;
		}

		__insert_fixup__(z);

		++size;
		if (height < height_counter) {
			height = height_counter;
		}
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
	rbtree<K, V, C>::rbtree(const rbtree<K, V, C>& rhs) : rbtree() {
/*
		for (const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
			this->insert(*it);
		}
		*/
		
		__postorder___traverse__(rhs.root, [this](node* cn) {
			this->insert(cn->entry);
			}, rhs.nil);
			
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::rbtree(rbtree<K, V, C>&& rhs) noexcept : rbtree() {
		swap(*this, rhs);
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>& rbtree<K, V, C>::operator=(const rbtree<K, V, C>& rhs) {
		rbtree temp(rhs);
		swap(*this, temp);
		return *this;
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>& rbtree<K, V, C>::operator=(rbtree<K, V, C>&& rhs) noexcept {
		swap(*this, rhs);
		return *this;
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::rbtree(std::initializer_list<std::pair<const K, V>> entries) : rbtree() {
		for (typename std::initializer_list<std::pair<const K, V>>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
			insert(*it);
		}
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::rbtree(std::initializer_list<V> values) : rbtree() {
		for (typename std::initializer_list<V>::const_iterator it = values.begin(); it != values.end(); ++it) {
			insert(std::make_pair(*it, *it));
		}
	}

	template <typename K, typename V, typename C>
	rbtree<K, V, C>::~rbtree() {
		__release__rbtree__(root);
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__rb__transplant__(rbtree<K, V, C>::node* u, rbtree<K, V, C>::node* v) {
		if (u->parent == nil) {
			root = v;
		}
		else if (u == u->parent->left_child) {
			u->parent->left_child = v;
		}
		else {
			u->parent->right_child = v;
		}
		v->parent = u->parent;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__rb__delete_entry__(rbtree<K, V, C>::node* z) {
		node* x;
		node* y = z;
		typename node::Color y_original_color = y->color;
		
		if (z->left_child == nil) {
			x = z->right_child;
			__rb__transplant__(z, z->right_child);
		} 
		else if (z->right_child == nil) {
			x = z->left_child;
			__rb__transplant__(z, z->left_child);
		}
		else {
			y = __minimum__(z->right_child);
			y_original_color = y->color;
			x = y->right_child;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				__rb__transplant__(y, y->right_child);
				y->right_child = z->right_child;
				y->right_child->parent = y;
			}
			__rb__transplant__(z, y);
			y->left_child = z->left_child;
			y->left_child->parent = y;
			y->color = z->color;
		}
		if (y_original_color == node::Color::black) {
			__rb__delete_fixup__(x);
		}

	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__rb__delete_fixup__(rbtree<K, V, C>::node* x) {
		while (x != root && x->color == node::Color::black) {
			if (x == x->parent->left_child) {
				node* w = x->parent->right_child;
				if (w->color == node::Color::red) {
					w->color = node::Color::black;
					x->parent->color = node::Color::red;
					__left_rotate__(x->parent);
					w = x->parent->right_child;
				}
				if (w->left_child->color == node::Color::black && w->right_child->color == node::Color::black) {
					w->color = node::Color::red;
					x = x->parent;
				}
				else {
					if (w->right_child->color == node::Color::black) {
						w->left_child->color = node::Color::black;
						w->color = node::Color::red;
						__right_rotate__(w);
						w = x->parent->right_child;
					}
					w->color = x->parent->color;
					x->parent->color = node::Color::black;
					w->right_child->color = node::Color::black;
					__left_rotate__(x->parent);
					x = root;
				}
			}
			else {
				if (x == x->parent->right_child) {
					node* w = x->parent->left_child;
					if (w->color == node::Color::red) {
						w->color = node::Color::black;
						x->parent->color = node::Color::red;
						__right_rotate__(x->parent);
						w = x->parent->left_child;
					}
					if (w->right_child->color == node::Color::black && w->left_child->color == node::Color::black) {
						w->color = node::Color::red;
						x = x->parent;
					}
					else {
						if (w->left_child->color == node::Color::black) {
							w->right_child->color = node::Color::black;
							w->color = node::Color::red;
							__left_rotate__(w);
							w = x->parent->left_child;
						}
						w->color = x->parent->color;
						x->parent->color = node::Color::black;
						w->left_child->color = node::Color::black;
						__right_rotate__(x->parent);
						x = root;
					}
				}
			}
		}
		x->color = node::Color::black;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::delete_entry(const K& key) noexcept(false) {
		typename rbtree<K, V, C>::node* node_to_delete = __search__(root, key);
		if (node_to_delete == nil) {
			return;
		}
		__rb__delete_entry__(node_to_delete);
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::insert(const V& value) {
		return insert(std::make_pair(value, value));
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__release__rbtree__(rbtree<K, V, C>::node* starting_node) {
		__postorder___traverse__(starting_node, [](node* cn) {
//#ifdef DEBUG_MODE
//			std::cout << "\nDeleting node with value: " << cn->entry.second;
//#endif // DEBUG_MODE
			delete cn;
			}, nil);
//#ifdef DEBUG_MODE
//		std::cout << std::endl;
//#endif // DEBUG_MODE
		delete nil;
		height = 0;
		size = 0;
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::inorder_traverse(std::function<void(std::pair<const K, V>&)> f) {
		__inorder___traverse__(root, f, nil);
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::postorder_traverse(std::function<void(std::pair<const K, V>&)> f) {
		__postorder___traverse__(root, f, nil);
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__postorder___traverse__(rbtree<K, V, C>::node* starting_node, std::function<void(node*)> f, rbtree<K, V, C>::node* nil_) {
		if (starting_node != nil_) {
			__postorder___traverse__(starting_node->left_child, f, nil_);
			__postorder___traverse__(starting_node->right_child, f, nil_);
			f(starting_node);
		}
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__postorder___traverse__(rbtree<K, V, C>::node* starting_node, std::function<void(std::pair<const K, V>&)> f, rbtree<K, V, C>::node* nil_) {
		if (starting_node != nil_) {
			__postorder___traverse__(starting_node->left_child, f, nil_);
			__postorder___traverse__(starting_node->right_child, f, nil_);
			f(starting_node->entry);
		}
	}

	template <typename K, typename V, typename C>
	void rbtree<K, V, C>::__inorder___traverse__(rbtree<K, V, C>::node* starting_node, std::function<void(std::pair<const K, V>&)> f, rbtree<K, V, C>::node* nil_) {
		if (starting_node != nil_) {
			__inorder___traverse__(starting_node->left_child, f, nil_);
			f(starting_node->entry);
			__inorder___traverse__(starting_node->right_child, f, nil_);
		}
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::node* rbtree<K, V, C>::__search__(rbtree<K, V, C>::node* starting_node, const K& key) noexcept(false) {
		if (starting_node == nil || key == starting_node->entry.first) {
			return starting_node == nil ? throw (key_not_found_exception()) : starting_node;
		}
		if (compare(key, starting_node->entry.first)) {
			return __search__(starting_node->left_child, key);
		}
		else {
			return __search__(starting_node->right_child, key);
		}
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& rbtree<K, V, C>::operator[](const K& key) {
		return __search__(root, key)->entry;
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::const_iterator rbtree<K, V, C>::begin() const {
		if (root == nil) {
			return { nullptr, nil };
		}
		const typename rbtree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nil) {
			min_node = min_node->left_child;
		}
		return { min_node, nil };
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::const_iterator rbtree<K, V, C>::end() const {
		if (root == nil) {
			return { nil, nil };
		}
		const typename rbtree<K, V, C>::node* max_node = __maximum__(root);
		return { max_node->left_child, nil };
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::iterator rbtree<K, V, C>::begin() {
		if (root == nil) {
			return { root, nil };
		}
		typename rbtree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nil) {
			min_node = min_node->left_child;
		}
		return { min_node, nil };
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::iterator rbtree<K, V, C>::end() {
		if (root == nil) {
			return { nil, nil };
		}
		typename rbtree<K, V, C>::node* max_node = __maximum__(root);
		return { max_node->left_child, nil };
	}

#ifdef DEBUG_MODE
	template <typename K, typename V, typename C>
	bool rbtree<K, V, C>::check_rbtree_properties() {
		std::map<K, std::size_t> leaf_keys;
		bool res = true;
		// 1 & 2
		if (root->color != node::Color::black && nil->color != node::Color::black) {
			std::cout << "root is not black!!!\n";
			res = false;
			return res;
		}
		// 3.
		__postorder___traverse__(root, [&res, this](typename rbtree<K, V, C>::node* node_) {
			res = node_->color == node::Color::red || node_->color == node::Color::black; },
			nil);
		// 4.
		__postorder___traverse__(root, [&res, this](typename rbtree<K, V, C>::node* node_) {
			if (node_->color == node::Color::red) {
				res = node_->left_child->color == node::Color::black && node_->right_child->color == node::Color::black;
			} },
			nil);
		// 5.
		__postorder___traverse__(root, [&leaf_keys, this](typename rbtree<K, V, C>::node* node_) {
			if (node_->left_child == nil && node_->right_child == nil) { // leaf node
				leaf_keys[node_->entry.first] = 0;
			} },
			nil);
		
		for (const auto& key_ : leaf_keys) {
			const node* starting_node = root;
			std::size_t black_count = 0;

			while (starting_node->entry.first != key_.first) {

				if (compare(key_.first, starting_node->entry.first)) {
					starting_node = starting_node->left_child;
				}
				else {
					starting_node = starting_node->right_child;
				}
				if (starting_node->color == node::Color::black) {
					++black_count;
				}
			}
			leaf_keys[starting_node->entry.first] = black_count;
		}
		std::size_t first_leaf_bc = leaf_keys.begin()->second;
		std::cout << "first_leaf_bc: " << first_leaf_bc << std::endl;
		res = std::all_of(std::next(leaf_keys.begin()), leaf_keys.end(),
			[first_leaf_bc](typename std::map<K, std::size_t>::const_reference t) { return t.second == first_leaf_bc; });
		return res;
	}
#endif // DEBUG_MODE

	template <typename K, typename V, typename C>
	void swap(rbtree<K, V, C>& l, rbtree<K, V, C>& r) noexcept {
		std::swap(l.root, r.root);
		std::swap(l.nil, r.nil);
		std::swap(l.height, r.height);
		std::swap(l.size, r.size);
		std::swap(l.compare, r.compare);
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::const_iterator& rbtree<K, V, C>::const_iterator::operator++() {
		if (node_ == nil_) {
			return *this;
		}

		if (node_->right_child != nil_) {
			const typename rbtree<K, V, C>::node* right_subtree = node_->right_child;
			while (right_subtree->left_child != nil_) {
				right_subtree = right_subtree->left_child;
			}
			node_ = right_subtree;
			return *this;
		}
		const typename rbtree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nil_ && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ = parent_node;

		return *this;
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
	typename rbtree<K, V, C>::iterator& rbtree<K, V, C>::iterator::operator++() {
		if (node_ == nil_) {
			return *this;
		}

		if (node_->right_child != nil_) {
			typename rbtree<K, V, C>::node* right_subtree = node_->right_child;
			while (right_subtree->left_child != nil_) {
				right_subtree = right_subtree->left_child;
			}
			node_ = right_subtree;
			return *this;
		}
		typename rbtree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nil_ && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ = parent_node;

		return *this;
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

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::node* rbtree<K, V, C>::__minimum__(rbtree<K, V, C>::node* starting_node) {
		typename rbtree<K, V, C>::node* min_node = starting_node;

		if (min_node == nil) {
			return min_node;
		}
		while (min_node->left_child != nil) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	const typename rbtree<K, V, C>::node* rbtree<K, V, C>::__minimum__(const rbtree<K, V, C>::node* starting_node) const {
		const typename rbtree<K, V, C>::node* min_node = starting_node;

		if (min_node == nil) {
			return min_node;
		}
		while (min_node->left_child != nil) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename rbtree<K, V, C>::node* rbtree<K, V, C>::__maximum__(rbtree<K, V, C>::node* starting_node) {
		typename rbtree<K, V, C>::node* max_node = starting_node;
		if (max_node == nil) {
			return max_node;
		}
		while (max_node->right_child != nil) {
			max_node = max_node->right_child;
		}
		return max_node;
	}

	template <typename K, typename V, typename C>
	const typename rbtree<K, V, C>::node* rbtree<K, V, C>::__maximum__(const rbtree<K, V, C>::node* starting_node) const {
		const typename rbtree<K, V, C>::node* max_node = starting_node;

		if (max_node == nil) {
			return max_node;
		}
		while (max_node->right_child != nil) {
			max_node = max_node->right_child;
		}
		return max_node;
	}

	template <typename K, typename V, typename C>
	std::size_t rbtree<K, V, C>::get_height() const {
		return height;
	}

	template <typename K, typename V, typename C>
	std::size_t rbtree<K, V, C>::get_size() const {
		return size;
	}
}