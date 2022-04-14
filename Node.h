#pragma once
#include "Util.h"

class Node {
   public:
    vector<shared_ptr<Node>> children;
    Node* parent;
    char symbol;
    int total;
    int visited;

    Game game;

    Node(Game& game, char symbol);

    void AddChild(Game& game, char symbol);
    void Expand();
};