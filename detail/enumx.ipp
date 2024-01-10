#pragma once

#include <stdexcept>

namespace enumx
{

template <typename EnumT>
class Map
{
public:
  std::string_view string(EnumT val) const
  {
    for (const auto& [id, name] : m_pairs)
      if (id == val)
        return name;
    throw std::logic_error(__PRETTY_FUNCTION__);
  }

  std::optional<EnumT> value(std::string_view str) const
  {
    for (const auto& [val, name] : m_pairs)
      if (name == str)
        return val;
    return {};
  }

  Map<EnumT>& operator()(EnumT val, std::string_view str)
  {
    m_pairs.push_back({val, str});
    return *this;
  }

private:
  std::vector<std::pair<EnumT, std::string_view>> m_pairs;
};

template <typename EnumT>
const Map<EnumT>& map()
{
  static auto the_map = [] {
    Map<EnumT> the_map;
    define(the_map);
    return the_map;
  }();

  return the_map;
}

template <typename EnumT>
std::string_view get(EnumT val)
{
  return map<EnumT>().string(val);
}

template <typename EnumT>
std::optional<EnumT> get(std::string_view str)
{
  return map<EnumT>().value(str);
}

template <typename EnumT>
const std::vector<std::pair<EnumT, std::string_view>>& all()
{
  return map<EnumT>().pairs;
}

} // namespace enumx

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>

#define MK_PAIR_ENUMERATOR(r, E, constant) (E::constant, BOOST_PP_STRINGIZE(constant))
#define MK_CASE_ENUMERATOR(r, E, constant) case E::constant:

#define ENUMX(E, constants)                                     \
namespace enumx                                                 \
{                                                               \
template <>                                                     \
void define(Map<E>& map)                                        \
{                                                               \
  map                                                           \
    BOOST_PP_SEQ_FOR_EACH(MK_PAIR_ENUMERATOR, E, constants);    \
}                                                               \
                                                                \
void completeness_check(E e)                                    \
{                                                               \
  switch (e) {                                                  \
    BOOST_PP_SEQ_FOR_EACH(MK_CASE_ENUMERATOR, E, constants);    \
    break;                                                      \
  }                                                             \
}                                                               \
} // namespace enumx
