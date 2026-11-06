#ifndef __MATHS__
#define __MATHS__

[[nodiscard]] inline double max(double x0, double x1);

[[nodiscard]] inline double max(double x0, double x1) {
	return ((x0 > x1) ? x0 : x1);
}

#endif
