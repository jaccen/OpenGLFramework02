/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Object/TreeObject.h"


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
            //-------------------------------------------------------------
            //!
            //! @brief �Z��
            //! @brief ��Ԃ�\���N���X
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_Cell
            {
            public:
                C_Cell();                                                   // �R���X�g���N�^
                ~C_Cell();                                                  // �f�X�g���N�^
                bool Push(S_TreeObject<T>* pTreeObject);                    // �c���[�̃I�u�W�F�N�g���v�b�V��
                void LastRemoveCheck(S_TreeObject<T>* pTreeObject);         // �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g�������[�u���邩�m�F
                void Reset(S_TreeObject<T>* pTreeObject);                   // �����N��S�ă��Z�b�g
                S_TreeObject<T>* GetLastTreeObject() const;                 // �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g���擾
            private:
                S_TreeObject<T>* pLastTreeObject_ = nullptr;                ///< @brief �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g
            };
        }
    }
}


/* ���� */
#include "CellImpl.h"