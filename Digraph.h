#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::pair;

/*
DiGraph implementation using an adjacency list
*/
template <typename T>
class Digraph
{
private:
    // Vector of vectors containing each nodes' neighbors
    vector<pair<T, vector<T>>> adjacency;

    // Returns the numeric index of a value
    // or -1 if value is not found
    int get_node_index(T node)
    {
        int i{0};
        for(auto n : adjacency)
        {
            if(node == n.first)
            {
                return i;
            }
            ++i;
        }
        return -1;
    }

public:
    // Adds a new node to the Digraph if the value isn't 
    // in the DiGraph yet
    // Returns true if the insertion was made or false otherwise
    bool add_node(T node)
    {
        if(get_node_index(node) == -1)
        {
            adjacency.push_back(std::make_pair(node, std::vector<T>{}));
            return true;
        }
        return false;
    }

    // Adds a new edge connecting src to dst
    // If either src or dst is not yet a node in the graph,
    // it adds it first
    void add_edge(T src, T dst)
    {
        int i{get_node_index(src)};
        int j{get_node_index(dst)};
        if(i == -1)
        {
            add_node(src);
            i = adjacency.size() - 1;
        }
        if(j == -1)
        {
            add_node(dst);
            j = adjacency.size()-1;
        }
        if(std::find(adjacency[i].second.begin(),
                     adjacency[i].second.end(), dst) == adjacency[i].second.end())
        {
            adjacency[i].second.push_back(dst);
        }
    }

    // Pretty print for the adjacency list 
    void print()
    {
        for(auto n : adjacency)
        {
            cout << n.first << ": ";
            for(auto nb : n.second)
            {
                cout << nb << " | ";
            }
            cout << "\n";
        }
    }

    vector<pair<T, vector<T>>> get_adjacency() const 
    {
        return adjacency;
    }

};

#endif
