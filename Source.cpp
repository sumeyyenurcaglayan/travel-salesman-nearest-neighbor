#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<set>
#include<iterator>
#include <chrono>
using namespace std;

float distance(pair<int, int> a, pair<int, int>b){
	return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

pair<int, int> nearest_neighbor(pair<int, int> a, set <pair<int, int>>cities){

	float min_distance = INT_MAX;

	pair <int, int> min;
	set< pair<int, int>>::iterator it;

	for (it = cities.begin(); it != cities.end(); it++){

		float temp_distance = distance(a, *it);
		if (temp_distance < min_distance){
			min_distance = temp_distance;
			min = *it;
		}
	}
	return min;
}


int main()
{
	auto t1 = chrono::high_resolution_clock::now();

	int a, b;

	ifstream reader("att48_xy.txt");
	pair<int, int> cities[48];
	int i = 0;

	while (reader >> a >> b){
		cities[i] = pair<int, int>(a, b);
		i++;
	}

	pair<int, int> c = cities[0];


	vector <pair<int, int>> tour;
	tour.push_back(c);
	set <pair<int, int>> unvisited(cities + 1, cities + 48);

	while (!unvisited.empty()){
		c = nearest_neighbor(c, unvisited);
		tour.push_back(c);
		unvisited.erase(c);
	}

	tour.push_back(tour[0]);
	float total_distance = 0;


	for (int i = 0; i < tour.size(); i++){
		cout << i + 1 << "-" << tour[i].first << "," << tour[i].second << endl;// for the path
		if (i != tour.size() - 1)
		{
			total_distance += distance(tour[i], tour[i + 1]);
		}
	}


	cout << "Total distance " << total_distance << endl;

	auto t2 = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "Execution Time: " << (float)duration/1000000 << endl;

	system("pause");




	
	return 0;
}