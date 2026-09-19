#pragma once
#include <vector>
#include <memory>
#include "Calculations/General/Types.hpp"
#include "Utils/Concepts/BufferConcepts.hpp"
#include "Utils/General/Logger.hpp"
#include <cassert>
#include <GLAD/glad.h>
template <typename BufferHandleType>
requires IsBufferHandle<BufferHandleType>
class BasicBuffer {
private:
	u32 gl_basic_buffer_id = {};
	struct Allocation {
		u32 size = {};
		u32 offset = {};
		boolean active = {};
	};
	usize buffer_size_bytes = {};
	usize used_size_bytes = {};
	std::unique_ptr<byte[]> data = {};
	std::vector<Allocation> allocations = {};
	void gen_gl_buffer() {
		glGenBuffers(1, &gl_basic_buffer_id);
	}
public:
	BasicBuffer(const BasicBuffer& other) = delete;
	BasicBuffer(BasicBuffer&& other) = delete;
	BasicBuffer& operator=(const BasicBuffer& other) = delete;
	BasicBuffer& operator=(BasicBuffer&& other) = delete;
	BasicBuffer() {
		gen_gl_buffer();
		buffer_size_bytes = 1024*1024;
		data = std::make_unique<byte[]>(buffer_size_bytes);
	}
	BasicBuffer(usize sizebytes) {
		gen_gl_buffer();
		buffer_size_bytes = sizebytes;
		data = std::make_unique<byte[]>(buffer_size_bytes);
	}
	~BasicBuffer() {
		glDeleteBuffers(1, &gl_basic_buffer_id);
	}
	void increaseBufferSize(usize byteamount) {
		if (byteamount < buffer_size_bytes) {
			Logger::getInstance().logWarning("VertexBuffer::increaseBufferSize: the new buffer size is less than the current one");
			return; // and log error
		}
		byte* newdata = new byte[byteamount];
		memcpy(newdata, data.get(), used_size_bytes);
		buffer_size_bytes = byteamount;
		data.reset(newdata);
	}
	void defragmentBuffer() {
		byte* newdata = new byte[buffer_size_bytes];
		u32 olddataoffset = 0;
		u32 newdataoffset = 0;
		used_size_bytes = 0;
		for (int currentnodeindex = 0; currentnodeindex < allocations.size(); currentnodeindex++) {
			auto& currentnode = allocations[currentnodeindex];
			if (allocations.at(currentnodeindex).active) {
				memcpy(newdata + newdataoffset, data.get() + olddataoffset, currentnode.size);
				currentnode.offset = newdataoffset;
				olddataoffset += currentnode.size;
				newdataoffset += currentnode.size;
			}
			else {
				olddataoffset += currentnode.size;
			}
		}
		used_size_bytes = newdataoffset;
		data.reset(newdata);
	}
	[[nodiscard]] BufferHandleType addElements(usize size, const void* vertices) {
		assert(used_size_bytes + size <= buffer_size_bytes, "BasicBuffer::addElements: exceeded maximum buffer size");
		Allocation newallocation = {};
		newallocation.size = size;
		newallocation.active = true;
		newallocation.offset = used_size_bytes;
		memcpy(data.get() + newallocation.offset, vertices, size);
		used_size_bytes += newallocation.size;
		BufferHandleType newallocationhandle;
		newallocationhandle.index = allocations.size(); // implicitly last index + 1
		allocations.push_back(newallocation);
		return newallocationhandle;
	}
	void deleteVertices(const BufferHandleType& handle) {
		allocations[handle.index].active = false;
	}
	void allocateGpuMemory(u32 target, u32 usage) const {
		if (buffer_size_bytes == 0) {
			Logger::getInstance().logWarning("BasicBuffer::allocateGpuMemory: attempted to allocate 0 bytes of VRAM");
			return;
		}
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferData(target, buffer_size_bytes, NULL, usage);
	}
	void sendDataToGpu(u32 target, u32 usage) {
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferSubData(target, allocations.back().offset, allocations.back().size, data.get() + allocations.back().offset);
	}
	u32 getGlBufferId() const {
		return gl_basic_buffer_id;
	}
	u32 getOffset(const BufferHandleType& handle) const {
		return allocations[handle.index].offset;
	}
};