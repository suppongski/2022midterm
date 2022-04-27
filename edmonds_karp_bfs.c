#include <stdio.h>
#define MAX 100
#define INF 1000000000

typedef struct{ //큐의 생성
  int front;
  int rear;
  int data[MAX];
} Queue;

void init_queue(Queue *q){ //큐 초기화 함수
  q->front=0;
  q->rear=-1;
}
void enqueue(Queue *q, int x){ //큐에 데이터 삽입 함수
  q->data[++q->rear] = x;
}
int dequeue(Queue *q){ //큐에 데이터 제거 함수
  return q->data[q->front++];
}
int is_empty(Queue *q){ //큐가 비어있는지 확인하는 함수
  return q->rear==q->front-1;
}

int graph[7][7]; //정점과 엣지 정의
int capacity[MAX][MAX]; //용량 배열
int flow[MAX][MAX]; //유량 배열
int visited[7]; //정점 방문 여부
int result; //최대유량
int e_path = 0; //경로의 번호

void maxFlow(int source, int sink) //시작점: source, 도착점: sink
{
  while (1)
  {
    for (int i = 0; i < 7; i++) //정점 방문 여부를 방문하지 않았다는 뜻의 -1로 초기화
    {
      visited[i] = -1;
    }

    Queue q;  //queue 생성 후, 시작정점 삽입
    init_queue(&q);
    enqueue(&q, source);

    while (!is_empty(&q)) //너비우선탐색
    {
      int start = q.data[q.front];
      dequeue(&q);
      for (int i = 2; i <= 6; i++) //queue의 맨 앞에 위치한 정점과 인접한 정점 탐색
      {
        int end = graph[start][i];
        if (capacity[start][end] - flow[start][end] > 0 && visited[end] == -1) //인접 정점에 잔여 용량이 남아있는지 확인하고, 방문여부 확인
        { 
          enqueue(&q, end);
          visited[end] = start; 
          if (end == sink) break; 
        }
      }
    }

    if (visited[sink] == -1) break; //sink 까지의 경로를 못 찾았다면 모든경로 탐색완료

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

int main(void)
{
  graph[1][2] = 2; //정점1에서 정점2로 가는 엣지 정의
  graph[2][1] = 1; //반대방향 엣지 추가
  capacity[1][2] = 7; //엣지의 용량 추가

  graph[1][3] = 3;
  graph[3][1] = 1;
  capacity[1][3] = 10;

  graph[3][2] = 2;
  graph[2][3] = 3;
  capacity[3][2] = 8;

  graph[2][5] = 5;
  graph[5][2] = 2;
  capacity[2][5] = 9;

  graph[2][4] = 4;
  graph[4][2] = 2;
  capacity[2][4] = 8;

  graph[3][4] = 4;
  graph[4][3] = 3;
  capacity[3][4] = 12;

  graph[4][5] = 5;
  graph[5][4] = 4;
  capacity[4][5] = 11;

  graph[4][6] = 6;
  graph[6][4] = 4;
  capacity[4][6] = 4;

  graph[5][6] = 6;
  graph[6][5] = 5;
  capacity[5][6] = 7;

  maxFlow(1, 6);

  printf("최대 유량 : %d", result);
}