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
        using Key = S_Key<T>;                                                                   // Key�^
        using LinearFunction = T(*)(const T&, const T&, U);                                     // LinearFunction�^
        using HermiteFunction = T(*)(const T&, const T&, const T&, const T&, U);                // HermiteFunction�^
        
        
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
                if (loopFlag_ == true)
                {
                    index_ = 0;
                    ++loopCount_;
                }
            }

            S_Key<T> startKey, endKey;

            // �L�[��2�擾����B�Ȃ��ꍇ��1���̃L�[�̒l��ݒ肵�A�I��
            if (index_ + 1 < static_cast<int32_t>(keys_.size()))
            {
                startKey = keys_[index_];
                endKey = keys_[index_ + 1];
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
                auto coefficient = static_cast<U>(frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_) - startKey.frame_) / static_cast<U>(endKey.frame_ - startKey.frame_);
                
                value_ = pLinearFunction_(startKey.value_,
                                          endKey.value_,
                                          coefficient);
            }
                break;
            case ecInterpolationType::HERMITE:
            {
                auto coefficient = static_cast<U>(frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_) - startKey.frame_) / static_cast<U>(endKey.frame_ - startKey.frame_);

                value_ = pHermiteFunction_(startKey.value_, 
                                           startKey.tangent_,
                                           endKey.value_,
                                           endKey.tangent_,
                                           coefficient);
            }
                break;
            }

            // �t���[���������̃L�[�܂ŒB������A���̃L�[�֐i�߂�
            if (waitFlag_ == false) frameCounter_.CountUp();
            if (endKey.frame_ == frameCounter_.GetCount() - (keys_[keys_.size() - 1].frame_ * loopCount_)) ++index_;
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


        /*************************************************************//**
         *
         *  @brief  ���[�v�񐔂��擾����
         *  @param  �Ȃ�
         *  @return ���[�v��
         *
         ****************************************************************/
        int32_t GetLoopCount() const
        {
            return loopCount_;
        }


        /*************************************************************//**
         *
         *  @brief  ���݂̃t���[������ݒ肷��
         *  @param  �t���[����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void SetNowFrame(int32_t frame)
        {
            frameCounter_.SetCount(frame);
        }


        /*************************************************************//**
         *
         *  @brief  �C���f�b�N�X��ݒ肷��
         *  @param  �C���f�b�N�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        void SetIndex(int32_t index)
        {
            index_ = index;
        }


        /*************************************************************//**
         *
         *  @brief  ���`��Ԋ֐���ݒ肷��
         *  @param  ���`��Ԋ֐�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void SetLinearFunction(LinearFunction pLinearFunction)
        {
            pLinearFunction_ = pLinearFunction;
        }


        /*************************************************************//**
         *
         *  @brief  �G���~�[�g��Ԋ֐���ݒ肷��
         *  @param  �G���~�[�g��Ԋ֐�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void SetHermiteFunction(HermiteFunction pHermiteFunction)
        {
            pHermiteFunction_ = pHermiteFunction;
        }


        /*************************************************************//**
         *
         *  @brief  �ҋ@��L��������
         *  @param  �L�������f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        void EnableWait(bool validFlag = true)
        {
            waitFlag_ = validFlag;
        }
    private:
        std::deque<Key> keys_;                                                                  ///< @brief �L�[
        int32_t index_ = 0;                                                                     ///< @brief �C���f�b�N�X
        Timer::C_FrameCounter frameCounter_;                                                    ///< @brief �t���[���J�E���^�[
        T value_;                                                                               ///< @brief �l
        bool loopFlag_ = false;                                                                 ///< @brief ���[�v�t���O
        LinearFunction pLinearFunction_ = nullptr;                                              ///< @brief ���`��Ԋ֐�
        HermiteFunction pHermiteFunction_ = nullptr;                                            ///< @brief �G���~�[�g��Ԋ֐�
        bool waitFlag_ = false;                                                                 ///< @brief �ҋ@�t���O
        int32_t loopCount_ = 0;                                                                 ///< @brief ���[�v��
    };
}
