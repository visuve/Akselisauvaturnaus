cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Akselisauvaturnaus" LANGUAGES CXX)

file(GLOB AkselisauvaSource "*.cpp" "*.hpp")

add_executable(Akselisauvaturnaus ${AkselisauvaSource})
target_precompile_headers(Akselisauvaturnaus PRIVATE "Akselisauvaturnaus.pch")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Akselisauvaturnaus PROPERTY CXX_STANDARD 23)
endif()
