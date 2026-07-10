#pragma once

#include <cstddef>
#include <cstdint>

namespace MARCH {
    template<typename T>
    struct StatisticsResult {
        T mean {};
        T median {};
        T minimum {};
        T maximum {};
        T range {};
        T variance {};
        T standardDeviation {};
        T coefficientOfVariation {};
        std::size_t count {};
    };

    namespace Statistics {
        template<typename T, std::size_t Size>
        constexpr T mean(const T (&data)[Size]);

        template<typename T, std::size_t Size>
        constexpr T minimum(const T (&data)[Size]);

        template<typename T, std::size_t Size>
        constexpr T maximum(const T (&data)[Size]);

        template<typename T, std::size_t Size>
        constexpr T variance(const T (&data)[Size], const T average);

        template<typename T>
        inline T standardDeviation(const T variance);

        template<typename T>
        constexpr T coefficientOfVariation(const T average, const T standardDeviation);

        template<typename T, std::size_t Size>
        constexpr T median(const T (&data)[Size]);

        template<typename T, std::size_t Size>
        constexpr StatisticsResult<T> calculate(const T (&data)[Size]);
    }
}

#include "MARCH_Statistics.hpp"