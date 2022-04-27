#include <stdio.h>
#define INF 1000000000

int graph[7][7]; //������ ���� ����
int capacity[7][7]; //�뷮 �迭
int flow[7][7]; //���� �迭
int visited[7]; //���� �湮 ����
int result; //�ִ�����
int e_path = 0; //����� ��ȣ

void maxFlow(int source, int sink) //������: source, ������: sink
{
    while (1)
    {
        for (int i = 1; i <= 6; i++) //���� �湮 ���θ� �湮���� �ʾҴٴ� ���� -1�� �ʱ�ȭ
        {
            visited[i] = -1;
        }

        dfs(source, sink); //���̿켱Ž���� ���� ��� Ž��

        if (visited[sink] == -1) break; //sink ������ ��θ� �� ã�Ҵٸ� ��� ��� Ž���Ϸ�

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


void dfs(int st, int ed) //���̿켱Ž�� �Լ� ����
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
    graph[1][2] = 1; //����1���� ����2�� ���� ���� ����
    graph[2][1] = 1; //�ݴ���� ���� �߰�
    capacity[1][2] = 7; //������ �뷮 �߰�

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

    printf("�ִ� ���� : %d", result);
}