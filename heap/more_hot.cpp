/*
문제 설명
매운 것을 좋아하는 Leo는 모든 음식의 스코빌 지수를 K 이상으로 만들고 싶습니다. 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 Leo는 스코빌 지수가 가장 낮은 두 개의 음식을 아래와 같이 특별한 방법으로 섞어 새로운 음식을 만듭니다.

섞은 음식의 스코빌 지수 = 가장 맵지 않은 음식의 스코빌 지수 + (두 번째로 맵지 않은 음식의 스코빌 지수 * 2)
Leo는 모든 음식의 스코빌 지수가 K 이상이 될 때까지 반복하여 섞습니다.
Leo가 가진 음식의 스코빌 지수를 담은 배열 scoville과 원하는 스코빌 지수 K가 주어질 때, 모든 음식의 스코빌 지수를 K 이상으로 만들기 위해 섞어야 하는 최소 횟수를 return 하도록 solution 함수를 작성해주세요.

제한 사항
scoville의 길이는 2 이상 1,000,000 이하입니다.
K는 0 이상 1,000,000,000 이하입니다.
scoville의 원소는 각각 0 이상 1,000,000 이하입니다.
모든 음식의 스코빌 지수를 K 이상으로 만들 수 없는 경우에는 -1을 return 합니다.
입출력 예
scoville	K	return
[1, 2, 3, 9, 10, 12]	7	2
입출력 예 설명
스코빌 지수가 1인 음식과 2인 음식을 섞으면 음식의 스코빌 지수가 아래와 같이 됩니다.
새로운 음식의 스코빌 지수 = 1 + (2 * 2) = 5
가진 음식의 스코빌 지수 = [5, 3, 9, 10, 12]

스코빌 지수가 3인 음식과 5인 음식을 섞으면 음식의 스코빌 지수가 아래와 같이 됩니다.
새로운 음식의 스코빌 지수 = 3 + (5 * 2) = 13
가진 음식의 스코빌 지수 = [13, 9, 10, 12]

모든 음식의 스코빌 지수가 7 이상이 되었고 이때 섞은 횟수는 2회입니다.
*/

#include <string>
#include <vector>
//heap(priority_queue)를 사용하기 위한 queue 헤더 포함
#include <queue>
#include <iostream>

using namespace std;

//깔끔하게 짠 코드
int solution(vector<int> scoville, int K) {
    int answer = 0;
    int needHot;
	//priority_queue<heap에 들어갈 값, 적용시킬 백터의 구조, 오름차순 설정>
	//들어가는 값과 백터의 자료형은 같아야한다
	//pq (vector.begin(), vector.end())를 이용하여 for 문을 써서 heap에 넣지 않고 바로 넣을 수 있다
    priority_queue<int,vector<int>,greater<int>> pq (scoville.begin(),scoville.end());

    while(pq.top()<K) {
        if(pq.size()==1) return answer = -1;
        needHot=pq.top();
		pq.pop();
        pq.push(needHot+pq.top()*2);
        pq.pop();
		answer++;
    }
    return answer;
}

/*
int		solution(vector<int> scoville, int k)
{
	//최대 힙
	//priority_queue <int> pq;
	//최소 힙
	priority_queue <int, vector<int>, greater<int>> pq;
	int cnt = 0;
	int min_scoville;
	int second_scoville;

	for (int i = 0 ; i < scoville.size(); i++)
	{
		pq.push(scoville[i]);
	}

	//음식이 k수치를 만족할때까지 섞기
	while (pq.top() < k)
	{
		//두음식을 힙에서 뺀후 섞고 다시 삽입
		min_scoville = pq.top();
		pq.pop();
		//더이상 섞을 음식이 없을 경우
		if (pq.empty())
			return (-1);
		second_scoville = pq.top();
		pq.pop();
		min_scoville = min_scoville + (second_scoville * 2);
		pq.push(min_scoville);
		cnt++;
	}
	return (cnt);
}
*/

int		main(void)
{
	int k = 7;
	int result;
	vector<int> scoville = {1, 2, 3, 9, 10, 12};

	result = solution(scoville, k);
	cout << result << endl;
}
