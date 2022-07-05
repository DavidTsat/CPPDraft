#pragma once
#include "rbtree.h"

void test1()
{
    bstree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    for (bstree_map<int, string>::iterator it = b1.begin(); it != b1.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
}

void test2()
{
    bstree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    b1.print_inorder();
    b1.print_preorder();
    b1.print_levelorder();
}

void test3()
{
    bstree_map<int, string> b1;

    b1[5] = "AAAAAAA";
    b1[5] = "BBBBBBB";
    b1[15] = "CCCCCCCC";
    b1[-7] = "DDDDDDDDDD";
    b1[0] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[12] = "GGGGG";
    b1[6] = "HHHHHHHHHH";

    
    b1.print_inorder();
    b1.print_preorder();
    b1.print_levelorder();
    

    for (bstree_map<int, string>::iterator it = b1.begin(); it != b1.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
    
    bstree_map<int, string> b2(b1);

    b2.print_inorder();
    b2.print_preorder();
    b2.print_levelorder();
    
}

void test4()
{
    bstree_map<int, string> b1;

    b1[-7] = "AAAAAAA";
    b1[0] = "BBBBBBB";
    b1[6] = "CCCCCCCC";
    b1[12] = "DDDDDDDDDD";
    b1[15] = "EEEEEEE";
    b1[51] = "FFFFFF";
    b1[78] = "GGGGG";
    b1[95] = "HHHHHHHHHH";

 //   b1.print_inorder();
    b1.print_levelorder();
}