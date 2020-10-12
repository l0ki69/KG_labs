#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void del_island(vector <vector <int>> *matrix, int x, int y, int& count) // method for removing shapes from a matrix
{
	count++;
	(*matrix)[x][y] = 0;
	if ((*matrix)[x + 1][y] == 1)
	{
		del_island(matrix, x + 1, y, count);
	}
	if ((*matrix)[x - 1][y] == 1)
	{
		del_island(matrix, x - 1, y, count);
	}
	if ((*matrix)[x][y + 1] == 1)
	{
		del_island(matrix, x, y + 1, count);
	}
	if ((*matrix)[x][y - 1] == 1)
	{
		del_island(matrix, x, y - 1, count);
	}

}

vector <int> island(vector <vector <int>> *matrix, int size)  // figure counting method
{
	vector <int> info;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int count = 0;
			if ((*matrix)[i][j] == 1)
			{
				del_island(matrix, i, j, count);
				info.push_back(count);

				// print(matrix, size);
				// cout << count << ' ';
			}
		}
	}

	return info;
}

void print(vector <vector <int>> *matrix, int size) // method for displaying a matrix on the screen
{
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << (*matrix)[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	string path = "C:\\projects\\labs_KG\\DZ_matrix_16x16\\"; // path to working directory
	path += "tests\\"; // path to the directory with tests
	ifstream file_in(path + "test_0.in"); // file with matrix 
	ofstream file_out(path + "test_0.out"); // file with information

	int size = 18; // size matrix

	vector <vector <int>> matrix (size, vector<int>(size, 0));

	string row = "";

	int k = 0;
	while (!file_in.eof()) // reading from a file and filling the matrix
	{
		file_in >> row;

		for (int i = 1; i < row.length() + 1; i++)
		{
			matrix[k + 1][i] = row[i - 1] - '0';
		}
		k++;
	}
	file_in.close();

	// print(&matrix, size);

	vector <int> info;
	info = island(&matrix, size);

	for (int i = 0; i < info.size(); i++)
	{

		string out = "", value = "";
		if (info[i] < 3)
		{
			value = " - шум или аномалия";
		}
		else if (info[i] < 5)
		{
			value = " - цель";
		} 
		else value = " - земля";
		out = "Отметка #" + to_string(i) + ". Площадь " + to_string(info[i]) + value + '\n';
		cout << out;
		file_out << out;
	}

	file_out.close();

	system("pause>>NULL");
	return 0;
}