#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <variant>

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
	std::cout << "Compare time: " << durr.count() << "ms\n";
	return count;
}

int main(int argc, char** argv) {
	// Globals
	int str_len = 3;

	//Generating 3600 strings
	std::string chars;
	for (int i = 65; i < 91; i++) chars += char(i);
	for (int i = 48; i < 58; i++) chars += char(i);

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
				std::cout << i << ' ' << j << '\n';
				std::cout << strings[i] << ' ' << strings[j] << '\n';
			}
		}
	}
	std::cout << "\nCollision count: " << count << '\n';

	// Time div
	std::cout << "Hashes comparison. ";
	compare(hashes);
	std::cout << "Strings comparison. ";
	compare(strings);
	
	return 0;
}
