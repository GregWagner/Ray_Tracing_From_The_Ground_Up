#pragma once

[[nodiscard]] inline double max(double x0, double x1);

[[nodiscard]] inline double max(double x0, double x1) {
    return ((x0 > x1) ? x0 : x1);
}