/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Task.h"
#include <forward_list>


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
    //! @brief �W�F�l�����^�X�N�V�X�e��
    //! @brief �ėp�^�X�N�̎��s���Ǘ����邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_GeneralTaskSystem
    {
    public:
        C_GeneralTaskSystem();                                          // �R���X�g���N�^
        virtual ~C_GeneralTaskSystem();                                 // �f�X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �^�X�N�̒ǉ��������s��
         *  @param  �`��D��x
         *  @param  �ǉ�����^�X�N�̃R���X�g���N�^�̈���
         *  @return �Ȃ�
         *
         ****************************************************************/
        template<typename T>
        T* Entry(const std::shared_ptr<T>& sprTask, float updatePriority, float drawPriority)
        {
            // �V�����^�X�N���쐬���A�ǉ�
            std::shared_ptr<C_Task<T>> spNewTask = std::make_shared<C_Task<T>>(sprTask, updatePriority, drawPriority);
            pReserveTasks_.push_front(spNewTask);

            return sprTask.get();
        }

        virtual void Update();                                          // �X�V����
        virtual void Draw();                                            // �`�揈��
        void AllRemove();                                               // �S�Ẵ^�X�N������
        void EnableUpdatePrioritySort(bool validFlag = true);           // �X�V�D��x�ł̃\�[�g��L����
        void EnableDrawPrioritySort(bool validFlag = true);             // �`��D��x�ł̃\�[�g��L����
    private:
        std::forward_list<TaskPtr> pUpdateTaskList_;                    ///< @brief �X�V�^�X�N���X�g
        std::forward_list<TaskWeakPtr> wpDrawTaskList_;                 ///< @brief �`��^�X�N���X�g
        std::forward_list<TaskPtr> pReserveTasks_;                      ///< @brief �\��^�X�N
        bool updatePrioritySortFlag_ = true;                            ///< @brief �X�V�D��x�ł̃\�[�g���s�������f����t���O
        bool drawPrioritySortFlag_ = true;                              ///< @brief �`��D��x�ł̃\�[�g���s�������f����t���O

        virtual void MergeReserveTask();                                // �\��^�X�N�̃}�[�W����
    };
}
