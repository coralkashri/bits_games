#include <iostream>
#include <vector>
#include <thread>

void print_val(int num) {
	for (char i = sizeof num * 8 - 1; i >= 0; i--) {
		std::cout << ((num >> i) & 1) << (i % 8 == 0 && i != 0 ? "\n" : " ");
	}
	std::cout << "\n";
}

void print_vec(const std::vector<int> &vec) {
	std::for_each(vec.rbegin(), vec.rend(), [](const auto &val) { print_val(val); });
}

void rotate_vec(std::vector<int> &vec, unsigned char steps) {
	int mask = -1 & ((1 << steps) - 1);
	int next_overflow = 0;
	for (auto it = vec.rbegin(); it != vec.rend(); it++) {
		int last_overflow = next_overflow;
		next_overflow = ((unsigned int)*it >> (sizeof *it * 8 - steps)) & mask;
		*it = (*it << steps) | last_overflow;
	}
	*vec.rbegin() = *vec.rbegin() | next_overflow;
}

int main() {
	std::vector<int> arr(2, 0);
	arr[0] = 0b00001110000010100000111000001110;
	arr[1] = 0b111000001010000011100000;
	for (;;) {
		print_vec(arr);
		std::cout << std::endl;
		rotate_vec(arr, 8);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}