#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<string>
using namespace std;

int assign(char str) {
    unordered_map<char, int>charmap;
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        charmap[ch] = ch - 'A'; 
    }
    charmap['!'] = 26; 
    charmap['@'] = 27; 
    charmap['#'] = 28; 
    charmap['$'] = 29; 
    for(auto it:charmap){
        if(it.first==str){
            return it.second;
        }
    }
    return -1; // jab mere charactersa na mile then i need to do this;
}
// made a function to assign the caharacters to the numbers

char getChar(int val) {
    if (val >= 0 && val <= 25) return 'A' + val;
    else if (val == 26) return '!';
    else if (val == 27) return '@';
    else if (val == 28) return '#';
    else if (val == 29) return '$';
    else return '?'; // unknown character
}
// gcd calculator 

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<int> lcgkey(int seed, int a, int c, int m, int length) {
    vector<int> key_1;
    int random = seed;
    while (key_1.size() < length) {  // Changed to ensure we get enough keys of the length of the string
        random = (a * random + c) % m; 
        random = random % 29;
        if (gcd(random, 29) == 1) { 
            key_1.push_back(random);
        }
    }
    return key_1;
}

vector<int> bbs_algorithm(int p, int q, int seed, int length) {
    vector<int> key_2;
    if (p % 4 == 3 && q % 4 == 3) {
        int n = p * q;

        while (seed <= p || seed <= q || gcd(seed, n) != 1) {
            seed++;
        }

        int x = seed;
        
        while (key_2.size() < length) {
            x = (x * x) % n;
            int bit = x % 29; // Generate values in 0-28 range
            key_2.push_back(bit);
        }
    } else {
        // Provide default key if condition fails
        key_2 = vector<int>(length, 1); // 1 is coprime with 29
    }
    return key_2;
}

vector<int> encrypt_text(string &str, vector<int> &key_1, vector<int> &key_2) {
    vector<int> enc_values;
    for(int i = 0; i < str.length(); i++){
        int p = assign(str[i]);
        if (p == -1) {
            // Handle invalid character
            enc_values.push_back(0);
            continue;
        }
        int k1 = key_1[i];
        int k2 = key_2[i];
        int enc_value = (p * k1 + k2) % 29;
        enc_values.push_back(enc_value);
    }
    return enc_values;
}

vector<int> decrypt_text(vector<int> &enc_values, vector<int> &key_1, vector<int> &key_2) {
    vector<int> dec_values;

    // Function to calculate modular multiplicative inverse
    auto mod_inverse = [](int a, int m) {
        int m0 = m, t, q;
        int x0 = 0, x1 = 1;
        if (m == 1) return 0;
        while (a > 1) {
            q = a / m;
            t = m;
            m = a % m, a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    };

    for (int i = 0; i < enc_values.size(); i++) {
        int enc = enc_values[i];
        int k1 = key_1[i];
        int k2 = key_2[i];

        // Calculate modular inverse of k1 modulo 29
        int k1_inverse = mod_inverse(k1, 29);

        // Decrypt the value
        int dec = (enc - k2) % 29;
        if (dec < 0) dec += 29; // Ensure non-negative
        dec = (dec * k1_inverse) % 29;

        dec_values.push_back(dec);
    }

    return dec_values;
}

int main() {
    string s;
    cout << "Enter text to encrypt (A-Z, !@#$): ";
    cin >> s;

    int seed = 12564;
    int a = 87645;
    int c = 98674;
    int m = 16;
    int length = s.length();
    int p = 7;
    int q = 11;

    // Generate keys
    vector<int> key_1 = lcgkey(seed, a, c, m, length);
    vector<int> key_2 = bbs_algorithm(p, q, seed, length);

    // Encrypt
    vector<int> enc_values = encrypt_text(s, key_1, key_2);

    // Print encrypted string
    string enc_str = "";
    for (int val : enc_values) {
        enc_str += getChar(val);
    }
    cout << "Encrypted: " << enc_str << endl;

    // Decrypt
    vector<int> dec_values = decrypt_text(enc_values, key_1, key_2);
    string dec_str = "";
    for (int val : dec_values) {
        dec_str += getChar(val);
    }
    cout << "Decrypted: " << dec_str << endl;

    return 0;
}