#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Case-insensitive string comparison
bool iequal(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b);
        });
}

// Wildcard string matching (case-insensitive)
bool matches(const std::string& str, const std::string& pattern) {
    return std::search(str.begin(), str.end(), pattern.begin(), pattern.end(),
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b) || b == '*';
        }) != str.end();
}

// Operator overloading for case-insensitive string comparison
struct ci_string {
    std::string str;
    
    bool operator==(const ci_string& other) const {
        return iequal(str, other.str);
    }
    
    bool operator<(const ci_string& other) const {
        return std::lexicographical_compare(
            str.begin(), str.end(),
            other.str.begin(), other.str.end(),
            [](char a, char b) {
                return std::tolower(a) < std::tolower(b);
            }
        );
    }
};

// Operator overloading for wildcard string matching
struct wc_string {
    std::string str;
    
    bool operator==(const wc_string& other) const {
        return matches(str, "*" + other.str + "*");
    }
    
    bool operator<(const wc_string& other) const {
        return matches(str, "*" + other.str + "*");
    }
};
bool containsIgnoreCase(const std::string& str1, const std::string& str2) {
    auto str1Begin = str1.begin();
    auto str1End = str1.end();
    auto str2Begin = str2.begin();
    auto str2End = str2.end();

    // Convert both strings to lowercase and remove special characters
    std::string str1Lower;
    std::transform(str1Begin, str1End, std::back_inserter(str1Lower), [](char c) { return std::tolower(c); });
    str1Lower.erase(std::remove_if(str1Lower.begin(), str1Lower.end(), [](char c) { return !std::isalnum(c); }), str1Lower.end());

    std::string str2Lower;
    std::transform(str2Begin, str2End, std::back_inserter(str2Lower), [](char c) { return std::tolower(c); });
    str2Lower.erase(std::remove_if(str2Lower.begin(), str2Lower.end(), [](char c) { return !std::isalnum(c); }), str2Lower.end());

    // Check if str1Lower contains str2Lower
    return str1Lower.find(str2Lower) != std::string::npos;
}

int main() {
    // Example usage of ci_string and wc_string
    
    // Case-insensitive string comparison
    // ci_string a{"Hello"};
    // ci_string b{"hello"};
    // std::cout << (a == b) << std::endl; // prints 1 (true)
    // std::cout << (a < b) << std::endl; // prints 0 (false)
    
    
    // // Wildcard string matching
    // wc_string c{"foobar"};
    // wc_string d{"*bar*"};
    // std::cout << (c == d) << std::endl; // prints 1 (true)
    // std::cout << (c < d) << std::endl; // prints 0 (false)

   std::cout<<containsIgnoreCase("5555","555666");
   std::cout<<containsIgnoreCase("*568669","56");
    
    return 0;
}
