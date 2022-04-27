#include <stdio.h>
#define MAX 100
#define INF 1000000000

typedef struct{ //ť�� ����
  int front;
  int rear;
  int data[MAX];
} Queue;

void init_queue(Queue *q){ //ť �ʱ�ȭ �Լ�
  q->front=0;
  q->rear=-1;
}
void enqueue(Queue *q, int x){ //ť�� ������ ���� �Լ�
  q->data[++q->rear] = x;
}
int dequeue(Queue *q){ //ť�� ������ ���� �Լ�
  return q->data[q->front++];
}
int is_empty(Queue *q){ //ť�� ����ִ��� Ȯ���ϴ� �Լ�
  return q->rear==q->front-1;
}

int graph[7][7]; //������ ���� ����
int capacity[MAX][MAX]; //�뷮 �迭
int flow[MAX][MAX]; //���� �迭
int visited[7]; //���� �湮 ����
int result; //�ִ�����
int e_path = 0; //����� ��ȣ

void maxFlow(int source, int sink) //������: source, ������: sink
{
  while (1)
  {
    for (int i = 0; i < 7; i++) //���� �湮 ���θ� �湮���� �ʾҴٴ� ���� -1�� �ʱ�ȭ
    {
      visited[i] = -1;
    }

    Queue q;  //queue ���� ��, �������� ����
    init_queue(&q);
    enqueue(&q, source);

    while (!is_empty(&q)) //�ʺ�켱Ž��
    {
      int start = q.data[q.front];
      dequeue(&q);
      for (int i = 2; i <= 6; i++) //queue�� �� �տ� ��ġ�� ������ ������ ���� Ž��
      {
        int end = graph[start][i];
        if (capacity[start][end] - flow[start][end] > 0 && visited[end] == -1) //���� ������ �ܿ� �뷮�� �����ִ��� Ȯ���ϰ�, �湮���� Ȯ��
        { 
          enqueue(&q, end);
          visited[end] = start; 
          if (end == sink) break; 
        }
      }
    }

    if (visited[sink] == -1) break; //sink ������ ��θ� �� ã�Ҵٸ� ����� Ž���Ϸ�

    int f = INF; //�ּ������� ū ������ �ʱ�ȭ
    for (int i = sink; i != source; i = visited[i]) //��ε��� �ݴ�� Ž���ϸ� �ּ� ������ f�� ����
    {
      if (f > capacity[visited[i]][i] - flow[visited[i]][i])
      {
        f = capacity[visited[i]][i] - flow[visited[i]][i];
      }
    }

    for (int i = sink; i != source; i = visited[i]) //�������
    {
      flow[visited[i]][i] += f;
      flow[i][visited[i]] -= f;
    }

    e_path++;
    printf("%d��° ����� �ּ�����: %d\n", e_path, f);
    result += f;
  }
}

int main(void)
{
  graph[1][2] = 2; //����1���� ����2�� ���� ���� ����
  graph[2][1] = 1; //�ݴ���� ���� �߰�
  capacity[1][2] = 7; //������ �뷮 �߰�

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

  printf("�ִ� ���� : %d", result);
}