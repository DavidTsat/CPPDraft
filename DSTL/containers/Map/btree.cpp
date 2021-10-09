/*
#include "btree.h"

namespace DSTL {


	template <typename KeyType, typename ValueType, typename ComparisonPredicate>
	void btree<KeyType, ValueType, ComparisonPredicate>::__postorder___traverse__(node* starting_node, std::function<void(node*)> f) {
		if (starting_node != nullptr) {
			__postorder___traverse__(starting_node->left_child, f);
			__postorder___traverse__(starting_node->right_child, f);
			f(starting_node);
		}
	}


}
*/