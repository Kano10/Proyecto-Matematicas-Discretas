#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
#include <limits>


void getData(std::string txt, std::vector<int>&, std::map<int, std::string>&, std::vector<std::vector<std::pair<int, int>>>&);

std::vector<int> getRecorrido(int, std::vector<int>&, std::vector<std::vector<std::pair<int, int>>>&);

int main(){
    std::vector<int> caminos_a_recorrer;
    std::vector<std::string> citys;
    std::vector<std::vector<std::pair<int, int>>> adj_list;

    getData("bianca.txt", caminos_a_recorrer, citys, adj_list);

    
    std::vector<int> camino = getRecorrido(citys.size(),caminos_a_recorrer, adj_list);

    for(auto x : camino) 
        std::cout<< citys[x] << std::endl;


}

void getData(std::string txt, std::vector<int>& caminos_a_recorrer, std::vector<std::string> citys, std::vector<std::vector<std::pair<int, int>>>& adj_list){
    std::ifstream data(txt);
   
    std::map<std::string, int> city_to_int;

    int num_citys{0};
    data >> num_citys;

    for(size_t i = 0; i < num_citys; i++){
        std::string city{""};
        data >> city;


        city_to_int.insert({city, i});
        citys.push_back(city);

        adj_list.push_back(std::vector<std::pair<int, int>>());
    }


    int num_roads; 
    data >> num_roads;

    for(int i = 0; i < num_roads; i++){
        std::string city_i;
        data >> city_i;

        std::string city_j; 
        data >> city_j;
        
        int weight; 
        data >> weight;

        adj_list[city_to_int[city_i]].push_back({weight, city_to_int[city_j]});
        adj_list[city_to_int[city_j]].push_back({weight, city_to_int[city_i]});
    }

    int tam_recorrido; data >> tam_recorrido;

    for(int i = 0; i < tam_recorrido; i++){
        std::string city; 
        data >> city;

        caminos_a_recorrer.push_back(city_to_int[city]);
    }
}

std::vector<int> getRecorrido(int num_citys, std::vector<int>& caminos_a_recorrer, std::vector<std::vector<std::pair<int, int>>>& adj_list){
    std::vector<int> camino;

    int entrenadores{0};
    int tam_recorrido{caminos_a_recorrer.size()};

    for(int i = 1; i < tam_recorrido; i++){
        int src = caminos_a_recorrer[i-1];
        int dest = caminos_a_recorrer[i];

        std::vector<int> distance(num_citys, INT_MAX);
        std::vector<int> anterior(num_citys, -1);
        std::vector<bool> visited(num_citys, false);

        std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int,int>>> priority_q;

        priority_q.push(std::make_pair(0, src));
        distance[src] = 0;

        while(!priority_q.empty()){
            int actual_node = priority_q.top().second;
            priority_q.pop();

            visited[actual_node] = true;

            for(auto next_node : adj_list[actual_node]){
                if (!visited[next_node.second]){
                    if (distance[next_node.second] > distance[actual_node] + next_node.first){
                        
                        distance[next_node.second] = distance[actual_node] + next_node.first;
                        priority_q.push(std::make_pair(distance[next_node.second], next_node.second));

                        anterior[next_node.second] = actual_node;
                    }
                }
            }
        }

        entrenadores += distance[dest];
        int previous_node = anterior[dest];

        std::vector<int> camino_aux;
        while(previous_node >= 0){
            camino_aux.push_back(previous_node);
            previous_node = anterior[previous_node];
        }

        std::reverse(camino_aux.begin(), camino_aux.end());

        for(auto node : camino_aux) 
            camino.push_back(node);
    }

    camino.push_back(caminos_a_recorrer.back());
}