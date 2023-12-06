#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

template <typename T>
int compare(std::vector<T> &v) {
	int count = 0;
	typedef std::chrono::high_resolution_clock Time;
	auto t0 = Time::now();
	for (int i = 0; i < 3600; i++) {
		for (int j = i + 1; j < 3600; j++) {
			if (v[i] == v[j]) count++;
		}
	}
	auto t1 = Time::now();
	std::chrono::duration<float> fs = t1 - t0;
	std::chrono::milliseconds durr = std::chrono::duration_cast<std::chrono::milliseconds>(fs);
	//std::cout << "Compare time: " << durr.count() << "ms\n";
	return durr.count();
}

int main(int argc, char** argv) {
	std::string chars;
	for (int i = 65; i < 91; i++) chars += char(i);
	for (int i = 48; i < 58; i++) chars += char(i);

	// Opening CSV
	std::ofstream file;
	file.open("data.csv", std::ios::app);
	file << "str_len;str_comp;hash_comp;coll\n";

	for (int i = 3; i < 8; i++) {
		//Generating 3600 strings
		int str_len = i;
		std::vector<std::string> strings;
		for (int i = 0; i < 100; i++) {
			std::string tmp = "";
			srand(i * 38945 + int(time(NULL)));
			for (int j = 0; j < str_len; j++) tmp += chars[rand() % 36];

			int rand_index = rand() % str_len;
			for (int j = 0; j < 36; j++) {
				tmp[rand_index] = chars[j];
				strings.push_back(tmp);
			}
		}

		// Generating hashes for strings
		std::vector<unsigned long long> hashes;
		for (int i = 0; i < 3600; i++) {
			unsigned long long tmp = LLONG_MAX / 3;
			for (const char& ch : strings[i]) tmp = (tmp << (tmp % 3)) * ch;
			hashes.push_back(tmp);

		}

		// Collision check
		int count = 0;
		for (int i = 0; i < 3600; i++) {
			for (int j = i + 1; j < 3600; j++) {
				if (hashes[i] == hashes[j] && strings[i] != strings[j]) {
					count++;
				}
			}
		}
		for (int j = 0; j < 10; j++) {
			file << str_len << ';' << compare(strings) << ';' << compare(hashes) << ';' << count << '\n';
		}
	}
	file.close();

	return 0;
}
