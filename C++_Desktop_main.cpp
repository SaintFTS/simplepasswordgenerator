#include <string>
#include <random>
#include <array>
#include <chrono>
#include <memory>
#include <iostream>
#include <algorithm>

#define SPECIALS_AMOUNT 16
#define NUMBERS_AMOUNT  16
#define CHARS_AMOUNT    16


template<const int Size>
constexpr std::array<char, Size + 1> fill_arr(char from, char to) {
    std::array<char, Size + 1> arr = { 0 };
    int i = 0;
    for (char ch = from; ch <= to && i < Size; ch++ && i++) {
        arr[i] = ch;
    }
    arr[Size] = '\0';
    return arr;
}

template<const int Size>
constexpr std::array<char, Size + 1> fill_arr(const char* from) {
    std::array<char, Size + 1> arr;
    arr[Size] = '\0';
    for (int i = 0; i < Size; i++) {
        arr[i] = from[i];
    }
    return arr;
}

template<const int Size>
inline void fill_symbols(char* dest, int& from, const int amount, std::array<char, Size> symbols, std::mt19937& rand_engine) {
    std::uniform_int_distribution<> dist{0, Size-2}; // Size-2, because size-1 == '\0'
    if (symbols.size() >= 2) {
        for (int i = from; i < from + amount; i++) {
            dest[i] = symbols[dist(rand_engine)];
        }
    }
    from += amount;
}

// All symbols declaration
constexpr auto upper = fill_arr<26>('A', 'Z');
constexpr auto lower = fill_arr<26>('a', 'z');
std::array<char, 52+1> eng_chars;               // 26*2 + '\0'
constexpr auto numbers = fill_arr<9>('0', '9');
constexpr auto specials = fill_arr<23>("@!#$%^&*()_,./'\";:`-+=\\");

char* gen_pass(const int specials_amount, const int numbers_amount, const int chars_amount, std::mt19937& rand_engine) {
    const int pass_length = numbers_amount+specials_amount+chars_amount;
    //+chars_amount;
    char* pass = new char[pass_length+1];
    if (!pass) {
        throw std::bad_alloc();
    }
    int i = 0;
    fill_symbols<specials.size()>(pass, i, specials_amount, specials, rand_engine);
    fill_symbols<numbers.size()>(pass, i, numbers_amount, numbers, rand_engine);   
    fill_symbols<eng_chars.size()>(pass, i, chars_amount, eng_chars, rand_engine); 

    std::shuffle(pass, pass + pass_length, std::mt19937{ std::random_device{}() });

    pass[pass_length] = '\0';

    return pass;
}


int main(){
    memcpy(eng_chars.data(), lower.data(), lower.size()-1);
	memcpy(eng_chars.data()+lower.size()-1, upper.data(), upper.size()-1); // -1 in the first parametar because last char of lower.data() is '\0'
    
    std::mt19937 mt_rand = std::mt19937{static_cast<unsigned long>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())};
    char* pass;
    try {
        pass = gen_pass(SPECIALS_AMOUNT, NUMBERS_AMOUNT, CHARS_AMOUNT, mt_rand);
        std::cout << pass;
    } catch (std::exception& exc) {
        std::cout << exc.what();
    }
    free(pass);
}
