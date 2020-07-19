from conans import ConanFile, tools, CMake

class UnscribeConan(ConanFile):
    name = 'unscribe'
    version = tools.load('VERSION').strip()

    license = 'MIT'
    url = 'https://github.com/yuri-kilochek/unscribe'
    description = "C++20 coroutine-based L-attributed grammar Earley parser"
    author = 'Yuri Kilochek <yuri.kilochek@gmail.com>'

    exports = (
        'VERSION',
    )
    exports_sources = (
        'CMakeLists.txt',
        'include/*',
        'tests/*',
    )
    generators = (
        'cmake_paths',
        'cmake_find_package',
    )
    no_copy_source = True

    _run_tests = tools.get_env('CONAN_RUN_TESTS', True)

    def build_requirements(self):
        if self._run_tests:
            self.build_requires('doctest/2.4.0')

    def build(self):
        cmake = CMake(self)
        cmake.configure(defs={'BUILD_TESTING': self._run_tests})
        cmake.build()
        cmake.install()
        if self._run_tests:
            output_on_failure = tools.get_env('CTEST_OUTPUT_ON_FAILURE', False)
            cmake.test(output_on_failure=output_on_failure)

    def package_id(self):
        self.info.header_only()
