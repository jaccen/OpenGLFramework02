/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Object/TreeObject.h"
#include "../Creater/CollisionListCreater.h"
#include <functional>


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
            /* �ʖ� */
            template <typename T>
            using CollisionFunction = std::function<void(T*, T*)>;                  // CollisionFunction�^


            //-------------------------------------------------------------
            //!
            //! @brief �N�A�b�h�c���[�}�l�[�W���[
            //! @brief 4���؂̊Ǘ����s���N���X
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_QuadtreeManager
            {
            public:
                /* �ʖ� */
                using CollisionFunction = CollisionFunction<T>;                                 // CollisionFunction�^���ȗ�


                explicit C_QuadtreeManager(uint32_t collisionObjectEstimateCount = 1000);       // �R���X�g���N�^
                virtual ~C_QuadtreeManager();                                                   // �f�X�g���N�^
                void Initialize(float leftPosition,                                             // ����������
                                float topPosition,
                                float rightPosition,
                                float bottomPosition,
                                const CollisionFunction& rCollisionFunction,
                                uint32_t level = 4);
                void AllRemove();                                                               // �Փ˃I�u�W�F�N�g��S�ď���
                bool Regist(float borderLeftPosition,                                           // �Փ˃I�u�W�F�N�g�̓o�^����
                            float borderTopPosition,
                            float borderRightPosition,
                            float borderBottomPosition,
                            T* pCollisionObject);
                bool Update();                                                                  // �X�V����
                void SetCollisionFunction(const CollisionFunction& rCollisionFunction);         // �Փˏ������s���֐���ݒ�
            private:
                std::vector<S_TreeObject<T>> treeObjects_;                                      ///< @brief 4���؂ɓo�^����I�u�W�F�N�g
                uint32_t treeObjectCount_ = 0;                                                  ///< @biref 4���؂ɓo�^����I�u�W�F�N�g�̐�
                std::deque<T*> pCollisionList_;                                                 ///< @brief �Փ˔�����s���I�u�W�F�N�g�̃��X�g
                C_CollisionListCreater<T> collisionListCreater_;                                ///< @brief �Փ˃��X�g�쐬�@
                CollisionFunction collisionFunction_;                                           ///< @brief �Փˏ������s���֐�
            };
        }
    }
}


/* ���� */
#include "QuadtreeManagerImpl.h"