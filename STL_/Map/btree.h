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
	class btree;
	
	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	void inorder_print(btree<KeyType, ValueType, ComparisonPredicate>& b);
	
	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	void postorder_print(btree<KeyType, ValueType, ComparisonPredicate>& b);


	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	class btree {

		using K = KeyType;
		using V = ValueType;

		struct node {
			node* parent;
			node* left_child;
			node* right_child;
			
			std::pair<K, V> entry;

			node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const std::pair<K, V>& entry_ = std::pair<K, V>())
				: parent(parent_), left_child(left_child_), right_child(right_child_), entry(entry_) {}
		};

		ComparisonPredicate compare = ComparisonPredicate();
		node* root = nullptr;

	public:
		class const_iterator {
			const node* node_;
		public:
			const_iterator(const node* node__) : node_(node__) {}
			void operator++();
			void operator--();
			bool operator!=(const const_iterator&);

			const std::pair<K, V>* operator->() const;
			operator const node* () const;
		};

		btree() = default;

		btree(std::initializer_list<std::pair<K, V>>);
		btree(std::initializer_list<V>);

		~btree();

		std::pair<K, V>& insert(const V&);
		std::pair<K, V>& insert(const std::pair<K, V>&);
		void delete_entry(const K&);
		void inorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)>);
		void postorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)>);
		std::pair<K, V>& operator[](const K&);

		friend void inorder_print<>(btree&);
		friend void postorder_print<>(btree&);

		const_iterator begin() const;
		const_iterator end() const;

	private:
		void __postorder___traverse__(node*, std::function<void(node*)>);
		node* __search__(node*, const K&);
		void __release__btree__(node*);
		node* __minimum__(const node*);
		const node* __minimum__(btree::const_iterator) const;
		node* __maximum__(const node*);
		const node* __maximum__(btree::const_iterator) const;
		void __transplant__(node*, node*);
		void __delete_entry__(node*);
		node* __successor__(btree::const_iterator) const;
	}; 


	template <typename K, typename V, typename C>
	void btree<K,V,C>::__postorder___traverse__(btree<K, V, C>::node* starting_node, std::function<void(node*)> f) {
		if (starting_node != nullptr) {
			__postorder___traverse__(starting_node->left_child, f);
			__postorder___traverse__(starting_node->right_child, f);
			f(starting_node);
		}
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::node* btree<K, V, C>::__search__(btree<K,V,C>::node* starting_node, const K& key) noexcept(false) {
		if (starting_node == nullptr || key == starting_node->entry.first) {
			return starting_node == nullptr ? throw (key_not_found_exception()) : starting_node;
		}
		if (compare(key, starting_node->entry.first)) {
			return __search__(starting_node->left_child, key);
		}
		else {
			return __search__(starting_node->right_child, key);
		}
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::__release__btree__(btree<K, V, C>::node* starting_node) {
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
	typename btree<K, V, C>::node* btree<K, V, C>::__minimum__(const btree<K, V, C>::node* starting_node) {
		if (starting_node == nullptr) {
			return starting_node;
		}
		typename btree<K, V, C>::node* min_node = starting_node;
		while (starting_node->left_child != nullptr) {
			min_node = starting_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	const typename btree<K, V, C>::node* btree<K, V, C>::__minimum__(btree<K, V, C>::const_iterator starting_node) const {
		if (starting_node == nullptr) {
			return starting_node;
		}
		typename btree<K, V, C>::node* min_node = starting_node;
		while (starting_node->left_child != nullptr) {
			min_node = starting_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::node* btree<K, V, C>::__maximum__(const btree<K, V, C>::node* starting_node) {
		if (starting_node == nullptr) {
			return starting_node;
		}
		typename btree<K, V, C>::node* max_node = starting_node;
		while (starting_node->right_child != nullptr) {
			max_node = starting_node->right_child;
		}
		return max_node;
	}

	template <typename K, typename V, typename C>
	const typename btree<K, V, C>::node* btree<K, V, C>::__maximum__(btree<K, V, C>::const_iterator starting_node) const {
		if (starting_node == nullptr) {
			return starting_node;
		}
		const typename btree<K, V, C>::node* max_node = starting_node;
		while (max_node->right_child != nullptr) {
			max_node = max_node->right_child;
		}
		return max_node;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::__transplant__(btree<K, V, C>::node* to_remove, btree<K, V, C>::node* to_add) {
		if (to_remove->parent == nullptr) {
			root = to_add;
		}
		else if (to_remove == to_remove->parent->left_child) {
			to_remove->parent->left_child = to_add;
		}
		else {
			to_remove->parent->right_child = to_add;
		}
		if (to_add != nullptr) {
			to_add->parent = to_remove->parent;
		}
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::__delete_entry__(btree<K, V, C>::node* node_to_delete) {
		if (node_to_delete->left_child == nullptr) {
			__transplant__(node_to_delete, node_to_delete->right_child);
		}
		else if (node_to_delete->right_child == nullptr) {
			__transplant__(node_to_delete, node_to_delete->left_child);
		}
		else {
			typename btree<K, V, C>::node* min_node = __minimum__(node_to_delete->right_child);
			if (min_node->parent != node_to_delete) {
				__transplant__(min_node, min_node->right_child);
				min_node->right_child = node_to_delete->right_child;
				node_to_delete->right_child->parent = min_node;
			}
			__transplant__(node_to_delete, min_node);
			min_node->left_child = node_to_delete->left_child;
			min_node->left_child->parent = min_node;
		}
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::node* btree<K, V, C>::__successor__(btree<K, V, C>::const_iterator starting_node) const {
		if (starting_node->right_child == nullptr) {
			return __minimum__(starting_node->right_child);
		}
		typename btree<K, V, C>::node* parent_node = starting_node->parent;
		while (parent_node != nullptr && starting_node == parent_node->right_child) {
			starting_node = parent_node;
			parent_node = parent_node->parent;
		}
		return parent_node;
	}

	template <typename K, typename V, typename C>
	btree<K,V,C>::btree(std::initializer_list<std::pair<K, V>> entries) {
		for (typename std::initializer_list<std::pair<K, V>>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
			insert(*it);
		}
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::btree(std::initializer_list<V> values) {
		for (typename std::initializer_list<V>::const_iterator it = values.begin(); it != values.end(); ++it) {
			insert(std::make_pair(*it, *it));
		}
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::~btree() {
		__release__btree__(root);
	}

	template <typename K, typename V, typename C>
	std::pair<K, V>& btree<K, V, C>::insert(const V& value) {
		return insert(std::make_pair(value, value));
	}

	template <typename K, typename V, typename C>
	std::pair<K, V>& btree<K, V, C>::insert(const std::pair<K, V>& entry_) noexcept(false) {
		node* temp_parent_node = nullptr;
		node* temp_current_node = root;

		while (temp_current_node != nullptr) {
			temp_parent_node = temp_current_node;

			if (entry_.first == temp_current_node->entry.first) {
				__release__btree__(root);
				throw repeated_key_exception();
			}

			if (compare(entry_.first, temp_current_node->entry.first)) {
				temp_current_node = temp_current_node->left_child;
			}
			else {
				temp_current_node = temp_current_node->right_child;
			}
		}

		node* new_node = new node(temp_parent_node, nullptr, nullptr, entry_);

		if (temp_parent_node == nullptr) {
			root = new_node;
		}
		else if (compare(entry_.first, temp_parent_node->entry.first)) {
			temp_parent_node->left_child = new_node;
		}
		else {
			temp_parent_node->right_child = new_node;
		}

		return new_node->entry;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::delete_entry(const K& key) noexcept(false) {
		typename btree<K, V, C>::node* node_to_delete = __search__(root, key);
		if (node_to_delete == nullptr) {
			return;
		}
		__delete_entry__(node_to_delete);
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::inorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)> f) {
		if (starting_node != nullptr) {
			inorder_traverse(starting_node->left_child, f);
			f(starting_node->entry);
			inorder_traverse(starting_node->right_child, f);
		}
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::postorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)> f) {
		if (starting_node != nullptr) {
			postorder_traverse(starting_node->left_child, f);
			postorder_traverse(starting_node->right_child, f);
			f(starting_node->entry);
		}
	}

	template <typename K, typename V, typename C>
	std::pair<K, V>& btree<K, V, C>::operator[](const K& key) {
		return __search__(root, key)->entry;
	}


	template <typename K, typename V, typename C>
	void inorder_print(btree<K,V,C>& b) {
		b.inorder_traverse(b.root, [](std::pair<K,V>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}

	template <typename K, typename V, typename C>
	void postorder_print(btree<K,V,C>& b) {
		b.postorder_traverse(b.root, [](std::pair<K,V>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::const_iterator btree<K, V, C>::begin() const {
		if (root == nullptr) {
			return root;
		}
		const typename btree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}
	
	template <typename K, typename V, typename C>
	typename btree<K, V, C>::const_iterator btree<K, V, C>::end() const {
		const typename btree<K, V, C>::node* max_node = __maximum__(root);
		return max_node->left_child;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::const_iterator::operator++() {
		if (node_ == nullptr) {
			return;
		}

		if (node_->right_child != nullptr) {
			const typename btree<K, V, C>::node* right_subtree = node_->right_child;
			while (right_subtree->left_child != nullptr) {
				right_subtree = right_subtree->left_child;
			}
			node_ = right_subtree;
			return;
		}
		typename btree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nullptr && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ =  parent_node;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::const_iterator::operator--() {
	// TODO
	}

	template <typename K, typename V, typename C>
	bool btree<K, V, C>::const_iterator::operator!=(const const_iterator& rhs) {
		return node_ != rhs.node_;
	}

	template <typename K, typename V, typename C>
	const std::pair<K, V>* btree<K, V, C>::const_iterator::operator->() const {
		return &node_->entry;
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::const_iterator::operator typename const btree<K, V, C>::node* () const {
		return node_;
	}
}