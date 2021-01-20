#include <vector>
#include <queue>
#include <iostream>

using namespace std;

//리턴할 백터만으로 코드 구현을 한 매우 이상적인 코드
//반복문을 하나만 사용하여 말도안되는 시간복잡도를 구현하였다
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int day;
    int max_day = 0;
    for (int i = 0; i < progresses.size(); ++i)
    {
        day = (99 - progresses[i]) / speeds[i] + 1;
		//가장 처음 answer에 아무것도 없거나
		//뒤에오는 task가 아직 개발이 안되서 같이 서비스를 릴리즈할 필요가 없을때
        if (answer.empty() || max_day < day)
            answer.push_back(1);
		//서비스를 같이 출시해야하는 기능일 경우
        else
            ++answer.back(); //같은날 출시할 횟수 증가
		
		//더이상 같이 서비스를 출시할 기능이 개발이 안됬을때
		//max날짜를 그다음 day로 최신화 시키고 다시 비교시작
        if (max_day < day)
            max_day = day;
    }
    return answer;
}


/* 내 코드
 * 큐를 이용한 소스코드
 * 코드 구조는 직관적이고, 생각한 알고리즘 대로 잘짰으나
 * 반복문이 3개나 나오기 때문에 시간복잡도가 굉장히 아쉬운 코드이다
vector<int> solution(vector<int> progresses, vector<int> speeds)
{
	vector<int> answer;
	//날짜 저장
	queue<int> que;
	int day;
	int i;
	int service_number;

	for (i = 0; i < progresses.size(); i++)
	{
		day = 100 - progresses[i];
		if (day % speeds[i] == 0)
		{
			day /= speeds[i];
		}
		else
			day = (day / speeds[i]) + 1;
		que.push(day);
	}
	while(!que.empty())
	{
		day = que.front();
		que.pop();
		service_number= 1;
		while (que.front() <= day && !que.empty())
		{
			service_number++;
			que.pop();
		}
		answer.push_back(service_number);
	}
	return answer;
}
*/
int		main(void)
{
	vector<int> progresses = {93, 30, 55};
	vector<int> speeds = {1, 30, 5};

	vector<int> answer = solution(progresses, speeds);
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << endl;
	}
	return (0);
}
