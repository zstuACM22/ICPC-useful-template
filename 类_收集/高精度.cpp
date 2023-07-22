// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 高精度类
// Source: https://blog.csdn.net/xiji333/article/details/120812406, Modified by GreatLiangpi
class BigInteger {
   private:
    deque<int32_t> nums;      // 低位到高位存储
    bool isPositive = true;   // 符号位
    int32_t length = 0;       // 位数
    static const int32_t digit = 8;  // 存储元位数
    static const int32_t mod = 1e8;

    // 去除前导 0, 更新 length
    void cutLeadZero() {
        while (nums.size() > 1 && nums.back() == 0)
            nums.pop_back();
        if (nums.empty())
            length = 0;
        else {
            length = (nums.size() - 1) * digit + to_string(nums.back()).size();
        }
    }
    bool isZero() const { return nums.size() == 1 && nums.back() == 0; }
    BigInteger absValue() const { return move(BigInteger(nums)); }

    // pair<BigInteger, int> divModCase1(int64_t x) const {}  // m <= 2
    // pair<BigInteger, BigInteger> divModCase2(const BigInteger &bInt) const {}  // n ~= m
    // pair<BigInteger, BigInteger> divModCase3(const BigInteger &bInt) const {}  // n >> m

   public:
    BigInteger() {};
    BigInteger(const string &s) {
        int32_t n = s.size(), minIdx = 0;
        if (s[0] == '-')
            isPositive = false, minIdx = 1;
        else if (s[0] == '+')
            isPositive = true, minIdx = 1;
        for (int32_t i = n - 1; i >= minIdx; i -= digit) {
            int32_t beg = max(minIdx, i - digit + 1);
            nums.push_back(stoi(s.substr(beg, i - beg + 1)));
        }
        cutLeadZero();
    }
    BigInteger(int64_t a) : BigInteger(to_string(a)) {}
    BigInteger(const BigInteger &bInt) : nums(bInt.nums), isPositive(bInt.isPositive), length(bInt.length) {}
    BigInteger(BigInteger &&bInt) noexcept : nums(move(bInt.nums)), isPositive(bInt.isPositive), length(bInt.length) {}
    BigInteger(const deque<int32_t> &vec, bool sign = true) : nums(vec), isPositive(sign) { cutLeadZero(); }
    BigInteger(const vector<int32_t> &vec, bool sign = true) : nums(deque<int32_t>(vec.begin(), vec.end())), isPositive(sign) { cutLeadZero(); }

    friend istream &operator>>(istream &cin, BigInteger &bInt) {
        string s;
        cin >> s;
        bInt = move(BigInteger(s));
        return cin;
    }
    friend ostream &operator<<(ostream &cout, const BigInteger &bInt) {
        cout << (string)bInt;
        return cout;
    }

    // 如果要去 0 建议先转换为 string
    operator string() const {
        string ans;
        if (!isPositive)
            ans += "-";
        int32_t n = nums.size();
        for (int32_t i = n - 1; i >= 0; i--) {
            string s = to_string(nums[i]);
            if (i != n - 1)
                ans += string(digit - s.size(), '0');
            ans += s;
        }
        return ans;
    }

    // 返回高精度对 1e18 取模
    explicit operator int64_t() const {
        int64_t res = 0, base = 1, modulo = 1e18;
        for (int32_t i = 0; i < (length + digit - 1) / digit and modulo; i++) {
            res += nums[i] % modulo * base;
            base *= mod;
            modulo /= mod;
        }
        return res;
    }
    
    // 10 的幂
    static BigInteger exp(size_t n) {
        if (n <= 0)
            return move(BigInteger(vector<int32_t>(1, 1)));
        int32_t m = n / digit;
        n -= m * digit;
        vector<int32_t> ans(m);
        string s = "1";
        s += move(string(n, '0'));
        ans.push_back(stoi(s));
        return move(BigInteger(ans));
    }

    BigInteger operator+() const { return *this; }
    BigInteger operator-() const {
        BigInteger tmp(*this);
        if (!tmp.isZero())
            tmp.isPositive = !isPositive;
        return tmp;
    }

    bool operator<(const BigInteger &bInt) const {
        if (isPositive && !bInt.isPositive)
            return false;
        if (!isPositive && bInt.isPositive)
            return true;
        bool flag = true;
        if (!isPositive)
            flag = false;  // 都为负数
        if (length < bInt.length)
            return flag;
        else if (length > bInt.length)
            return !flag;
        int32_t n = nums.size();
        for (int32_t i = n - 1; i >= 0; i--) {
            if (nums[i] < bInt.nums[i])
                return flag;
            else if (nums[i] > bInt.nums[i])
                return !flag;
        }
        return false;
    }
    bool operator<=(const BigInteger &bInt) const {
        if (isPositive && !bInt.isPositive)
            return false;
        if (!isPositive && bInt.isPositive)
            return true;
        bool flag = true;
        if (!isPositive)
            flag = false;  // 都为负数
        if (length < bInt.length)
            return flag;
        else if (length > bInt.length)
            return !flag;
        int32_t n = nums.size();
        for (int32_t i = n - 1; i >= 0; i--) {
            if (nums[i] < bInt.nums[i])
                return flag;
            else if (nums[i] > bInt.nums[i])
                return !flag;
        }
        return true;
    }
    bool operator==(const BigInteger &bInt) const {
        if (length != bInt.length)
            return false;
        int32_t n = nums.size();
        for (int32_t i = 0; i < n; i++)
            if (nums[i] != bInt.nums[i])
                return false;
        return true;
    }
    bool operator>(const BigInteger &bInt) const { return not (*this <= bInt); }
    bool operator>=(const BigInteger &bInt) const { return not (*this < bInt); }
    bool operator!=(const BigInteger &bInt) const { return not (*this == bInt); }

    BigInteger operator+(const BigInteger &bInt) const {
        if (!bInt.isPositive)
            return *this - (-bInt);  // 加上负数 = 减去其绝对值
        if (!isPositive)
            return bInt - (-*this);  // 负数+正数 = 整数-(-负数)
        // 要么都正 要么都负
        vector<int32_t> ans;
        int32_t n = nums.size(), m = bInt.nums.size(), sum = 0, i = 0, j = 0;
        while (i < n || j < m || sum) {
            if (i < n)
                sum += nums[i++];
            if (j < m)
                sum += bInt.nums[j++];
            ans.push_back(sum % mod);
            sum /= mod;
        }
        return move(BigInteger(ans, isPositive));
    }
    BigInteger operator-(const BigInteger &bInt) const {
        if (!bInt.isPositive)
            return *this + (-bInt);  // 减去负数 = 加上其绝对值
        if (!isPositive)
            return -((-*this) + bInt);  // 负数-正数 = -(-负数 + 正数)
        if (*this < bInt)
            return -(bInt - *this);
        // 只计算大数减去小数
        vector<int32_t> ans;
        int32_t i = 0, j = 0, n = nums.size(), m = bInt.nums.size(), sum = 0;
        while (i < n || j < m || sum) {
            if (i < n)
                sum += nums[i++];
            if (j < m)
                sum -= bInt.nums[j++];
            int32_t flag = 0;
            if (sum < 0) {
                flag = -1;
                sum += mod;
            }
            ans.push_back(sum);
            sum = flag;
        }
        return move(BigInteger(ans));
    }
    BigInteger operator*(const BigInteger &bInt) const {
        int32_t n = nums.size(), m = bInt.nums.size();
        vector<int32_t> ans(n + m);
        for (int32_t i = 0; i < n; i++) {
            for (int32_t j = 0; j < m; j++) {
                int64_t tmp = ans[i + j] + nums[i] * 1ll * bInt.nums[j];
                ans[i + j] = tmp % mod;
                ans[i + j + 1] += tmp / mod;
            }
        }
        return move(BigInteger(ans, isPositive == bInt.isPositive));
    }
    
    // 同时获取整除和余数. 时间: O(nm log(mod))
    pair<BigInteger, BigInteger> divMod(const BigInteger &bInt) const {
        BigInteger a = absValue();
        BigInteger b = bInt.absValue();
        if (b.isZero())
            return pair<BigInteger, BigInteger>(*this, move(b));
        if (a < b)
            return pair<BigInteger, BigInteger>(move(BigInteger(0)), *this);
        BigInteger ans, tmp;
        if (isPositive != bInt.isPositive) ans.isPositive = false;
        for (int32_t i = a.nums.size() - 1; i >= 0; i--) {
            tmp.nums.push_front(a.nums[i]);  // 每次偏移 digit 单位
            tmp.cutLeadZero();
            // 二分试商
            int32_t l = 0, r = mod - 1;
            while (l <= r) {
                int32_t m = l + r >> 1;
                if (b * BigInteger(m) <= tmp) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            tmp = tmp - b * BigInteger(r);
            ans.nums.push_front(r);
        }
        ans.cutLeadZero();
        tmp.cutLeadZero();
        return pair<BigInteger, BigInteger>(move(BigInteger(ans)), move(tmp));
    }
    BigInteger operator/(const BigInteger &bInt) const { return move(divMod(bInt).first); }
    BigInteger operator%(const BigInteger &bInt) const { return move(divMod(bInt).second); }

    // BigInteger operator<<(size_t n) {}
    // BigInteger operator>>(size_t n) {}

    BigInteger &operator+=(const BigInteger &bInt) { return *this = *this + bInt; }
    BigInteger &operator-=(const BigInteger &bInt) { return *this = *this - bInt; }
    BigInteger &operator*=(const BigInteger &bInt) { return *this = *this * bInt; }
    BigInteger &operator/=(const BigInteger &bInt) { return *this = *this / bInt; }
    BigInteger &operator%=(const BigInteger &bInt) { return *this = *this % bInt; }

    // 仅提供 ++BigInteger, 无 BigInteger++
    BigInteger &operator++() { return *this += 1; }
    BigInteger &operator--() { return *this -= 1; }


    BigInteger &operator=(const BigInteger &bInt) {
        if (bInt == *this)
            return *this;
        nums = bInt.nums;
        isPositive = bInt.isPositive;
        length = bInt.length;
        return *this;
    }
    BigInteger &operator=(BigInteger &&bInt) noexcept {
        nums = move(bInt.nums);
        isPositive = bInt.isPositive;
        length = bInt.length;
        return *this;
    }
};
