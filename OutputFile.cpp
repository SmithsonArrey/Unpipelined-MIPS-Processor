#include <fstream>
#include <iostream>
using namespace std;

struct reg{
	string name;
	string usage;
	//int32_t number; //Register number is the index of the register in the register_block
	int32_t data;
};

void OutputFile(string filename, int numOfIns, reg* regList) {
	ofstream fout(filename);
	int cc = 0; // clock cycle count
	for (int i = 0; i < numOfIns; i++) {
		fout << "C#" << cc++ << " I" << i + 1 << "-IF" << endl;
		fout << "C#" << cc++ << " I" << i + 1 << "-ID" << endl;
		fout << "C#" << cc++ << " I" << i + 1 << "-EX" << endl;
		/*if ()
			fout << "C#" << cc++ << " I" << i + 1 << "-MEM" << endl;
		if()
			fout << "C#" << cc++ << " I" << i + 1 << "-WB" << endl;*/
	}
	/*fout << "REGISTERS" << endl;
	for () {

	}

	fout << "MEMORY" << endl;
	for () {

	}*/
	fout.close();
}

int main() {
	OutputFile("output.txt", 6);
}