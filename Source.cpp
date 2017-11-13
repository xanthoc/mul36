#include <iostream>

using namespace std;

#define MIN_H	64
#define MAX_H 126
#define MAX_R (MAX_H*2)

bool g_flag = false;
char g_ctbl[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int g_ntbl[100];

int g_n1[MAX_H];
int g_n2[MAX_H];
int g_res[MAX_R];

int str_len(const char* _str) {
	int cnt = 0;
	while (*_str != '\0') {
		++_str;
		++cnt;
	}
	return cnt;
}

int char_to_num(char _c) {
	if (_c >= '0' && _c <= '9') return _c - '0';
	else return _c - 'A' + 10;
}

void init_tbl() {
	int len = str_len(g_ctbl);
	// << "len=" << len << endl;
	for (int i = 0; i < len; ++i) {
		g_ntbl[g_ctbl[i]] = char_to_num(g_ctbl[i]);
	}
	//for (int i = 0; i < 100; ++i) {
		//cout << g_ntbl[i] << endl;
	//}
}

void mul(char* _res, const char* _h1, const char* _h2) {
	if (g_flag==false	) {
		init_tbl();
		g_flag = true;
	}
	int len1 = str_len(_h1);
	int len2 = str_len(_h2);
	for (int i = 0; i < len1; ++i) g_n1[i] = g_ntbl[_h1[i]];
	for (int i = 0; i < len2; ++i) g_n2[i] = g_ntbl[_h2[i]];
	for (int i = 0; i < MAX_R; ++i) g_res[i] = 0;
	for (int i = 0; i < len1; ++i) {
		for (int j = 0; j < len2; ++j) {
			g_res[i + j] += g_n1[i] * g_n2[j];
		}
	}
	int max = len1 + len2 - 2;
	int idx = max;
	while (idx > 0) {
		g_res[idx - 1] += g_res[idx] / 36;
		g_res[idx] %= 36;
		--idx;
	}
	int carry = g_res[0] / 36;
	g_res[0] %= 36;

	int pos = 0;
	if (carry) _res[pos++] = g_ctbl[carry];
	idx = 0;
	while (idx <= max) {
		_res[pos++] = g_ctbl[g_res[idx++]];
	}
	_res[pos] = '\0';
}

void test_main() {
	char n1[] = "24N";
	char n2[] = "70KV";
	char res[MAX_R + 1];
	mul(res, n1, n2);
	cout << res << endl;
}

void main() {
	test_main();
	char h1[MAX_H + 1];
	char h2[MAX_H + 1];
	char res[MAX_R + 1];
	for (int pass = 0; pass < 50; ++pass) {
		for (int i = 0; i < 10000; ++i) {
			int len1 = rand() % (MAX_H + 1);
			int len2 = rand() % (MAX_H + 1);
			int idx;
			for (idx = 0; idx < len1; ++idx) {
				h1[idx] = g_ctbl[rand() % 36];
			}
			h1[idx] = '\0';
			for (idx = 0; idx < len2; ++idx) {
				h2[idx] = g_ctbl[rand() % 36];
			}
			h2[idx] = '\0';
			mul(res, h1, h2);
			//cout << "h1=" << h1 << " h2=" << h2 << ": " << res << endl;
		}
		cout << "pass " << pass << endl;
	}
}