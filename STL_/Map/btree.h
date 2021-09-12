#pragma once

#include <functional>
#include <iostream>

template <typename T>
class btree {
	struct node {
		node* parent;
		node* left_child;
		node* right_child;

		T value;

		node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const T& value_ = T()) : left_child(left_child_), right_child(right_child_), value(value_) {}
	};
	node* root = nullptr;
public:
	btree() = default;

	T& insert(const T& value_) {
		btree<T>::node* temp_parent_node = nullptr;
		btree<T>::node* temp_current_node = root;

		while (temp_current_node != nullptr) {
			temp_parent_node = temp_current_node;

			if (value_ < temp_current_node->value) {
				temp_current_node = temp_current_node->left_child;
			}
			else {
				temp_current_node = temp_current_node->right_child;
			}
		}

		btree<T>::node* new_node = new btree<T>::node(temp_parent_node, nullptr, nullptr, value_);

		if (temp_parent_node == nullptr) {
			root = new_node;
		}
		else if (value_ < temp_parent_node->value) {
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

	void inorder_print() {
		inorder_traverse(root, [](T& v) {std::cout << v << ' '; });
	}

};


//#include "btree.cpp"