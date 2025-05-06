//
// Created by Oliwier Komorowski on 26/05/2024.
//

#ifndef GRAPH2_0_MYSTRING_H
#define GRAPH2_0_MYSTRING_H
#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    size_t length;
    static bool isSpace(char c) {
        return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
    }
    static bool isDigit(char c) {
        return (c >= '0' && c <= '9');
    }
public:
    MyString() : data(nullptr), length(0) {}

    friend std::istream& getline(std::istream& is, MyString& str);

    MyString(const char* str, size_t len) {
        length = len;
        data = new char[length + 1];
        std::strncpy(data, str, length);
        data[length] = '\0';
    }

    static long long toLongLong(const MyString& str) {
        long long result = 0;
        int sign = 1;
        size_t i = 0;

        while (i < str.size() && isSpace(str[i])) {
            ++i;
        }
        if (i < str.size() && (str[i] == '+' || str[i] == '-')) {
            sign = (str[i++] == '-') ? -1 : 1;
        }
        // Convert digits to an integer
        while (i < str.size() && isDigit(str[i])) {
            result = result * 10 + (str[i++] - '0');
        }

        return sign * result;
    }

    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        std::strncpy(data, other.data, length);
        data[length] = '\0';
    }



    ~MyString() {}

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strncpy(data, other.data, length);
            data[length] = '\0';
        }
        return *this;
    }



    char& operator[](size_t index) {
        return data[index];
    }

    const char& operator[](size_t index) const {
        return data[index];
    }


    size_t size() const {
        return length;
    }

    const char* c_str() const {
        return data;
    }



    MyString& operator+=(const MyString& other) {
        size_t newLength = length + other.length;
        char* newData = new char[newLength + 1];
        std::memcpy(newData, data, length);
        std::memcpy(newData + length, other.data, other.length);
        newData[newLength] = '\0';
        delete[] data;
        data = newData;
        length = newLength;
        return *this;
    }
    friend bool operator!=(const MyString& lhs, const MyString& rhs) {
        return std::strcmp(lhs.data, rhs.data) != 0;
    }
    friend bool operator==(const MyString& lhs, const MyString& rhs) {
        return std::strcmp(lhs.data, rhs.data) == 0;
    }

    friend bool operator<(const MyString& lhs, const MyString& rhs) {
        return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }
    friend bool operator>(const MyString& lhs, const MyString& rhs) {
        return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }

    friend MyString operator+(const MyString& lhs, const MyString& rhs) {
        MyString result;
        result.length = lhs.length + rhs.length;
        result.data = new char[result.length + 1];
        std::strcpy(result.data, lhs.data);
        std::strcat(result.data, rhs.data);
        return result;
    }


};







#endif //GRAPH2_0_MYSTRING_H
