//============================================================================
// Reader.cpp
// By Pedro Garate
// on 01/19/2015
// Description : Reads in a paragraph of English text up to 100 words from the
// keyboard. Identifies the most frequent letter (case insensitive) and
// calculates the frequency of each unique word (case insensitive).
//============================================================================

#include <iostream>
#include <string>

using namespace std;

void getFreqLetter(string paragraph);
void countWordFreq(string paragraph);

bool found = false;
struct wordFreq {
	string word;
	int count;
};

int main() {
	string paragraph;
	cout << "Enter your paragraph (please limit your input "
		"to 100 words):" << endl;
	getline(cin, paragraph);

	getFreqLetter(paragraph);
	cout << endl;
	countWordFreq(paragraph);

	return 0;
}

void getFreqLetter(string paragraph) {
	//each address number represents one distinct ASCII character
	int counter[256] = { 0 };
	int max = 1;

	for (unsigned int i = 0; i<paragraph.size(); i++) {
		// increment bye one the number (data) corresponding to the address
		counter[(unsigned char)paragraph[i]]++;
	}

	// to make it case insensitive convert all A-Z to a-z
	for (int j = 65; j<91; j++) {
		counter[j + 32] += counter[j];
	}

	// determine the max number
	for (int k = 97; k<123; k++) {
		if (counter[k]>max)
			max = counter[k];
	}

	cout << endl;

	for (int l = 97; l<123; l++) {
		if (counter[l] == max) {
			cout << "The most frequent letter is: \"" <<
				(unsigned char)l << "\". It appears " <<
				max << " times." << endl;
			found = true;
		}
	}
	if (found == false) cout << "There are no letters."; //no letters in the input.

}

void countWordFreq(string paragraph) {
	if (found == false)
		return;

	wordFreq freqWords[100];
	// to store each word before putting it into the wordFreq.word[position]
	string temp = "";
	int wordCnt = 0; // how many words we have

	for (unsigned int i = 0; i<paragraph.size(); i++) {
		int c = (unsigned char)paragraph[i];

		//only use letters a-z. If A-Z found convert to a-z
		if (c >= 65 && c <= 90) { // A-Z
			temp.string::push_back(c + 32);
		}
		if (c >= 97 && c <= 122) { // a-z
			temp.string::push_back(c);
		}

		if ((c<65 || c>90) && (c<97 || c>122)) { // non-alphanumeric
			if (temp != "") {
				for (int i = 0; i<wordCnt; i++){
					if (temp == freqWords[i].word) {
						freqWords[i].count++;
						temp = "";
					}
				}
				if (temp != "") {
					freqWords[wordCnt].word = temp;
					freqWords[wordCnt].count = 1;
					temp = "";
					wordCnt++;
				}
			}
		}
	}
	// last check if the last word is not followed by any character
	if (temp != "") {
		for (int i = 0; i<wordCnt; i++){
			if (temp == freqWords[i].word) {
				freqWords[i].count++;
				temp = "";
			}
		}
		if (temp != "") {
			freqWords[wordCnt].word = temp;
			freqWords[wordCnt].count = 1;
			temp = "";
			wordCnt++;
		}
	}

	cout << "Here is the list of the words used and their frequencies:" << endl;
	cout << endl << "TIMES" << "\tWORD" << endl;
	for (int j = 0; j<wordCnt; j++) {
		cout << freqWords[j].count << "\t" << freqWords[j].word << endl;
	}
}
