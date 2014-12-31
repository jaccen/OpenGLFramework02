/* ��d�C���N���[�h�h�~ */ 
#pragma once


/* �w�b�_�t�@�C�� */
#include "../MemoryPool.h"


//-------------------------------------------------------------
//!
//! @brief ������
//! @brief �������֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Memory
{
    /** �e�o�C�g��\���\���� */
    struct S_Byte32 { char datas_[32]; };                           //!< @brief 32�o�C�g
    struct S_Byte64 { char datas_[64]; };                           //!< @brief 64�o�C�g
    struct S_Byte128{ char datas_[128]; };                          //!< @brief 128�o�C�g
    struct S_Byte256{ char datas_[256]; };                          //!< @brief 256�o�C�g


    //-------------------------------------------------------------
    //!
    //! @brief �W�F�l�����������v�[��
    //! @brief �ėp�I�ȃ������v�[����\���N���X
    //!
    //-------------------------------------------------------------
    class C_GeneralMemoryPool
    {
    public:
        C_GeneralMemoryPool() = default;                            //!< @brief �f�t�H���g�R���X�g���N�^
        ~C_GeneralMemoryPool() = default;                           //!< @brief �f�t�H���g�R���X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �v�[�����烁�����̊��蓖�Ă��s��
         *  @param  �������̃T�C�Y
         *  @return ���蓖�Ă�ꂽ�������̃|�C���^
         *
         ****************************************************************/
        void* PoolAlloc(uint32_t size)
        {
            void* pAllocPointer = nullptr;

            if (size < 32)  pAllocPointer = poolByte32_.Alloc();
            else if (size < 64)  pAllocPointer = poolByte64_.Alloc();
            else if (size < 128) pAllocPointer = poolByte128_.Alloc();
            else if (size < 256) pAllocPointer = poolByte256_.Alloc();

            return pAllocPointer;
        }


        /*************************************************************//**
         *
         *  @brief  �v�[�����烁�����̉�����s��
         *  @param  ������郁�����̃|�C���^
         *  @param  �������̃T�C�Y
         *  @return �Ȃ�
         *
         ****************************************************************/
        void PoolFree(void* pFreePointer, uint32_t size)
        {
            if (size < 32)  poolByte32_.Free(pFreePointer);
            else if (size < 64)  poolByte64_.Free(pFreePointer);
            else if (size < 128) poolByte128_.Free(pFreePointer);
            else if (size < 256) poolByte256_.Free(pFreePointer);
        }
    private:
        C_MemoryPool<S_Byte32> poolByte32_;                     ///< @brief 32�o�C�g�������v�[��
        C_MemoryPool<S_Byte64> poolByte64_;                     ///< @brief 64�o�C�g�������v�[��
        C_MemoryPool<S_Byte128> poolByte128_;                   ///< @brief 128�o�C�g�������v�[��
        C_MemoryPool<S_Byte256> poolByte256_;                   ///< @brief 256�o�C�g�������v�[��
    };
}