#include"Compress.h"
bool Compress(char Comstr[],unsigned char& ASCII) {  //��8λ��������תΪ1λ��char��
	ASCII=0;
		for (int i = 0; i < 8; i++) {
			if (Comstr[i] == '1') ASCII = ASCII * 2 + 1;
			else ASCII = ASCII * 2;
		}
	
	return true;
}
bool Decompress(char Decstr[],unsigned char ASCII) { //��1λ��char��תΪ8λ��������
	int cnt = 0;
	for (int i = 0; i < 10; i++)
		Decstr[i] = '0';
	while (ASCII) {
		Decstr[7 - cnt] = '0' + (ASCII % 2);
 		ASCII /= 2;
		cnt++;
	}
	if (cnt != 8) {
		Decstr[7 - cnt] = '0';
		cnt++;
	}
	Decstr[8] = '\0';
	return true;
}