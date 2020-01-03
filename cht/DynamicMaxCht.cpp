class DynamicMaxCht {
    struct Line {
        long long k;
        long long b;
        mutable long long rightX;

        bool operator<(const Line &rhs) const {
            return k < rhs.k;
        }

        bool operator<(long long x) const {
            return rightX < x;
        }
    };

    set<Line, less<>> lines;

    static long long divFloor(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool intersect(const set<Line>::iterator &x, const set<Line>::iterator &y) const {
        if (y == lines.end()) {
            x->rightX = LLONG_MAX;
            return false;
        }
        if (x->k == y->k) {
            x->rightX = x->b > y->b ? LLONG_MAX : LLONG_MIN;
        } else {
            x->rightX = divFloor(y->b - x->b, x->k - y->k);
        }
        return x->rightX >= y->rightX;
    }

public:
    void addLine(long long k, long long b) {
        auto r = lines.insert({k, b, 0}).first;
        auto m = r++;
        auto l = m;
        while (intersect(m, r)) {
            r = lines.erase(r);
        }
        if (l != lines.begin() && intersect(--l, m)) {
            intersect(l, lines.erase(m));
        }
        while ((m = l) != lines.begin() && (--l)->rightX >= m->rightX) {
            intersect(l, lines.erase(m));
        }
    }

    long long getMax(long long x) const {
        auto it = *lines.lower_bound(x);
        return it.k * x + it.b;
    }
};
