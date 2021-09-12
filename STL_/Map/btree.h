#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>

#define DEBUG_MODE

namespace DSTL {

	/*
	forward declaration
	*/
	template <typename ValueType, typename KeyType = ValueType, typename ComparisonPredicate = std::less<KeyType> >
	class btree;
	
	template <typename ValueType, typename KeyType = ValueType, typename ComparisonPredicate = std::less<KeyType> >
	void inorder_print(btree<ValueType, KeyType, ComparisonPredicate>& b);
	
	template <typename ValueType, typename KeyType = ValueType, typename ComparisonPredicate = std::less<KeyType> >
	void postorder_print(btree<ValueType, KeyType, ComparisonPredicate>& b);


	template <typename ValueType, typename KeyType, typename ComparisonPredicate>
	class btree {
		using T = ValueType;
		struct node {
			node* parent;
			node* left_child;
			node* right_child;
			T value;

			node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const T& value_ = T())
				: parent(parent_), left_child(left_child_), right_child(right_child_), value(value_) {}
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

		void __release__btree__(node* starting_node) {
			__postorder___traverse__(starting_node, [](node* cn) {
#ifdef DEBUG_MODE
				std::cout << "\nDeleting node with value: " << cn->value; 
#endif // DEBUG_MODE
				delete cn; 
				});
#ifdef DEBUG_MODE
			std::cout << std::endl;
#endif // DEBUG_MODE
		}


	public:
		btree() = default;

		btree(std::initializer_list<T> values) {
			for (typename std::initializer_list<T>::const_iterator it = values.begin(); it != values.end(); ++it) {
				insert(*it);
			}
		}

		~btree() {
			__release__btree__(root);
		}

		T& insert(const T& value_) {
			node* temp_parent_node = nullptr;
			node* temp_current_node = root;

			while (temp_current_node != nullptr) {
				temp_parent_node = temp_current_node;

				if (compare(value_, temp_current_node->value)) {
					temp_current_node = temp_current_node->left_child;
				}
				else {
					temp_current_node = temp_current_node->right_child;
				}
			}

			node* new_node = new node(temp_parent_node, nullptr, nullptr, value_);

			if (temp_parent_node == nullptr) {
				root = new_node;
			}
			else if (compare(value_, temp_parent_node->value)) {
				temp_parent_node->left_child = new_node;
			}
			else {
				temp_parent_node->right_child = new_node;
			}

			return new_node->value;
		}

		void inorder_traverse(node* starting_node, std::function<void(T& value_)> f) {
			if (starting_node != nullptr) {
				inorder_traverse(starting_node->left_child, f);
				f(starting_node->value);
				inorder_traverse(starting_node->right_child, f);
			}
		}


		void postorder_traverse(node* starting_node, std::function<void(T& value_)> f) {
			if (starting_node != nullptr) {
				postorder_traverse(starting_node->left_child, f);
				postorder_traverse(starting_node->right_child, f);
				f(starting_node->value);
			}
		}

		friend void inorder_print<>(btree&);
		friend void postorder_print<>(btree&);
	}; 

	template <typename ValueType, typename KeyType, typename ComparisonPredicate>
	void inorder_print(btree<ValueType, KeyType, ComparisonPredicate>& b) {
		b.inorder_traverse(b.root, [](ValueType& v) {std::cout << v << ' '; });
	}

	template <typename ValueType, typename KeyType, typename ComparisonPredicate>
	void postorder_print(btree<ValueType, KeyType, ComparisonPredicate>& b) {
		b.postorder_traverse(b.root, [](ValueType& v) {std::cout << v << ' '; });
	}
}

//#include "btree.cpp"