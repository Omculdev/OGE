#pragma once
#include <vector>
#include <memory>
#include "Calculations/General/Types.hpp"
#include "Utils/Concepts/BufferConcepts.hpp"
#include "Utils/General/Logger.hpp"
#include <cassert>
#include <GLAD/glad.h>
#include <iostream>
template <typename BufferHandleType>
requires IsBufferHandle<BufferHandleType>
class BasicBuffer {
private:
	u32 gl_basic_buffer_id = {};
	struct Allocation {
		usize size = {};
		usize offset = {};
		boolean active = {};
	};
	usize buffer_size_bytes = {};
	usize used_size_bytes = {};
	std::unique_ptr<byte[]> data = {};
	std::vector<Allocation> allocations = {};
	boolean needs_defragmentation = {};
	void gen_gl_buffer() {
		glGenBuffers(1, &gl_basic_buffer_id);
	}
public:
	BasicBuffer() = default;
	BasicBuffer(const BasicBuffer& other) = delete;
	BasicBuffer& operator=(const BasicBuffer& other) = delete;
	BasicBuffer(BasicBuffer&& other) noexcept :
		gl_basic_buffer_id(other.gl_basic_buffer_id),
		buffer_size_bytes(other.buffer_size_bytes),
		used_size_bytes(other.used_size_bytes),
		data(std::move(other.data)),
		allocations(std::move(other.allocations))
	{
		other.gl_basic_buffer_id = 0;
		other.buffer_size_bytes = 0;
		other.used_size_bytes = 0;
	}
	BasicBuffer& operator=(BasicBuffer&& other) noexcept {
		if (this == &other) return *this;
		if (gl_basic_buffer_id != 0) {
			glDeleteBuffers(1, &gl_basic_buffer_id);
		}
		gl_basic_buffer_id = other.gl_basic_buffer_id;
		buffer_size_bytes = other.buffer_size_bytes;
		used_size_bytes = other.used_size_bytes;
		data = std::move(other.data);
		allocations = std::move(other.allocations);
		other.gl_basic_buffer_id = 0;
		other.buffer_size_bytes = 0;
		other.used_size_bytes = 0;
		return *this;
	}
	void init() {
		gen_gl_buffer();
		buffer_size_bytes = 1024 * 1024;
		data = std::make_unique<byte[]>(buffer_size_bytes);
	}
	void init(usize sizebytes) {
		gen_gl_buffer();
		buffer_size_bytes = sizebytes;
		data = std::make_unique<byte[]>(buffer_size_bytes);
	}
	~BasicBuffer() {
		if (gl_basic_buffer_id != 0) {
			glDeleteBuffers(1, &gl_basic_buffer_id);
		}
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
		usize olddataoffset = 0;
		usize newdataoffset = 0;
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
		needs_defragmentation = false;
	}
	void sendEverythingToGpu(u32 target) {
		if (used_size_bytes == 0) {
			Logger::getInstance().logWarning("BasicBuffer::sendEverythingToGpu: attempted to send 0 bytes to gpu");
			return;
		}
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferSubData(target, 0, used_size_bytes, data.get());
	}
	template <typename ElementType>
	[[nodiscard]] BufferHandleType addElements(const std::vector<ElementType>& vertices, boolean active = true) {
		usize newitemsizebytes = vertices.size() * sizeof(ElementType);
		assert(used_size_bytes + newitemsizebytes <= buffer_size_bytes, "BasicBuffer::addElements: exceeded maximum buffer size");
		Allocation newallocation = {};
		newallocation.size = newitemsizebytes;
		newallocation.active = active;
		newallocation.offset = used_size_bytes;
		memcpy(data.get() + newallocation.offset, vertices.data(), newitemsizebytes);
		used_size_bytes += newallocation.size;
		BufferHandleType newallocationhandle = {};
		newallocationhandle.index = allocations.size(); // implicitly last index + 1
		allocations.push_back(newallocation);
		return newallocationhandle;
	}
	[[nodiscard]] BufferHandleType addBytes(usize size, const void* vertices) {
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
	void deleteElements(const BufferHandleType& handle) {
		allocations[handle.index].active = false;
		needs_defragmentation = true;
	}
	void allocateGpuMemory(u32 target, u32 usage) const {
		if (buffer_size_bytes == 0) {
			Logger::getInstance().logWarning("BasicBuffer::allocateGpuMemory: attempted to allocate 0 bytes of VRAM");
			return;
		}
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferData(target, buffer_size_bytes, NULL, usage);
	}
	void sendDataToGpu(u32 target) {
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferSubData(target, allocations.back().offset, allocations.back().size, data.get() + allocations.back().offset);
	}
	u32 getGlBufferId() const {
		return gl_basic_buffer_id;
	}
	usize getOffset(const BufferHandleType& handle) const {
		return allocations[handle.index].offset;
	}
	usize getBufferSize() const {
		return buffer_size_bytes;
	}
	usize getUsedBufferSize() const {
		return used_size_bytes;
	}
	boolean needsDefragmentation() const {
		return needs_defragmentation;
	}
};