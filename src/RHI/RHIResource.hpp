#pragma once
#include <stdint.h>
#include <string>
#include "RHIDefines.hpp"


namespace Persist 
{
    class IRHIResource 
    {
    public:
        virtual ~IRHIResource() {}
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
                ref_->AddRef();
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
        RHIRefPtr & operator=(const RHIRefPtr & other)
        {
            ref_ = other.ref_;
            if(ref_)
            {
                ref_->AddRef();
            }
            return * this;
        }

        refType ** initRef()
        {
            *this = nullptr;
            return &ref_;
        }
        
        refType * get()
        {
            return ref_;
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
        operator ptrType()
        {
            return ref_;
        }

        private:
        refType * ref_;

    };




    class RHIVertexBuffer : public IRHIResource
    {
        public : 
        RHIVertexBuffer(uint32_t size , uint32_t usage ) 
        {

        }
        //virtual int setValue(uint32_t size ,const void * value)  = 0 ;

        virtual uint32_t vertexCount() = 0 ;

        protected :

        private :
        //uint32_t size_;
        //uint32_t usage_;

    };
    using RHIVertexBufferPtr = RHIRefPtr<RHIVertexBuffer> ;

    class RHIIndexBuffer : public IRHIResource
    {
        public : 
        RHIIndexBuffer(uint32_t size , uint32_t usage) : 
            indexNum_(size / sizeof(int))
        {

        }
        uint32_t indexNum() { return indexNum_ ; } 
        protected:
        uint32_t indexNum_;

    };
    using RHIIndexBufferPtr = RHIRefPtr <RHIIndexBuffer>;

    class RHIConstantBuffer : public IRHIResource
    {
        public : 
        RHIConstantBuffer(uint32_t size , uint32_t usage)
        {

        }
    } ;
    using RHIConstantBufferPtr = RHIRefPtr <RHIConstantBuffer>;


    interface IRHIResourceArray 
    {
        public :
        static IRHIResourceArray * create(uint8_t * buffer, uint32_t size );

        virtual void * getArray() = 0 ;

        virtual uint32_t getArraySize() = 0 ;

    };

    class RHIResourceCreateInfo 
    {

        public :
        RHIResourceCreateInfo() : resourceArray_(nullptr)
        {

        }
        RHIResourceCreateInfo( IRHIResourceArray * src) :
            resourceArray_(src)
        {

        }

        IRHIResourceArray * resourceArray() { return resourceArray_;}

        private :
        IRHIResourceArray  * resourceArray_;

    };
    
    struct RHIVertexFormatElement 
    {
        EnumAsByte<ENMVertexUsageType> vertexUsageType;
        EnumAsByte<ENMVertexFormatType> vertexFormatType;
        uint16_t stride;
        RHIVertexFormatElement (ENMVertexUsageType && usage , ENMVertexFormatType && format , uint16_t stride ):
            vertexUsageType(usage ) , vertexFormatType(format), stride(stride)
        {

        }

        bool operator < (const RHIVertexFormatElement & rhs)
        {
            if(vertexUsageType.value() != rhs.vertexUsageType.value())
            {
                return vertexUsageType.value() < rhs.vertexUsageType.value()
                ? true : false;
            }
            if(vertexFormatType.value() != rhs.vertexUsageType.value()) 
            {
                return vertexFormatType.value() < rhs.vertexFormatType.value() 
                ? true : false;
            }
            if(stride < rhs.stride) return true;
            return false;
        }

    };
    using RHIVertexFormatElementList = Array <RHIVertexFormatElement>;


    interface IRHIVertexLayout : extends IRHIResource
    {

        public : 
        // ugly string based hash function
        uint64_t static GenerateKey(const RHIVertexFormatElementList & elementList)
        {
         //  std::hash <std::string> ( )
            std::string ans("");
            for(int i = 0 ;i < elementList.size() ; ++i) 
            {
                const RHIVertexFormatElement & element = elementList[i];
                ans += "%" + std::to_string(element.vertexUsageType.value()) + "%"
                + std::to_string(element.vertexFormatType.value()) + "%" + 
                std::to_string(element.stride);
            }
            return std::hash<std::string>()(ans);
        }

        virtual uint32_t vertexSize() = 0 ;


    };
    using RHIVertexLayoutPtr  = RHIRefPtr <IRHIVertexLayout>;


    struct RHIDepthStencilStateInitializer ; 
    struct RHIDepthStencilState : public IRHIResource
    {
        virtual bool getInitializer(struct RHIDepthStencilInitializer & init ) { return false ; } 


    };
    using RHIDepthStencilStatePtr = RHIRefPtr<RHIDepthStencilState>;


}