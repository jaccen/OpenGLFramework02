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
             *  @param  �Փ˃I�u�W�F�N�g�̌��ς��萔
             *
             ****************************************************************/
            template<typename T>
            C_QuadtreeManager<T>::C_QuadtreeManager(uint32_t collisionObjectEstimateCount) :

                // �c���[�I�u�W�F�N�g
                treeObjects_(collisionObjectEstimateCount)

            {
            }


            /*************************************************************//**
             *
             *  @brief  �f�X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            C_QuadtreeManager<T>::~C_QuadtreeManager()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �������������s��
             *  @param  ���[���W
             *  @param  ��[���W
             *  @param  �E�[���W
             *  @param  ���[���W
             *  @param  �Փˏ������s���֐�
             *  @param  ���x��
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::Initialize(float leftPosition,
                                                  float topPosition,
                                                  float rightPosition,
                                                  float bottomPosition,
                                                  const CollisionFunction& rCollisionFunction,
                                                  uint32_t level)
            {
                collisionListCreater_.Initialize(leftPosition, topPosition, rightPosition, bottomPosition, level);
            }


            /*************************************************************//**
             *
             *  @brief  �Փ˃I�u�W�F�N�g��S�ď�������
             *  @param  �Փ˃I�u�W�F�N�g
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::AllRemmove()
            {
                for (size_t i = 0; i < treeObjectCount_; ++i) treeObjects_[i].Remove();
                treeObjectCount_ = 0;
            }


            /*************************************************************//**
             *
             *  @brief  �Փ˃I�u�W�F�N�g��o�^����
             *  @param  ���E�͈͂̍��[���W
             *  @param  ���E�͈͂̏�[���W
             *  @param  ���E�͈͂̉E�[���W
             *  @param  ���E�͈͂̉��[���W
             *  @param  �Փ˃I�u�W�F�N�g
             *  @return ����I���Ftrue
             *  @return �ُ�I���Ffalse
             *
             ****************************************************************/
            template<typename T>
            bool C_QuadtreeManager<T>::Regist(float borderLeftPosition,
                                              float borderTopPosition,
                                              float borderRightPosition,
                                              float borderBottomPosition,
                                              T* pCollisionObject)
            {
                if (treeObjectCount_ >= treeObjects_.size()) treeObjects_.emplace_back();

                // �Փ˃��X�g�����@�ɓo�^
                treeObjects_[treeObjectCount_].pObject_ = pCollisionObject;
                if (collisionListCreater_.Regist(borderLeftPosition,
                                                 borderTopPosition,
                                                 borderRightPosition,
                                                 borderBottomPosition,
                                                 &treeObjects_[treeObjectCount_]) == false)
                {
                    return false;
                }

                ++treeObjectCount_;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  �X�V�������s��
             *  @param  �Ȃ�
             *  @return ����I���Ftrue
             *  @return �ُ�I���Ffalse
             *
             ****************************************************************/
            template<typename T>
            bool C_QuadtreeManager<T>::Update()
            {
                uint32_t collisionCount = 0;

                // �Փ˃��X�g���擾
                pCollisionList_.clear();
                if (liner4TreeManager_.GetCollisionList(&pCollisionList_, &collisionCount) == false) return false;

                // �Փˏ������s��
                for (size_t i = 0; i < collisionCount; ++i)
                {
                    collisionFunction_(pCollisionList_[i * 2], pCollisionList_[i * 2 + 1]);
                }
            }


            /*************************************************************//**
             *
             *  @brief  �Փˏ������s���֐���ݒ�
             *  @param  �Փˏ������s���֐�
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_QuadtreeManager<T>::SetCollisionFunction(const CollisionFunction& rCollisionFunction)
            {
                collisionFunction_ = rCollisionFunction;
            }
        }
    }
}