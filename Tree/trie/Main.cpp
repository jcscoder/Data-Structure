#include "dictionary.h"

int main() {
	Dictionary dictionary;
	string cmd;
	while (true) {
		cout << ">>>";
		cin >> cmd;
		if (cmd == "") continue;
		else if (cmd == "add") {
			string word;
			cin >> word;
			dictionary.addWord(word);
		}
		else if (cmd == "search") {
			cin >> cmd;
			if (cmd == "--f" || cmd == "--format") {
				string format;
				cin >> format;
				cout << (dictionary.search(format) ? "Yes" : "No") << endl;
			}
			else if (cmd == "--p" || cmd == "--prefix") {
				string format;
				cin >> format;
				cout << (dictionary.searchPrefix(format) ? "Yes" : "No") << endl;
			}
		}
		else if (cmd == "list") {
			cin >> cmd;
			if (cmd == "--f" || cmd == "--format") {
				string format;
				cin >> format;
				vector<string> words;
				dictionary.list(format, words);
				for (string word : words)
					cout << word << endl;
				words.clear();
				vector<string>().swap(words);
			}
			else if (cmd == "--p" || cmd == "--prefix") {
				string format;
				cin >> format;
				vector<string> words;
				dictionary.listPrefix(format, words);
				for (string word : words)
					cout << word << endl;
				words.clear();
				vector<string>().swap(words);
			}
			else if (cmd == "--a" || cmd == "--all") {			
				vector<string> words;
				dictionary.listAll(words);
				for (string word : words)
					cout << word << endl;
				words.clear();
				vector<string>().swap(words);
			}
		}
		else if (cmd == "remove") {
			cin >> cmd;
			if (cmd == "--f" || cmd == "--format") {
				string format;
				cin >> format;	
				dictionary.remove(format);
			}
			else if (cmd == "--p" || cmd == "--prefix") {
				string format;
				cin >> format;
				dictionary.removePrefix(format);
			}
			else if (cmd == "--a" || cmd == "--all") {
				dictionary.removeAll();
			}
		}
		else if (cmd == "size") {
			cout << dictionary.size() << endl;
		}
		else break;
	}
	return 0;
}