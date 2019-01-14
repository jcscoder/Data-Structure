#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define N_LETTERS 26
#define TO_INDEX(c) (c - 'a')
#define TO_CHAR(i) ((char)(i + 'a'))
#define IS_UPPERCASE(c) (c >= 'A' && c <= 'Z')
#define IS_LOWERCASE(c) (c >= 'a' && c <= 'z')
#define IS_LETTER(c) (IS_LOWERCASE(c) || IS_UPPERCASE(c))
#define TO_LOWERCASE(c) (c + 'a' - 'A')
#define DOT '.'

typedef struct TNode {
	char value;
	int num;
	bool isWordEnd;
	struct TNode ** subtrees;
	TNode(char value) : value(value), num(0), isWordEnd(false) {
		subtrees = new struct TNode*[N_LETTERS];
		for (int i = 0; i < N_LETTERS; i++)
			subtrees[i] = NULL;
	}
	~TNode() { free(subtrees); }
} *Tree;

class Dictionary {
public:
	Dictionary();
	~Dictionary();

	/* Adds a word into the dictionary. */
	void addWord(string word);

	//In the following functions, a dot character '.' in the string passed in can represent any one letter.
	
	/* Returns true if the word is in the dictionary. */
	bool search(string format);

	/* Returns true if there is any word in the dictionary starts with the prefix passed in. */
	bool searchPrefix(string prefix);

	/* Lists all the words in the dictionary with the format passed in.*/
	void list(string format, vector<string>& result);

	/* Lists all the words in the dictionary start with the prefix passed in. */
	void listPrefix(string prefix, vector<string>& result);

	/* Lists all the words in the dictionary. */
	void listAll(vector<string>& result);

	/* Removes all the words in the dictionary with the format passed in. */
	bool remove(string format);

	/* Removes all the words in the dictionary start with the prefix passed in, */
	bool removePrefix(string prefix);

	/* Removes all the word in the dictionary. */
	void removeAll();
	
	/* Returns the size of the dictionary. */
	int size();

private:

	Tree root;

	bool recursive_search(Tree tree, string& word, int index, bool isSearchPrefix);

	void recursive_list(Tree tree, string& format, vector<char>& word, vector<string>& result, int index, bool isListPrefix);
	void dfsList(Tree tree, vector<char>& word, vector<string>& result);		
	string tostring(vector<char>& word);

	bool recursive_remove(Tree tree, string& format, vector<Tree>& wordTree, int index, bool isRemovePrefix);
	void dfsRemove(Tree tree, vector<Tree>& wordTree);
	void dfsRemoveAll(Tree tree);
	void removeWordTree(vector<Tree>& wordTree);

	void deleteTree(Tree tree);
};
