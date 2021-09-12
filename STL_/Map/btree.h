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

		void __postorder___traverse__(node* starting_node, std::function<void(node*)> f) {
			if (starting_node != nullptr) {
				__postorder___traverse__(starting_node->left_child, f);
				__postorder___traverse__(starting_node->right_child, f);
				f(starting_node);
			}
		}

		std::pair<K, V>& __search__(node* starting_node, const K& key) {
			if (starting_node == nullptr, key == starting_node->entry.first) {
				return starting_node->entry;
			}
			if (compare(key, starting_node->entry.first)) {
				return __search__(starting_node->left_child, key);
			}
			else {
				return __search__(starting_node->right_child, key);
			}
		}

		void __release__btree__(node* starting_node) {
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


	public:
		btree() = default;

		btree(std::initializer_list<std::pair<K, V>> entries) {
			for (typename std::initializer_list<std::pair<K, V>>::const_iterator it = entries.begin(); it != entries.end(); ++it) {
				insert(*it);
			}
		}

		btree(std::initializer_list<V> values) {
			for (typename std::initializer_list<V>::const_iterator it = values.begin(); it != values.end(); ++it) {
				insert(std::make_pair(*it, *it));
			}
		}

		~btree() {
			__release__btree__(root);
		}

		std::pair<K, V>& insert(const ValueType& value) {
			return insert(std::make_pair(value, value));
		}

		std::pair<K,V>& insert(const std::pair<KeyType, ValueType>& entry_) {
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

		void inorder_traverse(node* starting_node, std::function<void(std::pair<K, V>&)> f) {
			if (starting_node != nullptr) {
				inorder_traverse(starting_node->left_child, f);
				f(starting_node->entry);
				inorder_traverse(starting_node->right_child, f);
			}
		}


		void postorder_traverse(node* starting_node, std::function<void(std::pair<K,V>&)> f) {
			if (starting_node != nullptr) {
				postorder_traverse(starting_node->left_child, f);
				postorder_traverse(starting_node->right_child, f);
				f(starting_node->entry);
			}
		}

		std::pair<K, V>& operator[](const K& key) {
			return __search__(root, key);
		}

		friend void inorder_print<>(btree&);
		friend void postorder_print<>(btree&);
	}; 

	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	void inorder_print(btree<KeyType, ValueType, ComparisonPredicate>& b) {
		b.inorder_traverse(b.root, [](std::pair<KeyType, ValueType>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}

	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	void postorder_print(btree<KeyType, ValueType, ComparisonPredicate>& b) {
		b.postorder_traverse(b.root, [](std::pair<KeyType, ValueType>& v) {std::cout << v.first << ':' << v.second << ' '; });
	}
}

//#include "btree.cpp"