#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

//Maximum value of cost
#define INF 1000001
//Maximum value of node count
#define LIMIT 1000000
//Maximum size of graph
#define MAXI 1000000 + 1
#define node pair<int, int>
using namespace std;
//cost array for finding the shortest distance
long long cost[MAXI] = { 0, };
//Judge whatever Area flooded or not
bool flooding[MAXI] = { 0, };
//struct for storing Node information
struct info { int num; int cost; };
string name[MAXI];

//Graph Information
vector<info> graph[MAXI];
int res[MAXI] = { 0, };
int n, m, q;

//Sorting Function for Requirement
bool comp(info tmp1, info tmp2) {
	if (tmp1.cost == tmp2.cost) return tmp1.num < tmp2.num;
	else return tmp1.cost < tmp2.cost;
}

//Find shortest distance
void shortest_distance(int _start, int _end) {
	//if start flooded
	if (flooding[_start] || flooding[_end]) {
		cout << "None\n";
		return;
	}
	//initialization cost INF & sort node
	for (int i = 100000; i < LIMIT; i++) {
		cost[i] = INF;
		if (!graph[i].size()) sort(graph[i].begin(), graph[i].end(), comp);
	}
	//Count for tree vertex
	int cnt = 1;
	//start node cost 0 because of Djikstra prerequisites
	cost[_start] = 0;

	// node first : cost, node second : num
	//priority queue is fringe set
	priority_queue<node, vector<node>, greater<node>>pq;
	pq.push(make_pair(cost[_start], _start));

	while (!pq.empty()) {
		//popped node is tree set
		int curCost = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();
		if (curNode == _end) break;
		if (curCost > cost[curNode] || flooding[curNode] == 1) 	continue;
		
		else {
			//count node in tree set
			cnt++;
			for (auto next : graph[curNode]) {
				//Update when value less than current value is received Djistra Algorithm 
				if (curCost + next.cost < cost[next.num] && !flooding[next.num]) {
					//if node is flooded Skip
					if (flooding[next.num]) continue;
					cost[next.num] = curCost + next.cost;
					pq.push(make_pair(curCost + next.cost, next.num));
				}
			}
		}
	}
	//if cost of Destination is INF or beyond the limit print out None
	if (cost[_end] == INF || cost[_end] >= LIMIT) 	cout << "None\n";
	//else print information
	else cout << cnt << " " << cost[_end] << " " << name[_start] << " " << name[_end] << " " << "\n";

}

//Find shortest path
void shortest_path(int _start, int _end) {

	if (flooding[_start] || flooding[_end]) {
		cout << "None\n";
		return;
	}
	for (int i = 100000; i < LIMIT; i++) {
		cost[i] = INF;
		if (!graph[i].size()) sort(graph[i].begin(), graph[i].end(), comp);
	}
	int cnt = 1;
	cost[_start] = 0;

	priority_queue<node, vector<node>, greater<node>>pq;
	pq.push(make_pair(cost[_start], _start));
	while (!pq.empty()) {
		int curCost = pq.top().first;
		int curNode = pq.top().second;
		pq.pop();
		if (curNode == _end) break;
		if (curCost > cost[curNode] || flooding[curNode] == 1) continue;
		else {
			if (graph[curNode].size() == 0 && curNode != _end) continue;
			else {
				cnt++;
				for (auto next : graph[curNode]) {
					if (curCost + next.cost < cost[next.num] && !flooding[next.num]) {
						if (flooding[next.num]) continue;
						cost[next.num] = curCost + next.cost;
						pq.push(make_pair(curCost + next.cost, next.num));
						//store about previous node because print out path
						res[next.num] = curNode;
					}
				}
			}
		}
	}
	if (cost[_end] == INF || cost[_end] >= LIMIT) 	cout << "None\n";
	else {
		//store information in reverse order to Stack
		cout << cnt << " ";
		stack<int> s;
		int next = _end;
		cout << _start << " ";
		while (next != _start) {
			s.push(next);
			next = res[next];
		}
		//print out Shortest Path
		while (!s.empty()) {
			cout << s.top() << " ";
			s.pop();
		}
		cout << "\n";
	}
}
int main() {
	//for speed up
	std::ios::sync_with_stdio(false);
	cin >> n >> m >> q;
	//input information
	for (int i = 0; i < n; i++) {
		int inputI; string inputS; int judge;
		cin >> inputI >> inputS >> judge;
		name[inputI] = inputS;
		flooding[inputI] = judge;
	}
	//input information to undirected graph
	for (int i = 0; i < m; i++) {
		int x, y, value;
		cin >> x >> y >> value;
		graph[x].push_back({ y,value });
		graph[y].push_back({ x,value });
	}
	//Running function size of q
	while (q--) {
		char type; int start, end;
		cin >> type >> start >> end;
		if (type == 'A')	shortest_distance(start, end);
		else if (type == 'B') shortest_path(start, end);
	}
	return 0;
}