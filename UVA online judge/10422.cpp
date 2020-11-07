// To find the problem, google uva 10422.
#include <bits/stdc++.h>

using namespace std; 

#define R 5
#define C 6

struct state {
    vector<string> config; 
    int r, c, l; 


    void print() {
        cout << "config: \n"; 
        for (auto e : config) 
            cout << e << endl;
        cout << r << " " << c << " " << l;
        cout << endl;
    }

    int dr[8] = {2, 2,-2,-2, 1,-1, 1,-1};
    int dc[8] = {1,-1, 1,-1, 2, 2,-2,-2};
    vector<state> generate() {
        vector<state> res; 
        for (int k=0; k<8; ++k) {
            int nr = r + dr[k]; 
            int nc = c + dc[k]; 

            if (nr<0 or nr>=R or nc<0 or nc>=C) continue; 

            state next; 
            next.r = nr; 
            next.c = nc; 
            next.l = l+1; 
            next.config = config;
            swap(next.config[r][c], next.config[nr][nc]); 

            res.push_back(next); 
        }
        return res; 
    }
};



struct problem {
    state root;  
    vector<string> tar_config = { "11111", "01111", "00 11", "00001", "00000" };


    // read the initial state of the board
    void init () {
        char tmp[R][C]; 
        for (int i=0; i<5; ++i) gets(tmp[i]); 
        
        root.config.resize(5); 
        for (int i=0; i<5; ++i) {
            for (int j=0; j<5; ++j) {
                if (tmp[i][j] == ' ') 
                    root.r = i, 
                    root.c = j; 

                root.config[i].push_back(tmp[i][j]); 
            }
        }

        root.l = 0;    
        // root.print(); 
    }

    

    void solve() {
        int res = bfs(); 
        if (res>10) 
            puts("Unsolvable in less than 11 move(s).");
        else 
            printf("Solvable in %d move(s).\n",res);
    }

    int bfs() {
        queue<state> q; 
        set<vector<string>> st;

        q.push(root);
        st.insert(root.config); 

        while (!q.empty()) {
            state cur = q.front(); q.pop(); 
            if (cur.config == tar_config) 
                return cur.l; 
            if (cur.l == 10) 
                continue; 


            vector<state> next = cur.generate(); 
            for (auto pos : next) {
                if (st.count(pos.config)) continue; 
                st.insert(pos.config); 
                q.push(pos); 
            }
        }   
        return 11; 
    }

    
};


int 
main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
    clock_t START_TIME = clock();
#endif 


    int tc; 
    scanf("%d", &tc); 
    getchar(); 
    while (tc--) {
        problem p; 
        p.init(); 
        p.solve(); 
    }
    




#ifndef ONLINE_JUDGE
    cout << endl << "// Time taken = " << fixed << setprecision(5)  << (clock() - START_TIME) * 1e3 / CLOCKS_PER_SEC << " ms";
#endif
    return 0;
}
