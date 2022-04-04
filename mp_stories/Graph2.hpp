#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;
//create a class to hold all different types in a single map
// template <class V = Vertex, class E = Edge>
  // class Properties{
  //   bool visited= false;
  //   int  distance=-1;
  //   string predecessor;
  // };


/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  //create the storages
  unordered_map<string, string> predecessor;
  unordered_map<string, bool> visited;
  unordered_map<string, int> distance;
  std::queue<string> traverse;
  string temp1, temp2;
  string currV, otherV;
  bool stop=false;
  //initialize values:
  for(auto it= vertexMap.begin(); it != vertexMap.end(); it++){
    predecessor[it->first]= "none";
    distance[it->first]=INT_MAX;
    visited[it->first]= false;
  }
  traverse.push(start);
  distance[start]=0;

  //start bfs traversal
  while(!traverse.empty()){
    currV= traverse.front();
    traverse.pop();
    //go through the adjList one by one
    for(auto it2= adjList.at(currV).begin(); it2 != adjList.at(currV).end(); it2++){
        temp1= (*it2)->get().source().key();
        temp2= (*it2)->get().dest().key();
    //go through vertex map so we can look at the correct vertex (can't do source or dest bc not a digraph
      for(auto it= vertexMap.begin(); it != vertexMap.end(); it++){
        //find the other vertex to look at:
        if(temp1==it->first && temp1 != currV){
          otherV= it->first;
        }else if(temp2 != currV){
          otherV= temp2;
        }
      }
        //check whether visited or not and set corresponding values:
        if(visited[otherV]==false){
          visited[otherV]=true;
          predecessor[otherV]= currV;
          distance[otherV]= distance[currV] + 1;
          traverse.push(otherV);
        }
        if(currV==end)
        {
          stop=true;
          break;
        }
        if(stop){break;}
      }
      if(stop){break;}
    }
  //put predecessors into list and reverse to get from beginning:
 path.push_back(end);
 string last= end;
 while(last != start){
   path.push_back(predecessor[last]);
   last= predecessor[last];
 }
 std::reverse(path.begin(), path.end());
 return path;
}
