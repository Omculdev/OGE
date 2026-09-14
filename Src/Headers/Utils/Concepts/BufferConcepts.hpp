#pragma once
#include "Utils/VideoMemory/ElementBufferHandle.hpp"
#include "Utils/VideoMemory/VertexBufferHandle.hpp"
#include <type_traits>
#include <concepts>
template <typename Type>
concept IsBufferHandle = std::same_as<VertexBufferHandle, Type> || std::same_as<ElementBufferHandle, Type>;