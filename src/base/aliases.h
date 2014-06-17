#pragma once

#include <third_party/libcxx/exported/include/cstdint>
#include <third_party/libcxx/exported/include/functional>
#include <third_party/libcxx/exported/include/list>
#include <third_party/libcxx/exported/include/memory>
#include <third_party/libcxx/exported/include/string>
#include <third_party/libcxx/exported/include/unordered_map>
#include <third_party/libcxx/exported/include/unordered_set>

namespace dist_clang {

using i8 = int8_t;
using ui8 = uint8_t;
using i16 = int16_t;
using ui16 = uint16_t;
using i32 = int32_t;
using ui32 = uint32_t;
using i64 = int64_t;
using ui64 = uint64_t;

template <typename Signature>
using Fn = std::function<Signature>;

template <class T>
using List = std::list<T>;

template <class T>
using UniquePtr = std::unique_ptr<T>;

using String = std::string;

template <class U, class V = U>
using Pair = std::pair<U, V>;

template <class U, class V>
using HashMap = std::unordered_map<U, V>;

template <class U>
using HashSet = std::unordered_set<U>;

}  // namespace dist_clang