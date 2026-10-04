#pragma once
#include "Rendering/VideoMemory/VertexBuffer.hpp"
#include "Utils/Enums/VertexBufferTypes.hpp"
#include "Utils/General/Logger.hpp"
#include <utility>
#include <optional>
class VertexBufferOrchestrator {
private:
	VertexBuffer statical_vertex_buffer = {};
	VertexBuffer dynamical_vertex_buffer = {};
	usize dynamical_buffer_defragmentation_threshold_bytes = {};
	usize statical_buffer_defragmentation_threshold_bytes = {};
	void init_members();
	void defragment_buffer_and_send_to_gpu(VertexBuffer& buffer, usize defragmentationthreshold);
public:
	VertexBufferOrchestrator() = default;
	VertexBufferOrchestrator(const VertexBufferOrchestrator& other) = delete;
	VertexBufferOrchestrator& operator=(const VertexBufferOrchestrator& other) = delete;
	VertexBufferOrchestrator(VertexBufferOrchestrator&& other) noexcept;
	VertexBufferOrchestrator& operator=(VertexBufferOrchestrator&& other) noexcept;
	void init(u32 staticalbufferusage = GL_STATIC_DRAW, u32 dynamicalbufferusage = GL_DYNAMIC_DRAW);
	template <typename DataType>
	[[nodiscard]] std::optional<VertexBufferHandle> saveDataAndSendToGpu(
		const std::vector<DataType>& data,
		const VertexBufferType& vertexbuffertype = VertexBufferType::dynamical,
		boolean active = true
	) {
		VertexBufferHandle datahandle;
		switch (vertexbuffertype) {
		case VertexBufferType::none:
		case VertexBufferType::amount:
			Logger::getInstance().logWarning("VertexBufferOrchestrator::saveData: invalid vertex buffer type");
			return std::nullopt;
		case VertexBufferType::statical:
			datahandle = statical_vertex_buffer.addElements<DataType>(data, active);
			statical_vertex_buffer.sendDataToGpu(GL_ARRAY_BUFFER);
			break;
		case VertexBufferType::dynamical:
			datahandle = dynamical_vertex_buffer.addElements<DataType>(data, active);
			dynamical_vertex_buffer.sendDataToGpu(GL_ARRAY_BUFFER);
			break;
		default:
			return std::nullopt;
		}
		return datahandle;
	}
	void updateBuffers();
};