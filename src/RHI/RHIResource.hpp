#pragma once
#include <stdint.h>


namespace Persist 
{
    class IRHIResource 
    {
    public:
        uint32_t AddRef() {  return ++ refCount_ ;}; 
        uint32_t Release()
        {
            uint32_t newCount = --refCount_;
            if(refCount_ == 0)
            {
                delete this;
            }
            return newCount;
        }
    private:
        uint32_t refCount_  = 0 ;

    };

    template <typename refType>
    class RHIRefPtr
    {
        public:
        typedef refType * ptrType;
        RHIRefPtr() : ref_(nullptr)
        { }

        RHIRefPtr(refType * ref ,bool addRef = true) :
            ref_(ref)
        {
            if(ref_ && addRef)
            {
                ref->AddRef();
            }
        }
        RHIRefPtr (const RHIRefPtr & rhs)
        {
            ref_ = rhs.ref_;
            if(ref_)
            {
                ref_->AddRef():
            }

        }
        RHIRefPtr(RHIRefPtr && rhs)
        {
            ref_ = rhs.ref_;
            rhs.ref_ = nullptr;
        }

        RHIRefPtr & operator=(refType * ref)
        {
            refType *  old = ref_;
            ref_ = ref;
            if(ref_)
            {
                ref_->AddRef();
            }
            if(old)
            {
                old->Release();
            }
            return *this;
        }

        refType ** initRef()
        {
            *this = nullptr;
            return &ref_;
        }
        ~RHIRefPtr()
        {
            if(ref_)
            {
                ref_->Release();
            }
        }
        refType * operator->() const
        {
            return ref_;
        }
        operator ptrType() const
        {
            return ref_;
        }

        private:
        refType * ref_;

    };




    class RHIVertexBuffer : public IRHIResource
    {
        public : 
        RHIVertexBuffer(uint32_t size , uint32_t usage) :
        size_(size),usage_(usage)
        {

        }
        private :
        uint32_t size_;
        uint32_t usage_;

    };
    using RHIVertexBufferPtr = RHIRefPtr<RHIVertexBuffer> ;

    class RHIResourceCreateInfo 
    {

    };

}