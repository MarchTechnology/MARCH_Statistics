#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>

#include "MARCH_Statistics.h"

namespace MARCH {
    namespace Detail {
        template<std::size_t Size>
        constexpr void validateSize() {
            static_assert(Size > 0, "Array size must be greater than zero.");
        }

        template<typename T, std::size_t Size>
        inline void insertionSort(T (&data)[Size]) noexcept {
            Detail::validateSize<Size>();
            for (std::size_t i = 1; i < Size; i++) {
                T value = data[i];
                std::size_t j = i;
                while (j > 0 && data[j - 1] > value) {
                    data[j] = data[j - 1];
                    j--;
                }

                data[j] = value;
            }
        }
    }
}

template<typename T, std::size_t Size>
constexpr T MARCH::Statistics::mean(const T (&data)[Size]) {
    Detail::validateSize<Size>();
    T sum {};
    for (std::size_t i = 0; i < Size; i++)
        sum += data[i];

    return sum / static_cast<T>(Size);
}

template<typename T, std::size_t Size>
constexpr T MARCH::Statistics::minimum(const T (&data)[Size]) {
    Detail::validateSize<Size>();
    T value = data[0];
    for (std::size_t i = 1; i < Size; i++) {
        if (data[i] < value)
            value = data[i];
    }

    return value;
}

template<typename T, std::size_t Size>
constexpr T MARCH::Statistics::maximum(const T (&data)[Size]) {
    Detail::validateSize<Size>();
    T value = data[0];
    for (std::size_t i = 1; i < Size; i++) {
        if (data[i] > value)
            value = data[i];
    }

    return value;
}

template<typename T, std::size_t Size>
constexpr T MARCH::Statistics::variance(const T (&data)[Size], const T average) {
    Detail::validateSize<Size>();
    T sum {};
    for (std::size_t i = 0; i < Size; i++) {
        T diff = data[i] - average;
        sum += diff * diff;
    }

    return sum / static_cast<T>(Size - 1);
}

template<typename T>
inline T MARCH::Statistics::standardDeviation(const T variance) {
    return static_cast<T>(std::sqrt(variance));
}

template<typename T>
constexpr T MARCH::Statistics::coefficientOfVariation(const T average, const T standardDeviation) {
    if (average == T {})
        return T {};

    constexpr T kPercent = static_cast<T>(100);
    return (standardDeviation / average) * kPercent;
}

template<typename T, std::size_t Size>
constexpr T MARCH::Statistics::median(const T (&data)[Size]) {
    Detail::validateSize<Size>();
    T sorted[Size];
    for (std::size_t i = 0; i < Size; i++)
        sorted[i] = data[i];

    Detail::insertionSort(sorted);
    if constexpr ((Size & 1U) == 0U)
        return (sorted[(Size / 2) - 1] + sorted[Size / 2]) / static_cast<T>(2);

    return sorted[Size / 2];
}

template<typename T, std::size_t Size>
constexpr MARCH::StatisticsResult<T> MARCH::Statistics::calculate(const T (&data)[Size]) {
    Detail::validateSize<Size>();
    StatisticsResult<T> result {};
    result.count = Size;
    result.mean = mean(data);
    result.minimum = minimum(data);
    result.maximum = maximum(data);
    result.range = result.maximum - result.minimum;
    result.variance = variance(data, result.mean);
    result.standardDeviation = standardDeviation(result.variance);
    result.coefficientOfVariation = coefficientOfVariation(result.mean, result.standardDeviation);
    result.median = median(data);
    return result;
}
