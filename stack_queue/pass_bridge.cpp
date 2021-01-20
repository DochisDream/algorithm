#include <iostream>
#include<algorithm>
#include <functional>         // greater 사용 위해 필요  
#include <vector>
#include<queue>
using namespace std;
/*
// dequeue를 이용한 소스코드 내 코드보다 2배빠르다..
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int count = 0;
    int Time = 0; 
    int Truck_weight = 0;
    queue<pair<int, int>> truck_move;

    while (true)
    {
        if (weight >= Truck_weight + truck_weights.at(count))
        {
            truck_move.push(make_pair(truck_weights.at(count), bridge_length + 1 + Time));
            Truck_weight += truck_weights.at(count);
            count++;
        }

        if (count >= truck_weights.size())
        {
            answer = truck_move.back().second;
            break;
        }
        else
        {
            Time++;
            if (truck_move.front().second == Time+1)
            {
                Truck_weight -= truck_move.front().first;
                truck_move.pop();
            }
        }

    }

    return answer;
}
*/
/* 내 코드는 deque를 사용한 코드보다 2배느리다..
 * 맨처음 queue를 코드 구조상 0으로 가득 차우는것을 제외하고는 헛짓하는게 없는데
 * 아마 이거만큼 느린것 같다
 */
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0; // 트럭이 모두 통과하는데 걸리는 시간(초단위)
	int	total_weight = 0; //다리를 건너는 트럭의 총량
	int	truck_number = 0;
	queue<int> bridge_condition; // 다리의 현재 상태(트럭의 무게가 들어감)
	
	//queue 에 다리의 최대 길이까지 0(빈공간)을 채워넣는다
	for (int i = 0; i < bridge_length; i++)
	{
		bridge_condition.push(0);
	}
	//queue에 bridge_length만큼 공간이 모두 채워졌을때
	//마지막 트럭이 다리에 입장할때 까지
	while (truck_number < truck_weights.size())
	{
		//가장 다리끝에 도착한 트럭 빼내고 총 무게 감소시키기
		//트럭이 아니라면 0을 뺄것이기 때문에 자연스럽게 진행된다
		total_weight -= bridge_condition.front();
		bridge_condition.pop();
		//다음 트럭이 추가로 건널 때 다리의 허용 무게치를 초과하지 않는다면
		if (total_weight + truck_weights[truck_number] <= weight)
		{
			bridge_condition.push(truck_weights[truck_number]); //현재 다리에 추가
			total_weight += truck_weights[truck_number]; //총 무게치 증가
			truck_number++; //다음 트럭을 가르키도록 인덱스 증가
		}
		//허가치를 넘어서 다음 트럭이 못건널 경우 0으로 큐의 공간을 채운다
		else
			bridge_condition.push(0);
		//반환할 시간초는 계속해서 카운트 해준다
		answer++;
	}
	//들어가 있는 트럭이 모두 빠져나올때까지 pop을 진행시켜준다
	//queue 가 모두 비울때 까지
	//bridge_condition.front() == -1 일때 왜 안되는가
	while(!bridge_condition.empty())
	{
		//queue가 모두 비워질 때까지 pop을 해준다
		bridge_condition.pop();
		answer++;
	}
    return answer;
}

int		main(void)
{
	int bridge_length = 2;
	int weight = 10;
	vector<int> truck_weights = {7, 4, 5, 6};

	int result = solution(bridge_length, weight, truck_weights);
	cout << result << endl;
	return (0);
}
