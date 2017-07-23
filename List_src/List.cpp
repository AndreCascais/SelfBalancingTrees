#include <iostream>
#include <map>
#include <chrono>
#include <list>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <ctgmath>
#include <cstring>


using namespace std;

FILE* file = nullptr;

int main(int argc, char** argv) {

	if (argc > 1) {
		file = fopen(argv[1], "r");
	}

    list<int>* l = new list<int>();
	
    int v, option = 1;
	if (file != nullptr) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		
		int n_inserts, n_removes, n_lookups;
		fscanf(file, "%d%d%d%d", &option, &n_inserts, &n_removes, &n_lookups);
		int balance_freq = floor(sqrt(n_inserts));
		for (int i = 0; i < n_inserts; i++) {
			fscanf(file, "%d", &v);
			l->push_back(v);
			cout << i%balance_freq << endl;
			if (i%balance_freq == 0) {
				l->sort();
			}
		}
		for (int i = 0; i < n_removes; i++) {
			fscanf(file, "%d", &v);
			l->remove(v);
		}
		for (int i = 0; i < n_lookups; i++) {
			fscanf(file, "%d", &v);
			auto it = std::find(l->begin(), l->end(), v);
		}
		std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds"<< std::endl;
	}
	
	delete l;
 
    return 0;
}