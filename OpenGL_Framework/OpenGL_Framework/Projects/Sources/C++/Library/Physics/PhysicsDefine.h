/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    /* �ʖ� */
    using Vector3 = btVector3;                                                  // Vector3�^
    using Vector4 = btVector4;                                                  // Vector4�^
    using Matrix3x3 = btMatrix3x3;                                              // Matrix3x3�^
    using Quaternion = btQuaternion;                                            // Quaternion�^
    using Transform = btTransform;                                              // Transform�^
    using SoftBodyInfo = btSoftBodyWorldInfo;                                   // SoftBodyInfo�^
    using CollisionCallbackFunction = ContactProcessedCallback;                 // CollisionCallbackFanction�^
    using SimulationSubstepCallbackFunction = btInternalTickCallback;           // SimulationSubstepCallbackFunction�^
    

    namespace
    {
        /* �`��̎�� */
        namespace ShapeType
        {
            const int32_t s_BOX = BOX_SHAPE_PROXYTYPE;                          ///< @brief �{�b�N�X�`��
            const int32_t s_SPHERE = SPHERE_SHAPE_PROXYTYPE;                    ///< @brief ���`��
            const int32_t s_CAPSULE = CAPSULE_SHAPE_PROXYTYPE;                  ///< @brief �J�v�Z���`��
            const int32_t s_COMPOUND = COMPOUND_SHAPE_PROXYTYPE;                ///< @brief �����`��

        }

        /* �A�N�e�B�x�[�V�����X�e�[�g */
        namespace ActivationState
        {
            const int32_t s_ACTIVE_TAG = ACTIVE_TAG;                            ///< @brief �ʏ�̏��
            const int32_t s_DISABLE_DEACTIVATION = DISABLE_DEACTIVATION;        ///< @brief �񊈓����̖��������
            const int32_t s_DISABLE_SIMULATION = DISABLE_SIMULATION;            ///< @brief �V�~�����[�V�����̖��������
        }
    }
    
    /** ���� */
    enum class ecDirection
    {
        X,
        Y,
        Z
    };


    /*************************************************************//**
     *
     *  @brief  �\�t�g�{�f�B�����쐬����
     *  @param  �Ȃ�
     *
     ****************************************************************/
    inline SoftBodyInfo* CreateSoftBodyInfo()
    {
        return new(_aligned_malloc(sizeof(SoftBodyInfo), __alignof(SoftBodyInfo))) SoftBodyInfo;
    }


    //-------------------------------------------------------------
    //!
    //! @brief �\�t�g�{�f�B�C���t�H�[�f���[�^�\
    //! @brief �\�t�g�{�f�B���̃f���[�^
    //!
    //-------------------------------------------------------------
    class C_SoftBodyInfoDeleter
    {
    public:
        /* �֐��Ăяo�����Z�q�̃I�[�o�[���[�h */
        void operator ()(SoftBodyInfo* pSoftBodyInfo)
        {
            // �Z���̃����������
            pSoftBodyInfo->m_sparsesdf.Reset();

            // �f�X�g���N�^�𖾎��I�ɌĂяo���A�����������
            pSoftBodyInfo->~btSoftBodyWorldInfo();
            ::_aligned_free(pSoftBodyInfo);
        }
    };
}