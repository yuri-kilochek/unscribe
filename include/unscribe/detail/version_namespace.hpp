#ifndef UNSCRIBE_DETAIL_INCLUDE_DETAIL_VERSION_NAMESPACE_HPP
#define UNSCRIBE_DETAIL_INCLUDE_DETAIL_VERSION_NAMESPACE_HPP

#include <unscribe/version.hpp>
#include <unscribe/detail/pp/join.hpp>

///////////////////////////////////////////////////////////////////////////////

#define UNSCRIBE_DETAIL_VERSION_NAMESPACE \
    UNSCRIBE_DETAIL_PP_JOIN(v, UNSCRIBE_VERSION_MAJOR)

///////////////////////////////////////////////////////////////////////////////

#endif
