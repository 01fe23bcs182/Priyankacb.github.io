"Job Search using the Knuth-Morris-Pratt (KMP) String Matching Algorithm"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute the longest prefix suffix (LPS) array
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int length = 0;
    int i = 1;
    lps[0] = 0; // lps[0] is always 0

    while (i < pattern.size()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP string matching algorithm
vector<int> KMPSearch(const string& text, const string& pattern) {
    int textLength = text.size();
    int patternLength = pattern.size();
    vector<int> lps(patternLength, 0);
    vector<int> matchPositions;

    computeLPSArray(pattern, lps);

    int i = 0, j = 0;
    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == patternLength) {
            matchPositions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return matchPositions;
}

int main() {
    string jobDatabase, searchQuery;
    cout << "Enter the job descriptions (single string): ";
    getline(cin, jobDatabase);
    cout << "Enter the search query: ";
    getline(cin, searchQuery);

    vector<int> results = KMPSearch(jobDatabase, searchQuery);

    if (!results.empty()) {
        cout << "Search query found at positions: ";
        for (int pos : results) {
            cout << pos << " ";
        }
        cout << endl;
    } else {
        cout << "Search query not found in the job descriptions.\n";
    }

    return 0;
}
