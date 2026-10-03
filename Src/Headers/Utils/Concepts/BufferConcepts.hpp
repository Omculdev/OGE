#pragma once
#include "Utils/Rendering/VideoMemory/ElementBufferHandle.hpp"
#include "Utils/Rendering/VideoMemory/VertexBufferHandle.hpp"
#include <type_traits>
#include <concepts>
template <typename Type>
concept IsBufferHandle = std::same_as<VertexBufferHandle, Type> || std::same_as<ElementBufferHandle, Type>;