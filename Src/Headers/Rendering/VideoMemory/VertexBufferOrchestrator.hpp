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
	void init_members(
		usize staticalbuffersizebytes,
		usize dynamicalbuffersizebytes,
		usize staticalbufferdefragmentationthresholdbytes,
		usize dynamicalbufferdefragmentationthresholdbytes
	);
	void defragment_buffer_and_send_to_gpu(VertexBuffer& buffer, usize defragmentationthreshold);
public:
	VertexBufferOrchestrator() = default;
	VertexBufferOrchestrator(const VertexBufferOrchestrator& other) = delete;
	VertexBufferOrchestrator& operator=(const VertexBufferOrchestrator& other) = delete;
	VertexBufferOrchestrator(VertexBufferOrchestrator&& other) noexcept;
	VertexBufferOrchestrator& operator=(VertexBufferOrchestrator&& other) noexcept;
	void init(
		usize staticalbuffersizebytes = 1024 * 1024,
		usize dynamicalbuffersizebytes = 1024 * 1024,
		usize staticalbufferdefragmentationthresholdbytes = 800 * 1024,
		usize dynamicalbufferdefragmentationthresholdbytes = 800 * 1024,
		u32 staticalbufferusage = GL_STATIC_DRAW,
		u32 dynamicalbufferusage = GL_DYNAMIC_DRAW
	);
	template <typename VertexType>
	[[nodiscard]] std::optional<VertexBufferHandle> saveVertexDataAndSendToGpu(
		std::span<const VertexType> vertices,
		const VertexBufferType& vertexbuffertype = VertexBufferType::dynamical,
		boolean active = true
	) {
		VertexBufferHandle datahandle;
		switch (vertexbuffertype) {
		case VertexBufferType::none:
		case VertexBufferType::amount:
			Logger::getInstance().logWarning("VertexBufferOrchestrator::saveVertexDataAndSendToGpu: invalid vertex buffer type");
			return std::nullopt;
		case VertexBufferType::statical:
			datahandle = statical_vertex_buffer.addData<VertexType>(vertices, active);
			statical_vertex_buffer.sendDataToGpu(datahandle, GL_ARRAY_BUFFER);
			break;
		case VertexBufferType::dynamical:
			datahandle = dynamical_vertex_buffer.addData<VertexType>(vertices, active);
			dynamical_vertex_buffer.sendDataToGpu(datahandle, GL_ARRAY_BUFFER);
			break;
		default:
			return std::nullopt;
		}
		return datahandle;
	}
	template <typename VertexType>
	void updateVertexDataAndSendToGpu(
		VertexBufferHandle& vertexbufferhandle,
		std::span<const VertexType> newvertices,
		const VertexBufferType& vertexbuffertype = VertexBufferType::dynamical,
		boolean active = true
	) {
		switch (vertexbuffertype) {
		case VertexBufferType::none:
		case VertexBufferType::amount:
			Logger::getInstance().logWarning("VertexBufferOrchestrator::updateVertexDataAndSendToGpu: invalid vertex buffer type");
			return;
		case VertexBufferType::statical:
			statical_vertex_buffer.updateData<VertexType>(vertexbufferhandle, newvertices, active);
			statical_vertex_buffer.sendDataToGpu(vertexbufferhandle, GL_ARRAY_BUFFER);
			break;
		case VertexBufferType::dynamical:
			dynamical_vertex_buffer.updateData<VertexType>(vertexbufferhandle, newvertices, active);
			dynamical_vertex_buffer.sendDataToGpu(vertexbufferhandle, GL_ARRAY_BUFFER);
			break;
		}
	}
	[[nodiscard]] std::optional<usize> getVertexBufferOffset(const VertexBufferHandle& vertexbufferhandle, const VertexBufferType& vertexbuffertype) const;
	void deleteData(VertexBufferHandle& vertexbufferhandle, const VertexBufferType& vertexbuffertype);
	[[nodiscard]] std::optional<u32> getGlVertexBufferId(const VertexBufferType& vertexbuffertype) const;
	void updateBuffers();
};