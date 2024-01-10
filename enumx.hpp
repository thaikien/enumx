#pragma once

#include <string_view>
#include <optional>
#include <vector>

namespace enumx
{

/// Return the string representation
/// of the given enumerator constant
template <typename EnumT>
std::string_view get(EnumT);

/// Given the enumeration type,
/// try to return the enumerator constant from a string
template <typename EnumT>
std::optional<EnumT> get(std::string_view);

/// Given the enumeration type,
/// return the complete list of its enumerator constants
/// along with their string representation
template <typename EnumT>
const std::vector<std::pair<EnumT, std::string_view>>& all();

}

namespace enumx
{
/// Forward declaration of an implementation detail
template <typename EnumT>
class Map;

/// Function to define by user to be able to use three functions above.
///
/// User should never define this function directly but
/// use the helper macro ENUMX.
/// Ex.
///
/// in E.hpp:
/// enum E { e0, e1, e2 };
///
/// then in E.cpp:
/// ENUMX(E, (e0)(e1)(e2))
///
template <typename EnumT>
void define(Map<EnumT>&);

}

#include "detail/enumx.ipp"
