#include"Compress.h"
bool Compress(char Comstr[],unsigned char& ASCII) {  //将8位二进制数转为1位的char型
	ASCII=0;
		for (int i = 0; i < 8; i++) {
			if (Comstr[i] == '1') ASCII = ASCII * 2 + 1;
			else ASCII = ASCII * 2;
		}
	
	return true;
}
bool Decompress(char Decstr[],unsigned char ASCII) { //将1位的char型转为8位二进制数
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