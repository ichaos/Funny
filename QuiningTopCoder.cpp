#include <string>
#include <vector>

using namespace std;

class QuiningTopCoder {
	public:
		string testCode(string source) {
			int ip = 0;
			int D = 1;
			int N = string.length();
			vector<int> stack;
			char c;
			while (ip < 80000) {
				c = source[ip];
				switch (c) {
					case '0' - '9':
						stack.push_back(c - '0');
						ip = (3 * N + ip + D) % N;
						break;
					case '$':
						stack.pop_back();
						break;
					case ':':
						int v = stack.pop_back();
						stack.push_back(v);
						stack.push_back(v);
						break;
					case 'W':
						int a = stack.pop_back();
						int b = stack.pop_back();
						stack.push_back(a);
						stack.push_back(b);
					case ',':
						break;
					default:
					break;
				}
			}
			return "";
		}
}