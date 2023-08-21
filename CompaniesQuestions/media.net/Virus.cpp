// C++ implementation of the above approach
#include <bits/stdc++.h>
using namespace std;

struct coord {
	long double x, y;
};

// Function to find the square of the
// distance between two given points
long double distance(coord a, coord b)
{
	// Distance Formulae
	return (a.x - b.x) * (a.x - b.x)
		+ (a.y - b.y) * (a.y - b.y);
}

// Function to check if there exist a
// point having K overlapping circles with
// the radius of each circle as mid
bool check(vector<coord> points, int k,
		long double mid)
{
	// Squaring the value of mid
	// for simplicity of calculation
	mid *= mid;
	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++) {

			// Stores the coordinates
			// of 1st circle
			coord C1 = points[i];

			// Stores the coordinates
			// of 2nd circle
			coord C2 = points[j];

			// Calculating dist and h
			// as discussed in approach
			long double dist = distance(C1, C2);
			long double h
				= sqrt((4 * mid - dist)
					/ dist);

			// If Circles do not intersect
			if (dist > 4 * mid)
				continue;

			// Stores two intersection points
			coord P1, P2;

			// By help of formulaes given above
			P1.x = ((C1.x + C2.x)
					+ h * (C1.y - C2.y))
				/ 2;
			P1.y = ((C1.y + C2.y)
					+ h * (C2.x - C1.x))
				/ 2;
			P2.x = ((C1.x + C2.x)
					- h * (C1.y - C2.y))
				/ 2;
			P2.y = ((C1.y + C2.y)
					+ h * (C2.x - C1.x))
				/ 2;

			// Stores count of overlapping
			// circles over P1 and P2
			int cnt1 = 0, cnt2 = 0;

			// Loop to traverse over all the circles
			for (int k = 0; k < points.size(); k++) {

				// If P1 lies inside Kth circle
				if (distance(P1, points[k]) - mid
					<= 0.000001)
					cnt1++;

				// If P2 lies inside Kth circle
				if (distance(P2, points[k]) - mid
					<= 0.000001)
					cnt2++;
			}

			// If count of overlapping circles
			// is more than K
			if (cnt1 >= k || cnt2 >= k) {
				return true;
			}
		}
	}

	// If no valid point is found
	return false;
}

// Function to perform the binary
// search over the radius of the
// circles in the range [0, ∞]
int binSearchOnRad(vector<coord>& points, int k)
{
	// Stores the start and end of
	// range of the binary search
	int start = 0, end = 1e6;

	// Loop to perform binary search
	while (start <= end) {

		// Stores the mid if the
		// current range
		int mid = start + (end - start) / 2;

		// If there exist a point having
		// k overlapping circles with the
		// radius of circles as mid
		if (check(points, k, mid)) {
			end = mid - 1;
		}

		// If the required point
		// does not exist
		else {
			start = mid + 1;
		}
	}

	// Return Answer
	return start;
}

// Driver Code
int main()
{
	vector<coord> points = { { 8, 5 },
							{ 0, 4 },
							{ 3, 6 } };
	int K = 3;

	cout << binSearchOnRad(points, K);

	return 0;
}
