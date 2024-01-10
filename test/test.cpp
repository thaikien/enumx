#include "enumx.hpp"

#define REQUIRE(expression)                     \
  do {                                          \
    if (expression)                             \
      printf("OK!\n");                          \
    else                                        \
      printf("Failed: %s\n", #expression);      \
  } while (false)


namespace ns1::ns2 {
enum class Se : std::size_t { se0, se1, se2 };

enum Use { use0, use1, use2 };
}

ENUMX(ns1::ns2::Se, (se0)(se1)(se2))

ENUMX(ns1::ns2::Use, (use0)(use1)(use2))

int main(int argc, char* argv[])
{
  {
    auto str = enumx::get(ns1::ns2::Se::se2);
    auto val = enumx::get<ns1::ns2::Se>(str);

    REQUIRE(ns1::ns2::Se::se2 == val);
  }
  {
    auto str = enumx::get(ns1::ns2::Use::use1);
    auto val = enumx::get<ns1::ns2::Use>(str);

    REQUIRE(ns1::ns2::use1 == val);
  }
  return 0;
}

