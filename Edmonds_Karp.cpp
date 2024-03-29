//Edmonds_Karp algorithm

#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

//Suppose there are only 10 vertexes at most
const int MAX_VERTEX = 10;
const int MAX_VALUE = 0x7FFFFFFF;

int graph[MAX_VERTEX][MAX_VERTEX];

int vertex_number;
queue<int> fifo_queue;
//store current vertex's prefix vertex
int prefix[MAX_VERTEX];
//store stream size of path which start s and end with current node
int stream[MAX_VERTEX];

/**
 * v0-s
 * v1-v1
 * v2-v2
 * v3-t
 */
void BuildGraph() {
    vertex_number=6;
    for (int i=0; i<MAX_VERTEX; i++)
        memset(graph[i], -1, sizeof(graph[i]));
	graph[0][1] = 16;
    graph[0][2] = 13;
    graph[1][3] = 12;
    graph[2][1] = 4;
    graph[2][4] = 14;
	graph[3][2] = 19;
	graph[3][5] = 20;
	graph[4][3] = 7;
	graph[4][5] = 4;
    
}

void ClearQueue() {
    while (!fifo_queue.empty())
        fifo_queue.pop();
}

void SearchTarget(int start, int stop) {
    if (start == stop)
        return;
    int max_stream = 0;
    while (true) {
        ClearQueue();
        memset(prefix, -1, sizeof(prefix));
        memset(stream, 0, sizeof(stream));
        stream[start] = MAX_VALUE;
        
        //start Breadth first search��BFS)
        fifo_queue.push(start);
        while (!fifo_queue.empty()) {
            int current = fifo_queue.front();
            fifo_queue.pop();
            for (int i=0; i<vertex_number; i++)
                if (i != current && graph[current][i] > 0 && prefix[i]==-1) {
                    fifo_queue.push(i);
                    prefix[i] = current;
                    //store current path's stream size
                    stream[i] = min(stream[current], graph[current][i]);
                    if (i == stop) {
                        break;
                    }
                }
            
            //break if we have found target node
            if (stream[stop])
                break;
        }
        
        for (int i = 0; i < vertex_number; i++)
            printf("[path] %d->%d\n", prefix[i], i);

        if (stream[stop]) {
            int max_value = stream[stop];
            max_stream += max_value;
            //modify graph stream value
            for (int current=stop; current!=start; current = prefix[current]) {
                printf("%d->%d, current stream is %d, will use %d \n", prefix[current], current, graph[prefix[current]][current], max_value);
                graph[prefix[current]][current] -= max_value;
                graph[current][prefix[current]] += max_value;
            }
        } else {
            printf("No available path found, exit now\n");
            break;
        }
    }
    printf("Max stream size is:%d\n", max_stream);
}

int main(int argc, char** argv) {
    BuildGraph();
    SearchTarget(0, 5);

	system("pause");
    return 0;
}
