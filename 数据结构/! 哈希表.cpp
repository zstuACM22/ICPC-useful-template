// Jamhus Tao / GreatLiangpi
// Start at 2022/10/6
// Please using int32_t and int64_t to replace the int and long long.
#include <bits/stdc++.h>
#define int int64_t
#define endl '\n'
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

// 哈希表. 时间: O(1), 内存: ?
// 哈希表. 时间: O(4.8), 内存: O(3n)
// !!!!!! 遍历存在 BUG
// 此哈希表拒绝遍历: 1. 未知下标越界, 2. 时间急剧上升至 O(14.4)
class HashMap {
   private:
    struct _pair {
        bool flag = false;
        int first = 0;
        int second = 0;
    } *_data = new _pair[1];
    const double _load_factor = 0.667;
    long long _size = 0;
    long long _log2_capacity = 0;
    unsigned long long _hash_xor;
    int _hash_size;
    int _hash_cut_size;
    int _hash_cut_base;
    int _key_shift;
    int _hash_cut_shift;
    unsigned long long _mark_1;
    unsigned long long _mark_2;
    unsigned long long _mark_3;
    unsigned long long _mark_4;
    unsigned long long _mark_5;

#define randull() ((unsigned long long)rand() << 60 | (unsigned long long)rand() << 45 | (unsigned long long)rand() << 30 | (unsigned long long)rand() << 15 | (unsigned long long)rand())

    void randomit(int new_log2_capacity) {
        _hash_size = new_log2_capacity;
        _hash_cut_size = _hash_size >> 1;
        _hash_cut_base = _hash_size + 1 >> 1;
        _hash_xor = randull();
        _hash_cut_shift = rand() % _hash_cut_size + _hash_cut_base - _hash_cut_size;
        _key_shift = _hash_size - _hash_cut_base;
        _mark_1 = (1ull << _hash_size) - (1ull << _hash_cut_base);
        _mark_2 = (1ull << _hash_cut_base) - 1ull;
        _mark_3 = (1ull << _hash_size) - (1ull << _hash_cut_size);
        _mark_4 = (1ull << _hash_cut_size) - 1ull;
        _mark_5 = (1ull << _hash_size) - 1ull;
    }

    // Test Data: 100000 randomize integer, 100 test, in average.
    // Hash collision expectation 3.27 for load factor 0.500
    // Hash collision expectation 4.06 for load factor 0.600
    // Hash collision expectation 4.80 for load factor 0.667
    // Hash collision expectation 5.28 for load factor 0.700
    // Hash collision expectation 5.76 for load factor 0.800
    // Never try to hack it, it's with no chink.
    int hash(unsigned long long key, unsigned long long cnt) {
        key = key ^ _hash_xor;
        unsigned long long __ = key & _mark_1 | key >> _key_shift & _mark_2;
        unsigned long long base = key << _hash_cut_size & _mark_3 | __ >> _hash_cut_shift & _mark_4;
        return base + cnt & _mark_5;
    }

    _pair *position(_pair *dst, int first) {
        int cnt = 0;
        _pair *it = dst + hash(first, cnt++);
        while (it->flag and it->first != first)
            it = dst + hash(first, cnt++);
        return it;
    }

    pair<_pair *, bool> push(_pair *dst, int first, int second) {
        _pair *it = position(dst, first);
        if (it->flag)
            return {it, false};
        *it = {true, first, second};
        return {it, true};
    }

    void reload(int new_log2_capacity) {
        randomit(new_log2_capacity);
        _pair *new_data = new _pair[1 << new_log2_capacity];
        for (_pair *it = _data; it != _data + (1 << _log2_capacity); it++)
            if (it->flag)
                push(new_data, it->first, it->second);
        _log2_capacity = new_log2_capacity;
        delete _data;
        _data = new_data;
    }

   public:
    HashMap(int capacity = 4) {
        if (capacity < 4)
            capacity = 4;
        srand(time(0) << 10 | clock());
        reload(log2(capacity * 2 - 1));
    }

    int operator[](int key) {
        _pair *it = position(_data, key);
        return it->second;
    }

    _pair *begin() { return _data; }

    int capacity() { return 1 << _log2_capacity; }

    void clear() {
        _size = 0;
        delete _data;
        _data = new _pair[1];
    }

    int count(int key) {
        _pair *it = position(_data, key);
        return it->flag;
    }

    bool empty() { return _size == 0; }

    _pair *end() { return _data + (1 << _log2_capacity); }

    bool erase(_pair *address) {
        if (not address->flag)
            return false;
        _size--;
        *address = {false, 0, 0};
        return true;
    }

    _pair *erase(int key) {
        _pair *it = position(_data, key);
        if (not it->flag)
            return end();
        _size--;
        *it = {false, 0, 0};
        return it;
    }

    _pair *find(int key) {
        _pair *it = position(_data, key);
        if (it->flag)
            return it;
        return end();
    }

    pair<_pair *, bool> insert(pair<int, int> pair_) {
        if (_size > _load_factor * (1 << _log2_capacity))
            reload(_log2_capacity + 1);
        pair<_pair *, bool> tmp = push(_data, pair_.first, pair_.second);
        if (tmp.second) {
            _size++;
            return tmp;
        } else
            return tmp;
    }

    void reserve(int new_capacity) {
        if (new_capacity < 4)
            return;
        int new_log2_capacity = log2(new_capacity * 2 - 1);
        if ((1 << new_log2_capacity) <= _size)
            return;
        if (_log2_capacity == new_log2_capacity)
            return;
        reload(new_log2_capacity);
    }

    void shrink_to_fit() {
        int new_log2_capacity = log2(_size / _load_factor - 1) + 1;
        reserve(new_log2_capacity);
    }

    long long size() { return _size; }

    ~HashMap() { delete _data; }
};