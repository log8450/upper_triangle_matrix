#include <iostream>

using namespace std;

int row;
int col;

double** matrix;
double** matrixElementary;
double** matrixResult;

void printMatrix() {			// 매트릭스 출력함수
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

void matrixMultiplication() {	// Elementary 매트릭스 곱셈 함수
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

void matrixReset() {			// Elemntary 매트릭스를 E로 리셋하는 함수 
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (i == j) matrixElementary[i][j] = 1;
			else matrixElementary[i][j] = 0;
		}
	}
}

int main() {
	double temp;
	double multiplier;			// 행의 연산에 사용할 Elementary 매트릭스에서 한 군데만 변형할 수
	double multipliersunder;
	double multipliersabove;

	cout << "Upper Triangular Matrix 변환 시스템" << endl << endl;
	cout << "매트릭스의 행 수를 입력해주세요 : ";
	cin >> row;
	cout << "매트릭스의 열 수를 입력해주세요 : ";
	cin >> col;

	matrix = new double* [row];
	matrixElementary = new double* [row];
	matrixResult = new double* [row];
	
	for (int i = 0; i < row; i++) {
		matrix[i] = new double[col];
		matrixElementary[i] = new double[row];
		matrixResult[i] = new double[col];
	}											// 2차원 배열 생성

	for (int i = 0; i < row; i++) {
		cout << i + 1 << "행의 원소들을 스페이스바로 구분해서 입력해주세요 : ";
		for (int j = 0; j < col; j++) {
			cin >> matrix[i][j];
		}
	}											// 매트릭스 입력받기

	cout << endl << "Origin Matrix" << endl;

	printMatrix();

	for (int c = 0; c < row; c++) {
		for (int i = 1 + c; i < row; i++) {
			if (matrix[c][c] == 0) {			// 대각요소가 0인 경우 행 교체
				for (int j = c; j < row; j++) {
					if (matrix[j][c] != 0) {
						cout << "계산 도중 " << c + 1 << "번째 대각 요소가 0이므로 " << j + 1 << "행과 교체합니다." << endl;
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
			}									// 해당 열의 대각요소 아래는 모두 0이므로 다음으로 continue

			multipliersunder = matrix[c][c];
			multipliersabove = matrix[i][c];
			multiplier = multipliersabove / multipliersunder;	// 멀티플라이어 설정

			matrixReset();
			matrixElementary[i][c] = -multiplier;
			matrixMultiplication();
			// Elementary 매트릭스의 한 요소만 바꿔주고 곱셈
		}
	}
	
	cout << "Upper Triangle Result" << endl;
	printMatrix();
}