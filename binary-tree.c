/* binary-tree.c */
/* Copyright (C) 2018  "Michael G. Morey" <mgmorey@gmail.com> */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

/*      A      */
/*     / \     */
/*    /   \    */
/*   B     E   */
/*  / \   / \  */
/* |   | |   | */
/* C   D F   G */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a,b)                                \
    ({ __typeof__ (a) _a = (a);                 \
        __typeof__ (b) _b = (b);                \
        _a > _b ? _a : _b; })

typedef struct _Node {
    int value;
    struct _Node* left;
    struct _Node* right;
} Node;

Node* alloc_node(int value)
{
    Node* node = calloc(1, sizeof *node);

    assert ( node != NULL );

    node->value = value;
    return node;
}

void free_nodes(Node* root)
{
    if ( root == NULL )
        return;

    free_nodes(root->right);
    free_nodes(root->left);
    free(root);
}

int get_height(Node* root)
{
    int left = 0;
    int right = 0;

    if ( root->left != NULL )
        left = get_height(root->left);

    if ( root->right != NULL )
        right = get_height(root->right);

    return max(left, right) + 1;
}

int get_width(Node* root)
{
    int left = 0;
    int right = 0;
    int width = 0;

    if ( root->left != NULL ) {
        ++width;
        left = get_width(root->left);
    }

    if ( root->right != NULL ) {
        ++width;
        right = get_width(root->right);
    }

    return max(width, left + right);
}

void print_inorder(Node* root)
{
    if ( root == NULL )
        return;

    print_inorder(root->left);
    printf("%c", (char)root->value);
    print_inorder(root->right);
}

void print_postorder(Node* root)
{
    if ( root == NULL )
        return;

    print_postorder(root->left);
    print_postorder(root->right);
    printf("%c", (char)root->value);
}

void print_preorder(Node* root)
{
    if ( root == NULL )
        return;

    printf("%c", (char)root->value);
    print_preorder(root->left);
    print_preorder(root->right);
}

void print_nodes(Node* root)
{
    int height = get_height(root);
    int width = get_width(root);

    printf("tree height: %d\n", height);
    printf("tree width: %d\n", width);
    printf("tree inorder: ");
    print_inorder(root);
    printf("\n");
    printf("tree postorder: ");
    print_postorder(root);
    printf("\n");
    printf("tree preorder: ");
    print_preorder(root);
    printf("\n");
    printf("\n");
}

int main(int argc, const char* argv[])
{
    Node* root = alloc_node('A');

    root->left = alloc_node('B');
    print_nodes(root);
    root->right = alloc_node('E');
    print_nodes(root);
    root->left->left = alloc_node('C');
    print_nodes(root);
    root->left->right = alloc_node('D');
    print_nodes(root->left);
    print_nodes(root);
    root->right->left = alloc_node('F');
    root->right->right = alloc_node('G');
    print_nodes(root->right);
    print_nodes(root);
    free_nodes(root);
    exit(EXIT_SUCCESS);
}
