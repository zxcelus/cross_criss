#pragma once
#include <iostream>
#include <vector>
using namespace std;

class crisscross {
private:
	int size;
	int* visited;
public:
	crisscross(int my_size) {
		size = my_size;
		visited = new int[size];
		for (size_t i = 0; i < size; i++) {
			visited[i] = 0;
		}
	};
	void making_crisscross(vector<string>& Array, char** Matrix);
	char** making_matrix(vector<string>& Array);
	~crisscross() {
		delete[] visited;
	};
};

int count_words_with_max_chars(const std::vector<std::string>& words);
void move_to_front(std::vector<std::string>& vector, size_t index);

void start(char* words, char* outputFile);
void output(vector<string>& Array);
int input_from_file(vector<string>& Array, char* words);
void caps_func(vector<string>& Array);
void caps_func_rus(vector<string>& Array);
int correct_insert_check(vector<string>& Array);
int isalpha_rus(char alphabet);
int max_size(vector<string>& Array);
void delete_matrix(char** matrix, size_t size);
int check_words_crisscross(string& Array_1, string& Array_2);
void unique_check(vector<string>& Array);
int find_w_begin_horizontally(char** Matrix, string Array, int n, int m);
int find_w_begin_vertically(char** Matrix, string Array, int n, int m);
void crisscross_reduction(char** Matrix, int Matrix_size_i, int Matrix_size_j);
void sort_words(vector<string>& Array);