/*
문제 설명
초 단위로 기록된 주식가격이 담긴 배열 prices가 매개변수로 주어질 때, 가격이 떨어지지 않은 기간은 몇 초인지를 return 하도록 solution 함수를 완성하세요.

제한사항
prices의 각 가격은 1 이상 10,000 이하인 자연수입니다.
prices의 길이는 2 이상 100,000 이하입니다.
입출력 예
prices	return
[1, 2, 3, 2, 3]	[4, 3, 1, 1, 0]
입출력 예 설명
1초 시점의 ₩1은 끝까지 가격이 떨어지지 않았습니다.
2초 시점의 ₩2은 끝까지 가격이 떨어지지 않았습니다.
3초 시점의 ₩3은 1초뒤에 가격이 떨어집니다. 따라서 1초간 가격이 떨어지지 않은 것으로 봅니다.
4초 시점의 ₩2은 1초간 가격이 떨어지지 않았습니다.
5초 시점의 ₩3은 0초간 가격이 떨어지지 않았습니다.
*/

#include <vector>
#include <iostream>

using namespace std;

//stack을 이용한 방법 O(N)
//라고는 하지만 실제 이중포문과의 속도차이는 얼마 나지 않는다
//스택을 이용했을때 부가적인 기능을 구현해야되서 그런거 같다
//인덱스를 stack에 넣고 비교하는 값보다적으면 answer에 넣고 인덱스를 뽑아낸다
vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    stack<int> s;
    int size = prices.size();
    for(int i=0;i<size;i++){
        while(!s.empty()&&prices[s.top()]>prices[i]){
            answer[s.top()] = i-s.top();
            s.pop();
        }
        s.push(i);
    }
    while(!s.empty()){
        answer[s.top()] = size-s.top()-1;
        s.pop();
    }
    return answer;
}

/*
 * 이중 포문을 이용한 방법 O(N^2)
vector<int> solution(vector<int> prices)
{
	vector<int> result;
	int j;
	for (int i = 0; i < prices.size(); i++)
	{
		//vector에 값을 push하는 과정이 for 문밖에 있기 때문에 -1 까지만 하면된다
		for (j = 0; j < prices.size() - i - 1; j++)
		{
			if (prices[j + i] < prices[i])
			{
				break ;
			}
		}
		result.push_back(j);
	}
	return (result);
}
*/

int		main(void)
{
	vector<int> prices = {1,2,3,2,3};

	vector<int> result = solution(prices);
	for(int i = 0; i < result.size(); i++)
		cout << result[i] << endl;
	return (0);
}
