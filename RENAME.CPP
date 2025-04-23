#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<math.h>
using namespace std;

int assign(char str) {
    if (str >= 'A' && str <= 'Z') return str - 'A';
    switch(str) {
        case '!': return 26;
        case '@': return 27;
        case '#': return 28;
        case '$': return 29;
        default: return -1;
    }
}

char getChar(int val) {
    if (val >= 0 && val <= 25) return 'A' + val;
    else if (val == 26) return '!';
    else if (val == 27) return '@';
    else if (val == 28) return '#';
    else if (val == 29) return '$';
    else return '?';
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int e, int phi) {
    int m0 = phi, t, q;
    int x0 = 0, x1 = 1;
    if (phi == 1) return 0;
    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

int find_smallest_e(int phi) {
    for (int e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            return e;
        }
    }
    return -1;
}

int main() {
    int p = 31;
    int q = 37;
    int n = p * q;
    int phi = (p-1)*(q-1);
    int e = find_smallest_e(phi);
    int d = mod_inverse(e, phi);

    string s;
    cout << "Enter text to encrypt (A-Z, !@#$): ";
    cin >> s;

    vector<int> values;
    for(char ch : s) {
        int num = assign(ch);
        if(num == -1) {
            cout << "Invalid character" << endl;
            return 0;
        }
        values.push_back(num);
    }

    // Encryption
    vector<int> enc_values;
    for(int m : values) {
                int c = 1;
        for (int i = 0; i < e; i++) {
            c = (c * m) % n;  
        }
        enc_values.push_back(c % 30);  
    }

    string enc_str;
    for(int val : enc_values) {
        enc_str += getChar(val);
    }

    cout << "Encrypted: " << enc_str << endl;

    return 0;
}