/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Task.h"


//-------------------------------------------------------------
//!
//! @brief �^�X�N
//! @brief �^�X�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Task
{
    //-------------------------------------------------------------
    //!
    //! @brief �A�b�v�f�[�g�^�X�N�\�[�g�I�u�W�F�N�g
    //! @brief �X�V�������\�[�g����֐��I�u�W�F�N�g
    //!
    //-------------------------------------------------------------
    class C_UpdateTaskSortObject
    {
    public:
        /*************************************************************//**
         *
         *  @brief  �֐��Ăяo�����Z�q�̃I�[�o�[���[�h
         *  @param  �^�X�N
         *  @param  ������̃^�X�N
         *  @return �Ȃ�
         *
         ****************************************************************/
        bool operator()(const TaskPtr& prTask, const TaskPtr& prAnotherTask)
        {
            return prTask->GetUpdatePriority() > prAnotherTask->GetUpdatePriority();
        }
    };



    //-------------------------------------------------------------
    //!
    //! @brief �h���[�^�X�N�\�[�g�I�u�W�F�N�g
    //! @brief �`�揇�����\�[�g����֐��I�u�W�F�N�g
    //!
    //-------------------------------------------------------------
    class C_DrawTaskSortObject
    {
    public:
        /*************************************************************//**
         *
         *  @brief  �֐��Ăяo�����Z�q�̃I�[�o�[���[�h
         *  @param  �^�X�N
         *  @param  ������̃^�X�N
         *  @return �Ȃ�
         *
         ****************************************************************/
        bool operator()(const TaskWeakPtr& prTask, const TaskWeakPtr& prAnotherTask)
        {
            if (prTask.expired() == false && prAnotherTask.expired() == false)
            {
                auto pTask = prTask.lock();
                auto pAnotherTask = prAnotherTask.lock();

                return pTask->GetDrawPriority() > pAnotherTask->GetDrawPriority();
            }

            // �� �� �t���[���X�L�b�v�����邱�Ƃł����ɓ���ꍇ�����邪�����͖��͂Ȃ�

            return false;
        }
    };
}