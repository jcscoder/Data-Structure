#include "dictionary.h"

Dictionary::Dictionary() : root(new TNode(' ')) {

}

Dictionary::~Dictionary() {
	deleteTree(root);
}

int Dictionary::size() {
	return root->num;
}


//add word
void Dictionary::addWord(string word) {
	Tree tree = root;
	for (int i = 0; i < word.size(); i++) {
		if (!IS_LETTER(word[i])) return;
		if (IS_UPPERCASE(word[i])) word[i] = TO_LOWERCASE(word[i]);
		if (tree->subtrees[TO_INDEX(word[i])] == NULL)
			tree->subtrees[TO_INDEX(word[i])] = new TNode(word[i]);
		tree->num++;
		tree = tree->subtrees[TO_INDEX(word[i])];
	}
	tree->num++;
	tree->isWordEnd = true;
}


//search word
bool Dictionary::search(string format) {
	for (int i = 0; i < format.size(); i++)
		if (!IS_LETTER(format[i]) && format[i] != DOT) return false;
	return recursive_search(root, format, 0, false);
}

bool Dictionary::searchPrefix(string prefix) {
	for (int i = 0; i < prefix.size(); i++)
		if (!IS_LETTER(prefix[i]) && prefix[i] != DOT) return false;
	return recursive_search(root, prefix, 0, true);
}

bool Dictionary::recursive_search(Tree tree, string & format, int index, bool isSearchPrefix) {
	for (int i = index; i < format.size(); i++) {
		if (IS_LETTER(format[i])) {
			if (IS_UPPERCASE(format[i])) format[i] = TO_LOWERCASE(format[i]);
			if (tree->subtrees[TO_INDEX(format[i])] == NULL || tree->subtrees[TO_INDEX(format[i])]->num == 0) return false;
			tree = tree->subtrees[TO_INDEX(format[i])];
		}
		else if (format[i] == DOT) {
			for (int j = 0; j < N_LETTERS; j++) 
				if (tree->subtrees[j] != NULL && tree->subtrees[j]->num != 0) {
					if (recursive_search(tree->subtrees[j], format, i + 1, isSearchPrefix)) return true;
				}
			return false;
		}
		else return false;
	}
	if (isSearchPrefix)
		return true;
	else
		return tree->isWordEnd;
}


//list word
void Dictionary::list(string format, vector<string>& result) {
	for (int i = 0; i < format.size(); i++) {
		if (!IS_LETTER(format[i]) && format[i] != DOT) return;		
	}
	vector<char> word;
	recursive_list(root, format, word, result, 0, false);
	word.clear();
	vector<char>().swap(word);	
}

void Dictionary::listPrefix(string prefix, vector<string>& result) {
	for (int i = 0; i < prefix.size(); i++) {
		if (!IS_LETTER(prefix[i]) && prefix[i] != DOT) return;
	}
	vector<char> word;
	recursive_list(root, prefix, word, result, 0, true);
	word.clear();
	vector<char>().swap(word);
}

void Dictionary::listAll(vector<string>& result) {
	vector<char> word;
	dfsList(root, word, result);
	word.clear();
	vector<char>().swap(word);
}

void Dictionary::recursive_list(Tree tree, string & format, vector<char>& word, vector<string>& result, int index, bool isListPrefix) {
	for (int i = index; i < format.size(); i++) {
		if (IS_LETTER(format[i])) {
			if (IS_UPPERCASE(format[i])) format[i] = TO_LOWERCASE(format[i]);
			if (tree->subtrees[TO_INDEX(format[i])] == NULL || tree->subtrees[TO_INDEX(format[i])]->num == 0) return;
			tree = tree->subtrees[TO_INDEX(format[i])];
			word.push_back(format[i]);
		}
		else if (format[i] == DOT) {
			for (int j = 0; j < N_LETTERS; j++) 
				if (tree->subtrees[j] != NULL && tree->subtrees[j]->num != 0) {
					int tmp_size = word.size();
					word.push_back(TO_CHAR(j));
					recursive_list(tree->subtrees[j], format, word, result, i + 1, isListPrefix);
					while (word.size() > tmp_size) word.pop_back();
				}
			return;
		}
		else return;
	}
	if (isListPrefix) {
		dfsList(tree, word, result);
	}
	else if (tree->isWordEnd) {
		string word_str = tostring(word);
		result.push_back(word_str);
	}
}

void Dictionary::dfsList(Tree tree, vector<char>& word, vector<string>& result) {
	if (tree == NULL) return;
	if (tree->isWordEnd) {
		string word_str = tostring(word);
		result.push_back(word_str);
	}
	for (int i = 0; i < N_LETTERS; i++)
		if (tree->subtrees[i] != NULL && tree->subtrees[i]->num != 0) {
			word.push_back(TO_CHAR(i));
			dfsList(tree->subtrees[i], word, result);
			word.pop_back();
		}
}

string Dictionary::tostring(vector<char>& word) {
	string word_str = "";
	for (auto it = word.begin(); it != word.end(); it++)
		word_str += (*it);
	return word_str;
}


//remove word

bool Dictionary::remove(string format) {
	for (int i = 0; i < format.size(); i++)
		if (!IS_LETTER(format[i]) && format[i] != DOT) return false;
	vector<Tree> wordTree;
	bool result = recursive_remove(root, format, wordTree, 0, false);
	wordTree.clear();
	vector<Tree>().swap(wordTree);
	return result;
}

bool Dictionary::removePrefix(string prefix) {
	for (int i = 0; i < prefix.size(); i++)
		if (!IS_LETTER(prefix[i]) && prefix[i] != DOT) return false;
	vector<Tree> wordTree;
	bool result = recursive_remove(root, prefix, wordTree, 0, true);
	wordTree.clear();
	vector<Tree>().swap(wordTree);
	return result;
}

void Dictionary::removeAll() {
	dfsRemoveAll(root);
}

bool Dictionary::recursive_remove(Tree tree, string & format, vector<Tree>& wordTree, int index, bool isRemovePrefix) {
	if (tree == root) wordTree.push_back(root);
	for (int i = index; i < format.size(); i++) {		
		if (IS_LETTER(format[i])) {
			if (IS_UPPERCASE(format[i])) format[i] = TO_LOWERCASE(format[i]);
			if (tree->subtrees[TO_INDEX(format[i])] == NULL || tree->subtrees[TO_INDEX(format[i])]->num == 0) return false;	
			tree = tree->subtrees[TO_INDEX(format[i])];
			wordTree.push_back(tree);
		}
		else if (format[i] == DOT) {
			bool removeSuccess = false;
			for (int j = 0; j < N_LETTERS; j++) 
				if (tree->subtrees[j] != NULL && tree->subtrees[j]->num != 0) {
					int tmp_size = wordTree.size();
					wordTree.push_back(tree->subtrees[j]);				
					if (recursive_remove(tree->subtrees[j], format, wordTree, i + 1, isRemovePrefix)) 
						removeSuccess = true;
					while (wordTree.size() > tmp_size) wordTree.pop_back();
				}
			return removeSuccess;
		}
		else return false;
	}
	if (isRemovePrefix) {
		dfsRemove(tree, wordTree);
	}
	else {
		if (!tree->isWordEnd) return false;
		removeWordTree(wordTree);
		return true;
	}
}

void Dictionary::dfsRemove(Tree tree, vector<Tree>& wordTree) {
	if (tree == NULL) return;
	if (tree->isWordEnd) {
		removeWordTree(wordTree);
	}
	for (int i = 0; i < N_LETTERS; i++) 
		if (tree->subtrees[i] != NULL && tree->subtrees[i]->num != 0) {
			wordTree.push_back(tree->subtrees[i]);
			dfsRemove(tree->subtrees[i], wordTree);
			wordTree.pop_back();
		}	
}

void Dictionary::removeWordTree(vector<Tree>& wordTree) {
	for (auto it = wordTree.begin(); it != wordTree.end(); it++) {
		(*it)->num--;
		if (it == wordTree.end())
			(*it)->isWordEnd = false;
	}
}

void Dictionary::dfsRemoveAll(Tree tree) {
	if (tree == NULL) return;
	tree->num = 0;
	tree->isWordEnd = false;
	for (int i = 0; i < N_LETTERS; i++)
		if (tree->subtrees[i] != NULL && tree->subtrees[i]->num != 0)
			dfsRemoveAll(tree->subtrees[i]);
}

void Dictionary::deleteTree(Tree tree) {
	if (tree == NULL) return;
	for (int i = 0; i < N_LETTERS; i++)
		if (tree->subtrees[i] != NULL)
			deleteTree(tree->subtrees[i]);
	delete tree;
}