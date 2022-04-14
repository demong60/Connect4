#include "Util.h"

vector<shared_ptr<Node>> children;
Node *parent;
Game game;
char symbol;
int total;
int visited;
double ucb;

Node::Node(Game &game, char symbol) {
    children.resize(0);
    total = 0;
    visited = 0;
    this->game = game;
    this->symbol = symbol;
}

void Node::AddChild(Game &game, char symbol) {
    shared_ptr<Node> child = make_shared<Node>(game, symbol);
    child->parent = this;
    children.push_back(child);
}

void Node::Expand() {
    vector<Game> children_vector;
    char next_symbol = (symbol == COMPUTER ? PLAYER : COMPUTER);
    Util::CreateChildren(game, children_vector, next_symbol);
    for (Game game : children_vector)
        AddChild(game, next_symbol);
}

// void Node::Select(){

// }