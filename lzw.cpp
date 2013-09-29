//Lempel–Ziv–Welch (LZW)

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void compress(ifstream &fin, ofstream &fout, map<string, short> dic) {
	int buf_sz = 4096;
	char buf[buf_sz];
	
	int cnt = 0;
	string w = "";
	int i = 0;
	short code = -1;
	int next = dic.size();
	while (!fin.eof()) {
		fin.read(buf, buf_sz);
		cnt = fin.gcount();
		cout << "read " << cnt << " bytes\n";
		//handle these bytes
		i = 0;
		while (i < cnt) {
			w += buf[i];
			//check if w is in dic
			if (dic.find(w) == dic.end()) { //encounter a new word, add it into dic
				dic[w] = next++;
				//cout << "[buf[i]: " << buf[i] << ", next: " << dic[w] << ", w: " << w << "]\n";
				w = buf[i];
				i++;
				//output the code
				fout.write(reinterpret_cast<char *>(&code), 2);
				code = dic[w];
			} else {
				i++;
				code = dic[w];
			}
		}
	}
	fout.write(reinterpret_cast<char *>(&code), 2);
}

void decompress(ifstream &fin, ofstream &fout, map<short, string> &dic) {
	int buf_sz = 2048;
	short buf[buf_sz];
	string w = "";

	int cnt = 0;
	int next = dic.size();
	int i = 0;

	string p = "";

	while (!fin.eof()) {
		fin.read((char *)buf, buf_sz * sizeof(short));
		cnt = fin.gcount();
		cout << "read " << cnt << " bytes\n";
		i = 0;
		while (i * sizeof(short) < cnt) {
			//w = dic[buf[i]];
			if (buf[i] >= next) {
				//w = p;
				//cout << "(buf[i]: " << buf[i] << ", next: " << next << ", w: " << w << ")\n";
				w += w[0];
				dic[next++] = w;
			} else {
				w += dic[buf[i]][0];
				if (w.size() != 1 || w[0] != dic[buf[i]][0])
					dic[next++] = w;
			}
			w = dic[buf[i]];
			//cout << w;
			//p = dic[buf[i]];
			i++;
			fout.write(w.c_str(), w.size());
		}
	}
}

int main(int argc, char *argv[]) {

	ifstream ifile(argv[1], ios::in | ios::binary);
	if (!ifile.is_open()) {
		cout << "Open file failed.\n";
		return -1;
	}

	string outFName = argv[1];
	outFName += ".czip";
	ofstream fout(outFName.c_str(), ios::binary);
	if (!fout.is_open()) {
		cout << "Open out file failed\n";
		return -1;
	}

	map<string, short> dic;
	string s = " ";
	for (short c = 0; c < 256; c++) {
		s[0] = (char)c;
		dic[s] = c;
	}

	compress(ifile, fout, dic);
	ifile.close();
	fout.close();

	map<short, string> decode;
	for (short c = 0; c < 256; c++) {
		s[0] = (char)c;
		decode[c] = s;
	}

	ifstream dfin(outFName.c_str(), ios::in | ios::binary);
	if (!dfin.is_open()) {
		cout << "open compress file failed\n";
		return -2;
	}
	string decomFile = argv[1];
	decomFile += ".decom";
	ofstream dfout(decomFile.c_str(), ios::out | ios::binary);
	if (!dfout.is_open()) {
		cout << "open decompress file failed\n";
		return -2;
	}

	decompress(dfin, dfout, decode);
	dfin.close();
	dfout.close();
}