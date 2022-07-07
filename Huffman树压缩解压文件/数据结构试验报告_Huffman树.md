

# 数据结构实验报告

## 实验题目：Huffman 编码压缩/解压器

## 一.实验要求

### 【问题描述】：

在合适的情况下，利⽤ Huffman 编码对⽂件进⾏压缩可以减少其占⽤空间，同时在需要使⽤到⽂件的 时候也可以根据压缩⽂件中所提供的信息来将其还原为原⽂件。本次实验中，我们将实现⼀个基于 Huffman 编码的⽂件压缩/解压缩⼯具。

### 【基本要求】：

基于 Huffman 编码实现⼀个压缩器和解压缩器（其中 Huffman 编码以字节作为统计和编码的基本符号 单元），使其可以对任意的⽂件进⾏压缩和解压缩操作。针对编译⽣成的程序，要求压缩和解压缩部分 可以分别独⽴运⾏。具体要求为：

 1.每次运⾏程序时，⽤⼾可以指定只压缩/只解压缩指定路径的⽂件。实现的时候不限制与⽤⼾的交互⽅式，可供参考的⽅式包括但不限于 根据命令⾏参数指定功能（压缩/解压缩）和输⼊/输出⽂件路径 GUI 界⾯ 运⾏程序后由⽤⼾交互输⼊指定功能和路径。

【CAUTION!】不被允许的交互⽅式： 通过修改源代码指定功能和⽂件路径 压缩时不需要指定解压⽂件的⽬标路径。

2.解压缩时不需要指定压缩前原⽂件的路径，压缩后的⽂件可以换到另⼀个位置再做解压缩。

### 【选作内容】：

##### 1.【实现可指定的任意基本符号单元大小的 Huffman 压缩/解压缩算法】

##### 2.【实现可指定的任意多元 Huffman 压缩/解压缩算法】

## 二.设计思路

#### 模块分析：

本程序包含三个模块：主函数模块，Huffman树模块，压缩模块，其调用关系如下：

![image-20211224164427077](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211224164427077.png)

##### 1.主函数模块设计思路及作用：

主函数的算法：读取需要压缩的文件并调用构建Huffman树的模块，通过二进制压缩，将文件压缩，并将Huffman树存进配置文件中以便解压。解压时读取配置文件，重新构建Huffman树，并转化为相应的进制，以便解码，实现解压文件的目的。具体代码在报告中第三部分详细展示。

##### 2.Huffman树模块设计思路及作用：

######  2叉Huffman树：

(1)用给定权值{𝑤1 , 𝑤2 ,…, 𝑤𝑛 }的 n 个结点，构造一个有 n 棵二叉树的森林 F={𝑇1, 𝑇2,…, 𝑇𝑛}，其中，每棵二叉树𝑇𝑖（1 ≤ 𝑖 ≤ 𝑛）只有一个权值为𝑤𝑖的根结点。

 (2)重复下面的操作①和操作②，直至 F 中只含有一棵二叉树为止

 操作①：合并。在F中选取根节点全职为最小和次最小的两颗二叉树𝐵1和𝐵2， 分别作为左子树和右子树，补上 1 个节点作为根，构造出一棵新的二叉树 B， 新二叉树 B 的根节点的权值为𝐵1和𝐵2根节点权值的和

 操作②：替换：用新二叉树 B 替换掉 F 中的𝐵1和𝐵2，这样 F 中的二叉树数量 就减少了 1.整个过程结束时，F 中仅存的那棵二叉树即为所求。 编码过程： 在编码过程中，把每个字符出现的频率看做{𝑤1, 𝑤2,…, 𝑤𝑛}，并令最初的 n 棵二 叉树在有权值𝑤𝑖的同时附上相应的字符作为关键字，在最终的 Huffman 树中，有 且只有 n 个叶子结点附有字符作为关键字。对于一棵按照 Huffman 算法的思路构 造出来的 Huffman 树，其根节点到各叶子节点的简单路径是唯一确定的，我们记 其向左子树走时为 0，向右子树走时为 1，这样到叶子结点的简单路径就可以转化 为响应的编码。且一个字符对应的编码不可能为另一字符的前缀。

###### k叉Huffman树：

k叉Huffman树的基本思想与2叉Huffman树一致。但需要考虑到，每次取出k个节点，并不能保证最终构造出的Huffman树为满k叉树，故在构建k叉树之前，需要补充虚拟节点。设原来节点的个数为n，若$ {(n - k)}\%{(k - 1)}!= 0 $ ，则$n=n+1$，直至$ {(n - k)}\%{(k - 1)}== 0 $ ，此时的n就是k叉树最终叶子节点的个数，而构建整棵k叉树需要的节点空间为：${(n-k)} \div {(k-1)} +n+1$​。Huffman树结构体定义和函数声明如下：

```cpp
typedef struct {
	unsigned int weight;
	unsigned char information;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;  //二叉Huffman树
typedef struct {
	unsigned int weight;
	unsigned char information;
	unsigned int parent, child[16];
}nHTNode, * nHuffmanTree;    //k叉Huffman树
struct CharInf {
	unsigned char letter;
	long int count;
	char code[15];
}; //保存文件中字符信息
typedef char** HuffmanCode;
void Select(HuffmanTree& HT, int n, int& s1, int& s2);
void Huffmancode(HuffmanTree& HT, HuffmanCode& HC, int* w, char* inf, int n);
int nHuffmancode(nHuffmanTree& nHT, HuffmanCode& nHC, int* w, char* inf, int n,int k);
void nSelect(nHuffmanTree& nHT, int n, int s[],int k);
int Min(nHuffmanTree t, int n);
```

因为k叉树的做法包含二叉树，故在之后的报告中将主要介绍k叉树的实现方法，具体代码在报告中第三部分详细展示。

##### 3.压缩模块设计思路及作用：

k叉树得到的Huffman编码为k进制的，我们需要将其转化为2进制，但因为解压需要确定以几位2进制数转为k进制，所以需要人为规定$3\leq k\leq4$时，一位k进制数转为两位二进制数，$5\leq k\leq 16$时，一位k进制数转为4位二进制数，再以8位一组写进文件中以达到压缩的目的。以3~4j进制为例，将得到的Huffman编码转为2进制代码如下：

```cpp
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
```

在得到二进制编码后，我们需要8位一组写入压缩文件，代码如下：

```cpp
bool Compress(char Comstr[],unsigned char& ASCII) {  //将8位二进制数转为1位的char型
	ASCII=0;
		for (int i = 0; i < 8; i++) {
			if (Comstr[i] == '1') ASCII = ASCII * 2 + 1;
			else ASCII = ASCII * 2;
		}
	
	return true;
}
```

同理，在解压文件时，需要将其转回二进制数：

```cpp
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
```

得到二进制串后，我们需要将其转回为k进制，由于之前人为规定几位二进制数转为一位k进制数，所以能准确的转回k进制编码，再通过重新构建的k叉Huffman树，就能完成解压功能。

## 三.关键代码讲解

#### 1.文件读取及Huffman树的构建

构建Huffman树首先要知道各个字符的权重，故先要读取一遍文件，记录下各个字符出现的次数，以便构建Huffman树：

```cpp
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
			int* w;
			w = (int*)malloc((256 + 1) * sizeof(int));
			char* inf;
			inf = (char*)malloc((256 + 1) * sizeof(char));
			for (int i = 1; i <= 256; i++) {
				w[i] = Charinfo[i].count;
			}
			for (int i = 1; i <= 256; i++) {
				inf[i] = Charinfo[i].letter;
			}
```

在得到各个字符权重后，开始构建Huffman树，得到Huffman编码，Huffman树的构建分为几个步骤，首先是初始化Huffman树：

```cpp
int m;
	int plusnum = 0;
	while ((n - k) % (k - 1) != 0) {
		plusnum++;//需要增加虚拟叶子节点的个数
		n = n + 1;
	}
	int temp=n-k;
	int m_cnt = 1;
		temp = temp / (k - 1);
		m_cnt+=temp;
	m = n + m_cnt;  //构建k叉Huffman树总共需要的节点空间
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
```

第二步是找出权重最小的k棵树，总共进行$m-n-1$次

```cpp
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
void nSelect(nHuffmanTree& nHT, int n, int s[], int k) {//找到k个权重最小的树
	for (int i = 0; i < k; i++) {
		s[i] = 0;
	}
	for (int i = 0; i < k; i++) {
		s[i] = Min(nHT, n); // 找到没有双亲且权重最小的树
	}
	int i, j,temp;
	for (i = 0; i < k - 1; ++i)
		for (j = 0; j < k - i - 1; ++j)
			if (nHT[s[j]].weight > nHT[s[j + 1]].weight)
				temp = s[j], s[j] = s[j + 1], s[j + 1] = temp;
}
```

第三步是从叶子节点出发，找到对应的Huffman编码

```cpp
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
					if (j <= 9 && j >= 0)cd[--start] = j+48;//int型转为char型
					else cd[--start] = 'A' + j - 10;
				}
			}
		}
		nHC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(nHC[i], &cd[start]);
	}
	free(cd);
```

#### 2.编码及解码过程

本实验为了压缩信息，将文本转化后的 01 串以二进制的形式写入文件当中 即在将 01 编码串写入文件时，将其八个一组进行分组，存入字符串中，但是对于最后一组，若转化后的字符长度不到8位，则通过补0的方式将其补到8bits。为了能够还原，所以我们还需记录补0的个数。将k进制Huffman编码转为二进制在第二部分已经阐述过，这里直接使用存储01码的Ltemp开始压缩。

```cpp
fwrite(&flag, sizeof(unsigned char), 1, fp2);
fwrite(&flag, sizeof(unsigned char), 1, fp2);   //在压缩文件开头留出两个字节用于存储补0个数和最后一个压缩的二进制编码
```

```cpp
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
Compress(constr, ASCII);
fseek(fp2, 0, SEEK_SET);//回到文件头
fwrite(&ASCII, sizeof(unsigned char), 1, fp2);//将补过0的最后一位写入
ASCII = cnt0;
fwrite(&ASCII, sizeof(unsigned char), 1, fp2);//将补0个数写入
```

解码过程时，要先将01码转为k进制，以$3\leq k\leq 4$为例

```cpp
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
```

转回k进制后，则开始沿着Huffman树解码，首先找到根节点，在从根节点出发，'0'为child[0],'1'为child[1]，一次类推，到叶子节点即解码了一个字符。需要注意的一点是最后一组需要去掉补上的0的个数。

```cpp
int root = 1;       //找根节点
for (int i = 1; i <= m; i++) {
	if (nHTnew[i].parent == 0) {
		root = i;
		break;
	}
}
for (int i = 0; Ltemp[i]; i++) {
		int nextnode;
		if (Ltemp[i] >= '0' && Ltemp[i] <= '9')nextnode = Ltemp[i] - 48;
		else nextnode = Ltemp[i] - 65 + 10;//'A'~'F'的情况
		node = nHTnew[node].child[nextnode];
		//else cout << "error";
		if (nHTnew[node].child[0] == 0) {   //找到叶子节点，写入文件
			fprintf(fin, "%c", nHTnew[node].information);
			node = root;
		}
	}
}
```

## 四.调试分析

#### 1.空间效率：

2叉Huffman树:对于大小为 n 的字符集，生成的 Huffman 树的结点总数为 2$*$n-1，又 Huffman 树为一棵较为平衡的二叉树，因此对应的深度大致为 log(2$*$n-1)，从而字符编码 最长为 log(2$*$n-1)，空间复杂度为 O(nlogn).

k叉Huffman树：，对于大小为n的字符集，生成的Huffman树的结点总数为$m={(n-k)} \div {(k-1)} +n+1$，因此大致深度为：$\log_k{m}$,所以空间复杂度为$O(n*\log_k{m})$.

#### 2.时间效率：

设文章总字符数为 L，转化并压缩后的编码文件总字符数为 L’.在初始化操作 时，创建 Huffman 树的时间复杂度为 O(n)，编码操作时时间复杂度为 O(n)。编码 时间复杂度为 O(Ln)，解码时间复杂度为 O(L’)，由于采用了二进制读写，编码和解 码的实际效率会进一步提升。由于 n 和 L 差距很大，结合测试数据特点、常数大小 等其他因素，解码用时可能会比编码用时长。

#### 3.实验过程中遇到的问题:

实验的难点主要有两个：一是得到Huffman编码后，如何压缩将其写入文件，最后的解决方法是在文件开头写入两个 0 占位，到最后一组时，将最后一组补零压缩后的字符和补零个数都写在文件开头，覆盖掉原先占位的两个 0，从而大大便利了问题的处理。二是k叉树得到的编码在转为01码后如何转回来，在规定转换后的位数后，这个问题便得到了解决。

## 五.代码测试

以7叉树为例进行测试

<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211224200422406.png" alt="image-20211224200422406" style="zoom:80%;" />

压缩后的文件和配置文件如下：

![image-20211224200547710](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211224200547710.png)

对比压缩前后的图片<img src="C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211224200647793.png" alt="image-20211224200647793" style="zoom:50%;" />

程序中，二进制一个一个读入比对，以及观察图片，发现压缩前后图片一致

## 六.实验总结

整个实验分为如下步骤：

1.统计：首先读取一个文件，统计出256个字符中各字符出现的次数以及字符出现的总次数；

2.建树：按照字符出现的次数，并以次数作为权值建立huffman树，根据所构建的huffman树生成huffman编码；

3.压缩：再次读取原文件，按照该字符对应的编码压缩文件；

4.加工：将字符出现的总次数以及各个字符出现的次数写进配置文件；

5.解压：利用压缩文件以及配置文件恢复原文件；

6.测试：首先对压缩和解压缩两个功能进行测试，看压缩后的文件是否比原文件小，以及解压缩文件与原文件的大小一致；在这个基础上再验证解压缩文件与原文件的内容是否保持一致

$\star$整个实验的关键在于构建完k叉Huffman树后如何将他的编码压缩写入文件，通过将01码以8bits一组写入大大节省了空间。

## 七.附录

文件清单：HuffmanCode.h    Compress.h    Compress.cpp   HuffmanCode.cpp   nHuffmanCode.cpp  main.cpp

HuffmanCode.h:Huffman树的定义及相关函数的声明

Compress.h:声明压缩函数

Compress.cpp:将8bits的01码转为char型及其逆变换

HuffmanCode.cpp:构造2叉Huffman树

nHuffmanCode.cpp:构造n叉Huffman树

main.cpp:实现总功能



