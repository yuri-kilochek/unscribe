#ifndef UNSCRIBE_DETAIL_INCLUDE_DETAIL_PP_JOIN_HPP
#define UNSCRIBE_DETAIL_INCLUDE_DETAIL_PP_JOIN_HPP

///////////////////////////////////////////////////////////////////////////////

#define UNSCRIBE_DETAIL_PP_JOIN_IMPL(a, b) \
    a ## b                                 \
//                                         \

#define UNSCRIBE_DETAIL_PP_JOIN(a, b)  \
    UNSCRIBE_DETAIL_PP_JOIN_IMPL(a, b) \
//                                     \

///////////////////////////////////////////////////////////////////////////////

#endif
