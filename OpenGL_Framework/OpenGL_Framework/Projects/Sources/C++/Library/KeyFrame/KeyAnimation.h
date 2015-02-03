/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Key.h"
#include "../Timer/Counter/Frame/FrameCounter.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �L�[�t���[��
//! @brief �L�[�t���[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace KeyFrame
{
    //-------------------------------------------------------------
    //!
    //! @brief �L�[�A�j���[�V����
    //! @brief �L�[�t���[���A�j���[�V�������s���N���X
    //!
    //-------------------------------------------------------------
    template<typename T, typename U = float>
    class C_KeyAnimation
    {
    public:
        /* �ʖ� */
        using Key = S_Key<T>;                                               // Key�^
        using LinearFunction = T(*)(T, T, U);                               // LinearFunction�^
        using HermiteFunction = T(*)(T, T, T, T, U);                        // HermiteFunction�^
        
        
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_KeyAnimation()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        ~C_KeyAnimation()
        {
        }


        /*************************************************************//**
         *
         *  @brief  �X�V�������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Update()
        {
            if (keys_.size() == 0) return;
        
            // �C���f�b�N�X���Ō�ŁA�����[�v������ꍇ�C���f�b�N�X�����Z�b�g
            if (index_ == keys_.size() - 1)
            {
                if (loopFlag_ == true) index_ = 0;
            }

            // �L�[��2�擾����B�Ȃ��ꍇ��1���̃L�[�̒l��ݒ肵�A�I��
            if (index_ + 1 < keys_.size())
            {
                startKey = keys_[index];
                endKey = keys_[index + 1];
            }
            else
            {
                value_ = keys_[index_].value_;
                return;
            }
            
            /* ��Ԃ̃^�C�v�ɂ���āA�������s�� */
            switch (keys_[index_].interpolationType_)
            {
            case ecInterpolationType::CONSTANT:
            {
                value_ = startKey.value_;
            }
                break;
            case ecInterpolationType::LINEAR:
            {
                value_ = pLinearFunction_(startKey.value_,
                                          endKey.value_,
                                          static_cast<U>(frameCounter_.GetCount()) / static_cast<U>(endKey.frame_ - startKey.frame_);
            }
                break;
            case ecInterpolationType::HERMITE:
            {
                value_ = pHermiteFunction_(startKey.value_, 
                                           startKey.tangent_,
                                           endKey.value_,
                                           endKey.tangent_,
                                           static_cast<U>(frameCounter_.GetCount()) / static_cast<U>(endKey.frame_ - startKey.frame_);
            }
                break;
            }

            // �t���[���������̃L�[�܂ŒB������A���̃L�[�֐i�߂�
            frameCounter_.CountUp();
            if (endKey.frame_ == frameCounter_.GetCount()) ++index_;
        }


        /*************************************************************//**
         *
         *  @brief  �L�[�̒ǉ����s��
         *  @param  �L�[
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Add(const Key& rKey)
        {
            keys_.push_back(rKey);
        }


        /*************************************************************//**
         *
         *  @brief  �L�[��S�ď�������
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void AllRemove()
        {
            keys_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ���[�v��L��������
         *  @param  �L�������f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        void EnableLoop(bool validFlag = true)
        {
            loopFlag_ = validFlag;
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾����
         *  @param  �Ȃ�
         *  @return �l
         *
         ****************************************************************/
        T GetValue() const
        {
            return value_;
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾����
         *  @param  �Ȃ�
         *  @return �l
         *
         ****************************************************************/
        T GetValue(uint32_t index) const
        {
            return keys_[index].value_;
        }


        /*************************************************************//**
         *
         *  @brief  �L�[�̐����擾����
         *  @param  �Ȃ�
         *  @return �L�[�̐�
         *
         ****************************************************************/
        uint32_t GetKeyCount() const
        {
            return keys_.size();
        }


        /*************************************************************//**
         *
         *  @brief  ���̃t���[�������擾����
         *  @param  �Ȃ�
         *  @return ���̃t���[����
         *
         ****************************************************************/
        int32_t GetNowFrame() const
        {
            return frameCounter_.GetCount();
        }
    private:
        std::deque<Key> keys_;                                              ///< @brief �L�[
        int32_t index_ = 0;                                                 ///< @brief �C���f�b�N�X
        Timer::C_FrameCounter frameCounter_;                                ///< @brief �t���[���J�E���^�[
        T value_;                                                           ///< @brief �l
        bool loopFlag_ = false;                                             ///< @brief ���[�v�t���O
        LinearFunction pLinearFunction_ = nullptr;                          ///< @brief ���`��Ԋ֐�
        HermiteFunction pHermiteFunction_ = nullptr;                        ///< @brief �G���~�[�g��Ԋ֐�
    };
}
