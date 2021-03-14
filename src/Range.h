//
// Created by mate on 14.03.2021.
//

#ifndef PGSTL_RANGE_H
#define PGSTL_RANGE_H

template<long from, long to>
class Range {
public:
    class iterator {
        long num = from;
    public:
        explicit iterator(long num = 0) : num(num) {}

        iterator& operator++() {
            num = to >= from ? num + 1 : num - 1;
            return *this;
        }

        bool operator == (iterator other) const {
            return num == other.num;
        }

        long operator*() const {
            return num;
        }
    };

    iterator begin() {
        return iterator(from);
    }

    iterator end() {
        return iterator(to >= from ? to + 1 : to - 1);
    }
};

#endif //PGSTL_RANGE_H
