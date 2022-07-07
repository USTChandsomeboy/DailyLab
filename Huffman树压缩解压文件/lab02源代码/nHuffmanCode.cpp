#include"HuffmanCode.h"
#define infinity 10000000000000

int Min(nHuffmanTree t, int n)
{
	int i, flag=-1;
	long long int f = infinity;
	for (i = 1; i <= n; i++)
	{
		if (t[i].weight < f )
		{
			if (t[i].parent == 0) {
				f = t[i].weight, flag = i;
			}

		}

	}
	if (flag != -1)t[flag].parent = 1;
	else cout << "error!"<<n << endl;
	return flag;
}
void nSelect(nHuffmanTree& nHT, int n, int s[], int k) {
	for (int i = 0; i < k; i++) {
		s[i] = 0;
	}
	for (int i = 0; i < k; i++) {
		s[i] = Min(nHT, n); 
	}
	int i, j,temp;
	for (i = 0; i < k - 1; ++i)
		for (j = 0; j < k - i - 1; ++j)
			if (nHT[s[j]].weight > nHT[s[j + 1]].weight)
				temp = s[j], s[j] = s[j + 1], s[j + 1] = temp;
	/*max_heapify(s, k);
	HeapSort(s, k);*/
}
int nHuffmancode(nHuffmanTree& nHT, HuffmanCode& nHC,long long int* w, char* inf, int n,int k) {
	if (n <= 1) return -1;
	int m;
	int plusnum = 0;
	while ((n - k) % (k - 1) != 0) {
		plusnum++;
		n = n + 1;
	}
	int temp=n-k;
	int m_cnt = 1;
		temp = temp / (k - 1);
		m_cnt+=temp;
	m = n + m_cnt;//构建k叉Huffman树总共需要的节点空间
	nHT = (nHuffmanTree)malloc((m + 1) * sizeof(nHTNode));
	for (int i = 1; i <= m; i++)
	{
		if (i <= n-plusnum) {
			nHT[i].weight = w[i];
			nHT[i].information = inf[i];
		}
		else nHT[i].weight = 0;
		nHT[i].parent = 0;
		for (int j = 0; j < 16; j++) {
			nHT[i].child[j] = 0;
		}
	}
	for (int i = n + 1; i <= m; i++) {
		int s[16];
		nSelect(nHT, i - 1, s,k);//找出权重最小的k棵树
		for (int j = 0; j < k; j++) {
			nHT[s[j]].parent = i;
		}
		nHT[i].weight = 0;
		for (int j = 0; j < k; j++) {
			nHT[i].child[j] = s[j];
			nHT[i].weight += nHT[s[j]].weight;
		}
	}
	nHC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		int c, p;
		for (c = i, p = nHT[c].parent; p != 0; c = p, p = nHT[p].parent) {
			for (int j = 0; j < k; j++) {
				if (nHT[p].child[j] == c) {
					if (j <= 9 && j >= 0)cd[--start] = j+48;
					else cd[--start] = 'A' + j - 10;
				}
				//if (k >= 3 )cd[--start] = '0';
				//if (k >= 5)cd[--start] = '0';
				//if (k >= 9)cd[--start] = '0';
			}
		}
		nHC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(nHC[i], &cd[start]);
	}
	free(cd);
	return m;
}