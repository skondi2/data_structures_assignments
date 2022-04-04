#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  // TODO: Part 2                           DONE
    return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2                           DONE
  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.emplace(key, v);
  //hold a spot open for the edge for the vertex
  std::list<edgeListIter> emptyEdges;
  adjList[v.key()]=emptyEdges;
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
   auto it = vertexMap.find(key);
  vertexMap.erase(it);

  unsigned b =0;
  auto it1 = adjList.find(key);
  std::map<std::string, bool> keysToRemove;
  while(b < adjList.size()){
  for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
    auto temp= it2;
    if ((**it2).get().source().key() == key) {
      keysToRemove.insert(std::pair<std::string, bool>((**it2).get().dest().key(), true));
    }
    if ((**it2).get().dest().key() == key) {
      keysToRemove.insert(std::pair<std::string, bool>((**it2).get().source().key(), false));
    }
    it1->second.erase(temp);
    break;
  }
  b++;
}
  adjList.erase(it1);

  for (auto mapIt = keysToRemove.begin(); mapIt != keysToRemove.end(); mapIt++) {
    auto keyIt = adjList.find(mapIt->first);

    for (auto it = keyIt->second.begin(); it != keyIt->second.end(); it++) {
      if (mapIt->second) {
        // the edge to remove was the source
        if ((**it).get().source().key() == key) {
          keyIt->second.erase(it);
          break;
        }
      } else {
        // the edge to remove was the dest
        if ((**it).get().dest().key() == key) {
          keyIt->second.erase(it);
          break;
        }
      }
    }
  }
/*
  if (adjList.find(key) == adjList.end()) {
    std::cout << "erased properly" << std::endl;
  } else {
    std::cout << "didn't erase well" << std::endl;
  }*/
  unsigned a=0;
  // problem : remove the edges also
    while(a < edgeList.size()){
      for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        if (it->get().source().key() == key || it->get().dest().key() == key) {
          //std::cout << "removing this edge from edgeList: " << *it << std::endl;
          auto temp= it;
          edgeList.erase(temp);
          break;
        }
      }
      a++;
  }
}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeListIter edgeItr= edgeList.insert(edgeList.begin(), e);
  adjList[v1.key()].push_back(edgeItr);
  adjList[v2.key()].push_back(edgeItr);
  // adjList[v1.key()].push_back(edgeList.insert(edgeList.begin(),e));
  // adjList[v2.key()].push_back(edgeList.insert(edgeList.begin(),e));
  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
  void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
    // TODO: Part 2
    auto it1 = adjList.find(key1);
    auto it2 = adjList.find(key2);

    for (auto it3 = it1->second.begin(); it3 != it1->second.end(); it3++) {
      if ((**it3).get().source().key() == key1 && (**it3).get().dest().key() == key2) {
        // remove from adjacent list
        auto temp= it3++;
        // auto temp= it3;
        it1->second.erase(temp);
        break;
      }
    }
    for (auto it4 = it2->second.begin(); it4 != it2->second.end(); it4++) {
      if ((**it4).get().source().key() == key1 && (**it4).get().dest().key() == key2) {
        // remove from adjacent list
        auto temp= it4++;
        // auto temp= it4;
        it2->second.erase(temp);
        break;
      }
    }
    for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
      if ((*it).get().source().key() == key1 && (*it).get().dest().key() == key2) {
        // remove from edgeList
        auto temp= it++;
        edgeList.erase(temp);
        break;
      }
    }
  }


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  edgeList.erase(it);
  //remoce from edgeListIter:
  for(edgeListIter keyIt= adjList.begin(); keyIt != adjList.end(); keyIt++){
    for(edgeListIter edgeIt= keyIt->second.begin(); edgeIt != keyIt->second.end(); edgeIt++){
      if(*edgeIt==*it){
        keyIt->second.erase(*it);
        break;
      }
    }
  }
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  for(auto it= adjList.at(key).begin(); it != adjList.at(key).end(); it++){
    edges.push_back(**it);
  }

  // for(auto it= adjList.at(key).begin(); it != adjList.at(key).end(); it++){
  //   cout<<"source: "<<(*it)->get().source()<<" dest: "<<(*it)->get().dest()<<" adjSize: "<< adjList.at(key).size()<<endl;
  // }
  // for(auto it=edges.begin(); it != edges.end(); it++){
  //       cout<<"source: "<<it->get().source()<<" dest: "<<it->get().dest()<<" size: "<<edges.size()<<endl;
  // }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  //find the vertex with the smaller degree
  bool checkK1= false;
  bool check= false;
  bool check2=false;
  if(adjList.at(key1).size() < adjList.at(key2).size()){
    checkK1=true;
  }
  if(checkK1){
  for(edgeListIter it : adjList.at(key1)){
    if(it->get().dest().key() == key2){
    check=true;
    }
  }
} else{
  for(edgeListIter it : adjList.at(key2)){
    if(it->get().source().key() == key1){
    check2=true;
    }
  }
}
if(check == true || check2==true){
  return true;
}
  return false;
}
