#pragma GCC optimize("O2")
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
namespace calculator {
    using ll = long long int;

    void del_zero_back(vector <int>& a) {
        while (a.size() > 1 && a.back() == 0) a.pop_back();
    }

    template <int D> // chon boi so cua 4 
    struct BigHex {
        static const int BASE = 1UL << D;

        vector <int> number;
        int sign = 0;

        BigHex() {}

        BigHex(const vector <int>& number, int sign) {
            this->number = number;
            this->sign = sign;
        }

        BigHex(ll x) {
            if (x < 0) {
                x *= -1;
                sign = 1;
            }

            if (x == 0) number.push_back(0);

            while (x > 0) {
                number.push_back(x & (BASE - 1));
                x >>= D;
            }
        }

        BigHex(string numberHex) {
            if (numberHex[0] == '-') {
                sign = 1;
                numberHex.erase(numberHex.begin());
            }

            int cnt = 0, b = 1, add = 0;
            while (numberHex.size()) {
                if (cnt == D / 4) {
                    number.push_back(add);
                    cnt = 0, b = 1, add = 0;
                }
                if ('0' <= numberHex.back() && numberHex.back() <= '9') {
                    add += (numberHex.back() - '0') * b;
                }
                else {
                    add += (numberHex.back() - 'A' + 10) * b;
                }
                cnt++;
                b *= 16;
                numberHex.pop_back();
            }
            if (add) number.push_back(add);
        }

        BigHex operator -() const {
            BigHex res = *this;
            res.sign ^= 1;
            return res;
        }

        BigHex abs() const {
            BigHex res = *this;
            res.sign = 0;
            return res;
        }

        bool operator > (const BigHex& otherNumber) const {
            if (sign != otherNumber.sign) return sign < otherNumber.sign;
            int sizeNum1 = this->number.size();
            int sizeNum2 = otherNumber.size();
            if (sizeNum1 != sizeNum2) return sizeNum1 > sizeNum2;
            for (int i = sizeNum1 - 1; i >= 0; --i) {
                if (this->number[i] != otherNumber[i]) {
                    if (sign) {
                        return this->number[i] < otherNumber[i];
                    }
                    else {
                        return this->number[i] > otherNumber[i];
                    }
                }
            }
            return false;
        }

        bool operator < (const BigHex& otherNumber) const {
            return otherNumber > *this;
        }

        bool operator == (const BigHex& otherNumber) const {
            return !(*this > otherNumber) && !(otherNumber > *this);
        }

        bool operator <= (const BigHex& otherNumber) const {
            return otherNumber > *this || *this == otherNumber;
        }

        bool operator >= (const BigHex& otherNumber) const {
            return *this > otherNumber || *this == otherNumber;
        }

        void operator = (const BigHex& otherNumber) {
            sign = otherNumber.sign;
            int n = otherNumber.size();
            this->number.resize(n);
            for (int i = 0; i < n; ++i) this->number[i] = otherNumber[i];
        }

        int operator[] (const int& index) const {
            if (index < 0 || index >= this->number.size()) {
                cerr << "Array index out of range\n";
                exit(0);
            }
            return this->number[index];
        }

        int size() const {
            return number.size();
        }

        string to_str() const {
            if (number.empty()) return "0";
            string res = "";
            if (sign == 1) res = "-";
            for (int i = (int)number.size() - 1; i >= 0; i--) {
                int x = number[i];
                string add = "";
                for (int j = 0; j < D / 4; j++) {
                    int c = x & 15;
                    if (c < 10) add += c + '0';
                    else add += 'A' + c - 10;
                    x >>= 4;
                }
                if (i + 1 == number.size()) {
                    while (add.size() > 1 && add.back() == '0') add.pop_back();
                }
                //reverse(add.begin(), add.end());
                for (auto it = add.rbegin(); it != add.rend(); ++it) res+= * it;
                //res += add;
            }
            if (res == "-0") res = "0";
            return res;
        }

        friend ostream& operator << (ostream& os, const BigHex& num) {
            os << num.to_str();
            return os;
        }

        BigHex& operator <<= (const int& x) {
            if (!number.empty()) {
                vector <int> add(x, 0);
                for (auto i : number) add.push_back(i);
                number = add;
            }
            return *this;
        }

        BigHex& operator >>= (const int& x) {
            number = vector <int>(number.begin() + min(x, (int)number.size()), number.end());
            return *this;
        }


        BigHex& operator += (const BigHex& otherNumber) {
            if (otherNumber.sign != sign) {
                *this -= (-otherNumber);
                return *this;
            }

            int i = 0, j = 0;
            int n = this->number.size();
            int m = otherNumber.size();

            this->number.resize(max(n, m) + 1);

            int l = 0;
            int carry = 0;
            while (i < n || j < m) {
                int digitNumber1 = i == n ? 0 : (*this)[i++];
                int digitNumber2 = j == m ? 0 : otherNumber[j++];

                int r = (digitNumber1 + digitNumber2 + carry) & (BASE - 1);
                carry = (digitNumber1 + digitNumber2 + carry) >> D;
                this->number[l++] = r;
            }

            if (carry > 0) this->number[l++] = carry;
            del_zero_back(this->number);
            return *this;
        }

        BigHex operator + (const BigHex& otherNumber) const {
            BigHex tmp(*this);
            tmp += otherNumber;
            return move(tmp);
        }

        BigHex& operator ++ () {
            *this += BigHex(1);
            return *this;
        }

        BigHex& operator ++ (int) {
            return ++ * this;
        }

        BigHex& operator -= (const BigHex& otherNumber) {
            if (sign != otherNumber.sign) {
                *this += (-otherNumber);
                return *this;
            }

            if (abs() < otherNumber.abs()) {
                *this = otherNumber - *this;
                sign ^= 1;
                return *this;
            }

            int carry = 0;
            int n = this->number.size();
            int m = otherNumber.size();

            this->number.resize(max(n, m) + 1);

            int i = 0, j = 0, l = 0;
            while (i < n || j < m) {
                int digitNumber1 = i == n ? 0 : (*this)[i++];
                int digitNumber2 = j == m ? 0 : otherNumber[j++];

                int r = digitNumber1 - digitNumber2 + carry;

                if (r < 0) {
                    carry = -1;
                    r += BASE;
                }
                else carry = 0;

                this->number[l++] = r;
            }


            del_zero_back(this->number);
            return *this;

        }

        BigHex operator - (const BigHex& otherNumber) const {
            BigHex tmp(*this);
            tmp -= otherNumber;
            return move(tmp);
        }

        BigHex& operator --() {
            *this -= BigHex(1);
            return *this;
        }

        BigHex& operator --(int) {
            return -- * this;
        }

        BigHex& operator *= (const BigHex& otherNumber) {
            if (otherNumber.sign) {
                if (sign) sign = 0;
                else sign = 1;
                *this *= (-otherNumber);
                return *this;
            }
            int n = this->number.size(), m = otherNumber.size();

            vector <ll> c(n + m + 1);
            this->number.resize(n + m + 1);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    c[i + j] += (1ll * (*this)[i] * otherNumber[j]);
                    c[i + j + 1] += c[i + j] / BASE;
                    c[i + j] &= (BASE - 1);

                }
            }

            for (int i = 0; i < n + m; ++i) {
                c[i + 1] += (c[i] >> D);
                this->number[i] = c[i] & (BASE - 1);
            }

            del_zero_back(this->number);
            return *this;
        }


        BigHex operator * (const BigHex& otherNumber) const {
            BigHex tmp(*this);
            tmp *= otherNumber;
            return move(tmp);
        }


        BigHex& operator *= (ll x) {
            if (x < 0) {
                if (sign) sign = 0;
                else sign = 1;
                x = -x;
            }
            int carry = 0;
            int n = this->number.size();
            for (int i = 0; i < n; ++i) {
                int r = (this->number[i] * x + carry) & (BASE - 1);
                carry = (this->number[i] * x + carry) >> D;
                this->number[i] = r;
            }

            if (carry > 0) this->number.push_back(carry);

            return *this;
        }

        BigHex operator * (const ll& x) const {
            BigHex tmp(*this);
            tmp *= x;
            return move(tmp);
        }


        BigHex& operator /= (const ll& x) {
            ll r = 0;
            for (int i = (int)this->number.size() - 1; i >= 0; --i, r %= x) {
                r = r * BASE + (*this)[i];
                this->number[i] = r / x;
            }
            del_zero_back(this->number);
            return *this;
        }

        BigHex operator / (const ll& x) const {
            BigHex tmp(*this);
            tmp /= x;
            return move(tmp);
        }

        BigHex& operator %= (const BigHex& otherNumber) {
            static vector <BigHex> power2;
            if (power2.empty()) {
                string res = "";
                for (int i = 0; i <= 1024 * 2; i += 4) {
                    power2.emplace_back(BigHex('1' + res));
                    power2.emplace_back(BigHex('2' + res));
                    power2.emplace_back(BigHex('4' + res));
                    power2.emplace_back(BigHex('8' + res));
                    res += '0';
                }
            }

            BigHex mul;
            int Spw2 = (this->number.size() < 35) ? 1029 : power2.size();

            //Spw2 = min(1ll * Spw2, MAXBIT * this->get_size()); // (2^MAXBIT)^i.... 0 
            for (int i = Spw2 - 1; i >= 0; --i) if (*this >= power2[i] && *this >= otherNumber) {
                mul = otherNumber * power2[i];
                while (*this >= mul) *this -= mul;
            }

            return *this;
        }

        BigHex operator % (const BigHex& otherNumber) const {
            BigHex tmp(*this);
            tmp %= otherNumber;
            return move(tmp);
        }

        bool is_odd() const {
            if (this->number.empty()) return 0;
            return this->number[0] & 1;
        }

        bool is_even() const {
            return !is_odd();
        }

    };

    typedef BigHex<28> data_type;
    data_type power(data_type a, data_type b, const data_type& m) {
        a %= m;

        data_type res(1), zero(0);
        while (b > zero) {
            if (b.is_odd()) {
                res *= a;
                if (res >= m) res %= m;
            }
            a *= a;
            if (a >= m) a %= m;
            b /= 2;
        }
        return res;
    }

    data_type power(data_type a, data_type b) {
        data_type res(1);
        while (b > data_type(0)) {
            if (b.is_odd()) res *= a;
            a *= a;
            b /= 2;
        }
        return move(res);
    }

    namespace MONTGOMERY {
        data_type BitLength(data_type v, int& x) {
            x = 0;
            data_type zero(0);
            while (v > zero) {
                v /= 2;
                ++x;
            }
            return move(data_type(x));
        }

        struct Montgomery {
            data_type m;
            data_type n;
            data_type rrm;
            int x;

            Montgomery(const data_type& m) {
                if (m == data_type(0) || !m.is_odd()) {
                    cerr << m << " :m must be greater than zero and odd";
                    exit(0);
                }
                this->m = m;
                this->n = BitLength(m, x);
                this->rrm = power(2, n * 2, m);
            }

            data_type reduce(const data_type& t) {
                data_type a = t;
                for (int i = 0; i < x; i++) {
                    if (a.is_odd()) a += m;
                    a /= 2;
                }
                if (a >= m) a -= m;
                return move(a);
            }
        };

        data_type powerMod(data_type x1, const data_type& x2, const data_type& m) {
            x1 %= m;

            Montgomery mont(m);
            //data_type t1 = x1 * mont.rrm;
            //data_type t2 = x2 * mont.rrm;

            data_type r1 = mont.reduce(x1 * mont.rrm);
            data_type r2 = mont.reduce(x2 * mont.rrm);
            data_type r = power(2, mont.n);

            data_type prod = mont.reduce(mont.rrm);
            data_type base = mont.reduce(x1 * mont.rrm);
            data_type exp = x2;
            int x = 0;
            data_type zero(0);
            while (BitLength(exp, x) > zero) {
                if (exp.is_odd()) prod = mont.reduce(prod * base);
                exp /= 2;
                base = mont.reduce(base * base);
            }

            return move(mont.reduce(prod));
        }
    }
}

using namespace calculator;

bool test(data_type a, const int& k, const data_type& m, const data_type& n) {
    data_type tmp = n;
    --tmp;
    data_type pw = MONTGOMERY::powerMod(a, m, n);
    data_type numberone = data_type(1);
    if (pw == numberone || pw == tmp) return true;
    for (int l = 1; l < k; l++) {
        pw *= pw;
        if (pw >= n) pw %= n;
        if (pw == tmp) return true;
        if (pw == numberone) return false; //
    }
    return false;
}

bool miller_rabin(const data_type& n, const vector <string>& primes) {
    if (n < data_type(2)) return false;
    if (!n.is_odd()) return false;

    int k = 0;
    data_type m = n;
    --m;
    while (!m.is_odd()) {
        m /= 2;
        k++;
    }
    
    for (const auto &a : primes) {
        data_type tmp(a);
        if (n == tmp) return true;
        if (!test(tmp, k, m, n)) return false;
    }
    return true;
}

bool check(const data_type& n) {
    if (n < data_type(2)) return false;
    if (n == data_type(2) || n == data_type(3) || n == data_type(5)) return true;

    data_type zero = data_type(0);
    if (n % data_type(2) == zero || n % data_type(3) == zero || n % data_type(5) == zero) return false;

    if (n < data_type(49)) return true;

    if (n %  data_type(7) == zero || n % data_type(11) == zero || n % data_type(13) == zero ||
        n % data_type(17) == zero || n % data_type(19) == zero || n % data_type(23) == zero || 
        n % data_type(29) == zero || n % data_type(31) == zero || n % data_type(37) == zero || 
        n % data_type(41) == zero || n % data_type(43) == zero || n % data_type(47) == zero) 
        
        return false;

    if (n < data_type(2809)) return true;
    if (n < data_type(65077)) {
        data_type pw = MONTGOMERY::powerMod(2, n / 2, n);
        if (!(pw == data_type(1)) && !(pw == data_type(n - data_type(1)))) return false;
        for (auto i: {8321, 31621, 42799, 49141, 49981}) {
            if (n == data_type(i)) return false;
        }
        return true;
    }

    if (n < data_type(341531))
        return miller_rabin(n, {"81B33F22EFDCEAA9"});

    if (n < data_type(885594169))
        return miller_rabin(n, {"A10AD7D5C6610C1", "318A8C12CE9C70E7"});

    if (n < data_type(350269456337))
        return miller_rabin(n, {"3AB4F88FF0CC7C80", "CBEE4CDF120C10AA", "E6F1343B0EDCA8E7"});

    if (n < data_type(55245642489451))
        return miller_rabin(n, {"2", "810C207B08BF", "10A42595B01D3765", "99FD2B545EAB5322"});

    if (n < data_type(7999252175582851))
        return miller_rabin(n, {"2", "3C1C7396F6D", "2142E2E3F22DE5C", "297105B6B7B29DD", "370EB221A5F176DD"});

    if (n < data_type("81F23F390AFFE89"))
        return miller_rabin(n, {"2", "70722E8F5CD0", "20CD6BD5ACE2D1", "9BBC940C751630", "A90404784BFCB4D", "1189B3F265C2B0C7"});

    if (n < data_type("10000000000000000"))
        return miller_rabin(n, {"2", "145", "249F", "6E12", "6E0D7", "953D18", "6B0191FE"});

    if (n < data_type("437AE92817F9FC85B7E5"))
        return miller_rabin(n, {"2", "3", "5", "7", "B", "D", "11", "13", "17", "1D", "1F", "25"});
    
    if (n == data_type("2BE6951ADC5B22410A5FD")) return false;

    return miller_rabin(n, {"2", "3", "5", "7", "B", "D", "11", "13", "17", "1D", "1F", "25", "29"});
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(0);
    if (argc == 1) {
        const char* x[] = { argv[0], "test.inp", "test.out" };
        argv = const_cast<char**>(x);
    }

    string m;
 
    ifstream Fin(argv[1]);
    Fin >> m;
    Fin.close();

    ofstream Fout(argv[2]);
    Fout << check(m);
    Fout.close();

	return 0;
}

