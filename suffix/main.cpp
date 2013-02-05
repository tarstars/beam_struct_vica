#include <iostream>
#include <map>

using namespace std;

struct state {
	int len, link;
	map<char,int> next;
};

const int MAXLEN = 100000;
state st[MAXLEN*2];
int sz, last;

void sa_init() {
	sz = last = 0;
	st[0].len = 0;
	st[0].link = -1;
	++sz;
	/*
	// этот код нужен, только если автомат строится много раз для разных строк:
	for (int i=0; i<MAXLEN*2; ++i)
		st[i].next.clear();
	*/
}

void sa_extend (char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p;
	for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void sa_print() {
  for(int t = 0; t < sz; ++t) {
    cout << t << ") len = " << st[t].len << " link = " << st[t].link << endl;
    for(map<char,int>::iterator it = st[t].next.begin(); it != st[t].next.end(); ++it)
      cout << "\t (" << it -> first << " -> " << it -> second << ")" << endl;
  }
}

void sa_print_graph() {
  cout << "digraph G {" << endl;
  for(int t = 0; t < sz; ++t) {
    cout << t << " -> " << st[t].link << ";" << endl;
    for(map<char,int>::iterator it = st[t].next.begin(); it != st[t].next.end(); ++it) {
      cout << t << " -> " << it -> second << " [style=bold,label=\"" << it -> first <<"\"];" << endl;
    }
  }
  cout << "}" << endl;
}

int main() {
  sa_init();

  string s;
  cin >> s;

  for(string::iterator it = s.begin(); it != s.end(); ++it) {
    sa_extend(*it);
  }

  sa_print_graph();
}
