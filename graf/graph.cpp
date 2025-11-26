#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const string solvetest(int n, int r, int m, const vector<pair<int, int>>& roads, const vector<pair<int, int>>& soldiers) {
    vector<vector<int>> graph(n+1);

    for (const auto& road : roads) {
        graph[get<0>(road)].push_back(get<1>(road));
        graph[get<1>(road)].push_back(get<0>(road));
    }

    deque<pair<int, int>> queue;
    deque<int> lqueue;

    for (size_t i = 0; i < soldiers.size();i++) {
        queue.push_back(make_pair(i,get<0>(soldiers[i])));
        lqueue.push_back(get<1>(soldiers[i]));
    }

    vector<int> towers(n+1, -1);
    towers[0] = 0;

    while (queue.size() > 0) {
        int index = get<0>(queue.front());
        int city = get<1>(queue.front());
        int length = lqueue.front();

        queue.pop_front();
        lqueue.pop_front();

        if (towers[city] == -1) {
            towers[city] = index;
        }else if (towers[city] != index) {
            return "No";
        }

        if (length > 0) {
            for(const auto& c : graph[city]) {
                if(towers[c] == -1) {
                    queue.push_back(make_pair(index, c));
                    lqueue.push_back(length-1);
                }else if (towers[c] != index) {
                    return "No";
                }
            }
        }
    }


    bool valid = true;
    for (const auto& tower : towers) {
        if (tower == -1) {
            valid = false;
            break;
        }
    }
    if(valid) {
        return "Yes";
    }
    return "No";
}

int main() {
    int test_case = 0;
    string state = "NRM";
    vector<int> N;
    vector<int> R;
    vector<int> M;
    vector<vector<std::pair<int,int>>> roads;
    vector<vector<std::pair<int,int>>> soldiers;

    int tcaseindex = 0;

    int num;
    cin >> num;
    if (test_case == 0) {
        test_case = num;
    }
    vector<pair<int, int>> tmpvector;
    while (tcaseindex < test_case) {
        if (state == "NRM") {
            cin >> num;
            N.push_back(num);
            cin >> num;
            R.push_back(num);
            cin >> num;
            M.push_back(num);
            state = "roads";
        }else if (state == "roads") {
            int tmp = 0;
            cin >> num;
            tmp = num;
            cin >> num;
            tmpvector.push_back(make_pair(tmp, num));
            if (tmpvector.size() == R[tcaseindex]) {
                state = "soldiers";
                roads.push_back(tmpvector);
                tmpvector.clear();
            }
        }else if (state == "soldiers") {
            int tmp = 0;
            cin >> num;
            tmp = num;
            cin >> num;
            tmpvector.push_back(make_pair(tmp,num));
            if (tmpvector.size() == M[tcaseindex]) {
                state = "NRM";
                soldiers.push_back(tmpvector);
                tmpvector.clear();
                tcaseindex++;
            }
        }
    }

    for (size_t i = 0; i < test_case;i++) {
        string ans = solvetest(N[i],R[i],M[i],roads[i],soldiers[i]);
        cout << ans << endl;
    }

    return 0;
}
