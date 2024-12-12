#include "criss_cross.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <clocale>
#include <algorithm>
#include <conio.h>
#include <cctype>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#define N 1000
using namespace std;
#define Matrix_symbol ' '

ofstream outFile;

int countWordsWithMaxChars(const std::vector<std::string>& words) {
	if (words.empty()) {
		return 0;
	}

	int maxChars = 0;
	for (const std::string& word : words) {
		if (word.length() > maxChars) {
			maxChars = word.length();
		}
	}

	int count = 0;
	for (const std::string& word : words) {
		if (word.length() == maxChars) {
			count++;
		}
	}

	std::cout << "Наиболее длинные слова: ";
	for (const std::string& word : words) {
		if (word.length() == maxChars) {
			std::cout << word << " ";
		}
	}
	std::cout << "\n";

	return count;
}

void moveToFront(std::vector<std::string>& vec, size_t index) {
	if (index >= vec.size()) return; // Обработка ошибки: индекс вне диапазона
	std::rotate(vec.begin(), vec.begin() + index, vec.begin() + index + 1);
}

void start(char* words, char* outputFile) {
	outFile = ofstream(outputFile);
	if (!outFile) {
		cerr << "Ошибка при открытии файла!" << endl;
		return;
	}
	vector<string> Array;
	cout << "Введённые слова:" << endl;
	//input(Array);
	///*
	//char words[] = "C:/Users/user/Desktop/university/3 семестр/ОП/kursach1/words.txt";
	int correct_words_input = input_from_file(Array, words);
	if (correct_words_input == -1) {
		cout << "Маловато слов, нужно добавить ещё" << endl;
		return;
	}
	if (correct_words_input == -2) {
		cout << "Ошибка! Неправильный ввод слов. Введите снова" << endl;
		return;
	}
	if (correct_words_input == -3) {
		cout << "Маловато слов, нужно добавить ещё" << endl;
		return;
	}
	//*/
	unique_check(Array);
	words_sort(Array);
	output(Array);

	int maxLenNumber = countWordsWithMaxChars(Array);
	std::cout << "Количество слов с максимальным количеством символов в массиве: " << maxLenNumber << std::endl;

	for (int i = 0; i < maxLenNumber; i++) {
		moveToFront(Array, maxLenNumber - 1);

		crisscross_versions a(Array.size());
		char** mtx_main;
		mtx_main = a.making_matrix(Array);
		a.making_crisscross(Array, mtx_main);
		crisscross_reduction(mtx_main, max_size(Array) * max_size(Array) + 2, max_size(Array) * max_size(Array) + 2);
		delete_matrix(mtx_main, max_size(Array) * max_size(Array) + 2);
	}
}

void words_sort(vector<string>& Array) {
	for (size_t i = 0; i < Array.size() - 1; i++) {
		for (size_t j = 0; j < Array.size() - 1 - i; j++) {
			if (Array[j].size() < Array[j + 1].size())
				swap(Array[j], Array[j + 1]);
		}
	}
}

int isalpha_rus(char c) {
	if (c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я' || c == 'ё' || c == 'Ё')
		return 1;
	else if (isalpha(c))
		return 2;
	else
		return 0;
}

void caps_func_rus(vector<string>& Array) {
	int i = 0;
	int j = 0;

	char lower[] = { 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я' };
	char upper[] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };

	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array[i].size(); j++) {
			for (size_t k = 0; k < 34; k++)
				if (Array[i][j] == lower[k])
					Array[i][j] = upper[k];
		}
	}
}

int correct_insert_check(vector<string>& Array) {
	int err = 0;
	if (isalpha_rus(Array[0][0]) == 2) {
		for (size_t i = 0; i < Array.size(); i++) {
			for (size_t j = 0; j < Array[i].size(); j++) {
				if (isalpha_rus(Array[i][j]) != 2)
					err++;
			}
		}
	}
	if (isalpha_rus(Array[0][0]) == 1) {
		for (size_t i = 0; i < Array.size(); i++) {
			for (size_t j = 0; j < Array[i].size(); j++) {
				if (isalpha_rus(Array[i][j]) != 1)
					err++;
			}
		}
	}
	return err;
}

void caps_func(vector<string>& Array) {
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = 0; j < Array[i].size(); j++) {
			Array[i][j] = (char)toupper(Array[i][j]);
		}
	}
}

int max_size(vector<string>& Array) {
	vector<string> Arr = Array;
	for (size_t j = 0; j < Arr.size() - 1; j++) {
		for (size_t i = 0; i < Arr.size() - 1; i++) {
			if (Arr[i].size() < Arr[i + 1].size())
				swap(Arr[i], Arr[i + 1]);
		}
	}
	return Arr[0].size();
}

void output(vector<string>& Array) {
	for (auto i : Array)
	{
		cout << i << " ";
	}

	cout << endl;
}

int input_from_file(vector<string>& Array, char* words) {
	char Arr[255];
	char Tmp[N] = { 0 };
	int begin = 0;
	int end, count = 0;
	string s;
	ifstream file(words);
	while (getline(file, s)) {
		Array.push_back(s);
	}
	file.close();

	if (Array.size() < 2) {
		return -1;
	}
	if (correct_insert_check(Array) > 0) {
		return -2;
	}
	if (isalpha_rus(Array[0][0]) == 2)
		caps_func(Array);
	else if (isalpha_rus(Array[0][0]) == 1)
		caps_func_rus(Array);

	return 1;
}

void unique_check(vector<string>& Array) {
	for (size_t i = 0; i < Array.size(); i++) {
		for (size_t j = i + 1; j < Array.size(); j++) {
			if (Array[i] == Array[j]) {
				Array[j].clear();
				for (size_t z = j; z < Array.size() - 1; z++)
					Array[z] = Array[z + 1];
				Array.pop_back();
				j--;
			}
		}
	}
}

void delete_matrix(char** mtrx, size_t size) {
	for (size_t i = 0; i < size; i++) {
		delete[] mtrx[i];
	}
	delete[] mtrx;
}

char** crisscross_versions::making_matrix(vector<string>& Array) {
	int mtx_size = max_size(Array) * max_size(Array) + 2;
	char** Matrix = new char* [mtx_size];
	for (size_t i = 0; i < mtx_size; i++)
		Matrix[i] = new char[mtx_size];

	for (size_t i = 0; i < mtx_size; i++) {
		for (size_t j = 0; j < mtx_size; j++) {
			Matrix[i][j] = Matrix_symbol;
		}
	}
	return Matrix;
}

int check_words_crisscross_v2(string& Array_1, string& Array_2, int idx_symb) {
	int true_count = 0;
	int symb_address = 0;

	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);

	if (Array[0] != Array[1]) {
		for (size_t i = 0; i < Array[0].size(); i++) {
			if (Array[0][i] == Array[1][idx_symb]) {
				symb_address = i;
				return symb_address;
			}
		}
	}
	else
		return -1;
	return -1;
}


int check_words_crisscross(string& Array_1, string& Array_2) {
	int true_count = 0;

	char* symb = new char[Array_1.size() + Array_2.size()];
	for (size_t i = 0; i < Array_1.size(); i++)
		symb[i] = 0;

	int* symb_address = new int[Array_1.size() + Array_2.size()];
	for (size_t i = 0; i < Array_1.size(); i++)
		symb_address[i] = 0;

	vector<string> Array;
	Array.push_back(Array_1);
	Array.push_back(Array_2);
	int k = 0;

	if (Array[0] != Array[1]) {
		for (size_t i = 0; i < Array[0].size(); i++) {
			for (size_t j = 0; j < Array[1].size(); j++) {
				if (Array[0][i] == Array[1][j]) {
					symb[k] = Array[0][i];
					symb_address[k] = i;
					k++;
				}
			}
		}
		if (k == 0)
			return -1;
		int word_center = Array_1.size() / 2;
		for (size_t i = 0; i < word_center; i++) {
			for (size_t j = 0; j < word_center; j++) {
				if (Array_1[word_center + j] == symb[i]) {
					return word_center + j;
				}
				if (Array_1[word_center - j] == symb[i]) {
					return word_center - j;
				}
			}
		}
		return -1;
	}
	else
		return -1;
}

int find_w_begin_horizontally(char** Matrix, string Array, int n, int m) {
	int isFit = 0;
	int m_tmp = m;
	for (size_t i = 0; i < Array.size(); i++) {
		if (Matrix[n][m_tmp] == Array[i])
			isFit++;
		m_tmp++;
	}
	if (isFit == Array.size())
		return 1;
	else
		return 0;
}

int find_w_begin_vertically(char** Matrix, string Array, int n, int m) {
	int isFit = 0;
	int n_tmp = n;
	for (size_t i = 0; i < Array.size(); i++) {
		if (Matrix[n_tmp][m] == Array[i])
			isFit++;
		n_tmp++;
	}
	if (isFit == Array.size())
		return 1;
	else
		return 0;
}



void crisscross_versions::making_crisscross(vector<string>& Array, char** Matrix) {
	int mtrx_i = 0, mtrx_j = 0;
	int Matrix_size_i = max_size(Array) * max_size(Array) + 2;
	int Matrix_size_j = max_size(Array) * max_size(Array) + 2;
	int first_word = 0;
	char symb_for_check = 0;
	int words_symb = -1;

	for (size_t counter = 0; counter < Array.size(); counter++) {
		for (size_t i = 0; i < Array.size(); i++) {
			if (Array[counter] == Array[i])
				continue;
			for (size_t j = 0; j < Array[i].size() / 2; j++) {
				int word_center = Array[i].size() / 2;
				words_symb = check_words_crisscross_v2(Array[counter], Array[i], word_center - j);
				if (words_symb == -1)
					words_symb = check_words_crisscross_v2(Array[counter], Array[i], word_center + j);
				if ((words_symb == -1) || (visited[i] == 1)) {
					continue;
				}
				char symb_for_check = Array[counter][words_symb];

				if (first_word == 0) {
					first_word = 1;
					visited[counter] = 1;
					if (Array[counter].size() % 2 == 0) {
						mtrx_i = (max_size(Array) * max_size(Array) + 2) / 2;
						mtrx_j = (max_size(Array) * max_size(Array) + 2) / 2 - max_size(Array) / 2;
						for (size_t f = 0; f < Array[counter].size(); f++) {
							Matrix[mtrx_i][mtrx_j + f] = Array[counter][f];
						}
					}

					else {
						mtrx_i = (max_size(Array) * max_size(Array) + 2) / 2;
						mtrx_j = (max_size(Array) * max_size(Array) + 2) / 2 - max_size(Array) / 2;
						for (size_t j1 = 0; j1 < Array[counter].size(); j1++) {
							Matrix[mtrx_i][mtrx_j + j1] = Array[counter][j1];
						}
					}
				}


				int break_count = 0;
				for (size_t n = 0; n < Matrix_size_i; n++) {
					for (size_t m = 0; m < Matrix_size_j; m++) {
						if ((Matrix[n][m] == Array[counter][0]) && (Matrix[n][m + 1] == Array[counter][1])) {
							if (find_w_begin_horizontally(Matrix, Array[counter], n, m)) { // нахождение слова в матрице (горизонтально)
								mtrx_i = n;
								mtrx_j = m;
								break_count++;
							}
						}
						else if ((Matrix[n][m] == Array[counter][0]) && (Matrix[n + 1][m] == Array[counter][1])) {
							if (find_w_begin_vertically(Matrix, Array[counter], n, m)) { // нахождение слова в матрице (вертикально)
								mtrx_i = n;
								mtrx_j = m;
								break_count++;
							}
						}
					}if (break_count == 1) break;
				}


				for (size_t t = 0; t < Array[counter].size(); t++) {
					if (Matrix[mtrx_i][mtrx_j + t] == symb_for_check) {
						mtrx_j += t;
						break;
					}
					else if (Matrix[mtrx_i + t][mtrx_j] == symb_for_check) {
						mtrx_i += t;
						break;
					}
				}

				for (size_t t = 0; t < Array[counter].size(); t++) {
					if (Matrix[mtrx_i][mtrx_j + t] == symb_for_check || Matrix[mtrx_i][mtrx_j + t] == ' ') {
						mtrx_j += t;
						break;
					}
					else if (Matrix[mtrx_i + t][mtrx_j] == symb_for_check || Matrix[mtrx_i + t][mtrx_j] == ' ') {
						mtrx_i += t;
						break;
					}
				}

				int symb_idx = 0;
				for (size_t n = 0; n < Array[i].size(); n++) {
					if (Array[i][n] == symb_for_check) {
						symb_idx = n;
						break;
					}
				}


				int horizontally_check = -2, vertically_check = -2;

				int iter = 0;
				//vertically
				if (Matrix[mtrx_i - symb_idx - 1][mtrx_j] == Matrix_symbol) // проверка перед началом слова
					vertically_check++;
				for (size_t q = symb_idx; q > 0; q--) {
					if ((Matrix[mtrx_i - q][mtrx_j] == Matrix_symbol) && (Matrix[mtrx_i - q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i - q][mtrx_j + 1] == Matrix_symbol))
						vertically_check++;
					iter++;
				}
				int tmp_for_vertically = 0;
				for (size_t q = 1; Array[i].size() != iter; q++, iter++) {
					if ((Matrix[mtrx_i + q][mtrx_j] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j - 1] == Matrix_symbol) && (Matrix[mtrx_i + q][mtrx_j + 1] == Matrix_symbol))
						vertically_check++;
					tmp_for_vertically = q;
				}
				if (Matrix[mtrx_i + tmp_for_vertically + 1][mtrx_j] == Matrix_symbol) // проверка в конце слова
					vertically_check++;


				//horizontally
				iter = 0;

				if (Matrix[mtrx_i][mtrx_j - symb_idx - 1] == Matrix_symbol) // проверка перед началом слова
					horizontally_check++;

				for (size_t q = symb_idx; q > 0; q--) {
					if ((Matrix[mtrx_i][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j - q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j - q] == Matrix_symbol))
						horizontally_check++;
					iter++;
				}

				for (size_t q = 1; Array[i].size() != iter; q++, iter++) {
					if ((Matrix[mtrx_i][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i - 1][mtrx_j + q] == Matrix_symbol) && (Matrix[mtrx_i + 1][mtrx_j + q] == Matrix_symbol))
						horizontally_check++;
				}

				if (Matrix[mtrx_i][mtrx_j + symb_idx + 1] == Matrix_symbol) // проверка в конце слова
					horizontally_check++;


				if (vertically_check == Array[i].size()) { //word isFit to vertically, writting
					int p = 0;

					int replaceNumber = 0;

					//std::cout << mtrx_i - symb_idx << " " << mtrx_i - symb_idx + Array[i].size() << " " << mtrx_i - symb_idx + Array[i].size() - mtrx_i + symb_idx - 1  << " " << Array[i].size() << std::endl;
					for (int q = mtrx_i - symb_idx; q < mtrx_i - symb_idx + Array[i].size(); q++, p++) {
						//std::cout << "(" << Array[i][p] << " " << q << ", i = " << i << ") ";
						if (Matrix[q][mtrx_j] == Matrix_symbol) {
							replaceNumber++;
						}

						Matrix[q][mtrx_j] = Array[i][p];
					}
					//std::cout << std::endl;

					if (replaceNumber == Array[i].size()) {
						std::cout << "Не удалось вставить слово: " << Array[i] << std::endl;

						for (int q = mtrx_i - symb_idx; q < mtrx_i - symb_idx + Array[i].size(); q++, p++) {
							Matrix[q][mtrx_j] = Matrix_symbol;
						}
					}

					visited[i] = 1;
				}

				else if (horizontally_check == Array[i].size()) { //word isFit to horizontally, writting
					int p = 0;
					int replaceNumber = 0;

					for (int q = mtrx_j - symb_idx; q < mtrx_j - symb_idx + Array[i].size(); q++, p++) {
						if (Matrix[mtrx_i][q] == Matrix_symbol) {
							replaceNumber++;
						}

						Matrix[mtrx_i][q] = Array[i][p];
					}

					if (replaceNumber == Array[i].size()) {
						std::cout << "Не удалось вставить слово: " << Array[i] << std::endl;

						for (int q = mtrx_j - symb_idx; q < mtrx_j - symb_idx + Array[i].size(); q++, p++) {
							Matrix[mtrx_i][q] = Matrix_symbol;
						}
					}

					visited[i] = 1;
				}
				else
					continue;
			}
		}
	}
}

void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j) {
	// алгоритм отсечения матрицы (сверху, слева, справа, снизу)
	int tmp_cut[4][2] = { 0 };
	int tmp_cut_result[4][2];
	int break_count = 0;
	for (int i = 0; i < Matrix_size_i; i++) { //сверху
		for (int j = 0; j < Matrix_size_j; j++) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[0][0] = i - 1;
				tmp_cut[0][1] = j;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int j = 0; j < Matrix_size_i; j++) { // слева
		for (int i = 0; i < Matrix_size_j; i++) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[1][0] = i;
				tmp_cut[1][1] = j - 1;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int i = Matrix_size_i - 1; i > 0; i--) { // снизу
		for (int j = Matrix_size_i - 1; j > 0; j--) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[2][0] = i + 1;
				tmp_cut[2][1] = j;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	break_count = 0;
	for (int j = Matrix_size_i - 1; j > 0; j--) { // справа
		for (int i = Matrix_size_i - 1; i > 0; i--) {
			if (Matrix[i][j] != Matrix_symbol) {
				tmp_cut[3][0] = i;
				tmp_cut[3][1] = j + 1;
				break_count++;
			}
			if (break_count == 1)
				break;
		}
		if (break_count == 1)
			break;
	}

	tmp_cut_result[0][0] = tmp_cut[0][0]; // левая верхняя точка 
	tmp_cut_result[0][1] = tmp_cut[1][1];

	tmp_cut_result[1][0] = tmp_cut[0][0]; // правая верхняя точка
	tmp_cut_result[1][1] = tmp_cut[3][1];

	tmp_cut_result[2][0] = tmp_cut[2][0]; // правая нижняя точка
	tmp_cut_result[2][1] = tmp_cut[3][1];

	tmp_cut_result[3][0] = tmp_cut[2][0]; // левая нижняя точка
	tmp_cut_result[3][1] = tmp_cut[1][1];


	int mtx_size_i = tmp_cut_result[3][0] - tmp_cut_result[0][0] + 1;
	int mtx_size_j = tmp_cut_result[2][1] - tmp_cut_result[0][1] + 1;

	for (size_t i = tmp_cut[0][0], q1 = 0; q1 < mtx_size_i; i++, q1++) { //output matrix
		cout << endl << "\t";
		outFile << endl << "\t";
		for (size_t j = tmp_cut[1][1], q2 = 0; q2 < mtx_size_j; j++, q2++) {
			cout << Matrix[i][j] << " ";
			outFile << Matrix[i][j] << " ";
		}
	}
	cout << endl;
	outFile << endl;
}