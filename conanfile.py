from conans import ConanFile, CMake, tools
import os


class MyTestConan(ConanFile):
    name = "my-test"
    version = "1.8.2"
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    requires = [
       
    ]
    generators = "cmake_find_package"
    _cmake = None

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def source(self):
        git = tools.Git(folder=self._source_subfolder)
        git.clone("", "test")

    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        self._cmake = CMake(self)
        if self.settings.os == "Android":
            self._cmake.definitions["Android"] = "True"
            self._cmake.definitions["CONAN_CMAKE_TOOLCHAIN_FILE"] = \
                os.getenv("CONAN_CMAKE_TOOLCHAIN_FILE")
            self._cmake.definitions["ANDROID_ABI"] = os.getenv("ANDROID_ABI")
            self._cmake.definitions["ANDROID_NATIVE_API_LEVEL"] = \
                os.getenv("ANDROID_NATIVE_API_LEVEL")
        self._cmake.definitions["CMAKE_BUILD_TYPE"] = self.settings.build_type
        self._cmake.configure(build_folder=self._build_subfolder)
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("*", src=os.path.join(self.source_folder, "output",
                                        self.name),  keep_path=True)

    def package_info(self):
        self.cpp_info.libs = [self.name]
        self.cpp_info.names["cmake_find_package"] = self.name
        self.cpp_info.set_property("cmake_find_mode", "both")
        self.cpp_info.set_property("cmake_find_name", self.name)
