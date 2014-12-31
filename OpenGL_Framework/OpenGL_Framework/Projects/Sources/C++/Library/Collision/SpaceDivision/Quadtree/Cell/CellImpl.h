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
            /*************************************************************//**
             *
             *  @brief  �R���X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            C_Cell<T>::C_Cell()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �f�X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            C_Cell<T>::~C_Cell()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �c���[�̃I�u�W�F�N�g���v�b�V������
             *  @param  �c���[�̃I�u�W�F�N�g
             *  @return ����I���Ftrue
             *  @return �ُ�I���Ffalse
             *
             ****************************************************************/
            template<typename T>
            bool C_Cell<T>::Push(S_TreeObject<T>* pTreeObject)
            {
                if (pTreeObject == nullptr) return false;

                // �Z���������ꍇ�͉������Ȃ�
                if (pTreeObject->pCell_ == this) return false;

                // �c���[�I�u�W�F�N�g��1���o�^����ĂȂ��ꍇ�͐V�K�o�^
                if (pLastTreeObject_ == nullptr)
                {
                    pLastTreeObject_ = pTreeObject;
                }
                else
                {
                    // �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g���X�V
                    pTreeObject->pNextObject_ = pLastTreeObject_;
                    pLastTreeObject_->pPreviousObject_ = pTreeObject;
                    pLastTreeObject_ = pTreeObject;
                }

                // �Z����o�^
                pTreeObject->pCell_ = this;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g�������[�u���邩�m�F����
             *  @param  �c���[�̃I�u�W�F�N�g
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_Cell<T>::LastRemoveCheck(S_TreeObject<T>* pTreeObject)
            {
                if (pLastTreeObject_ == pTreeObject)
                {
                    if (pLastTreeObject_) pLastTreeObject_ = pLastTreeObject_->pNextObject_;
                }
            }


            /*************************************************************//**
             *
             *  @brief  �����N��S�ă��Z�b�g����
             *  @param  �c���[�̃I�u�W�F�N�g
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_Cell<T>::Reset(S_TreeObject<T>* pTreeObject)
            {
                pTreeObject->pNextObject_;

                // ����nullptr�̃c���[�̃I�u�W�F�N�g�܂ōċA����
                if (pTreeObject->pNextObject_) Reset(pTreeObject->pNextObject_);

                // �S�ẴI�u�W�F�N�g��nullptr�ɂ���
                pTreeObject = nullptr;
            }


            /*************************************************************//**
             *
             *  @brief  �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g���擾����
             *  @param  �Ȃ�
             *  @return �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g
             *
             ****************************************************************/
            template<typename T>
            S_TreeObject<T>* C_Cell<T>::GetLastTreeObject() const
            {
                return pLastTreeObject_;
            }
        }
    }
}