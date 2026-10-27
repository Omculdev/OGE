#pragma once
#include <vector>
#include <memory>
#include "Calculations/General/Types.hpp"
#include "Utils/Concepts/BufferConcepts.hpp"
#include "Utils/General/Logger.hpp"
#include <cassert>
#include <GLAD/glad.h>
#include <iostream>
#include <span>
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
	std::vector<u32> free_indices = {};
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
		allocations(std::move(other.allocations)),
		free_indices(std::move(other.free_indices)),
		needs_defragmentation(other.needs_defragmentation)
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
		needs_defragmentation = other.needs_defragmentation;
		data = std::move(other.data);
		allocations = std::move(other.allocations);
		free_indices = std::move(other.free_indices);
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
			gl_basic_buffer_id = 0;
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
		for (auto& currentnode : allocations) {
			if (currentnode.active) {
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
	void clear() {
		if (gl_basic_buffer_id != 0) {
			glDeleteBuffers(1, &gl_basic_buffer_id);
			gl_basic_buffer_id = 0;
		}
		buffer_size_bytes = 0;
		used_size_bytes = 0;
		data.reset();
		allocations.clear();
		free_indices.clear();
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
	[[nodiscard]] BufferHandleType addBytes(usize size, const void* bufferdata, boolean active = true) {
		assert(used_size_bytes + size <= buffer_size_bytes, "BasicBuffer::addData: exceeded maximum buffer size");
		Allocation newallocation = {};
		newallocation.size = size;
		newallocation.active = active;
		newallocation.offset = used_size_bytes;
		memcpy(data.get() + newallocation.offset, bufferdata, size);
		used_size_bytes += newallocation.size;
		BufferHandleType newallocationhandle = {};
		if (free_indices.empty()) {
			newallocationhandle.setId(allocations.size()); // implicitly last index + 1
			allocations.push_back(newallocation);
		}
		else {
			u32 freeindex = free_indices.back();
			free_indices.pop_back();
			newallocationhandle.setId(freeindex);
			allocations[freeindex] = newallocation;
		}
		return newallocationhandle;
	}
	template <typename DataType>
	[[nodiscard]] BufferHandleType addData(std::span<const DataType> bufferdata, boolean active = true) {
		return addBytes(bufferdata.size_bytes(), bufferdata.data(), active);
	}
	void deleteData(BufferHandleType& bufferhandle) {
		if (!bufferhandle.getId().has_value()) {
			Logger::getInstance().logWarning("BasicBuffer::deleteData: attempted to access data via an invalid handle");
			return;
		}
		if (!allocations[bufferhandle.getIdValue()].active) return;
		allocations[bufferhandle.getIdValue()].active = false;
		needs_defragmentation = true;
		free_indices.push_back(bufferhandle.getIdValue());
		bufferhandle.invalidate();
	}
	void updateBytes(BufferHandleType& bufferhandle, usize size, const void* bufferdata, boolean active = true) {
		std::optional<u32> allocationindex = bufferhandle.getId();
		if (!allocationindex.has_value()) {
			Logger::getInstance().logWarning("BasicBuffer::updateBytes: attempted to update bytes via an invalid handle");
			return;
		}
		if (size > allocations[*allocationindex].size) {
			BufferHandleType newbufferhandle = addBytes(size, bufferdata, active);
			deleteData(bufferhandle);
			bufferhandle = std::move(newbufferhandle);
		}
		else {
			memcpy(data.get() + allocations[*allocationindex].offset, bufferdata, size);
			allocations[*allocationindex].active = active;
		}
	}
	template <typename DataType>
	void updateData(BufferHandleType& bufferhandle, std::span<const DataType> bufferdata, boolean active = true) {
		updateBytes(bufferhandle, bufferdata.size_bytes(), bufferdata.data(), active);
	}
	void allocateGpuMemory(u32 target, u32 usage) const {
		if (buffer_size_bytes == 0) {
			Logger::getInstance().logWarning("BasicBuffer::allocateGpuMemory: attempted to allocate 0 bytes of VRAM");
			return;
		}
		glBindBuffer(target, gl_basic_buffer_id);
		glBufferData(target, buffer_size_bytes, NULL, usage);
	}
	void sendDataToGpu(const BufferHandleType& bufferhandle, u32 target) {
		glBindBuffer(target, gl_basic_buffer_id);
		if (!bufferhandle.getId().has_value()) {
			Logger::getInstance().logWarning("BasicBuffer::sendDataToGpu: attempted to access data via an invalid handle");
			return;
		}
		glBufferSubData(target, allocations[bufferhandle.getIdValue()].offset, allocations[bufferhandle.getIdValue()].size, data.get() + allocations[bufferhandle.getIdValue()].offset);
	}
	u32 getGlBufferId() const {
		return gl_basic_buffer_id;
	}
	std::optional<usize> getOffset(const BufferHandleType& bufferhandle) const {
		if (!bufferhandle.getId().has_value()) {
			Logger::getInstance().logWarning("BasicBuffer::getOffset: attempted to access data via an invalid handle");
			return std::nullopt;
		}
		return allocations[bufferhandle.getIdValue()].offset;
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