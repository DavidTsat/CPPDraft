/*
#include "btree.h"

template <typename T>
T& btree<T>::insert(const T& value_) {
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
	else if (value_ < temp_parent_node->value)  {
		temp_parent_node->left_child = new_node;
	}
	else {
		temp_parent_node->right_child = new_node;
	}


	return new_node->value;
}
*/