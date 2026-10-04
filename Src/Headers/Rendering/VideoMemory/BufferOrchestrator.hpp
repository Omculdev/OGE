#pragma once
#include "Rendering/VideoMemory/VertexBuffer.hpp"
#include "Rendering/VideoMemory/ElementBuffer.hpp"
#include "Utils/Rendering/VideoMemory/Mesh.hpp"
#include "Utils/Rendering/VideoMemory/Vertex.hpp"
#include "Rendering/VideoMemory/VertexArray.hpp"
// depricated
class BufferOrchestrator {
private:
	VertexBuffer vertex_buffer = {};
	std::vector<ElementBuffer> element_buffers = {};
	usize vertex_buffer_defragmentation_threshold_bytes = {};
	usize element_buffer_defragmentation_threshold_bytes = {};
	template <typename VertexType, typename IndexType>
	[[nodiscard]] Mesh save_data(std::vector<VertexType> vertices, std::vector<IndexType> indeces, usize elementbufferindex = 0) {
		Mesh mesh;
		mesh.vertex_buffer_handle = vertex_buffer.addElements<VertexType>(vertices);
		mesh.element_buffer_handle = element_buffers[elementbufferindex].addElements<IndexType>(indeces);
		return mesh;
	}
	void send_latest_data_to_gpu_and_save_to_vertex_array(
		const VertexArray& vertexarray,
		u32 vertexbufferusage,
		u32 elementbufferusage,
		usize elementbufferindex = 0
	);
	void create_initial_element_buffer();
	void create_vertex_buffer();
	void init_initial_element_buffer(const VertexArray& vertexarray, u32 elementbufferusage);
	void init_vertex_buffer(u32 vertexbufferusage);
	void init_members(const VertexArray& vertexarray, u32 vertexbufferusage, u32 elementbufferusage);
public:
	BufferOrchestrator() = default;
	BufferOrchestrator(const BufferOrchestrator& other) = delete;
	BufferOrchestrator& operator=(const BufferOrchestrator& other) = delete;
	void init(const VertexArray& vertexarray, u32 vertexbufferusage, u32 elementbufferusage);
	template <typename VertexType, typename IndexType>
	[[nodiscard]] Mesh saveDataAndSendToGpu(
		const VertexArray& vertexarray,
		std::vector<VertexType> vertices,
		std::vector<IndexType> indeces,
		u32 vertexbufferusage,
		u32 elementbufferusage,
		usize elementbufferindex = 0
	) {
		Mesh saveddatamesh = save_data<VertexType, IndexType>(vertices, indeces);
		send_latest_data_to_gpu_and_save_to_vertex_array(
			vertexarray, 
			vertexbufferusage,
			elementbufferusage,
			elementbufferindex
		);
		return saveddatamesh;
	}
	void updateBuffers(std::vector<usize> elementbufferindecestoclear = {0});
};