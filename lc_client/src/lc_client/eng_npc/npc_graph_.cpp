Path NpcGraph::getShortestPath(unsigned int source, unsigned int destination) { 
	assert(m_vertices.size() < UINT_MAX, "NpcGraph: too much vertices.");

	std::vector<unsigned int> vertices;
	std::vector<float> distances(m_vertices.size());
	std::vector<unsigned int> previous(m_vertices.size());

//1  function Dijkstra(Graph, source):
// 2      
// 3      for each vertex v in Graph.Vertices:
// 4          dist[v] = INFINITY
// 5          prev[v] = UNDEFINED
// 6          add v to Q
// 7      dist[source] = 0
// 8      
// 9      while Q is not empty:
//10          u = vertex in Q with min dist[u]
//11          remove u from Q
//12          
//13          for each neighbor v of u still in Q:
//14              alt = dist[u] + Graph.Edges(u, v)
//15              if alt < dist[v]:
//16                  dist[v] = alt
//17                  prev[v] = u
//18
//19      return dist[], prev[]



	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		distances[i] = INFINITY;
		vertices.push_back(i);
	}

	distances[source] = 0;
	float alt = 0;

	unsigned int vertices_size = (unsigned int) vertices.size();

	while (vertices_size > 0) {
		unsigned int minDistVertex = INFINITY;
		float minDist = INFINITY;
		for (unsigned int i = 0; i < distances.size(); i++) {
			bool isVerticeInVertices = false;
			//for (unsigned int vertex : vertices) {
			//	if (i == vertex) {
			//		isVerticeInVertices = true;
			//	}
			//}

			if (vertices[i] != UINT_MAX) {
				isVerticeInVertices = true;
			}

			if ((distances[i] < minDist) && isVerticeInVertices) {
				minDistVertex = i;
				minDist = distances[i];
			}
		}

		vertices[minDistVertex] = -1;
		vertices_size--;

		for (unsigned int adjVertex : m_vertices[minDistVertex].adjacentVertices) {
			alt = distances[minDistVertex] + getDistance(minDistVertex, adjVertex);

			if (alt < distances[adjVertex]) {
				distances[adjVertex] = alt;
				previous[adjVertex] = minDistVertex;
			}
		}
	}

	
	return Path(previous, alt);
}