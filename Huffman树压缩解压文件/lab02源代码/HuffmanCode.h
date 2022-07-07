#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
typedef struct {
	unsigned int weight;
	unsigned char information;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;  //¶þ²æHuffmanÊ÷
typedef struct {
	unsigned int weight;
	unsigned char information;
	unsigned int parent, child[16];
}nHTNode, * nHuffmanTree;    //k²æHuffmanÊ÷
struct CharInf {
	unsigned char letter;
	long int count;
	char code[15];
};
typedef char** HuffmanCode;
void Select(HuffmanTree& HT, int n, int& s1, int& s2);
void Huffmancode(HuffmanTree& HT, HuffmanCode& HC, int* w, char* inf, int n);
int nHuffmancode(nHuffmanTree& nHT, HuffmanCode& nHC, long long int* w, char* inf, int n,int k);
void nSelect(nHuffmanTree& nHT, int n, int s[],int k);
int Min(nHuffmanTree t, int n);