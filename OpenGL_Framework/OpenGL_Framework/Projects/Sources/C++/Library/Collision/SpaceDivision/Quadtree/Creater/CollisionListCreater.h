/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Cell/Cell.h"
#include <vector>
#include <forward_list>
#include <deque>


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
            //! @brief ���j�A�N�A�b�h�c���[�}�l�[�W���[
            //! @brief ���`4���؋�Ԃ��Ǘ�����N���X
            //!
            //-------------------------------------------------------------
            template<typename T>
            class C_CollisionListCreater
            {
            public:
                C_CollisionListCreater();                                                       // �R���X�g���N�^
                ~C_CollisionListCreater();                                                      // �f�X�g���N�^
                void Initialize(float left,                                                     // ����������
                                float top,
                                float right,
                                float bottom,
                                uint32_t level = 4);
                bool Regist(float borderLeft,                                                   // �c���[�̃I�u�W�F�N�g�̓o�^����
                            float borderTop,
                            float borderRight,
                            float borderBottom,
                            S_TreeObject<T>* pTreeObject);
                bool GetCollisionList(std::deque<T*>* ppCollisionPairList,                      // �Փ˔���̃��X�g���擾
                                      uint32_t* pCollisionCount);
            private:
                std::unique_ptr<std::unique_ptr<C_Cell<T>>[]> upCells_;                         ///< @brief ���`���
                std::vector<uint32_t> exponentialValues_;                                       ///< @brief �ׂ��搔�l�z��
                uint32_t level_ = 0;                                                            ///< @brief ��Ԃ̃��x��
                float width_ = 0.0f;                                                            ///< @brief �̈�̕�
                float height_ = 0.0f;                                                           ///< @brief �̈�̍���
                float left_ = 0.0f;                                                             ///< @brief �̈�̍��[
                float top_ = 0.0f;                                                              ///< @brief �̈�̏�[
                float unitWidth_ = 0.0f;                                                        ///< @brief �ŏ����x����Ԃ̕�
                float unitHeight_ = 0.0f;                                                       ///< @brief �ŏ����x����Ԃ̍���
                uint32_t cellNumber_ = 0;                                                       ///< @brief ��Ԃ̐�

                void CalculateExponentialValue(uint32_t level);                                 // �ׂ��搔�l�z����v�Z
                void SetTerritory(float left,                                                   // �̈��ݒ�
                                  float top,
                                  float right,
                                  float bottom);
                uint32_t GetMortonNumberFromAABB(float borderLeft,                              // ���E�͈͂��烂�[�g���ԍ����擾
                                                 float borderTop,
                                                 float borderRight,
                                                 float borderBottom);
                uint32_t ConvertPointToMortonNumber(float positionX, float positionY);          // �_�����[�g���ԍ��֕ϊ�
                uint32_t BitSeparate32(uint32_t value);                                         // 1bit��т�32�r�b�g�ɕ���
                void CreateCell(uint32_t element);                                              // ��Ԃ��쐬
                void CreateCollisionList(uint32_t cellElement,                                  // �Փ˃��X�g���쐬
                                         std::deque<T*>* ppCollisionStack,
                                         std::deque<T*>* ppCollisionPairList);
            };
        }
    }
}

/* ���� */
#include "CollisionListCreaterImpl.h"