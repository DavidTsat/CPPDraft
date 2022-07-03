#pragma once
#include <utility>
#include <functional>
#include <iostream>
#include <queue>
#include <assert.h>

#include <limits.h>

using namespace std;

#define debug_mode

/*
		12
	  /    \
	 5      18
    / \    /  \
   2   9  15  19
         /  \
        13  17
		-
*/ 

template <typename Key, typename T, typename Compare = less<Key>>
class btree_map
{
public:
	using key_type			= Key;
	using mapped_type		= T;
	using value_type		= std::pair<const Key, T>;
	using reference			= T&;
	using const_reference	= const T&;
	using size_type			= size_t;
private:
	struct node
	{
		value_type	entry;
		node*		left_child;
		node*		right_child;
		node*		parent;

		node(const value_type& e, node* l = nullptr, node* r = nullptr, node* p = nullptr) : entry(e), left_child(l), right_child(r), parent(p) {}
	};
	node* root;
	Compare cmp;

	template <typename F>
	void preorder_traversal(node* p, F f) 
	{
		if (p == nullptr)
			return;

		preorder_traversal(p->left_child, f);
		f(p);
		preorder_traversal(p->right_child, f);
	}

	template <typename F>
	void postorder_traversal(node* p, F f)
	{
		if (p == nullptr)
			return;

		postorder_traversal(p->left_child, f);
		postorder_traversal(p->right_child, f);
		f(p);
	}

	template <typename F>
	void levelorder_traversal(queue<node*>& q, F f)
	{
		// BFS
		if (q.empty())
			return;

		node* p = q.front();
		q.pop();
		f(p);

		if (p->left_child)
			q.push(p->left_child);
		if (p->right_child)
			q.push(p->right_child);

		levelorder_traversal(q, f);
	}

	static node* get_min(node* p)
	{
		if (p == nullptr)
			return p;
		
		while (p->left_child)
		{
			p = p->left_child;
		}
		return p;
	}

	static node* get_max(node* p)
	{
		if (p == nullptr)
			return p;

		while (p->right_child)
		{
			p = p->right_child;
		}
		return p;
	}

	void transplant(node* u, node* v)
	{
		if (u->parent == nullptr)
			root = v;

		else if (u == u->parent->left_child)
		{
			u->parent->left_child = v;
		}
		else
		{
			u->parent->right_child = v;
		}
		if (v != nullptr)
		{
			v->parent = u->parent;
		}
	}

public:

#ifdef debug_mode
	void print_inorder()
	{
		preorder_traversal(root, [](node* p) {cout << p->entry.first << " : " << p->entry.second << ' '; });
		cout << endl;
	}

	void print_postorder()
	{
		postorder_traversal(root, [](node* p) {cout << p->entry.first << " : " << p->entry.second << ' '; });
		cout << endl;
	}

	void print_levelorder()
	{
		queue<node*> q;
		q.push(root);

		levelorder_traversal(q, [](node* p) { cout << p->entry.first << " : " << p->entry.second << ' '; });
	}
#endif

	class iterator
	{
		node* p;
		node* successor(node* x)
		{
			if (x->right_child != nullptr)
			{
				return get_min(x->right_child);
				
			}
			node* y = x->parent;
			while (y != nullptr && x == y->right_child)
			{
				x = y;
				y = x->parent;
			}
			return y;
		}

		node* predecessor(node* x)
		{
			// TODO
		}
	public:
		iterator(node* p_ = nullptr) : p(p_) {}
		value_type& operator*()
		{
			return p->entry;
		}
		value_type* operator->()
		{
			return &p->entry;
		}
		iterator& operator++()
		{
			p = successor(p);
			return *this;
		}
		iterator& operator++(int)
		{
			node* x = p;
			p = successor(p);
			return x;
		}
		iterator& operator--()
		{

		}
		iterator& operator--(int)
		{

		}

		bool operator==(const iterator& it2) const
		{
			return p == it2.p;
		}
		bool operator!=(const iterator& it2) const
		{
			return p != it2.p;
		}

		explicit operator node* ()
		{
			return p;
		}
	};

	btree_map() : root(nullptr), cmp(Compare()) {} 
	explicit btree_map(const Compare& cmp_) : root(nullptr), cmp(cmp_) {}
	btree_map(const btree_map& m) : root(nullptr), cmp(m.cmp) 
	{
		// QUESTION: WHY INORDER IS BAD AND LEVELORDER IS GOOD
		// level-order <=> BFS

		if (m.root == nullptr)
			return;

		queue<node*> q;
		q.push(m.root);

		levelorder_traversal(q, [this](node* p) {this->operator[](p->entry.first) = p->entry.second; });
	}

	btree_map(btree_map&& m) noexcept : btree_map()  //QUESTION. WHY WE SHOULD DEFAULT INITIALIZE ??? 
	{
		this->swap(m);
		//m.~btree_map();
	}

	btree_map& operator=(const btree_map& m)
	{
		btree_map temp(m);
		this->swap(temp);

		return *this;
	}

	btree_map& operator=(btree_map&& m) noexcept
	{
		this->swap(m);
	//	m.~btree_map();
		return *this;
	}

	template <typename It>
	btree_map(It first, It last, const Compare& cmp = Compare()) {}

	~btree_map() noexcept
	{
		_release_tree_(root);
	}

	mapped_type& operator[](const key_type& k)
	{
		node* p = root;
		if (p == nullptr)
		{
			p = new node({ k, mapped_type{} }); // 2 copies here
			root = p;
			return root->entry.second;
		}

		node* prev = p;
		while (p != nullptr)
		{
			prev = p;
			if (!cmp(k, p->entry.first) && !cmp(p->entry.first, k))
			{
				return p->entry.second;
			}
			if (cmp(k, p->entry.first))
			{
				p = p->left_child;
			}
			else
			{
				p = p->right_child;
			}
		}
		p = new node({ k, mapped_type{} });
		p->parent = prev;
		if (cmp(k, prev->entry.first))
		{
			prev->left_child = p;
		}
		else
		{
			prev->right_child = p;
		}
		return p->entry.second;
	}

	iterator begin()
	{
		return get_min(root);
	}

	iterator end()
	{
		return nullptr;
	}

	void swap(btree_map& m) noexcept
	{
		std::swap(root, m.root);
		std::swap(cmp,  m.cmp);
	}

	iterator find(const key_type& k)
	{
		return find_recursive(root, k);
	}

	void erase(iterator it)
	{
		node* z = (node*)it;
		if (z->left_child == nullptr)
			transplant(z, z->right_child);
		else if (z->right_child == nullptr)
			transplant(z, z->left_child);
		else
		{
			node* y = get_min(z->right_child);
			if (y == z->right_child)
			{
				transplant(z, y->right_child);
				y->right_child->left_child = z->left_child;
				z->left_child->parent = y->right_child;
			}
			else
			{
				transplant(y, y->right_child);
				transplant(z, y);
				y->right_child = z->right_child;
				z->right_child->parent = y;
				y->left_child = z->left_child;
				z->left_child->parent = y;
			}
		}
		delete z;
	}

#ifdef debug_mode
	bool is_valid_bst()
	{
		return validate_btree(root);
	}

	void check_is_valid_bst()
	{
		vector<pair<node*, bool>> v = bad_bst_examples();

		for (pair<node*, bool> p : v)
		{
			bool b = validate_btree(p.first);
			assert(b == p.second);
		}
	}
#endif

private:
	void _release_tree_(node* p)
	{
		postorder_traversal(p, [](node* x) {delete x; });
	}

	iterator find_recursive(node* p, const key_type& k)
	{
		if (p == nullptr || (!cmp(p->entry.first, k) && !cmp(k, p->entry.first)))
		{
			return p;
		}

		if (cmp(k, p->entry.first))
			return find_recursive(p->left_child, k);
		else
			return find_recursive(p->right_child, k);
	}

#ifdef debug_mode
	bool validate_btree(node* p)
	{
		if (p == nullptr)
			return true;

		key_type max_k = numeric_limits<key_type>::min();
		key_type min_k = numeric_limits<key_type>::max();

		preorder_traversal(p->left_child, [this, &max_k, &min_k](node* x) { if (cmp(x->entry.first, min_k)) min_k = x->entry.first; if (!cmp(x->entry.first, max_k)) max_k = x->entry.first; });

		if (!cmp(max_k, p->entry.first))
		{
			return false;
		}

		max_k = numeric_limits<key_type>::min();
		min_k = numeric_limits<key_type>::max();

		preorder_traversal(p->right_child, [this, &max_k, &min_k](node* x) { if (cmp(x->entry.first, min_k)) min_k = x->entry.first; if (!cmp(x->entry.first, max_k)) max_k = x->entry.first; });

		if (cmp(min_k, p->entry.first))
		{
			return false;
		}

		return validate_btree(p->left_child) && validate_btree(p->right_child);
	}

	vector<pair<node*, bool>> bad_bst_examples()
	{
		/*
		*		    2		true
		*		   / \
		*		  1	  3
		*/

		/*		    5		false
		*		   / \
		*		  1   4
		*			 / \
		*			3   6
		*/

		/*			5		false
		*		   / \
		*		  4   6
		*			 / \
		*           3   7
		*/

		// no need to use parent nodes
		node* ex1 = new node({ 2, 2 }, new node({ 1, 1 }), new node({ 3, 3 }));
		node* ex2 = new node({ 5, 5 }, new node({ 1, 1 }, new node({ 4, 4 }, new node({ 3, 3 }), new node({ 6, 6 }))));
		node* ex3 = new node({ 5, 5 }, new node({ 4, 4 }, new node({ 6, 6 }, new node({ 3, 3 }, new node({ 7,7 })))));

		vector<pair<node*, bool>> r = { {ex1, true}, {ex2, false}, {ex3, false} };
		return r;
	}

#endif

};

