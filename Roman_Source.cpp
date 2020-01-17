#include <string>
#include <vector>
#include <cmath>

std::vector<int> split_number(int nNumber) {
	std::vector<int> vDigits;

	while (nNumber) {
		int nRem = nNumber % 10;
		nNumber -= nRem;
		nNumber /= 10;
		vDigits.push_back(nRem);
	}

	int nMiddle = vDigits.size() / 2;
	for (int i = 0, j = vDigits.size() - 1; i < nMiddle; i++, j--) {
		int nTemp = vDigits[i];
		vDigits[i] = vDigits[j];
		vDigits[j] = nTemp;
	}

	int nIndex = vDigits.size() - 1;
	for (int& n : vDigits)
		n *= pow(10, nIndex--);
	return vDigits;
}

bool excess(const std::string& sStr) {
	for (char c : sStr) {
		int nCount = 0;

		for (char d : sStr)
			if (c == d)
				nCount++;
		
		if (nCount > 3)
			return true;
	}
	return false;
}

std::string number_to_roman(int nNumber) {
	std::vector<std::pair<char, int> > vRoma { 
          std::pair<char, int>{'I', 1}, 
          std::pair<char, int>{'V', 5},
          std::pair<char, int>{'X', 10},
          std::pair<char, int>{'L', 50},
          std::pair<char, int>{'C', 100},
          std::pair<char, int>{'D', 500},
          std::pair<char, int>{'M', 1000}};

	std::string sRoma = "";

	int nCopy = nNumber;
	while (nCopy) {
		for (int i = vRoma.size() - 1; i >= 0; i--) {
			if (nCopy >= vRoma[i].second) {
				sRoma += vRoma[i].first;
				nCopy -= vRoma[i].second;
				break;
			}
		}
	}

	if (excess(sRoma)) {
		sRoma = "";
		char cPre, cPost;

		int nIndex;
		for (int i = 0; i < vRoma.size(); i++)
			if (vRoma[i].second > nNumber) {
				cPost = vRoma[i].first;
				nIndex = i;
				break;
			}
		
		for (int i = 0; i < vRoma.size(); i++)
			if (vRoma[nIndex].second - vRoma[i].second == nNumber)
				cPre = vRoma[i].first;
		
		sRoma += cPre;
		sRoma += cPost;
	}
	return sRoma;
}

std::string roman(int nNumber) {
	std::string sRoma = "";

	std::vector<int> vSplit = split_number(nNumber);

	for (int n : vSplit) {
		sRoma += number_to_roman(n);
	}

	return sRoma;
}

//###########################test##############################

#include <iostream>

int main() {
  std::cout << roman(1934) << '\n';
}

//######################end_test##############################
