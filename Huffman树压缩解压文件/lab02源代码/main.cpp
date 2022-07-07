#include"HuffmanCode.h"
#include"Compress.h"
int main() {
	int Command=1;
	char filename[50];
	char config[50];
	char Compressedfile[50];
	char Decompressedfile[50];
	int k;
	long long int* w;
	w = (long long int*)malloc((256 + 1) * sizeof(long long int));
	cout << "请输入huffmna树的叉数：";
	cin >> k;
	while (Command != 3) {
		cout << "1.压缩指定文件" << endl;
		cout << "2.解压指定文件" << endl;
		cout << "3.比较解压前后文件是否相同" << endl;
		cout << "请选择功能：" ;
		cin >> Command;
		if (Command == 1) {
			clock_t start1, end1;
			start1 = clock();
			//HuffmanTree HT;
			//HuffmanCode HC;
			nHuffmanTree nHT;
			HuffmanCode nHC;
			CharInf Charinfo[258];
			for (int i = 1; i <= 256; i++) {   //初始化各个字符信息
				Charinfo[i].letter = i - 1;
				Charinfo[i].count = 0;
			}
			cout << "请输入要压缩的文件名:";
			cin >> filename;
			FILE* fp1 = fopen(filename, "rb");
			unsigned char ch = '1';//读取文件字符
			long long charcount = 0;
			while (ch != EOF)
			{
				ch = fgetc(fp1);
				//if (ch == '\r')continue;
				if (feof(fp1))
				{
					break;
				}
				Charinfo[ch + 1].count++;//此字符对应的次数
				charcount++;
			}
			fclose(fp1);
			
			
			char* inf;
			inf = (char*)malloc((256 + 1) * sizeof(char));
			for (int i = 1; i <= 256; i++) {
				w[i] = Charinfo[i].count;
				cout << w[i]<<endl;
			}
			for (int i = 1; i <= 256; i++) {
				inf[i] = Charinfo[i].letter;
			}
			int m=nHuffmancode(nHT, nHC, w, inf, 256,k);
			/*for (int i = 1; i <= 256; i++) {
				cout << nHT[i].information << ' ' << nHT[i].weight << ' ' << nHC[i];
				printf("\n");
			}*/
			for (int i = 1; i <= m; i++) {
				cout << nHT[i].parent << ' ' ;
				for (int j = 0; j < k; j++)cout << nHT[i].child[j] << ' ';
				cout << endl;
			}
			//cout << nHT[385].parent<<' '<< nHT[385].child[0]<<' '<< nHT[385].child[1]<< ' '<<nHT[385].child[2];
			//cout << "finish";
		
			//Huffmancode(HT, HC, w, inf, 256);
			/*for (int i = 1; i <= 256; i++) {
				cout << HT[i].information << ' ' << HT[i].weight << ' ' << HC[i];
				printf("\n");
			}*/
			for (int i = 1; i <= 256; i++) {
				strcpy(Charinfo[i].code, nHC[i]);
				//cout << Charinfo[i].code << endl;
			}
			FILE* fp = fopen(filename, "rb");
			strcpy(Compressedfile, filename);
			char filetile[10] = { ".huffman" };
			strcat(Compressedfile, filetile);
			FILE* fp2 = fopen(Compressedfile, "wb");
			unsigned char flag = 0;
			fwrite(&flag, sizeof(unsigned char), 1, fp2);
			fwrite(&flag, sizeof(unsigned char), 1, fp2);   //在压缩文件开头留出两个字节用于存储补0个数和最后一个压缩的二进制编码
			int cnt = 0;
			char comstr[15];
			unsigned char ASCII;
			//fread(&ch, sizeof(char), 1, fp);
			char Ltemp[257][50];
			if (k == 2) {
				for (int i = 1; i <= 256; i++) {
					strcpy(Ltemp[i], nHC[i]);
				}
			}
			else if (k >= 3 && k <= 4) {
				for (int i = 1; i <= 256; i++) {
					int p = 0;
					for (int j = 0; nHC[i][j]; j++) {
						if (nHC[i][j] == '0') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '1') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '2') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '3') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
					}
					Ltemp[i][p] = '\0';
				}
			}
			else if (k >= 5 && k <= 8) {
				for (int i = 1; i <= 256; i++) {
					int p = 0;
					for (int j = 0; nHC[i][j]; j++) {
						if (nHC[i][j] == '0') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '1') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '2') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '3') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '4') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '5') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '6') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '7') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
					}
					Ltemp[i][p] = '\0';
				}
			}
			else if (k >= 9 && k <= 16) {
				for (int i = 1; i <= 256; i++) {
					int p = 0;
					for (int j = 0; nHC[i][j]; j++) {
						if (nHC[i][j] == '0') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '1') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '2') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '3') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '4') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '5') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '6') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '7') {
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == '8') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == '9') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == 'A') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == 'B') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == 'C') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == 'D') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
							Ltemp[i][p++] = '1';
						}
						else if (nHC[i][j] == 'E') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '0';
						}
						else if (nHC[i][j] == 'F') {
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
							Ltemp[i][p++] = '1';
						}
					}
					Ltemp[i][p] = '\0';
				}
			}
			ch = '1';
			while (ch != EOF) {
				//cout << ch;
				ch = fgetc(fp);
				//if (ch == '\r')continue;
				if (feof(fp))
				{
					break;
				}
				for (int i = 0; Ltemp[ch + 1][i]; i++) {
					comstr[cnt++] = Ltemp[ch + 1][i];
					if (cnt == 8) {
						comstr[8] = '\0';
						cnt = 0;
						Compress(comstr, ASCII);
						fwrite(&ASCII, sizeof(unsigned char), 1, fp2);
					}
				}
			}
			int cnt0 = 0; //记录补0个数
			for (int i = cnt; i < 8; i++) {
				comstr[i] = '0';
				cnt0++;
			}
			comstr[8] = '\0';
			Compress(comstr, ASCII);
			fseek(fp2, 0, SEEK_SET);
			fwrite(&ASCII, sizeof(unsigned char), 1, fp2);
			ASCII = cnt0;
			fwrite(&ASCII, sizeof(unsigned char), 1, fp2);
			fclose(fp1);
			fclose(fp2);
			//写配置文件
			strcpy(config, filename);
			char filetile2[10] = { ".config" };
			strcat(config, filetile2);
			FILE* fconfig = fopen(config, "w");
			int configcnt = 1;
			while (configcnt <= 256) {
				fprintf(fconfig, "%lld\n",w[configcnt]);
				configcnt++;
			}
			fclose(fconfig);
			//free(HT);
			//free(HC);
			//free(w);
			free(inf);
			free(nHT);
			free(nHC);
			end1 = clock();
			//cout << "压缩完成，用时： " << end1 - start1 << " ms" << endl;
			cout << "压缩完成" << endl;
		}
		//开始解压
		if (Command == 2) {
			clock_t start, end;
			cout << "输入需要解压的文件名：";
			cin >> Compressedfile;
			char tile1[15] = {".huffman"};
			char tile2[15] = { ".config" };
			strcpy(config, Compressedfile);
			strcpy(Decompressedfile, Compressedfile);
			strcat(Compressedfile, tile1);
			strcat(config, tile2);
			cout << "开始解压" << endl;
			start = clock();
			FILE* fconfig1 = fopen(config, "r");
			int configcnt = 1;
			long long int* New_w;
			New_w = (long long int*)malloc((256 + 1) * sizeof(long long int));
			char* New_inf;
			New_inf = (char*)malloc((256 + 1) * sizeof(char));
			while (configcnt <= 256) { //重新构建Huffman树
				fscanf(fconfig1, "%lld", &New_w[configcnt]);
				configcnt++;
			}
			for (int i = 1; i <= 256; i++) {
				if (w[i] != New_w[i])cout << "error!" << endl;
			}
			for (int i = 1; i <= 256; i++) {
				New_inf[i] = i - 1;
			}
			nHuffmanTree nHTnew;
			HuffmanCode nHCnew;
			int m=nHuffmancode(nHTnew, nHCnew, New_w, New_inf, 256,k);
			/*for (int i = 1; i <= m; i++) {
				cout << nHTnew[i].parent << ' ' << nHTnew[i].child[0] << ' ' << nHTnew[i].child[1] << ' ' << nHTnew[i].child[2] << endl;
			}*/
			/*HuffmanTree HTnew;
			HuffmanCode HCnew;
			Huffmancode(HTnew, HCnew, New_w, New_inf, 256);*/
			FILE* fp3 = fopen(Compressedfile, "rb");
			char filetile1[30] = { "Dec" };
			strcat(filetile1, Decompressedfile);
			strcpy(Decompressedfile, filetile1);
			FILE* fin = fopen(Decompressedfile, "wb");
			unsigned char c;
			char letter[30], lastword[30];
			fread(&c, sizeof(unsigned char), 1, fp3);
			Decompress(lastword, c);
			int num;//记录补零个数
			fread(&c, sizeof(char), 1, fp3);
			num = c;
			int root = 1;       //找根节点
			for (int i = 1; i <= m; i++) {
				if (nHTnew[i].parent == 0) {
					root = i;
					break;
				}
			}
			int node = root;
			while (fread(&c, sizeof(unsigned char), 1, fp3)) {
				if (feof(fp3))break;
				Decompress(letter, c);
				char Ltemp[30];
				if (k == 2) {
					strcpy(Ltemp, letter);
				}
				else if (k >= 3 && k <= 4) {
					int j = 0;
					char temp=0;
					int p = 0;
					int bitcnt = 0;
					for (int i = 0; letter[i]; i++) {
						temp += (letter[i] - 48) * pow(2, 1-bitcnt);
						bitcnt++;
						if ((i + 1) % 2 == 0) {
							temp = temp + 48;
							Ltemp[p++] = temp;
							temp = 0;
							bitcnt = 0;
						}
					}
					Ltemp[p] = '\0';
				}
				else if (k >= 5 && k <= 16) {
					int j = 0;
					char temp = 0;
					int p = 0;
					int bitcnt = 0;
					for (int i = 0; letter[i]; i++) {
						temp += (letter[i] - 48) * pow(2, 3-bitcnt);
						bitcnt++;
						if ((i + 1) % 4 == 0) {
							temp = temp + 48;
							if(temp>='0'&&temp<='9')
							Ltemp[p++] = temp;
							else Ltemp[p++] = temp+7;
							temp = 0;
							bitcnt = 0;
						}
					}
					Ltemp[p] = '\0';
				}
				for (int i = 0; Ltemp[i]; i++) {
					/*if (letter[i] == '0') {
						node = HTnew[node].lchild;
					}
					else if (letter[i] == '1') node = HTnew[node].rchild;*/
					int nextnode;
					if (Ltemp[i] >= '0' && Ltemp[i] <= '9')nextnode = Ltemp[i] - 48;
					else nextnode = Ltemp[i] - 65 + 10;
					node = nHTnew[node].child[nextnode];
					//else cout << "error";
					if (nHTnew[node].child[0] == 0) {
						/*cout << HT[node].information<<1;*/
						//cout << c;
						fprintf(fin, "%c", nHTnew[node].information);
						node = root;
					}
				}
			}
			char Ltemp[20];
			if (k == 2) {
				strcpy(Ltemp, lastword);
			}
			else if (k >= 3 && k <= 4) {
				int j = 0;
				char temp = 0;
				int p = 0;
				int bitcnt = 0;
				for (int i = 0; i<8-num; i++) {
					temp += (lastword[i] - 48) * pow(2, 1 - bitcnt);
					bitcnt++;
					if ((i + 1) % 2 == 0) {
						temp = temp + 48;
						Ltemp[p++] = temp;
						temp = 0;
						bitcnt = 0;
					}
				}
				Ltemp[p] = '\0';
			}
			else if (k >= 5 && k <= 16) {
				int j = 0;
				char temp = 0;
				int p = 0;
				int bitcnt = 0;
				for (int i = 0;  i < 8 - num; i++) {
					temp += (lastword[i] - 48) * pow(2, 3 - bitcnt);
					bitcnt++;
					if ((i + 1) % 4 == 0) {
						temp = temp + 48;
						if (temp >= '0' && temp <= '9')
							Ltemp[p++] = temp;
						else Ltemp[p++] = temp + 7;
						temp = 0;
						bitcnt = 0;
					}
				}
				Ltemp[p] = '\0';
			}
			if (k == 2) {
				for (int i = 0; i < 8 - num; i++) {
					int nextnode;
					if (Ltemp[i] >= '0' && Ltemp[i] <= '9')nextnode = Ltemp[i] - 48;
					else nextnode = Ltemp[i] - 65 + 10;
					node = nHTnew[node].child[nextnode];
					if (nHTnew[node].child[0]==0) {
						fprintf(fin, "%c", nHTnew[node].information);
						node = root;
					}
				}
			}
			else {
				for (int i = 0; Ltemp[i]; i++) {
					int nextnode;
					if (Ltemp[i] >= '0' && Ltemp[i] <= '9')nextnode = Ltemp[i] - 48;
					else nextnode = Ltemp[i] - 65 + 10;
					node = nHTnew[node].child[nextnode];
					if (!nHTnew[node].child[0]) {
						fprintf(fin, "%c", nHTnew[node].information);
						node = root;
					}
				}
			}
			end = clock();
			cout << "解压完成，用时： " << end - start << " ms" << endl;
			fclose(fp3);
			fclose(fin);
		}
	}
	//比较两个文件是否一致
	cout << "开始比较两个文件是否相同：" << endl;
	cout << "请输入解压前文件名：";
	cin >> filename;
	char filetile2[30] = { "Dec" };
	strcat(filetile2, filename);
	strcpy(Decompressedfile, filetile2);
	FILE* Unfp = fopen(filename, "rb");
	FILE* Cofp = fopen(Decompressedfile, "rb");
	unsigned char ch1='1', ch2='1';
	int fpflag = 1;
	while (ch1 != EOF)
	{
		ch1 = fgetc(Unfp);
		ch2 = fgetc(Cofp);
		if (feof(Unfp))
		{
			break;
		}
		if (ch1 != ch2) {
			cout << "解压前后文件不相同";
			fpflag = 0;
			break;
		}
	}
	if (fpflag == 1) {
		if (feof(Unfp) && feof(Cofp))cout << "解压前后文件相同";
		else cout << "解压前后文件不相同";
	}
	/*FILE* fp4 = fopen("Decompressed.txt", "r");
	FILE* fout = fopen("CodePrint.txt", "w");
	ch = fgetc(fp4);
	while (ch != EOF)
	{
		if (feof(fp1))
		{
			break;
		}
		fprintf(fout, "%c", ch);
		ch = fgetc(fp4);
	}*/
	return 0;
}