#include <iostream>

using namespace std;

const int VNUM = 10;
const int VDIM = 10;

struct vector_t {
	int id;
	int dim;
	int value[VDIM];
};

vector_t* vArray() {
	static vector_t vArray[VNUM];
	for (int i = 0; i < VNUM; i++) {
		vArray[i].id = -1;
	}
	return vArray;
}

vector_t* vRead(vector_t vArray[VNUM]) {
	int id;
	cin >> id;
	vArray[id].id = id;
	cin >> vArray[id].dim;
	for (int i = 0; i < vArray[id].dim; i++) {
		cin >> vArray[id].value[i];
	}
	return vArray;
}

void vPrint(vector_t vArray[VNUM]) {
	int id;
	cin >> id;
	if (vArray[id].dim == NULL) {
		cerr << "ERROR: UNINITIALIZED VECTOR USED" << endl;
		exit(-1);
	}
	cout << id << ": ";
	for (int i = 0; i < vArray[id].dim; i++) {
		cout << vArray[id].value[i] << " ";
	}
	cout << endl;
}

vector_t* vSelect(vector_t vArray[VNUM]) {
	int id[3];
	static vector_t operands[3];
	for (int i = 0; i < 3; i++) {
		cin >> id[i];
		operands[i] = vArray[id[i]];
	}
	operands[0].id = id[0];
	if (operands[1].dim == NULL || operands[2].dim == NULL) {
		cerr << "ERROR: UNINITIALIZED VECTOR USED" << endl;
		exit(-1);
	}
	if (operands[1].dim == operands[2].dim || operands[2].dim == 1) {
		operands[0].dim = operands[1].dim;
	}
	else {
		operands[0].dim = operands[2].dim;
	}
	return operands;
}

vector_t* vCompute(vector_t vArray[VNUM],char op) {
	vector_t* opers = vSelect(vArray);
	if (opers[1].dim != opers[2].dim) {
		cerr << "ERROR: IMPROPER OPERANDS" << endl;
		exit(0);
	}
	for (int j = 0; j < opers[0].dim; j++) {
		if (op == '+') {
			opers[0].value[j] = (opers[1].value[j]) + (opers[2].value[j]);
		}
		else if (op == '-') {
			opers[0].value[j] = (opers[1].value[j]) - (opers[2].value[j]);
		}
		else if (op == '*') {
			if (opers[1].dim== opers[2].dim) {
				opers[0].value[j] = (opers[1].value[j]) * (opers[2].value[j]);
			}
			else {
				if (opers[1].dim == 1) {
					opers[0].value[j] = opers[2].value[j] * opers[1].value[0];
				}
				else {
					opers[0].value[j] = opers[1].value[j] * opers[2].value[0];
				}
			}
		}
	}
	vArray[opers[0].id] = opers[0];
	return vArray;
}

vector_t* vDotProd(vector_t vArray[VNUM]) {
	vector_t* opers = vSelect(vArray);
	if (opers[1].dim != opers[2].dim) {
		cerr << "ERROR: IMPROPER OPERANDS" << endl;
		exit(0);
	}
	opers[0].dim = 1;
	for (int i = 0; i < opers[1].dim; i++) {
		opers[0].value[0] = opers[0].value[0] + (opers[1].value[i] * opers[2].value[i]);
	}
	vArray[opers[0].id] = opers[0];
	return vArray;
}

vector_t* vCrossProd(vector_t vArray[VNUM]) {
	vector_t* opers = vSelect(vArray);
	if (opers[1].dim != 3 || opers[2].dim != 3) {
		cerr << "ERROR: IMPROPER OPERANDS" << endl;
		exit(0);
	}
	opers[0].dim = 3;
	opers[0].value[0] = opers[1].value[1] * opers[2].value[2] - opers[1].value[2] * opers[2].value[1];
	opers[0].value[1] = opers[1].value[0] * opers[2].value[2] - opers[1].value[2] * opers[2].value[0];
	opers[0].value[2] = opers[1].value[0] * opers[2].value[1] - opers[1].value[1] * opers[2].value[0];
	vArray[opers[0].id] = opers[0];
	return vArray;
}

void calc() {
	char op[3];
	vector_t* vectors = vArray();
	while (true) {
		cin >> op;
		if (op[0] == '>') {
			vectors = vRead(vectors);
		}
		if (op[0] == '<') {
			vPrint(vectors);
		}
		if (op[0] == '+') {
			vectors = vCompute(vectors,op[0]);
		}
		if (op[0] == '-') {
			vectors = vCompute(vectors, op[0]);
		}
		if (op[0] == '*') {
			vectors = vCompute(vectors, op[0]);
		}
		if (op[0] == '.') {
			vectors = vDotProd(vectors);
		}
		if (op[0] == 'x') {
			vectors = vCrossProd(vectors);
		}
	}
}

int main() {
	calc();
	return 1;
}
