#pragma once
class ResourceView
{
public:
    uint32_t GetSize()
    {
        return m_Size;
    }

    D3D12_CPU_DESCRIPTOR_HANDLE GetCPU(uint32_t i = 0)
    {
        D3D12_CPU_DESCRIPTOR_HANDLE CPUDescriptor = m_CPUDescriptor;
        CPUDescriptor.ptr += i * m_descriptorSize;
        return CPUDescriptor;
    }

    D3D12_GPU_DESCRIPTOR_HANDLE GetGPU(uint32_t i = 0)
    {
        D3D12_GPU_DESCRIPTOR_HANDLE GPUDescriptor = m_GPUDescriptor;
        GPUDescriptor.ptr += i * m_descriptorSize;
        return GPUDescriptor;
    }

private:
    friend class StaticResourceViewHeapDX12;
    friend class DynamicResourceViewHeapDX12;

    uint32_t m_Size = 0;
    uint32_t m_descriptorSize = 0;

    D3D12_CPU_DESCRIPTOR_HANDLE m_CPUDescriptor;
    D3D12_GPU_DESCRIPTOR_HANDLE m_GPUDescriptor;

public:
    void SetResourceView(uint32_t size, uint32_t dsvDescriptorSize, D3D12_CPU_DESCRIPTOR_HANDLE CPUDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE GPUDescriptor)
    {
        m_Size = size;
        m_CPUDescriptor = CPUDescriptor;
        m_GPUDescriptor = GPUDescriptor;
        m_descriptorSize = dsvDescriptorSize;
    }
};

