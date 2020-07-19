#ifndef UNSCRIBE_DETAIL_INCLUDE_DETAIL_OVERLOAD_HPP
#define UNSCRIBE_DETAIL_INCLUDE_DETAIL_OVERLOAD_HPP

#include <unscribe/detail/version_namespace.hpp>

namespace unscribe::inline UNSCRIBE_DETAIL_VERSION_NAMESPACE::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename... Callables>
struct overload
: Callables...
{
    using Callables::operator()...;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
