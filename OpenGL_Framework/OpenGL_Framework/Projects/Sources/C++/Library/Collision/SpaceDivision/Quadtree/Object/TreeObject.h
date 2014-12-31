/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �R���W����
//! @brief �Փˊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief �X�y�[�X�f�B�r�W����
    //! @brief ��ԕ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SpaceDivision
    {
        //-------------------------------------------------------------
        //!
        //! @brief �N�A�b�h�c���[
        //! @brief 4���؊֘A�̖��O���
        //!
        //-------------------------------------------------------------
        namespace Quadtree
        {
            /* �O���錾 */
            template<typename T>
            class C_Cell;


            //-------------------------------------------------------------
            //!
            //! @brief �c���[�I�u�W�F�N�g
            //! @brief �c���[�̃I�u�W�F�N�g��\���\����
            //!
            //-------------------------------------------------------------
            template<typename T>
            struct S_TreeObject
            {
                C_Cell<T>* pCell_ = nullptr;                        ///< @brief �o�^���
                T* pObject_ = nullptr;                              ///< @brief �I�u�W�F�N�g
                S_TreeObject<T>* pPreviousObject_ = nullptr;        ///< @brief �O�̃I�u�W�F�N�g
                S_TreeObject<T>* pNextObject_ = nullptr;            ///< @brief ���̃I�u�W�F�N�g

                /*************************************************************//**
                 *
                 *  @brief  ���X�g���玩�g�������[�u����
                 *  @param  �Ȃ�
                 *  @return ����I���Ftrue
                 *  @return �ُ�I���Ffalse
                 *
                 ****************************************************************/
                bool Remove()
                {
                    if (pCell_ == nullptr) return false;

                    // �Ō�̃c���[�̃I�u�W�F�N�g���m�F
                    pCell_->LastRemoveCheck(this);

                    // �O��̃I�u�W�F�N�g���q��������
                    if (pPreviousObject_) pPreviousObject_->pNextObject_ = pNextObject_;
                    if (pNextObject_) pNextObject_->pPreviousObject_ = pNextObject_;

                    pPreviousObject_ = nullptr;
                    pNextObject_ = nullptr;
                    pCell_ = nullptr;

                    return true;
                }
            };
        }
    }
}