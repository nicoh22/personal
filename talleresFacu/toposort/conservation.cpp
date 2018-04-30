#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

int indeg[100001][2];
int labo[100001];

int main () {
    // Realizo dos copias de indeg y de las colas, una según el nodo inicial
    // Luego corro toposort como en el ejercicio anterior y tomo minimo
    
	int t, a, b, n, m;
	cin >> t;

	for (int tc = 0; tc < t; tc++) {
		cin >> n >> m;

		vector<vector<int> > out(n);
		
		for (int i = 0; i < n; i++) {
			indeg[i][0] = 0;
            indeg[i][1] = 0;
        }

		for (int i = 0; i < n; i++) {
			cin >> a;
            labo[i] = a-1;
        }
        
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			a--; b--;
			out[a].push_back(b);
            indeg[b][0]++;
            indeg[b][1]++;
		}

        queue<int> colaVacios[2][2];
        for (int i = 0; i < n; i++) {
            if (indeg[i][0] == 0) {
                colaVacios[labo[i]][0].push(i);
                colaVacios[labo[i]][1].push(i);
            }
        }
        
        int minCambios = n+1;
        for (int laboInicial = 0; laboInicial < 2; laboInicial++) {
            int analizados = 0, laboActual = laboInicial, cambios = 0;
                
            while (!colaVacios[0][laboInicial].empty() || !colaVacios[1][laboInicial].empty()) {
                if (colaVacios[laboActual][laboInicial].empty()) {
                    laboActual = 1 - laboActual;
                    cambios++;
                }
                
                int t = colaVacios[laboActual][laboInicial].front();
                colaVacios[laboActual][laboInicial].pop();
                analizados++;
                
                for (int i = 0; i < (int) out[t].size(); i++) {
                    indeg[out[t][i]][laboInicial]--;
                    
                    if (indeg[out[t][i]][laboInicial] == 0)
                        colaVacios[labo[out[t][i]]][laboInicial].push(out[t][i]);
                }
            }
            
            if (analizados == n)
                minCambios = min (minCambios, cambios);
        }

		cout << minCambios << endl;
	}
}
