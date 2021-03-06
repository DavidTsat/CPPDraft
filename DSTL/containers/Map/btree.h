#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>
#include "dexception.h"

//#define DEBUG_MODE

namespace DSTL {

	/*
	forward declaration
	*/
	template <typename KeyType, typename ValueType, typename ComparisonPredicate = std::less<KeyType> >
	class btree;

	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	class btree {

		using K = KeyType;
		using V = ValueType;

		struct node {
			node* parent;
			node* left_child;
			node* right_child;

			std::pair<const K, V> entry;

			node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const std::pair<const K, V>& entry_ = std::pair<const K, V>())
				: parent(parent_), left_child(left_child_), right_child(right_child_), entry(entry_) {}
		};

		ComparisonPredicate compare = ComparisonPredicate();
		node* root = nullptr;
		std::size_t height = 0;
		std::size_t size = 0;
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

		btree() = default;

		btree(std::initializer_list<std::pair<const K, V>>);
		btree(std::initializer_list<V>);

		~btree();

		std::pair<const K, V>& insert(const V&);
		std::pair<const K, V>& insert(const std::pair<const K, V>&);
		void delete_entry(const K&);
		void inorder_traverse(std::function<void(std::pair<const K, V>&)>);
		void postorder_traverse(std::function<void(std::pair<const K, V>&)>);
		std::size_t get_height() const;
		std::size_t get_size() const;
		std::pair<const K, V>& operator[](const K&);

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

	private:
		void __postorder___traverse__(node*, std::function<void(node*)>);
		void __postorder___traverse__(node*, std::function<void(std::pair<const K, V>&)>);
		void __inorder___traverse__(node*, std::function<void(std::pair<const K, V>&)>);

		node* __search__(node*, const K&);
		void __release__btree__(node*);
		void __transplant__(node*, node*);
		void __delete_entry__(node*);

		btree::iterator __minimum__(btree::iterator);
		btree::const_iterator __minimum__(btree::const_iterator) const;
		btree::iterator __maximum__(btree::iterator);
		btree::const_iterator __maximum__(btree::const_iterator) const;
	};


	template <typename K, typename V, typename C>
	void btree<K, V, C>::__postorder___traverse__(btree<K, V, C>::node* starting_node, std::function<void(node*)> f) {
		if (starting_node != nullptr) {
			__postorder___traverse__(starting_node->left_child, f);
			__postorder___traverse__(starting_node->right_child, f);
			f(starting_node);
		}
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::__postorder___traverse__(btree<K, V, C>::node* starting_node, std::function<void(std::pair<const K, V>&)> f) {
		if (starting_node != nullptr) {
			__postorder___traverse__(starting_node->left_child, f);
			__postorder___traverse__(starting_node->right_child, f);
			f(starting_node->entry);
		}
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::__inorder___traverse__(btree<K, V, C>::node* starting_node, std::function<void(std::pair<const K, V>&)> f) {
		if (starting_node != nullptr) {
			__inorder___traverse__(starting_node->left_child, f);
			f(starting_node->entry);
			__inorder___traverse__(starting_node->right_child, f);
		}
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::node* btree<K, V, C>::__search__(btree<K, V, C>::node* starting_node, const K& key) noexcept(false) {
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
	typename btree<K, V, C>::iterator btree<K, V, C>::__minimum__(btree<K, V, C>::iterator starting_node) {
		typename btree<K, V, C>::node* min_node = starting_node;

		if (min_node == nullptr) {
			return min_node;
		}
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::const_iterator btree<K, V, C>::__minimum__(btree<K, V, C>::const_iterator starting_node) const {
		const typename btree<K, V, C>::node* min_node = starting_node;

		if (min_node == nullptr) {
			return min_node;
		}
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::iterator btree<K, V, C>::__maximum__(btree<K, V, C>::iterator starting_node) {
		typename btree<K, V, C>::node* max_node = starting_node;
		if (max_node == nullptr) {
			return max_node;
		}
		while (max_node->right_child != nullptr) {
			max_node = max_node->right_child;
		}
		return max_node;
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::const_iterator btree<K, V, C>::__maximum__(btree<K, V, C>::const_iterator starting_node) const {
		const typename btree<K, V, C>::node* max_node = starting_node;

		if (max_node == nullptr) {
			return max_node;
		}
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
		delete node_to_delete;
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::btree(std::initializer_list<std::pair<const K, V>> entries) {
		for (typename std::initializer_list<std::pair<const K, V>>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
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
	std::pair<const K, V>& btree<K, V, C>::insert(const V& value) {
		return insert(std::make_pair(value, value));
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& btree<K, V, C>::insert(const std::pair<const K, V>& entry_) noexcept(false) {
		std::size_t height_counter = 1;
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
			++height_counter;
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

		++size;
		if (height < height_counter) {
			height = height_counter;
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
	void btree<K, V, C>::inorder_traverse(std::function<void(std::pair<const K, V>&)> f) {
		__inorder___traverse__(root, f);
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::postorder_traverse(std::function<void(std::pair<const K, V>&)> f) {
		__postorder___traverse__(root, f);
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& btree<K, V, C>::operator[](const K& key) {
		return __search__(root, key)->entry;
	}

	template <typename K, typename V, typename C>
	std::size_t btree<K, V, C>::get_height() const {
		return height;
	}

	template <typename K, typename V, typename C>
	std::size_t btree<K, V, C>::get_size() const {
		return size;
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
	typename btree<K, V, C>::iterator btree<K, V, C>::begin() {
		if (root == nullptr) {
			return root;
		}
		typename btree<K, V, C>::node* min_node = root;
		while (min_node->left_child != nullptr) {
			min_node = min_node->left_child;
		}
		return min_node;
	}

	template <typename K, typename V, typename C>
	typename btree<K, V, C>::iterator btree<K, V, C>::end() {
		typename btree<K, V, C>::node* max_node = __maximum__(root);
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
		const typename btree<K, V, C>::node* parent_node = node_->parent;
		while (parent_node != nullptr && node_ == parent_node->right_child) {
			node_ = parent_node;
			parent_node = parent_node->parent;
		}

		node_ = parent_node;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::const_iterator::operator--() {
		// TODO
	}

	template <typename K, typename V, typename C>
	bool btree<K, V, C>::const_iterator::operator!=(const const_iterator& rhs) const {
		return node_ != rhs.node_;
	}

	template <typename K, typename V, typename C>
	const std::pair<const K, V>* btree<K, V, C>::const_iterator::operator->() const {
		return &node_->entry;
	}

	template <typename K, typename V, typename C>
	const  std::pair<const K, V>& btree<K, V, C>::const_iterator::operator*() const {
		return node_->entry;
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::const_iterator::operator typename const btree<K, V, C>::node* () const {
		return node_;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::iterator::operator++() {
		if (node_ == nullptr) {
			return;
		}

		if (node_->right_child != nullptr) {
			typename btree<K, V, C>::node* right_subtree = node_->right_child;
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

		node_ = parent_node;
	}

	template <typename K, typename V, typename C>
	void btree<K, V, C>::iterator::operator--() {
		// TODO
	}

	template <typename K, typename V, typename C>
	bool btree<K, V, C>::iterator::operator!=(const iterator& rhs) {
		return node_ != rhs.node_;
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>* btree<K, V, C>::iterator::operator->() {
		return &node_->entry;
	}

	template <typename K, typename V, typename C>
	std::pair<const K, V>& btree<K, V, C>::iterator::operator*() {
		return node_->entry;
	}

	template <typename K, typename V, typename C>
	btree<K, V, C>::iterator::operator typename btree<K, V, C>::node* () {
		return node_;
	}
}