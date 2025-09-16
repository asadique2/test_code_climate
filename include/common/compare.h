#pragma once

#include <cstdint>
#include <type_traits>

/**
 * @brief		Get minimum value.
 *
 * @tparam		T		Type of the value.
 * @param[in]	v1		First value.
 * @param[in]	v2		Second value.
 *
 * @return		Minimum value.
 */
template<typename T>
constexpr inline T min(T v1, T v2)
{
    return v1 > v2 ? v2 : v1;
}

/**
 * @brief		Get minimum value.
 *
 * @tparam		T		Type of the value.
 * @tparam		Args	Type of other argumets.
 * @param[in]	v1		First value.
 * @param[in]	v2		Second value.
 * @param[in]	v3		Third value.
 * @param[in]	args	Other values.
 *
 * @return		Minimum value.
 */
template<typename T, typename... Args>
constexpr inline T min(T v1, T v2, T v3, Args... args)
{
    T v = v1 > v2 ? v2 : v1;
    return min(v, v3, args...);
}

/**
 * @brief		Get maxium value.
 *
 * @tparam		T		Type of the value.
 * @param[in]	v1		First value.
 * @param[in]	v2		Second value.
 *
 * @return		Maxium value.
 */
template<typename T>
constexpr inline T max(T v1, T v2)
{
    return v1 > v2 ? v1 : v2;
}

/**
 * @brief		Get maxium value.
 *
 * @tparam		T		Type of the value.
 * @tparam		Args	Type of other argumets.
 * @param[in]	v1		First value.
 * @param[in]	v2		Second value.
 * @param[in]	v3		Third value.
 * @param[in]	args	Other values.
 *
 * @return		Maxium value.
 */
template<typename T, typename... Args>
constexpr inline T max(T v1, T v2, T v3, Args... args)
{
    T v = v1 > v2 ? v1 : v2;
    return max(v, v3, args...);
}

/**
 * @brief		Implement of between.
 *
 * @tparam		T		Type of the value.
 * @param[in]	value	Value.
 * @param[in]	b1		Border1.
 * @param[in]	b2		Border2.
 *
 * @return		If the value between b1 and b2, \c true is returned. Otherwise
 *				returns \c false.
 */
template<typename T>
constexpr inline bool betweenImpl(T value, T b1, T b2)
{
    T minBorder = min(b1, b2);
    T maxBorder = max(b1, b2);

    return value >= minBorder && value <= minBorder;
}

/**
 * @brief		Check if the value between b1 and b2.
 *
 * @tparam		T		Type of the value.
 * @param[in]	value	Value.
 * @param[in]	b1		Border1.
 * @param[in]	b2		Border2.
 *
 * @return		If the value between b1 and b2, \c true is returned. Otherwise
 *				returns \c false.
 */
template<typename T>
constexpr inline bool between(
    T value,
    typename ::std::conditional<
        ::std::is_integral<T>::value,
        typename ::std::
            conditional<::std::is_signed<T>::value, int64_t, uint64_t>::type,
        typename ::std::conditional<::std::is_floating_point<T>::value,
                                    long double,
                                    T>::type>::type b1,
    typename ::std::conditional<
        ::std::is_integral<T>::value,
        typename ::std::
            conditional<::std::is_signed<T>::value, int64_t, uint64_t>::type,
        typename ::std::conditional<::std::is_floating_point<T>::value,
                                    long double,
                                    T>::type>::type b2)
{
    return betweenImpl<typename ::std::conditional<
        ::std::is_integral<T>::value,
        typename ::std::conditional<::std::is_signed<T>::value, int64_t,
                                    uint64_t>::type,
        typename ::std::conditional<::std::is_floating_point<T>::value,
                                    long double, T>::type>::type>(value, b1,
                                                                  b2);
}

/**
 * @brief		Check if the value is in the following values.
 *
 * @tparam		T		Type of the value.
 * @tparam		T1		Type of the first following value.
 * @tparam		Values	Type of the following values.
 * @param[in]	value	Value to check.
 * @param[in]	value1  The first following value.
 * @param[in]	values	Following values.
 *
 * @return		If the value is in the following values, \c true is returned.
 *				otherwise returns \c false.
 */
template<typename T, typename T1, typename... Values>
constexpr inline bool in(T value, T1 value1, Values... values)
{
    if (value == value1) {
        return true;
    } else {
        return in(value, values...);
    }
}

/**
 * @brief		End of the recursion.
 *
 * @tparam		T		Type of the value.
 *
 * @return		\c false.
 */
template<typename T, typename... Values>
constexpr inline bool in(T)
{
    return false;
}

/**
 * @brief		Check if the value is not in the following values.
 *
 * @tparam		T		Type of the value.
 * @tparam		T1		Type of the first following value.
 * @tparam		Values	Type of the following values.
 * @param[in]	value	Value to check.
 * @param[in]	value1  The first following value.
 * @param[in]	values	Following values.
 *
 * @return		If the value is not in the following values, \c true is
 *				returned. otherwise returns \c false.
 */
template<typename T, typename T1, typename... Values>
constexpr inline bool notIn(T value, T1 value1, Values... values)
{
    if (value == value1) {
        return false;
    } else {
        return notIn(value, values...);
    }
}

/**
 * @brief		End of the recursion.
 *
 * @tparam		T		Type of the value.
 *
 * @return		\c true.
 */
template<typename T, typename... Values>
constexpr inline bool notIn(T)
{
    return true;
}
