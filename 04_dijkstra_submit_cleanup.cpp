/* Menemukan shortest path dalam directed graph dari source vertex ke destination vertex */

#include <bits/stdc++.h>
#define infi 1000000000
using namespace std;

// Class Node
class Node {
public:
	int vertexNumber;

    /* Adjacency list yang menunjukkan vertexNumber dari child vertex
     * dan weight dari edge */
	vector<pair<int, int> > children;
	Node(int vertexNumber)
	{
		this->vertexNumber = vertexNumber;
	}

    // Fungsi untuk menambahkan child untuk suatu node
	void add_child(int vNumber, int length)
	{
		pair<int, int> p;
		p.first = vNumber;
		p.second = length;
		children.push_back(p);
	}
};

/* Fungsi untuk mencari jarak source ke destination vertex */
vector<int> dijkstraDist(
	vector<Node*> g,
	int s, vector<int>& path)
{   
    // Menyimpan jarak tiap vertex dari source vertex
	vector<int> dist(g.size());

    // Array boolean yang menunjukkan apakah suatu vertex sudah dikunjungi atau belum
	bool visited[g.size()];
	for (int i = 0; i < g.size(); i++) {
		visited[i] = false;
		path[i] = -1;
		dist[i] = infi;
	}
	dist[s] = 0;
	path[s] = -1;
	int current = s;

    /* Kumpulan vertex yang mempunyai parent, ditandai visited */
	unordered_set<int> sett;
	while (true) {

		// Vertex saat ini ditandai visited
		visited[current] = true;
		for (int i = 0;
			i < g[current]->children.size();
			i++) {
			int v = g[current]->children[i].first;
			if (visited[v])
				continue;

			// Tambahkan ke dalam set berisi vertex2 yang sudah dikunjungi
			sett.insert(v);
			int alt
				= dist[current]
				+ g[current]->children[i].second;

            // Jika jarak hasil perhitungan lebih kecil daripada jarak sebelumnya, maka nilanya diupdate
			if (alt < dist[v]) {
				dist[v] = alt;
				path[v] = current;
			}
		}
		sett.erase(current);
		if (sett.empty())
			break;

		// Current yang baru
		int minDist = infi;
		int index = 0;

        // Loop untuk mengupdate distance dari vertex-vertex graph
		for (int a: sett) {
			if (dist[a] < minDist) {
				minDist = dist[a];
				index = a;
			}
		}
		current = index;
	}
	return dist;
}

// Driver Code
int main()
{
    int n,s,f,w;
    scanf("%d %d %d",&n,&s,&f);
    s--;
    f--;

    vector<Node*> v;

	// Loop untuk membuat node
	for (int i = 0; i < n; i++) {
		Node* a = new Node(i);
		v.push_back(a);
	}

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d", &w);
            if(w > 0)
            {
                v[i]->add_child(j, w);
            }
        }
    }

	vector<int> path(v.size());
	vector<int> dist
		= dijkstraDist(v, s, path);

    if(dist[f]==infi)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", dist[f]);
    }
    

	return 0;
}

/* References
 * https://www.youtube.com/watch?v=XB4MIexjvY0
 * https://youtu.be/pVfj6mxhdMw
 * https://youtu.be/5hPfm_uqXmw
 * https://www.geeksforgeeks.org/shortest-path-in-a-directed-graph-by-dijkstras-algorithm/ */