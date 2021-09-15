#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <utility>

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

		void __postorder___traverse__(node*, std::function<void(node*)>);
		std::pair<K, V>& __search__(node*, const K&);
		void __release__btree__(node*);

	public:
		btree() = default;

		btree(std::initializer_list<std::pair<K, V>>);
		btree(std::initializer_list<V>);

		~btree();

		std::pair<K, V>& insert(const V&);
		std::pair<K, V>& insert(const std::pair<K, V>&);
		void inorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)>);
		void postorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)>);
		std::pair<K, V>& operator[](const K&);

		friend void inorder_print<>(btree&);
		friend void postorder_print<>(btree&);
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
	std::pair<K, V>& btree<K, V, C>::__search__(btree<K,V,C>::node* starting_node, const K& key) {
		if (starting_node == nullptr || key == starting_node->entry.first) {
			return starting_node->entry;
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
	std::pair<K, V>& btree<K, V, C>::insert(const std::pair<K, V>& entry_) {
		node* temp_parent_node = nullptr;
		node* temp_current_node = root;

		while (temp_current_node != nullptr) {
			temp_parent_node = temp_current_node;

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
		return __search__(root, key);
	}


	template <typename K, typename V, typename C>
	void inorder_print(btree<K,V,C>& b) {
		b.inorder_traverse(b.root, [](std::pair<K,V>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}

	template <typename K, typename V, typename C>
	void postorder_print(btree<K,V,C>& b) {
		b.postorder_traverse(b.root, [](std::pair<K,V>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}

}