#include<iostream>
#include <vector>
using namespace std;

struct MyNode
{    
    bool flag = false;
    MyNode* links[26];
    bool hasKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void putNode(char ch, MyNode* newNode) {
         links[ch - 'a'] = newNode; 
    }

    MyNode* getLink(char ch) {
        return links[ch-'a'];
    }

    void markEnd() {
        flag = true; 
    }

    bool seeEnd() {
        return flag; 
    }
};

class Mytrie{
private:
    MyNode* root;
public:
    Mytrie() {
        root = new MyNode();
    }   

    void insert(string word) {
        MyNode* node = root;
        for(int i = 0; i < word.size(); i++) {
            if(!(node->hasKey(word[i]))) {
                node->putNode(word[i], new MyNode()); 
            }
            node=node->getLink(word[i]);

        }
        node->markEnd();
    }
    
    bool search(string word) {
        MyNode* node = root;
        for(int i = 0; i < word.size(); i++) {
            if(node == nullptr || !(node->hasKey(word[i]))) {
                return false;
            }
            node = node->getLink(word[i]);
        }
        return node->seeEnd();
    }

    bool startsWith(string prefix) {
        MyNode* node = root;
        for(int i = 0; i < prefix.size(); i++) {
            if(!(node->hasKey(prefix[i]))) {
                return false;
            }
            node = node->getLink(prefix[i]);
        }
        return true;
    }

    void printHelper(vector<string> words) {
        cout << endl;
        for(string word : words) {
            cout << word << endl<<endl;
        }   
    }

    void FetchAllFromNode(MyNode* node, string prefix, vector<string> &allMatching) {
        if(node == nullptr) {
            return;
        }
        if(node->seeEnd()) {
            allMatching.push_back(prefix);
        }
        
        for(int i = 0; i < 26 ; i++) {
           if(node->links[i] != nullptr) {
            string updtd = prefix + ((char)('a'+i));
        // updtd.append;
            FetchAllFromNode(node->links[i], updtd, allMatching);
           }
        }

    }

    vector<string> getAllWordsInTrie() {
        vector<string> allWords;
        FetchAllFromNode(root, "", allWords);
        return allWords;
    }

    // Function to calculate the Levenshtein distance (distance or cost to convert s1 to s2 by editing characters (by insrt, del or subst))
    int checkLevenshteinDist(string& s1, string& s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1)); // dp[i][j] = min cost to transform (insrt del or subst) i chars of s1  to match with j char of s2 
        
        for (int j = 0; j <= n; ++j) dp[0][j] = j;
        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        
        /*
        ******************************************************************************
        s1 --> indexed using i   
        s2 --> indexed using j

        insrt: dp[i][j-1]: min cost to transform i char of s1 to match with j-1 chars of s2 
               then insrt a char into s1 to which is same as jth char of s2.
               Total cost :  ( cost of dp[i][j-1] + cost 1 for insert). 

        del:  dp[i-1][j] min cost to transform i-1 char of s1 to match with j chars of s2 
              then del ith char of s1 so that resultant s1 matches with s2. 
              Total cost : ( cost of dp[i-1][j] + cost 1 for delete ). 
. 
        subst: dp[i-1][j-1] min cost to transform i-1 chars of s1 to match with j-1 chars of s2 
               then replace(subst operation) ith char with same char as jth char of s2 if ith char != jth char (costs 1) otherwise if the last chars already same then cost 0
               Total cost : (cost of dp[i-1][j-1] + 0 or 1 depending on last chars (i and j))
         
        *******************************************************************************
        */

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1; // ith char means i-1 index
                dp[i][j] = min(dp[i - 1][j] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost)); // adding min cost among(cost by following operation insrt, del , subs)
            }
        }
        
        return dp[m][n];

        /*
            USING LCS (from s2 - lcs, if result <= 3 taking it)
                int a = s1.size();
                int b = s2.size();
                vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

                for (int i = 1; i <= a; ++i) {
                    for (int j = 1; j <= b; ++j) {
                        if (s1[i - 1] == s2[j - 1]) {
                            dp[i][j] = dp[i - 1][j - 1] + 1;
                        } else {
                            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                        }
                    }
                }
                return dp[a][b];
        */
       
    }

    void Autocomplete(string prefix) {
        MyNode* node = root;
        vector<string> allMatching;
        for(int i = 0; i < prefix.size(); i++) {
            if(node == nullptr || !(node->hasKey(prefix[i]))) {
                cout << allMatching.size() << endl;
                return;
            }
            node = node->getLink(prefix[i]);
        }
            if(node != nullptr) {
                FetchAllFromNode(node, (prefix), allMatching );
            }
        cout /*<< "Total AUTOCOMPLETED WORDS : "*/<< allMatching.size() << endl;
        printHelper(allMatching);
    }

    void Autocorrect(string query) {
        MyNode* node = root;
        vector<string> allCorrected;

        for(string word : getAllWordsInTrie()) {
            if(checkLevenshteinDist(query, word) <= 3) {
                allCorrected.push_back(word);
            }
        }
        cout /*<< "Total AUTOCOMPLETED WORDS : " */<<  allCorrected.size() << endl;
        printHelper(allCorrected);
    }
};


void operate(int op, string query, Mytrie tr) {
    switch (op) {
        case 1: // Spell Checking
            cout << (tr.search(query)? true : false) << endl;
            break;
        
        case 2: // Auto Completion
            tr.Autocomplete(query);
            break;

        case 3: // Auto Correction
            tr.Autocorrect(query);
            break;
        default:
            cout << "Your selected operation is incorrect!. Supported Op Codes: '1' '2' '3' "  << endl;
            break;
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    if ( n < 0 || q < 0) {
        cerr << " Please Enter n > 0 & q > 0 for some meaningful operation"<< endl;
        return 0;
    }

    if ( n == 0 && q == 0) {
        cerr << "you basically don't want to do any operation! "<< endl;
        return 0;
    }

    Mytrie tr;
    for(int i = 0; i< n ; i++) {
        string s;
        cin >> s;
        tr.insert(s);
    }
    vector<pair<int, string>> queries;
    for(int i = 0; i< q ; i++) {
        int op; 
        string s;
        cin >> op >> s;
        queries.push_back({op,s});
    }
    cout << endl <<"-------- OUTPUT --------"<< endl;
    for(int i = 0; i< q ; i++) {
        operate(queries[i].first, queries[i].second, tr);
    }
    return 0;
}

/**********************************************************************
 
        For compilation use below command
        g++ 2024201066_A1_Q2.cpp -o 'Executable File Name'

************************************************************************/