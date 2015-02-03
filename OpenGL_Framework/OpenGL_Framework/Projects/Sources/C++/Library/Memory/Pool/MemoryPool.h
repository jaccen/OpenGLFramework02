/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief ������
//! @brief �������֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Memory
{
    //-------------------------------------------------------------
    //!
    //! @brief �������v�[��
    //! @brief ��{�I�ȃ������v�[����\���N���X
    //!
    //-------------------------------------------------------------
    template<typename T, size_t DefaultExpandNumber = 1000>
    class C_MemoryPool
    {
    public:
        /* �ʖ� */
        using MemoryPtr = C_MemoryPool<T, DefaultExpandNumber>*;        // MemoryPtr�^


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_MemoryPool()
        {
            // ���������g��
            ExpandFreeList(DefaultExpandNumber);
        }

        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        ~C_MemoryPool()
        {
            // �S�Ẵ����������
            for (MemoryPtr pNext = this->pNext_; pNext != nullptr; pNext = this->pNext_)
            {
                pNext_ = pNext_->pNext_;
                std::free(pNext);
            }
        }

        /*************************************************************//**
         *
         *  @brief  �������̊��蓖�Ă��s��
         *  @param  �Ȃ�
         *  @return ���蓖�Ă��������̃|�C���^
         *
         ****************************************************************/
        void* Alloc()
        {
            // ������������Ȃ��ꍇ�͂���Ƀ��������g��
            if (pNext_ == nullptr)
            {
                ExpandFreeList(DefaultExpandNumber);
            }

            // ���̃|�C���^��ݒ�
            MemoryPtr pHead = pNext_;
            pNext_ = pHead->pNext_;

            return pHead;
        }

        /*************************************************************//**
         *
         *  @brief  �������̉�����s��
         *  @param  ������郁�����̃|�C���^
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Free(void* pFreePointer)
        {
            assert(pFreePointer);

            // �������|�C���^�����̃|�C���^�Ƃ��Đݒ�
            MemoryPtr pHead = static_cast<MemoryPtr>(pFreePointer);
            pHead->pNext_ = pNext_;
            pNext_ = pHead;
        }

    private:
        MemoryPtr pNext_ = nullptr;                                 ///< @brief ���̃������̃|�C���^

        /*************************************************************//**
         *
         *  @brief  �������̊g�����s��
         *  @param  �������g����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void ExpandFreeList(size_t expandNumber)
        {
            assert(expandNumber > 0);

            // �T�C�Y���v�Z
            size_t size = (sizeof(T) > sizeof(MemoryPtr) ? sizeof(T) : sizeof(MemoryPtr));

            // �����������蓖�āA���̃|�C���^�ɐݒ�
            MemoryPtr pRunner = reinterpret_cast<MemoryPtr>(std::malloc(size));
            pNext_ = pRunner;

            // �c��̊g�������������������g��
            for (size_t i = 0; i < expandNumber; ++i)
            {
                pRunner->pNext_ = reinterpret_cast<MemoryPtr>(std::malloc(size));
                pRunner = pRunner->pNext_;
            }

            // ��ԍŌ�̃�������nullptr��ݒ�
            pRunner->pNext_ = nullptr;
        }
    };
}