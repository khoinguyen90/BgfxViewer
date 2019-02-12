#pragma once

#include "../renderer/GeometryBuffer.h"
#include "../core/Base.h"
#include "bgfx/bgfx.h"

namespace MimicViewer
{
class BGFXIndexBuffer : public GeometryBuffer
{
	enum IndexFormat
	{
		INDEX8 = 0x1401, //@@GL_UNSIGNED_BYTE,
		INDEX16 = 0x1403, //@@GL_UNSIGNED_SHORT,
		INDEX32 = 0x1405, //@@GL_UNSIGNED_INT
	};

public:
    BGFXIndexBuffer(const IndexFormat indexFormat, uint32_t indexCount, bool dynamic);
    virtual ~BGFXIndexBuffer();
    void set(const void* data, uint32_t count, uint32_t start) override;
    void bind() const override;
    void* lock(uint32_t start, uint32_t count) override;
    void unLock() override;

private:
    void createStaticBuffer();
    void createDynamicBuffer();

    bgfx::IndexBufferHandle _sibh;              // static index buffer handle
    bgfx::DynamicIndexBufferHandle _dibh;       // dynamic index buffer handle
    IndexFormat _indexFormat;             // 8, 16 or 32 bits
};

} // end namespace MimicViewer

