#include "pathFinding.h"
#include "node.h"
#include <set>

using namespace std;

PathFinding::PathFinding(const Map *map, bool climb) : climb(climb), map(map) {}

std::queue<std::pair<int, int>> PathFinding::findPath(const pair<int, int> &currentPosition) const {
    queue<Node> q;
    Node node = {currentPosition};
    q.push(node);
    set<pair<int, int>> visited;
    while (!q.empty()) {
        node = q.front();
        q.pop();
        if (node.coordinates == map->exit)
            return node.path;
        for (const auto &dir: directions) {
            auto newCoords = node + dir;
            if (!visited.count(newCoords) && map->validTile(newCoords, climb)) {
                Node newNode = {newCoords, node.path};
                visited.emplace(newCoords);
                newNode.path.emplace(node.coordinates);
                q.push(newNode);
            }
        }
    }
    return {};
}

std::unique_ptr<PathFinding> PathFinding::clone() const {
    return make_unique<PathFinding>(*this);
}
