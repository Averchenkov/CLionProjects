
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#define ALPHABET_LENGTH 256  

//��������� ���������� �������� ��������
size_t iterations = 0;

//�������� ������� � ������ ��������
bool CompCharsWithReg(char a, char b)
{
	if (a == b)
		return true;
	return false;
}

//�������� ������� ��� ����� ��������
bool CompCharsWithoutReg(char a, char b)
{
	if (tolower(a) == tolower(b))
		return true;
	return false;
}

//�������� �������� � ������
void AddValueInArray(size_t*& arr, int value)
{
	size_t length = 0;
	if (arr != nullptr)
		length = _msize(arr) / sizeof(size_t);

	size_t* temp = new size_t[length + 1];

	for (int i = 0; i < length; i++)
		temp[i] = arr[i];
	temp[length] = value;

	delete[] arr;
	arr = temp;
}

//��������� ������� d
size_t* FindPrefix(/*�����*/const std::string& image, /*��������� �������*/bool considerReg)
{
	//������ d ��� �������� �������
	size_t* const d = new size_t[image.length()];
	d[0] = 0;

	//�������� �� ���� ���������
	bool(*Compare)(char, char);
	if (considerReg)
		Compare = CompCharsWithReg;
	else
		Compare = CompCharsWithoutReg;

	//����������� ������� ������
	for (size_t i = 1, j = 0; i < image.length(); i++)
	{
		//���� ����� ���������� ���������� ������� ��������
		while ((j > 0) && !Compare(image[i], image[j]))
			j = d[j - 1]; //����� ����� ������������ �������� (������� � ����������� ����������)

		//���� �������� ������ �����
		if (Compare(image[i], image[j]))
			j++;
		d[i] = j;
	}
	return d;
}

//�������� �����-�������-������
size_t* KMPSearch(/*�������� ������*/const std::string& str, /*�����*/const std::string& image, /*��������� �������*/bool considerReg)
{
	//��������� ����� �������� ������
	size_t n = str.length();

	//��������� ����� ������
	size_t m = image.length();

	//���� ����� ������� ������ ��� ����� ���� ��� ������ �����, �� ������������ ���
	if (n < m || m == 0 || n == 0)
		return nullptr;

	size_t* pointers = nullptr;

	//��������� ������� d
	size_t* const d = FindPrefix(image, considerReg);

	//�������� �� ���� ���������
	bool(*Compare)(char, char);
	if (considerReg)
		Compare = CompCharsWithReg;
	else
		Compare = CompCharsWithoutReg;

	//������ �� ������
	for (int i = 0, j = 0; i < n; i++)
	{
		//���� ����� ���������� ���������� ��x����� ��������
		if ((j > 0) && !Compare(image[j], str[i]))
			while ((j > 0) && !Compare(image[j], str[i]))
			{
				iterations++;
				j = d[j - 1];
			}
		else
			iterations++;

		//���� ������� ������������ ����� �������� ������ � �������� ������
		if (Compare(image[j], str[i]))
			j++; //������� � ���������� ������� ������
		if (j == m) //���� ��� ������� ������ ������� � ��������� ������
			AddValueInArray(pointers, i - j + 1); //�������� ������ ������ � ������
	}
	delete[] d;

	return pointers;
}

//��������� ������� ��� ��������� ������-����
int* BMTable(const std::string& image, bool considerReg)
{
	int* const bmTable = new int[ALPHABET_LENGTH];
	int i;

	//���������������� ��� �������� ��������� '-1'  
	for (i = 0; i < ALPHABET_LENGTH; i++)
		bmTable[i] = -1;

	//��������� ������ ��������� ��������� ��������� ��������
	//� ������ ��������
	if (considerReg)
		for (i = 0; i < image.length(); i++)
			bmTable[image[i]] = i;
	//��� ����� ��������
	else
		for (i = 0; i < image.length(); i++)
			bmTable[tolower(image[i])] = i;

	return bmTable;
}

//�������� ������-����
size_t* BMSearch(const std::string& str, const std::string& image, bool considerReg)
{
	//��������� ����� �������� ������
	size_t n = str.length();

	//��������� ����� ������
	size_t m = image.length();

	//���� ����� ������� ������ ��� ����� ���� ��� ������ �����, �� ������������ ���
	if (n < m || m == 0 || n == 0)
		return nullptr;

	size_t* pointers = nullptr;

	//�������� �� ���� ���������
	bool(*Compare)(char, char);
	if (considerReg)
		Compare = CompCharsWithReg;
	else
		Compare = CompCharsWithoutReg;

	//��������� ������� ��� ����� ���������
	int* const bmTable = BMTable(image, considerReg);

	//���������� �������� ������ �� ��������� � ������
	int s = 0;

	//���� s ������, ��� �������� ����� ������ � ������
	while (s <= (n - m))
	{
		int j = m - 1;

		//���� ����� ��������� �� �������, ������� � �����
		if ((j >= 0) && Compare(image[j], str[s + j]))
			while ((j >= 0) && Compare(image[j], str[s + j]))
			{
				iterations++;
				j--; //��������� �� ����� ������
			}
		else
			iterations++;

		//���� ����� ��������� ������ �� �������
		if (j < 0)
		{
			AddValueInArray(pointers, s); //�������� ������ ������ � ������

			//�������� ����� ���, ����� ��������� ������ � ������ �������� � ���������
			//����� �� �������� � ������ ��� �� 1, ���� ����� ������ �� �������
			if (considerReg)
				s += ((s + m) < n) ? m - bmTable[str[s + m]] : 1;
			else
				s += ((s + m) < n) ? m - bmTable[tolower(str[s + m])] : 1;
		}
		//�����
		else
		{
			//�������� ����� ���, ����� ������ � ������, �� ��������� � ��������
			//� ������, �������� � ��������� ����� �� �������� � ������ ��� �� 1,
			//���� ����������� ������ ������ �������� ������� � ������
			if (considerReg)
				s += (1 >= (j - bmTable[str[s + j]])) ? 1 : (j - bmTable[str[s + j]]);
			else
				s += (1 >= (j - bmTable[tolower(str[s + j])])) ? 1 : (j - bmTable[tolower(str[s + j])]);
		}
	}
	delete[] bmTable;

	return pointers;
}

//����������� �������� ������ �����-�������-������ � ������-����
size_t* KMPAndBMSearch(const std::string& str, const std::string& image, bool considerReg)
{
	//��������� ����� �������� ������
	size_t n = str.length();

	//��������� ����� ������
	size_t m = image.length();

	//���� ����� ������� ������ ��� ����� ���� ��� ������ �����, �� ������������ ���
	if (n < m || m == 0 || n == 0)
		return nullptr;

	size_t* pointers = nullptr;

	//�������� �� ���� ���������
	bool(*Compare)(char, char);
	if (considerReg)
		Compare = CompCharsWithReg;
	else
		Compare = CompCharsWithoutReg;

	//��������� ������� d
	size_t* const d = FindPrefix(image, considerReg);

	//��������� ������� ������-����
	int* const bmTable = BMTable(image, considerReg);

	//���������� �������� ������ �� ��������� � ������
	int s = 0;

	int bm[256];
    for (int l = 0; l < 256; ++l) {
        bm[l] = bmTable[l];
    }

	//���� s ������, ��� �������� ����� ������ � ������
	while (s <= (n - m))
	{
		int j = m - 1;

		//���� ����� ��������� �� �������, ������� � �����
		while ((j >= 0) && Compare(image[j], str[s + j]))
			j--; //��������� �� ����� ������

		//���� ����� ��������� ������ �� �������
		if (j < 0)
		{
			AddValueInArray(pointers, s); //�������� ������ ������ � ������

			int k = m;
			while ((k > 0) && !Compare(image[k], str[m]))
				k = d[k - 1];

			//���� ����� �����-�������-������ ������, ��� ����� ������-����
			if (k > (m - bmTable[str[s + m]]))
				s += ((s + k) < n) ? k : 1;
			//�����
			else
				//�������� ����� ���, ����� ��������� ������ � ������ �������� � ���������
				//����� �� �������� � ������
				if (considerReg)
					s += ((s + m) < n) ? (m - bmTable[str[s + m]]) : 1;
				else
					s += ((s + m) < n) ? (m - bmTable[tolower(str[s + m])]) : 1;
		}
		//�����
		else
		{
			int i = s + j;
			int k = j;
			while ((k > 0) && !Compare(image[k], str[i]))
				k = d[k - 1];

			if (considerReg)
			{
				//���� ����� �����-�������-������ ������, ��� ����� ������-����
				if (k > (j - bmTable[str[s + j]]))
					s += ((s + k) < n) ? k : 1;
				//�����
				else
					//�������� ����� ���, ����� ��������� ������ � ������ �������� � ���������
					//����� �� �������� � ������
					s += ((j - bmTable[str[s + j]]) <= 1) ? 1 : (j - bmTable[str[s + j]]);
			}
			else
			{
				//���� ����� �����-�������-������ ������, ��� ����� ������-����
				if (k > (j - bmTable[tolower(str[s + j])]))
					s += ((s + k) < n) ? k : 1;
				//�����
				else
					//�������� ����� ���, ����� ��������� ������ � ������ �������� � ���������
					//����� �� �������� � ������
					s += ((j - bmTable[tolower(str[s + j])]) <= 1) ? 1 : (j - bmTable[tolower(str[s + j])]);
			}
		}
		iterations++;
	}
	delete[] d, bmTable;

	return pointers;
}

//�������� ������� ������
size_t* BruteForceSearch(const std::string& str, const std::string& image, bool considerReg)
{
	//��������� ����� ������
	size_t n = str.length();

	//��������� ����� ������
	size_t m = image.length();

	//���� ����� ������� ������ ��� ����� ���� ��� ������ �����, �� ������������ ���
	if (n < m || m == 0 || n == 0)
		return nullptr;

	size_t* pointers = nullptr;

	//�������� �� ���� ���������
	bool(*Compare)(char, char);
	if (considerReg)
		Compare = CompCharsWithReg;
	else
		Compare = CompCharsWithoutReg;

	//������ �� ������
	for (int i = 0; i < n - m; i++)
	{
		//������ �� ������
		for (int j = 0; j < m; j++)
		{
			iterations++;
			//����� �� ����� ������� ������, ���� ������� ��������������
			if (!Compare(str[i + j], image[j]))
				break;

			//���� ����� ��������� ������ �� �������, �� �������� ������
			if (j == m - 1)
				AddValueInArray(pointers, i);
		}
	}
	return pointers;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string input1;
	std::string input2;
	std::cout << "������� ������: ";
	std::getline(std::cin, input1);
	std::cout << "������� ������� �����: ";
	std::getline(std::cin, input2);

	size_t res[4];

	size_t* arr1 = BruteForceSearch(input1, input2, false);
	std::cout << "����� ������� ������: " << iterations << " ��������" << std::endl;
	res[0] = iterations;
	iterations = 0;

	size_t* arr2 = KMPSearch(input1, input2, false);
	std::cout << "����� ���: " << iterations << " ��������" << std::endl;
	res[1] = iterations;
	iterations = 0;

	size_t* arr3 = BMSearch(input1, input2, false);
	std::cout << "����� ��: " << iterations << " ��������" << std::endl;
	res[2] = iterations;
	iterations = 0;

	size_t* arr4 = KMPAndBMSearch(input1, input2, false);
	std::cout << "����� �� � ���: " << iterations << " ��������" << std::endl;
	res[3] = iterations;
	iterations = 0;
	if (arr4 != nullptr)
	{
		size_t n = _msize(arr4) / sizeof(arr4[0]);

		for (int i = 0; i < n; i++)
			std::cout << arr4[i] << " ";
		std::cout << std::endl;
	}
	else
		std::cout << "���������� �� �������" << std::endl;

	delete[] arr1, arr2, arr3, arr4;

	system("PAUSE");
	return 0;
}