#pragma once
#include "Utils/Rendering/Shaders/ShaderDescriptor.hpp"
#include "Utils/Enums/ShaderTypes.hpp"
#include <optional>
class ShaderLibrary {
public:
	[[nodiscard]] static inline std::optional<ShaderDescriptor> getShaderPaths(const ShaderType& shadertype) {
		switch (shadertype) {
		case ShaderType::none:
			return std::nullopt;
		case ShaderType::amount:
			return std::nullopt;
		case ShaderType::custom:
			return std::nullopt;
		case ShaderType::no_rotate_2D:
			return ShaderDescriptor(
				"Src/Shaders/NoRotate2DVertexShader.glsl",
				"Src/Shaders/NoRotate2DFragmentShader.glsl"
			);
			// add others later
		}
		return std::nullopt;
	}
};