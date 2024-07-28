#include "functions.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#include "role.h"
#include "user.h"

using namespace std;

namespace functions {
    const int INF = 1e9;

    vector<User> DistributeMMRGreedy(vector<User>& users) {
        sort(users.begin(), users.end(),
             [](const User& a, const User& b) {
                return a.mmr < b.mmr;
             });
        
        int to_skip = users.size() % 10;
        vector<vector<pair<int, int>>> g(users.size() + 2);
        for(int from = 0; from <= users.size(); from++) {
            for(int to = from + 2; to - from - 2 <= to_skip && to <= users.size(); to++) {
                g[from].push_back({to, users[to - 1].mmr - users[to - 2].mmr});
            }
        }
        for(int i = users.size(); users.size() - i <= to_skip; i--) {
            g[i].push_back({users.size() + 1, 0});
        }

        int n = g.size();
	    int s = 0; // first vertex
	    vector<vector<int>> d(n, vector<int>(to_skip + 1, INF)),  p(n, vector<int>(to_skip + 1));
        for(int i = 0; i <= to_skip; i++)
	        d[s][i] = 0;
	    set<tuple<int, int, int>> q; // {dist, to, skiped}
	    q.insert(make_tuple(d[s][0], s, 0));
	    while (!q.empty()) {
		    int v, dist, skipped;
            tie(dist, v, skipped) = *q.begin();
		    q.erase(q.begin());
 
		    for (int j = 0; j < g[v].size(); j++) {
		    	int to = g[v][j].first,
		    		len = g[v][j].second,
                    skip = skipped + max(to - v - 2, 0);
		    	if (skip <= to_skip && d[v][skipped] + len < d[to][skip]) {
		    		q.erase(make_tuple(d[to][skip], to, skip));
		    		d[to][skip] = d[v][skipped] + len;
		    		p[to][skip] = v;
		    		q.insert(make_tuple(d[to][skip], to, skip));
		    	}
		    }
	    }

        vector<User> result;
        int skipped = to_skip,
            v = users.size() + 1;
        while(v != 0) {
            int a = p[v][skipped];
            skipped -= max(v - a - 2, 0);
            v = a;

            if(v) {
                result.push_back(users[v - 1]);
                result.push_back(users[v - 2]);
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }
    
    vector<User> DistributeRolesGreedy(vector<User>& users, const vector<Role>& roles) {
        int users_in_role = users.size() / 10 * 2;
        int total_roles = roles.size();

        sort(users.begin(), users.end(),
             [](const User& a, const User& b) {
                return a.mmr < b.mmr;
             });

        vector<vector<User>> distribution(total_roles);
        vector<char> used(users.size());
        for(int prior = 0; prior < total_roles; prior++) {
            for(Role role : roles) {
                if(distribution[static_cast<int>(role)].size() == users_in_role)
                    continue;

                for(int i = 0; i < users.size(); i++) {
                    if(used[i] || users[i].roles[prior] != role)
                        continue;
                    if(distribution[static_cast<int>(role)].size() == users_in_role)
                        break;
                    users[i].role = role;
                    distribution[static_cast<int>(role)].push_back(users[i]);
                }
            }
        }

        vector<User> result;
        for(int i = 0; i < total_roles; i++) {
            result.insert(result.end(), distribution[i].begin(), distribution[i].end());
        }

        return result;
    }

} // namespace functions
