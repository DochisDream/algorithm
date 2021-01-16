/*
문제 설명
스트리밍 사이트에서 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범을 출시하려 합니다. 노래는 고유 번호로 구분하며, 노래를 수록하는 기준은 다음과 같습니다.

속한 노래가 많이 재생된 장르를 먼저 수록합니다.
장르 내에서 많이 재생된 노래를 먼저 수록합니다.
장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.
노래의 장르를 나타내는 문자열 배열 genres와 노래별 재생 횟수를 나타내는 정수 배열 plays가 주어질 때, 베스트 앨범에 들어갈 노래의 고유 번호를 순서대로 return 하도록 solution 함수를 완성하세요.

제한사항
genres[i]는 고유번호가 i인 노래의 장르입니다.
plays[i]는 고유번호가 i인 노래가 재생된 횟수입니다.
genres와 plays의 길이는 같으며, 이는 1 이상 10,000 이하입니다.
장르 종류는 100개 미만입니다.
장르에 속한 곡이 하나라면, 하나의 곡만 선택합니다.
모든 장르는 재생된 횟수가 다릅니다.
입출력 예
genres	plays	return
[classic, pop, classic, classic, pop]	[500, 600, 150, 800, 2500]	[4, 1, 3, 0]
입출력 예 설명
classic 장르는 1,450회 재생되었으며, classic 노래는 다음과 같습니다.

고유 번호 3: 800회 재생
고유 번호 0: 500회 재생
고유 번호 2: 150회 재생
pop 장르는 3,100회 재생되었으며, pop 노래는 다음과 같습니다.

고유 번호 4: 2,500회 재생
고유 번호 1: 600회 재생
따라서 pop 장르의 [4, 1]번 노래를 먼저, classic 장르의 [3, 0]번 노래를 그다음에 수록합니다.
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

//hash_map 의 value의 자료형을 pair로 활용하여 2개 이상의 value값에 접근하는 방식
//데이터를 한번에 몰아 넣을 수 있기 때문에 처리해야할 기능도 적어서 속도도 빠르고, 코드 길이도 짧다

//sort에서 정렬을 하기위해 정의한 compare 함수
//매개변수인 pair는 plays의 플레이 숫자와 고유번호가 들어가 있다
bool compare (pair<int, int> left, pair<int, int> right){
	//먼저 페어의 첫번째 인자인 플레이수를 비교하여 내림차순으로 정렬한다
	if(left.first > right.first){
        return true;
	//만약 플레이수가 같은 경우 두번째 인자인 고유번호를 이용하여 정렬한다
    }else if(left.first == right.first){
        if(left.second < right.second){
            return true;
        }
    }
    return false;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    unordered_map<string, int> summap; //key: 장르, value: 각 장르의 총 플레이 횟수
    unordered_map<string, vector<pair<int, int>>> genmap; //key: 장르, value: 노래 플레이 횟수, 노래의 고유번호
    for (int i = 0; i < genres.size(); i++) {
        summap[genres[i]] += plays[i];	//장르의 총 플레이 횟수 저장
        genmap[genres[i]].push_back(make_pair(plays[i], i)); //장르에 따른 플레이 횟수와 고유번호 저장
    }
	//unordered_map으로 만든 hash table은 순서가 없어 정렬이 불가능하기 때문에
	//정렬을 위해 unordered_map의 값을 vector에 옮겨 담는다
    vector<pair<int, string>> fororder;
    for (auto x : summap) {
        fororder.push_back(make_pair(x.second, x.first));
    }
	//옮겨 담은 vector 정렬(각 장르의 플레이 횟수대로 랭크가 세워짐
    sort(fororder.begin(), fororder.end());
	//백터 크기만큼 배열의 순서대로(랭킹 순) 진행하며 answer에 각 장르의 1,2등 플레이 곡(고유번호)들만 저장
    while (fororder.size() > 0) {
		//sort는 오름차순 으로 렝킹이 정렬 되기 때문에 .back을 이용하여
		//뒤에서 부터 시작한다
        pair<int, string> temp= fororder.back();
        fororder.pop_back(); //뽑아낸 장르는 삭제
		//장르에 맞는 백터 확인
		//백터에는 각 곡들의 플레이 횟수와 pair로 고유번호가 들어가 있다
        vector<pair<int, int>> a = genmap[temp.second];
        sort(a.begin(), a.end(), compare); //compare 규칙을 이용하여 정렬한다
        int lastn = 2;
        if (a.size() < 2) {
            lastn = a.size(); //정렬된 vector 를 2만큼 자른다(각 장르당 1,2등 곡까지만 저장할 것이 때문)
        }
		//answer에 a에 들어가 있는 값 순서대로 저장한다
        for (int i = 0; i < lastn; i++) {
            answer.push_back(a[i].second); //a[i].second = 곡의 고유번호
        }
    }
    return answer;
}


/* # 해쉬
 * 나의 하드 코딩
 * 1. 각 장르의 play 횟수를 key값에 대응하는 value에 모두 더함
 * 2. 더해진 값들을 1차원 배열 rank에 넣고 sort를 이용하여 내림차순 정렬함
 * 3. rank에 정렬된 순서대로 genres에 대응하는 plays를 비교해가며 각 장르의 1,2등을 answer에 저장
 * 4. 고유번호로 저장된 answer값 리턴
 * 
 * 어려웠던점
 * 1.hash table의 key 값에 대응하는 value값을 하나만 1대1대응 하는 방법밖에 몰랐기에 구현 과정이 복잡했다
 * 만약 여러값을 저장하거나 구조체형식으로 저장하여 key값을 통해 value 로 접근했을때 고유번호나 정렬된 play 횟수를 
 * 같이 알 수 있었다면 구현과정이 매우 쉽고 빨랐을 것 같다
 *
 * 2. 백터를 선언만 하고 초기화를 하지않으면 값에 접근할때 segmentation fault가 발생한다
 * 따라서 알맞은 크기로 백터의 사이즈를 설정해서 값을 0으로 초기화 해주던지
 * 아니면 접근할때 v.push_back 등을 이용하여 할때마다 값을 넣어주던지 해서 segmentation falut를 방지해야한다
 *
 * 3. 메모리에 값이 들어가 있는지 0을 확인하는 과정에서 원소의 인덱스 0과 잘못 비교되어
 * 에러가 발생했다 이를 해결하기 위해 인덱스 값을 1부터 시작하게 한 후 나중에 값을 -1 해주는 식으로 해결하였다.
 *  
vector<int> solution(vector<string> genres, vector<int> plays)
{
	vector<int> rank;
	vector<int> answer(genres.size());
	unordered_map<string, int> rank_map; //ranking을 세우기 위한 해쉬
	int cnt = 0;	//반복문의 반복 횟수를 세기 위한 변수
	int resize_n = 0;
	//ranking를 세우기 위한 hash table 구성
	for(int i = 0; i < genres.size(); i++)
	{
		rank_map[genres[i]] += plays[i];
	}
	//value의 값을 2차원 int형 배열에 넣고 sort를 이용하여 랭킹 매기기
	for (auto it = rank_map.begin(); it != rank_map.end(); it++)
	{
		//cout << it->second << endl; //test
		//rank[cnt] = it->second 의 값 접근이 안된다 (segmentation fault)
		//왜 안되는가? vector 공부 더하기
		//=> vector 에 대한 초기화가 없다면 할당이 안되어 값을 넣을 수가 없다
		//이 경우 push_back() 을 이용하여 넣어줄 수 있다
		rank.push_back(it->second);
		cnt++;
	}
	//1.함수를 사용하여 내림차순으로 정렬하거나
	//sort(rank.begin(), rank.end(), compare;
	//bool compare(int i, int j)
	//			return j < i;
	//
	//2.greater<type>(a, b) 이용
	//less : 첫번째 인자가 두번째 인자보다 작으면 true 반환 (bool)
	//greater : 첫번째 인자가 두번째 인자보다 크면 true 반환 (bool)
	//plus : 두개의 인자를 더한 값 반환
	//minus : 첫번째 인자에서 두번째 인자를 뺀 값 반환
	sort(rank.begin(), rank.end(), greater<>());
	cnt = 0;
	//rank에 순서에 따라 리턴해줄 answer를 채워나간다
	for (int i = 0; i < rank.size(); i++)
	{
		//j를 0부터가 아닌 1부터 시작해서 각 장르에 등수가 정해져있는지 확인할때
		//vector 초기화 값이 0과 j(고유번호)가 0일때를 비교해서 생기는 에러를 방지한다
		for (int j = 1; j < genres.size() + 1; j++)
		{
			//랭크에 맞는 장르를 탐색한다 (아닐 경우 j 증가)
			if (rank_map[genres[j - 1]] == rank[i])
			{
				//만약 각 장르의 1등이 정해져 있지 않다면
				if (answer[cnt] == 0)
				{
					answer[cnt] = j; //1등에 현 고유번호 저장
					resize_n++;
				}
				//각 장르의 2등이 정해져 있지 않다면
				//첫번째 answer의 첫번째 칸부터 비교 후에 집어 넣는다
				else if (answer[cnt + 1] == 0)
				{
					//answer[cnt] 는 장르의 1등 고유번호를 뜻한다
					//answer[cnt + 1] 은 장르의 2등 고유번호를 뜻한다
					//1등 고유번호보다 현재 탐색중인 고유번호의 플레이 횟수가 더많다면
					if (plays[answer[cnt] - 1] < plays[j - 1])
					{
						answer[cnt + 1] = answer[cnt]; //현 1등을 2등으로 지정
						answer[cnt] = j; //현재 고유번호를 1등으로 지정
					}
					//1등보다 작거나 같다면 2등 자리에 넣기 (플레이 횟수가 같을 경우 고유번호 순으로 정렬)
					else
						answer[cnt + 1] = j;
						resize_n++;
				}
				//1등 2등이 이미 정해져 있다면
				//j 의 플레이 횟수가 2등보다 큰지 1등보다 큰지를 확인하고 알맞게 값을 넣어준다
				else
				{
					//2등 먼저 플레이 횟수 비교
					//2등이 현재 고유 번호보다 작다면 값 현재 고유 번호 저장
					if (plays[answer[cnt + 1] - 1] < plays[j - 1])
					answer[cnt + 1] = j;
					//그 후 1등 과 2등 비교 후 2등이 더 크다면 고유 번호 값 swap
					if (plays[answer[cnt] - 1] < plays[answer[cnt + 1] - 1])
						swap(answer[cnt], answer[cnt + 1]);
				}
			}
		}
		//두번째 칸이 안채워져 있을때
		//즉 장르의 플레이 곡이 1곡일때
		if (answer[cnt + 1] == 0)
		{
			cnt++; //answer에 저장할 배열 1칸만 증가
		}
		//두칸 모두 채워져 있을 경우
		else
			cnt += 2; //answer에 접근할 인덱스 2증가
	}
	//필요한 만큼의 answer보다 많이 할당된 경우 삭제하고 리턴한다
	answer.resize(resize_n);
	for (int i = 0; i < answer.size(); i++)
		answer[i]--;
	return (answer);
}
*/

int		main(void)
{
	vector<string>	genres = {"classic", "classic","classic","pop","pop","pop"};
	vector<int>		plays = {1,2,3,4,5,6};
	//6,1 5,2, 4,0
	vector<int> result = solution(genres, plays);
	for (int i =0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}
	return (0);
}
