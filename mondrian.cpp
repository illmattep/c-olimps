#include <cstdio>
#include <vector>

struct Point {
    int x, y;
};

bool isPointPresent(const std::vector<Point>& canvas, const Point& center) {
    for (const Point& p : canvas) {
        if (p.x == center.x || p.y == center.y) {
            return true;
        }
    }
    return false;
}

bool doesSegmentIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool onSegment(const Point& p, const Point& q, const Point& r) {
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;

    return false;
}

int orientation(const Point& p, const Point& q, const Point& r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2;
}

bool doesIntersectExistingSegments(const std::vector<Point>& canvas, const Point& center, const Point& A, const Point& B) {
    for (size_t i = 0; i + 1 < canvas.size(); ++i) {
        if (doesSegmentIntersect(canvas[i], canvas[i + 1], center, A) ||
            doesSegmentIntersect(canvas[i], canvas[i + 1], center, B)) {
            return true;
        }
    }
    return false;
}

std::vector<Point> draw(int N, int L, const std::vector<Point>& A, const std::vector<Point>& B) {
    std::vector<Point> canvas = {{L / 2, L / 2}};

    for (int i = 0; i < N; ++i) {
        Point center;
        if (A[i].y == B[i].y) {
            center.x = (A[i].x + B[i].x) / 2;
            center.y = A[i].y;
        } else {
            center.x = A[i].x;
            center.y = (A[i].y + B[i].y) / 2;
        }

        if (!isPointPresent(canvas, center) && !doesIntersectExistingSegments(canvas, center, A[i], B[i])) {
            canvas.push_back(center);
        } else {
            return {};
        }
    }

    return canvas;
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);

    std::vector<Point> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &A[i].x, &A[i].y, &B[i].x, &B[i].y);
    }

    std::vector<Point> result = draw(N, L, A, B);

    if (result.empty()) {
        printf("0\n");
    } else {
        printf("%zu\n", result.size());
        for (const Point& p : result) {
            printf("%d %d\n", p.x, p.y);
        }
    }

    return 0;
}
