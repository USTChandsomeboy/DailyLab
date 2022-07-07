#include"HuffmanCode.h"
void Select(HuffmanTree& HT, int n, int& s1, int& s2) {
	s1 = s2 = 0;
	for (int i = 1; i <= n; i++) {
		if (HT[i].parent != 0) continue;
		else {
			if (!s1) {
				s1 = i;
				continue;
			}
			else if (HT[i].weight < HT[s1].weight) {
				s2 = s1;
				s1 = i;
			}
			else {
				if (!s2) {
					s2 = i;
					continue;
				}
				else if (HT[i].weight < HT[s2].weight) s2 = i;
			}
		}
	}
}
void Huffmancode(HuffmanTree& HT, HuffmanCode& HC, int* w, char* inf, int n) {
	if (n <= 1) return;
	int m;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (int i = 1; i <= m; i++)
	{
		if (i <= n) {
			HT[i].weight = w[i];
			HT[i].information = inf[i];
		}
		else HT[i].weight = -1;
		HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
	}
	for (int i = n + 1; i <= m; i++) {
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		int c, p;
		for (c = i, p = HT[c].parent; p != 0; c = p, p = HT[p].parent) {
			if (HT[p].lchild == c)cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);

}