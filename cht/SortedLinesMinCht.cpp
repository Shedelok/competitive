class SortedLinesMinCht {
    vector<pair<long long, long long>> lines;
    vector<long double> intersections;

public:
    void addLine(long long k, long long b) {
        pair<long long, long long> line = {k, b};
        if (!lines.empty() && k == lines.back().first) {
            if (b >= lines.back().second) {  // <= for max
                return;
            }
            lines.pop_back();
            if (!intersections.empty()) {
                intersections.pop_back();
            }
        }
        while (lines.size() > 1) {
            long double x = intersections[lines.size() - 2];
            if (1. * line.first * x + line.second <= 1. * lines.back().first * x + lines.back().second) {  // >= for max
                lines.pop_back();
                intersections.pop_back();
            } else {
                break;
            }
        }
        if (!lines.empty()) {
            intersections.push_back(1. * (lines.back().second - line.second) / (line.first - lines.back().first));
        }
        lines.push_back(line);
    }

    long long getMin(long long x) const {
        if (lines.size() == 1) {
            return 1LL * lines[0].first * x + lines[0].second;
        }
        int bl = 1;
        int br = lines.size() - 1;
        int bRes = 0;
        while (bl <= br) {
            int mid = (bl + br) / 2;
            if (intersections[mid - 1] <= x) {  // >= for max
                bRes = mid;
                bl = mid + 1;
            } else {
                br = mid - 1;
            }
        }
        return 1LL * lines[bRes].first * x + lines[bRes].second;
    }
};
