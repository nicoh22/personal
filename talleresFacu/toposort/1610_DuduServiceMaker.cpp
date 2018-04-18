#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int indeg[10001];

int main () {
	// Esta implementación es un Topological Sort del grafo
	// Otra opción sería hacer un DFS

	int t, a, b, n, m;
	cin >> t;

	for (int tc = 0; tc < t; tc++) {
		cin >> n >> m;

		vector<vector<int> > out(n);
		
		for (int i = 0; i < n; i++) {
			indeg[i] = 0;
        }
        
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			a--; b--;
			out[a].push_back(b);
            indeg[b]++;
		}

		queue<int> colaVacios;
		for (int i = 0; i < n; i++)
			if (indeg[i] == 0)
				colaVacios.push(i);

		int analizados = 0;
		while (!colaVacios.empty()) {
			int t = colaVacios.front();
			colaVacios.pop();
			analizados++;

			for (int i = 0; i < (int) out[t].size(); i++) {
				indeg[out[t][i]]--;
                
				if (indeg[out[t][i]] == 0) {
					colaVacios.push(out[t][i]);
                }
			}
		}

		if (analizados == n)
			cout << "NAO" << endl;
		else
			cout << "SIM" << endl;
	}
}
