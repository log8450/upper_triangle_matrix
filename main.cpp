#include <iostream>

using namespace std;

int row;
int col;

double** matrix;
double** matrixElementary;
double** matrixResult;

void printMatrix() {			// ��Ʈ���� ����Լ�
	cout << "+";
	for (int i = 0; i < col; i++) {
		cout << "----------";
	}
	cout << "+" << endl;
	for (int i = 0; i < row; i++) {
		cout << "|";
		for (int j = 0; j < col; j++) {
			printf("%+9.3f ", matrix[i][j]);
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int i = 0; i < col; i++) {
		cout << "----------";
	}
	cout << "+" << endl;
}

void matrixMultiplication() {	// Elementary ��Ʈ���� ���� �Լ�
	double temp = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp = 0;
			for (int k = 0; k < row; k++) {
				temp += matrixElementary[i][k] * matrix[k][j];
			}
			matrixResult[i][j] = temp;
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matrix[i][j] = matrixResult[i][j];
		}
	}
}

void matrixReset() {			// Elemntary ��Ʈ������ E�� �����ϴ� �Լ� 
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (i == j) matrixElementary[i][j] = 1;
			else matrixElementary[i][j] = 0;
		}
	}
}

int main() {
	double temp;
	double multiplier;			// ���� ���꿡 ����� Elementary ��Ʈ�������� �� ������ ������ ��
	double multipliersunder;
	double multipliersabove;

	cout << "Upper Triangular Matrix ��ȯ �ý���" << endl << endl;
	cout << "��Ʈ������ �� ���� �Է����ּ��� : ";
	cin >> row;
	cout << "��Ʈ������ �� ���� �Է����ּ��� : ";
	cin >> col;

	matrix = new double* [row];
	matrixElementary = new double* [row];
	matrixResult = new double* [row];
	
	for (int i = 0; i < row; i++) {
		matrix[i] = new double[col];
		matrixElementary[i] = new double[row];
		matrixResult[i] = new double[col];
	}											// 2���� �迭 ����

	for (int i = 0; i < row; i++) {
		cout << i + 1 << "���� ���ҵ��� �����̽��ٷ� �����ؼ� �Է����ּ��� : ";
		for (int j = 0; j < col; j++) {
			cin >> matrix[i][j];
		}
	}											// ��Ʈ���� �Է¹ޱ�

	cout << endl << "Origin Matrix" << endl;

	printMatrix();

	for (int c = 0; c < row; c++) {
		for (int i = 1 + c; i < row; i++) {
			if (matrix[c][c] == 0) {			// �밢��Ұ� 0�� ��� �� ��ü
				for (int j = c; j < row; j++) {
					if (matrix[j][c] != 0) {
						cout << "��� ���� " << c + 1 << "��° �밢 ��Ұ� 0�̹Ƿ� " << j + 1 << "��� ��ü�մϴ�." << endl;
						for (int k = 0; k < col; k++) {
							temp = matrix[c][k];
							matrix[c][k] = matrix[j][k];
							matrix[j][k] = temp;
						}
						break;
					}
				}
			}
			if (matrix[c][c] == 0) {
				continue;
			}									// �ش� ���� �밢��� �Ʒ��� ��� 0�̹Ƿ� �������� continue

			multipliersunder = matrix[c][c];
			multipliersabove = matrix[i][c];
			multiplier = multipliersabove / multipliersunder;	// ��Ƽ�ö��̾� ����

			matrixReset();
			matrixElementary[i][c] = -multiplier;
			matrixMultiplication();
			// Elementary ��Ʈ������ �� ��Ҹ� �ٲ��ְ� ����
		}
	}
	
	cout << "Upper Triangle Result" << endl;
	printMatrix();
}