/*
문제 설명
수많은 마라톤 선수들이 마라톤에 참여하였습니다. 단 한 명의 선수를 제외하고는 모든 선수가 마라톤을 완주하였습니다.

마라톤에 참여한 선수들의 이름이 담긴 배열 participant와 완주한 선수들의 이름이 담긴 배열 completion이 주어질 때, 완주하지 못한 선수의 이름을 return 하도록 solution 함수를 작성해주세요.

제한사항
마라톤 경기에 참여한 선수의 수는 1명 이상 100,000명 이하입니다.
completion의 길이는 participant의 길이보다 1 작습니다.
참가자의 이름은 1개 이상 20개 이하의 알파벳 소문자로 이루어져 있습니다.
참가자 중에는 동명이인이 있을 수 있습니다.
입출력 예
participant	completion	return
[leo, kiki, eden]	[eden, kiki]	leo
[marina, josipa, nikola, vinko, filipa]	[josipa, filipa, marina, nikola]	vinko
[mislav, stanko, mislav, ana]	[stanko, ana, mislav]	mislav
입출력 예 설명
예제 #1
leo는 참여자 명단에는 있지만, 완주자 명단에는 없기 때문에 완주하지 못했습니다.

예제 #2
vinko는 참여자 명단에는 있지만, 완주자 명단에는 없기 때문에 완주하지 못했습니다.

예제 #3
mislav는 참여자 명단에는 두 명이 있지만, 완주자 명단에는 한 명밖에 없기 때문에 한명은 완주하지 못했습니다.
*/

#include <string>
//동적 메모리 할당을 쉽게 해주는 vector 헤더 추가
#include <vector>
//sort 함수를 사용하기 위한 algorithm 헤더 추가
#include <algorithm>
//헤쉬테이블을 사용하기 위한 unordeered_map 헤더 사용
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion)
{
    unordered_map<string, int> hash_map;
    for (int i = 0; i < completion.size(); i++)
    {
        hash_map[completion[i]]++;
    }
    for (int i = 0; i < participant.size(); i++)
    {
        if (--hash_map[participant[i]] < 0)
        {
            return (participant[i]);
        }
    }
}
/*
//정렬을 이용한 풀이
string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
	//두 문자열을 순서대로 졍렬
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    for(int i=0;i<participant.size();i++)
    {
		//서로 비교해가며 다를 경우 완주자가 아니기 때문에 participant의 원소를 리턴
        if(participant[i] != completion[i])
            return participant[i];
    }
}

//SOL
//단 한명의 완주하지 못한 사람을 찾는 것이기 때문에 두 백터를 sort함수를 이용하여 정렬을 한뒤
////서로의 백터의 원소들을 비교하며 서로가 같지 않은 문자열을 찾아 리턴
*/
