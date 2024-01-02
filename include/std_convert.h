/*
 *  Create by YuSuiXian on 2024/01/02
 *  cpp std convert
 */

#ifndef __STD_CONVERT_H__
#define __STD_CONVERT_H__

#include <string>

#ifdef __WIN32__
#ifdef __has_include
#if __has_include(<Windows.h>)
#include <Windows.h>
#else
#error "Windows.h not found, dont support wstring convert"
#endif
#endif
#else
#if __cplusplus >= 201103L && __cplusplus < 201703L
#include <codecvt>
#include <locale>
#elif __cplusplus >= 201703L && __cplusplus < 202600L
#error "c++17 - c++20 not support std string convert"
#elif __cplusplus >= 202600L
#include <text_encoding>
#endif
#endif

#ifdef __WIN32__
inline std::string convert(UINT before_code, UINT after_code, const std::string &string)
{
    int len = MultiByteToWideChar(before_code, 0, string.c_str(), -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len * 2 + 2);
    MultiByteToWideChar(before_code, 0, string.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(after_code, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(after_code, 0, wstr, -1, str, len, NULL, NULL);
    std::string ret_string = str;
    delete[] wstr;
    delete[] str;
    return ret_string;
}
#endif

static std::string gbk_to_utf8(const std::string &source_gbk)
{
#ifdef __WIN32__
    return convert(CP_ACP, CP_UTF8, source_gbk);
#else
#if __cplusplus >= 201103L && __cplusplus < 201703L
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring temp = convert.from_bytes(source_gbk);
    return std::string(temp.begin(), temp.end());
#elif __cplusplus >= 201703L && __cplusplus < 202600L
    throw std::runtime_error("c++17 - c++20 not implement");
#elif __cplusplus >= 202600L
    throw std::runtime_error("c++26 not implement");
#else
#endif
#endif
}

static std::string utf8_to_gbk(const std::string &source_utf8)
{
#ifdef __WIN32__
    return convert(CP_UTF8, CP_ACP, source_utf8);
#else
#if __cplusplus >= 201103L && __cplusplus < 201703L
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring temp = convert.from_bytes(source_utf8);
    return std::string(temp.begin(), temp.end());
#elif __cplusplus >= 201703L && __cplusplus < 202600L
    throw std::runtime_error("c++17 - c++20 not implement");
#elif __cplusplus >= 202600L
    throw std::runtime_error("c++26 not implement");
#else
#endif
#endif
}

static bool is_utf8(const std::string &source)
{
#ifdef __WIN32__
    return convert(CP_UTF8, CP_UTF8, source) == source;
#else
#if __cplusplus >= 201103L && __cplusplus < 201703L
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring temp = convert.from_bytes(source);
    return convert.to_bytes(temp) == source;
#elif __cplusplus >= 201703L && __cplusplus < 202600L
    throw std::runtime_error("c++17 - c++20 not implement");
#elif __cplusplus >= 202600L
    throw std::runtime_error("c++26 not implement");
#else
    bool result = true;
    for (auto &c : source)
    {
        if (c & 0x80)
        {
            result = false;
            break;
        }
    }
    return result;
#endif
#endif
}

static bool is_gbk(const std::string &source)
{
#ifdef __WIN32__
    return convert(CP_ACP, CP_ACP, source) == source;
#else
#if __cplusplus >= 201103L && __cplusplus < 201703L
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring temp = convert.from_bytes(source);
    return convert.to_bytes(temp) == source;
#elif __cplusplus >= 201703L && __cplusplus < 202600L
    throw std::runtime_error("c++17 - c++20 not implement");
#elif __cplusplus >= 202600L
    throw std::runtime_error("c++26 not implement");
#else
    bool result = true;
    for (auto &c : source)
    {
        if (c & 0x80)
        {
            result = false;
            break;
        }
    }
    return result;
#endif
#endif
}

static std::string to_utf8(const std::string &source)
{
    return is_gbk(source) ? gbk_to_utf8(source) : source;
}

static std::string to_gbk(const std::string &source)
{
    return is_utf8(source) ? utf8_to_gbk(source) : source;
}

#endif // __STD_CONVERT_H__
