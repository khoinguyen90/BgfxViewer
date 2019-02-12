#include "../renderer/BGFXIndexBuffer.h"

namespace MimicViewer {

BGFXIndexBuffer::BGFXIndexBuffer(const IndexFormat indexFormat, uint32_t indexCount, bool dynamic) :
    _sibh(BGFX_INVALID_HANDLE)
  , _dibh(BGFX_INVALID_HANDLE)
  , _indexFormat(indexFormat)
{
    switch (indexFormat)
    {
    case IndexFormat::INDEX8:
        _elementSize = 1;
        break;
    case IndexFormat::INDEX16:
        _elementSize = 2;
        break;
    case IndexFormat::INDEX32:
        _elementSize = 4;
        break;
    default:
        MV_ERROR("Unsupported index format (%d).", indexFormat);
    }

    // initialise Geometry buffer.
    initialize(_elementSize, indexCount, dynamic);

    // if dynamic, create bgfx vertex buffer here.
    // if static, creation will be delayed when setting vertice data.
    if(_dynamic)
    {
        createDynamicBuffer();
    }
}

BGFXIndexBuffer::~BGFXIndexBuffer()
{
    if(_dynamic)
    {
        if(bgfx::isValid(_dibh))
            bgfx::destroy(_dibh);
    }
    else
    {
        if(bgfx::isValid(_sibh))
            bgfx::destroy(_sibh);
    }
}

void BGFXIndexBuffer::createStaticBuffer()
{
    MV_ASSERT(!_dynamic && !bgfx::isValid(_sibh));
    MV_ASSERT(_memoryBuffer.getSize() > 0);

    void * dataPtr = _memoryBuffer.map(0);
    MV_ASSERT(dataPtr);
    const bgfx::Memory * mem = bgfx::makeRef(dataPtr, _memoryBuffer.getSize());

    uint16_t flags = /*BGFX_BUFFER_NONE; //*/BGFX_BUFFER_ALLOW_RESIZE;
    if(_indexFormat == IndexFormat::INDEX32)
        flags |= BGFX_BUFFER_INDEX32;

    _sibh = bgfx::createIndexBuffer(mem, flags);
    MV_ASSERT(bgfx::isValid(_sibh));
}

void BGFXIndexBuffer::createDynamicBuffer()
{
    MV_ASSERT(_dynamic);

    uint16_t flags = /*BGFX_BUFFER_NONE; //*/BGFX_BUFFER_ALLOW_RESIZE;
    if(_indexFormat == IndexFormat::INDEX32)
        flags |= BGFX_BUFFER_INDEX32;

    _dibh = bgfx::createDynamicIndexBuffer(_elementCount, flags);
    MV_ASSERT(bgfx::isValid(_dibh));
}

void BGFXIndexBuffer::set(const void* data, uint32_t count, uint32_t start)
{
    GeometryBuffer::set(data, count, start);

    if(_dynamic)
    {
        // if dynamic, update vertex buffer with memory buffer
        MV_ASSERT(bgfx::isValid(_dibh));
        const bgfx::Memory* mem = bgfx::makeRef(_memoryBuffer.map(0), _memoryBuffer.getSize());
        bgfx::update(_dibh, 0, mem);
    }
    else
    {
        // create static bgfx buffer
        if(!bgfx::isValid(_sibh))
            createStaticBuffer();
    }
}

void BGFXIndexBuffer::bind() const
{
    if(_dynamic)
    {
        MV_ASSERT(bgfx::isValid(_dibh));
        bgfx::setIndexBuffer(_dibh, _drawStart, _drawCount);
    }
    else
    {
        MV_ASSERT(bgfx::isValid(_sibh));
        bgfx::setIndexBuffer(_sibh, _drawStart, _drawCount);
    }
}

void * BGFXIndexBuffer::lock(uint32_t start, uint32_t count)
{
    MV_ASSERT(_dynamic && bgfx::isValid(_dibh));

    return GeometryBuffer::lock(start, count);
}

void BGFXIndexBuffer::unLock()
{
    MV_ASSERT(_dynamic && bgfx::isValid(_dibh));

    if (_lockState == LOCK_ACTIVE)
    {
        bgfx::update(_dibh, _lockStart, bgfx::makeRef(_lockData, _lockCount * _elementSize));//_memoryBuffer.getSize()));
        GeometryBuffer::unLock();
    }
}

} // end namespace MimicViewer
