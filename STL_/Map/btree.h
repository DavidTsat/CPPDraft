#pragma once

#include <functional>
#include <iostream>
#include <initializer_list>
#include <vector>

#define DEBUG_MODE

template <typename T>
class btree {
	struct node {
		node* parent;
		node* left_child;
		node* right_child;
		T value;

		node(node* parent_ = nullptr, node* left_child_ = nullptr, node* right_child_ = nullptr, const T& value_ = T()) 
			: parent(parent_), left_child(left_child_), right_child(right_child_), value(value_) {}
	};
	
	node* root = nullptr;

	void __get__nodes__inorder__traverse__(node* starting_node, std::vector<node*>& v) {
		if (starting_node != nullptr) {
			__get__nodes__inorder__traverse__(starting_node->left_child, v);
			v.push_back(starting_node);
			__get__nodes__inorder__traverse__(starting_node->right_child, v);
		}
	}

	void __release__btree__(node* starting_node) {
		std::vector<node*> nodes;
		__get__nodes__inorder__traverse__(root, nodes);

#ifdef DEBUG_MODE
		std::cout << std::endl;
#endif // DEBUG_MODE

		for (node* current_node : nodes) {
#ifdef DEBUG_MODE
			std::cout << "deleting node with value: " << current_node->value; 
			std::cout << std::endl;
#endif // DEBUG_MODE
			delete current_node; 
		}
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