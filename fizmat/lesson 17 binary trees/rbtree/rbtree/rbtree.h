#pragma once

#include <iostream>
#include <functional>
#include <utility>
#include <queue>

#define debug_mode

using namespace std;

template<typename K, typename T, typename Compare = std::less<K>>
class bstree_map {
public:
    using key_type = K;
    using mapped_type = T;
    using value_type = pair<const K, T>;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using key_compare = Compare;
private:

    enum class color {RED, BLACK};

    struct node {
        value_type entry;
        color c;

        node* parent, * left, * right;

        node(const value_type& entry_, color c_ = color::RED, node* parent_ = nullptr, node* left_ = nullptr, node* right_ = nullptr) : entry(entry_), c(c_), parent(parent_),
            left(left_), right(right_) {}
    };

    node* root;
    static node* nil;// = new node(make_pair(key_type(), mapped_type()), color::BLACK);
    Compare cmp;
    size_type sz;

private:
    static node* get_min(node* p)
    {
        while (p->left && p->left != nil)
            p = p->left;
        return p;
    }

    template <typename F>
    void inorder_traversal(node* p, F f)
    {
        /*
        left subtree, root, right subtree
        */
        if (!p || p == nil)
            return;
        if (p->left)
            inorder_traversal(p->left, f);

        f(p);
        if (p->right)
            inorder_traversal(p->right, f);
    }

    template <typename F>
    void preorder_traversal(node* p, F f)
    {
        /*
        root, left subtree, right subtree
        */
        if (!p || p == nil)
            return;

        f(p);
        if (p->left)
            preorder_traversal(p->left, f);
        if (p->right)
            preorder_traversal(p->right, f);
    }

    template <typename F>
    void postorder_traversal(node* p, F f)
    {
        /*
        root, left subtree, right subtree
        */
        if (!p || p == nil)
            return;

        if (p->left)
            postorder_traversal(p->left, f);
        if (p->right)
            postorder_traversal(p->right, f);
        f(p);
    }

    template <typename F>
    void level_traversal(node* p_, F f)
    {
        /*
        BFS
        */
        if (!p_ || p_ == nil)
            return;

        queue<node*> q;
        q.push(p_);

        while (!q.empty()) {
            node* p = q.front();
            q.pop();

            f(p);
            if (p->left && p->left != nil)
                q.push(p->left);
            if (p->right && p->right != nil)
                q.push(p->right);
        }
    }

    void right_rotate(node* y)
    {
        /*
                |                           |
                y                           x
               / \             ------>     / \
              x   g (subtree)             a   y
             / \                             / \
  (subtree) a   b (subtree)                 b   g
        */
        node* x = y->left;
        y->left = x->right;
        if (x->right != nil)
            x->right->parent = y;
        x->parent = y->parent;
        if (y == root)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void left_rotate(node* x)
    {
        /*
               |                            |
               x               ------->     y
              / \                          / \
   (subtree) a   y                        x   g
                / \                      / \   
     (subtree) b   g (subtree)          a   b
        */
        node* y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        y->parent = x->parent;
        if (x == root)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else 
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void insert_fixup(node* z)
    {
        while (z->parent->c == color::RED)
        {
            /*
            *  RED      *
            *  BLACK    +
            */
            if (z->parent == z->parent->parent->left)
            {
                node* y = z->parent->parent->right;
                if (y->c == color::RED)
                {
                    /*
                    *               +11+            случай 1.
                    *              /    \
                    *            *2*    +14+
                    *           /   \     \
                    *         +1+   +7+   *15*
                    *              /   \
                    *             *5*  *8* (y)
                    *             /
                    *           *4* (z)
                    */
                    z->parent->c = color::BLACK;
                    y->c = color::BLACK;
                    z->parent->parent->c = color::RED; // IT WAS BLACK BEFORE
                    z = z->parent->parent;
                    /*
                     *               +11+      
                     *              /    \
                     *            *2*    +14+ (y)
                     *           /   \      \
                     *         +1+   *7*(z) *15*
                     *              /   \
                     *             +5+  +8+
                     *             /
                     *           *4*
                     */
                }
                else
                {
                    /*
                    *               +11+
                    *              /    \
                    *            *2*    +14+ (y)
                    *           /   \      \
                    *         +1+   *7*(z) *15*
                    *              /   \
                    *             +5+  +8+
                    *             /
                    *           *4*
                    */
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        right_rotate(z);
                    /*
                    *               +11+
                    *              /    \
                    *            *7*    +14+ (y)
                    *           /   \      \
                    *         *2*(z) +8+   *15*
                    *        /  \       
                    *       +1+  +5+  
                    *            /
                    *           *4*
                    */
                    }
                    z->parent->c = color::BLACK;
                    z->parent->parent->c = color::RED;
                   /*
                   *               *11*
                   *              /    \
                   *            +7+    +14+ (y)
                   *           /   \      \
                   *         *2*(z) +8+   *15*
                   *        /  \
                   *       +1+  +5+
                   *            /
                   *           *4*
                   */
                    right_rotate(z->parent->parent);
                    /*
                    *                +7+
                    *              /     \
                    *            *2*      *11*
                    *           /  \      /  \
                    *         +1+  +5+   +8+ +14+
                    *              /            \
                    *             *4*           *15*
                    *           
                    *           
                    */
                }
            }
            else
            {
                node* y = z->parent->parent->left;
                if (y->c == color::RED)
                {
                    z->parent->c = color::BLACK;
                    y->c = color::BLACK;
                    z->parent->parent->c = color::RED; 
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->c = color::BLACK;
                    z->parent->parent->c = color::RED;
     
                    left_rotate(z->parent->parent);
                }
            }
            if (z == root) break;
        }
        root->c = color::BLACK;
    }
public:
    bstree_map(Compare cmp_ = Compare()) : root(nullptr), cmp(cmp_), sz(0) {}

    bstree_map(const bstree_map& other) : root(nullptr), cmp(other.cmp), sz(other.sz) {
        if (sz == 0)
            return;
        // 
        // BS Tree -> red black BS Tree -> std::map

        // TODO to make this O(n)

        level_traversal(other.root, [this](node* p) {this->operator[](p->entry.first) = p->entry.second; });
        //   inorder_traversal(other.root, [this](node* p){this->operator[](p->entry.first) = p->entry.second;});
    }

    bstree_map(bstree_map&& other) noexcept {}

    bstree_map& operator=(const bstree_map& other) {}

    bstree_map& operator=(bstree_map&& other) noexcept {}

    ~bstree_map() noexcept
    {
        postorder_traversal(root, [](node* p) { delete p; });
    //    delete nil;
    }
    
    reference operator[](const key_type& key)
    {
        if (!root) {
            ++sz;
            root = new node(make_pair(key, mapped_type()), color::BLACK, nil, nil);
            return root->entry.second;
        }
        node* p = root;
        node* prev = nullptr;
        while (p && p != nil)
        {
            prev = p;
            //if (!cmp(key, p->entry.first)  && !cmp(p->entry.first, key))
            if (cmp(key, p->entry.first))
                p = p->left;
            else if (cmp(p->entry.first, key))
                p = p->right;
            else
                return p->entry.second;
        }
        ++sz;
        p = new node(make_pair(key, mapped_type()), color::RED, prev, nil, nil);
        if (cmp(prev->entry.first, key))
            prev->right = p;
        else
            prev->left = p;
        p->parent = prev;
        insert_fixup(p);

        return p->entry.second;
    }

    class iterator {
        node* it;

        node* successor(node* p)
        {
            if (it->right)
                return get_min(it->right);
            node* parent_it = it->parent;
            while (parent_it && parent_it->right == it) {
                parent_it = parent_it->parent;
                it = it->parent;
            }
            return parent_it;
        }
        node* predecessor(node* p)
        {
            //TODO
        }
    public:
        iterator(node* it_) : it(it_) {}

        value_type& operator*() {
            return it->entry;
        }

        value_type* operator->() {
            return &it->entry;
        }

        iterator& operator++() { //++it
            it = successor(it);
            return *this;
        }

        iterator operator++(int) { //it++
          // QUESTION
            iterator old_it = it;
            it = successor(it);
            return old_it;
        }

        bool operator==(iterator other) const {
            return it != other.it;
        }

        bool operator!=(iterator other) const {
            return it != other.it;
        }
    };

    iterator begin()
    {
        return get_min(root);
    }

    iterator end()
    {
        return nullptr;
    }

    void erase(iterator it)
    {

    }

#ifdef debug_mode
    void print_inorder()
    {
        inorder_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }

    void print_preorder()
    {
        preorder_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }
    void print_levelorder()
    {
        level_traversal(root, [](node* it) {cout << it->entry.first << ' ' << it->entry.second << '\n'; });
        cout << endl;
    }

#endif 
};

//template<typename K, typename T, typename C>
//bstree_map<K, T, C>::node* bstree_map<K,T,C>::nil = new node(make_pair(key_type(), mapped_type()), color::BLACK);

template<typename K, typename T, typename C>
typename bstree_map<K, T, C>::node* bstree_map<K, T, C>::nil = new node(make_pair(key_type(), mapped_type()), color::BLACK);