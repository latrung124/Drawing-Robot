/*
 * draw_algorithm.cpp
 * Author: Trung La
 * Date: 2021-09-26
 * This file contains the implementation of the draw algorithm.
 */

#include <queue>

#include "draw_algorithm.h"

namespace draw_algorithm {

std::vector<position> draw_algorithm::drawLine(const draw_data &data)
{
	return findPath(data);
}

std::vector<position> draw_algorithm::findPath(const draw_data &data)
{
	std::vector<position> path;
	// Implement the algorithm to find the path
	// between the start and end positions
	int16_t dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
	int16_t dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
	std::vector<std::vector<bool>> visited(
	    data.grid.width, std::vector<bool>(data.grid.height, false));
	std::vector<std::vector<position>> parent(
	    data.grid.width, std::vector<position>(data.grid.height, {0, 0}));
	std::queue<position> q;
	q.push(data.start);
	visited[data.start.x][data.start.y] = true;
	while (!q.empty()) {
		position current = q.front();
		q.pop();
		if (current.x == data.end.x && current.y == data.end.y) {
			position p = data.end;
			while (p.x != data.start.x || p.y != data.start.y) {
				path.push_back(p);
				p = parent[p.x][p.y];
			}
			path.push_back(data.start);
			std::reverse(path.begin(), path.end());
			break;
		}
		for (int i = 0; i < 8; i++) {
			position next = {current.x + dx[i], current.y + dy[i]};
			if (next.x >= 0 && next.x < data.grid.width && next.y >= 0 && next.y < data.grid.height
			    && !visited[next.x][next.y] && data.grid.data[next.x][next.y] == 0) {
				visited[next.x][next.y] = true;
				parent[next.x][next.y] = current;
				q.push(next);
			}
		}
	}

	return path;
}

} // namespace draw_algorithm
