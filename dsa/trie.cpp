#include <iostream>
#include <vector>
using namespace std;

class Trie {
    struct node {
        vector<bool> isword;
        vector<node *> next;
        node() : isword(vector<bool>(26, false)), next(vector<node *>(26, nullptr)){};
    };
    node *root;

public:
    Trie() {
        root = new node();
        for (int i = 0; i < 26;i++) {
            root->isword[i] = true;
        }
    }

    void insert(string s) {
        auto temp = root;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            int ind = s[i] - 'a';
            if (temp->next[ind]==nullptr) {
                temp->next[ind] = new node();
            }
            temp = temp->next[ind];
        }

        temp->isword[s[n - 1] - 'a'] = true;
    }

    bool isPrefix(string prefix) {
        auto temp = root;
        for (int i = 0; i < prefix.length();i++) {
            int ind = prefix[i] - 'a';
            if (temp->next[ind] == nullptr)
            {
                return false;
            }
            temp = temp->next[ind];
        }

        return true;
    }

    bool isWord(string word) {
        auto temp = root;
        int n = word.length();
        for (int i = 0; i < n; i++)
        {
            int ind = word[i] - 'a';
            if (temp->next[ind] == nullptr)
            {
                return false;
            }
            temp = temp->next[ind];
        }

        if(temp->isword[word[n-1]-'a']) {
            return true;
        }

        return false;
    }
};

int main() {
    Trie* t = new Trie();
    t->insert("abc");
    if(t->isPrefix("abd"))
        cout << "prefix match incorrect" << endl;
    if(t->isPrefix("ab"))
        cout << "prefix match correct" << endl;
    if(t->isWord("abc"))
        cout << "word match correct" << endl;
    if(t->isWord("ab"))
        cout << "word match incorrect" << endl;
}