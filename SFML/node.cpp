#include <string>
#include "node.h"

std::vector<Node*> Node::nodes;

void Node::Update() {
	box.left = rect.getPosition().x;
	box.top = rect.getPosition().y;
}