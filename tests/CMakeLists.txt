find_package(doctest REQUIRED)
include(doctest)

add_executable(tests
    main.cpp

    detail/generator.cpp
)
target_link_libraries(tests PRIVATE
    unscribe
    doctest::doctest
)
doctest_discover_tests(tests)
