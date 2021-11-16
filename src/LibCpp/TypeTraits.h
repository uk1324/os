#pragma once

template <typename T>
struct MakeUnsigned
{ typedef T type; };

template<>
struct MakeUnsigned<char>
{ typedef unsigned char type; };

template<>
struct MakeUnsigned<short>
{ typedef unsigned short type; };

template<>
struct MakeUnsigned<int>
{ typedef unsigned int type; };

template<>
struct MakeUnsigned<long>
{ typedef unsigned long type; };

template<>
struct MakeUnsigned<long long>
{ typedef unsigned long long type; };

template<typename T>
using MakeUnsignedT = typename MakeUnsigned<T>::type;