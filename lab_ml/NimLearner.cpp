/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <iostream>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    startingTokens_ = startingTokens;

    // initialize the starting vertex
    startingVertex_ = "p1-" + std::to_string(startingTokens);

    for (unsigned i = 0; i < startingTokens+1; i++) {
      std::string vertex1 = "p1-" + std::to_string(i);
      std::string vertex2 = "p2-"+ std::to_string(i);

      std::string vertexNext1 = "p2-"+ std::to_string(i - 1);
      std::string vertexNext2 = "p2-"+ std::to_string(i - 2);

      std::string vertexNext3 = "p1-"+ std::to_string(i-1);
      std::string vertexNext4 = "p1-"+ std::to_string(i-2);

      // insert the vertices
      g_.insertVertex(vertex1);
      g_.insertVertex(vertex2);

      // edge case
      if (i == 1) {
        g_.insertEdge(vertex1, vertexNext1);
        g_.setEdgeWeight(vertex1, vertexNext1, 0);

        g_.insertEdge(vertex2, vertexNext3);
        g_.setEdgeWeight(vertex2, vertexNext3, 0);
      }
      else if (i >= 2) {
        // create and set edges for vertex1
        g_.insertEdge(vertex1, vertexNext1);
        g_.setEdgeWeight(vertex1, vertexNext1, 0);
        g_.insertEdge(vertex1, vertexNext2);
        g_.setEdgeWeight(vertex1, vertexNext2, 0);

        // create and set edges for vertext 2
        g_.insertEdge(vertex2, vertexNext3);
        g_.setEdgeWeight(vertex2, vertexNext3, 0);
        g_.insertEdge(vertex2, vertexNext4);
        g_.setEdgeWeight(vertex2, vertexNext4, 0);
      }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
/*
  int tokensLeft = (int)startingTokens_;
  while (tokensLeft > 0) {
    int random = rand() % 2;
    std::string startString = std::to_string(startingTokens_);
    std::string tokensLeftString = std::to_string(tokensLeft);
    if (tokensLeft == (int)startingTokens_) {
      if (random == 0) {
        path.push_back(Edge("p1-" + startString, "p2-" + std::to_string(tokensLeft - 1)));
      } else {
        path.push_back(Edge("p1-" + startString, "p2-" + std::to_string(tokensLeft - 2)));
      }
    } else {
      if (tokensLeft == 1) {
        path.push_back(Edge("p1-" + tokensLeftString, "p2-" + std::to_string(tokensLeft - 1)));
      } else {
        if (random == 0) {
          path.push_back(Edge("p1-" + tokensLeftString, "p2-" + std::to_string(tokensLeft - 1)));
        } else {
          path.push_back(Edge("p1-" + tokensLeftString, "p2-" + std::to_string(tokensLeft - 2)));
        }
      }
    }
    tokensLeft--;
  }
  */
  int tokensLeft = (int)startingTokens_;
  Vertex current = "p1-" + std::to_string(startingTokens_);
  while (tokensLeft > 0) {
    std::vector<Vertex> adjV = g_.getAdjacent(current);
    Vertex random = adjV[rand() % adjV.size()];
    path.push_back(Edge(current, random));
    current = random;
    if ( (tokensLeft - std::stoi(random.substr(3,3)) ) == 1) {
      tokensLeft--;
    }
    if ( (tokensLeft - std::stoi(random.substr(3,3)) ) == 2) {
      tokensLeft = tokensLeft - 2;
    }
  }

  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {

  bool player1W = false;
  bool player2w = false;
  if (path.back().dest == "p1-0") {
    player2w = true;
  }
  if (path.back().dest == "p2-0") {
    player1W = true;
  }

  for (unsigned i = 0; i < path.size(); i++) {
    auto currWeight = g_.getEdgeWeight(path[i].source, path[i].dest);
   if (player1W) {
     if (path[i].source.substr(0,2) == "p1") {
       g_.setEdgeWeight(path[i].source, path[i].dest, currWeight + 1);
     } else {
       g_.setEdgeWeight(path[i].source, path[i].dest, currWeight - 1);
     }
   }
   if (player2w) {
     if (path[i].source.substr(0,2) == "p2") {
       g_.setEdgeWeight(path[i].source, path[i].dest, currWeight + 1);
     } else {
       g_.setEdgeWeight(path[i].source, path[i].dest, currWeight - 1);
     }
   }
 }


}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
