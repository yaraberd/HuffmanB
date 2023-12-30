#include <iostream>
#include <bits/stdc++.h>
#include<fstream>
using namespace std;

struct Forest {
    int weight;
    int root;
};
Forest forest[256];

struct Tree {
    int left, right, parent;
};
Tree tree[520];

struct Code {
    int length;
    int coding[250];
};
Code code[256];
FILE * f, *g;

void getMin(Forest f[], int size, int &p1, int &p2) {
    if (f[0].weight <= f[1].weight) {
        p1 = 0;
        p2 = 1;
    }
    else {
        p2 = 0;
        p1 = 1;
    }
    for (int i = 2; i < size; i++) {
        if (f[i].weight < f[p2].weight) {
            if (f[i].weight < f[p1].weight) {
                p2 = p1;
                p1 = i;
            }
            else {
                p2 = i;
            }
        }

    }
}

int main()
{
    f = fopen("input.txt", "rb");
    freopen("outh.txt", "wb", stdout);
    int freg [256];
    int pr [256];
    for (int i = 0; i < 256; i++) {
        freg[i] = 0;
    }
    char ch;
    while (fscanf(f,"%c", &ch) != -1) {
        freg[ch]++;
    }
    //инициализация
    int size_forest = 0;
    for (int i = 0; i < 256; i++) {
        if (freg[i] != 0) {
            forest[size_forest].weight = freg[i];
            forest[size_forest].root = size_forest;
            pr[i] = size_forest;
            size_forest++;
        }
    }
    for (int i = 0; i < size_forest; i++) {
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].parent = -1;
    }
    int size_tree = size_forest;
    int symb = size_tree;
    for (int i = 0; i < size_forest; i++) {
        cout << forest[i].weight << " " << forest[i].root << endl;
    }

    for (int i = 0; i < size_forest; i++) {
        cout << tree[i].right << " " << tree[i].left << " " << tree[i].parent << endl;
    }
    //формирование дерева
    int pos1 = 0;
    int pos2 = 0;
    while (size_forest > 1) {
        getMin(forest, size_forest, pos1, pos2);
        tree[size_tree].left = forest[pos1].root;
        tree[size_tree].right = forest[pos2].root;
        tree[size_tree].parent = -1;
        tree[forest[pos1].root].parent = size_tree;
        tree[forest[pos2].root].parent = size_tree;
        forest[pos1].weight = forest[pos1].weight + forest[pos2].weight;
        forest[pos1].root = size_tree;
        forest[pos2] = forest[size_forest-1];
        size_forest--;
        size_tree++;

    }
    for (int i = 0; i < symb; i++) {
        int li = 0;
        int m = i;
        while (tree[m].parent != -1) {
            if (tree[tree[m].parent].left == m) {
                code[i].coding[li] = 0;
            }
            else {
                code[i].coding[li] = 1;
            }
            m = tree[m].parent;
            li++;
        }
        code[i].length = li;
        reverse(code[i].coding, code[i].coding + li);
    }
    unsigned char byte = 0;
    unsigned cut_bit = 0;
    unsigned char ch1;
    fclose(f);
    f = fopen("input.txt", "rb");
    while (fscanf(f, "%c", &ch1)!= -1) {
        byte <<=1;
        for (int i = 0; i < code[pr[ch1]].length; i++) {
            byte += code[pr[ch1]].coding[i];
            cut_bit++;
            if (cut_bit == 8) {
                fprintf(stdout, "%c", byte);
                byte = 0;
                cut_bit= 0;
            }

        }
    }

    return 0;
}


