#include <stdio.h>
#define INF 1000000000

int graph[7][7]; //정점과 엣지 정의
int capacity[7][7]; //용량 배열
int flow[7][7]; //유량 배열
int visited[7]; //정점 방문 여부
int result; //최대유량
int e_path = 0; //경로의 번호

void maxFlow(int source, int sink) //시작점: source, 도착점: sink
{
    while (1)
    {
        for (int i = 1; i <= 6; i++) //정점 방문 여부를 방문하지 않았다는 뜻의 -1로 초기화
        {
            visited[i] = -1;
        }

        dfs(source, sink); //깊이우선탐색을 통한 경로 탐색

        if (visited[sink] == -1) break; //sink 까지의 경로를 못 찾았다면 모든 경로 탐색완료

        int f = INF; //최소유량을 큰 값으로 초기화
        for (int i = sink; i != source; i = visited[i]) //경로들을 반대로 탐색하며 최소 유량을 f에 저장
        {
            if (f > capacity[visited[i]][i] - flow[visited[i]][i])
            {
                f = capacity[visited[i]][i] - flow[visited[i]][i];
            }
        }

        for (int i = sink; i != source; i = visited[i]) //유량상쇄
        {
            flow[visited[i]][i] += f;
            flow[i][visited[i]] -= f;
        }

        e_path++;
        printf("%d번째 경로의 최소유량: %d\n", e_path, f);

        result += f;
    }
}


void dfs(int st, int ed) //깊이우선탐색 함수 정의
{
    for (int i = 2; i <= ed; i++)
    {
        if (graph[st][i] == 1 && capacity[st][i] - flow[st][i] > 0 && visited[i] == -1)
        {
            visited[i] = st;
            dfs(i,ed);
        }
    }
}


int main(void)
{
    graph[1][2] = 1; //정점1에서 정점2로 가는 엣지 정의
    graph[2][1] = 1; //반대방향 엣지 추가
    capacity[1][2] = 7; //엣지의 용량 추가

    graph[1][3] = 1;
    graph[3][1] = 1;
    capacity[1][3] = 10;

    graph[3][2] = 1;
    graph[2][3] = 1;
    capacity[3][2] = 8;

    graph[2][4] = 1;
    graph[4][2] = 1;
    capacity[2][4] = 8;

    graph[2][5] = 1;
    graph[5][2] = 1;
    capacity[2][5] = 9;

    graph[3][4] = 1;
    graph[4][3] = 1;
    capacity[3][4] = 12;

    graph[4][5] = 1;
    graph[5][4] = 1;
    capacity[4][5] = 11;

    graph[4][6] = 1;
    graph[6][4] = 1;
    capacity[4][6] = 4;

    graph[5][6] = 1;
    graph[6][5] = 1;
    capacity[5][6] = 7;

    maxFlow(1, 6);

    printf("최대 유량 : %d", result);
}