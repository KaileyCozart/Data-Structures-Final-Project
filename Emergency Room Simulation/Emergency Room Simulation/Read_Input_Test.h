#pragma once
#ifndef READ_INPUT_TEST_H_
#define READ_INPUT_TEST_H_
#include <iostream>
#include <string>

int read_input(const std::string &prompt, int low, int high)
{
	if (low >= high)
		throw std::invalid_argument("An invalid range was specified.");

	std::cin.exceptions(std::ios_base::failbit);
	int num = 0;
	while (true) {
		try {
			while (true) {
				std::cout << prompt;
				std::cin >> num;
				if (num >= low && num <= high) {
					std::cout << std::endl;
					std::cin.clear();
					return num;
				}
			}
		}
		catch (std::ios_base::failure) {
			std::cout << "Bad numeric string. Please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
	}
}

#endif