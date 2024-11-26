#include <iostream>
#include <vector>
using namespace std;

// Function to compute the LPS array for the given pattern
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int length = 0;  // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    for (int i = 1; i < pattern.size(); i++) {
        while (length > 0 && pattern[i] != pattern[length]) {
            length = lps[length - 1];
        }
        if (pattern[i] == pattern[length]) {
            length++;
        }
        lps[i] = length;
    }
}

// KMP algorithm to search for the pattern in the given text
void KMPSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);

    // Preprocess the pattern to create the LPS array
    computeLPSArray(pattern, lps);

    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << "\n";
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "Text: " << text << "\n";
    cout << "Pattern: " << pattern << "\n";
    KMPSearch(text, pattern);

    return 0;
}

