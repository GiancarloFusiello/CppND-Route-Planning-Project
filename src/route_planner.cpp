#include "route_planner.h"
#include <algorithm>
#include <string>
#include <cassert>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}


void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();

    for (auto neighbor: current_node->neighbors) {
        if (!neighbor->visited) {
            neighbor->parent = current_node;
            neighbor->h_value = CalculateHValue(neighbor);
            neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
            neighbor->visited = true;
            open_list.push_back(neighbor);
        }
    }

}


RouteModel::Node *RoutePlanner::NextNode() {
    // sort in descending order
    std::sort(open_list.begin(), open_list.end(), [](RouteModel::Node *a, RouteModel::Node *b){
        float a_f_value = a->g_value + a->h_value;
        float b_f_value = b->g_value + b->h_value;

        // first check if the F values are the same. If so, sort by H value (nearest to the goal)
        if (a_f_value == b_f_value) {
            return a->h_value > b->h_value;
        }

        return a_f_value > b_f_value;
    });

    auto *node = open_list.back();
    open_list.pop_back();

    return node;
}


std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while (current_node->parent) {
        distance += current_node->distance(*current_node->parent);
        path_found.push_back(*current_node);
        current_node = current_node->parent;
    }
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.

    // add the start_node which does not have a parent
    path_found.push_back(*current_node);

    // correct the path order
    std::reverse(path_found.begin(), path_found.end());

    // validate that path starts with the start node
    assert (path_found.front().x != start_node->x || path_found.front().y != start_node->y);

    // validate that path ends with the end node
    assert (path_found.back().x != end_node->x || path_found.back().y != end_node->y);

    return path_found;
}


void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    start_node->visited = true;
    open_list.push_back(start_node);

    while (!open_list.empty()) {
        current_node = NextNode();

        if (current_node == end_node) {
            break;
        }

        AddNeighbors(current_node);
    }

    m_Model.path = ConstructFinalPath(current_node);
}