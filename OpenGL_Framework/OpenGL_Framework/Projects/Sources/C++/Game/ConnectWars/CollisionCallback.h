/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �R���W�����R�[���o�b�N
    //! @brief �Փ˂̃R�[���o�b�N�������s���֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    class C_CollisionCallback
    {
    public:
        static bool s_ContactProcess(btManifoldPoint& rManifoldPoint, void* pBody, void* pAnotherBody);
    };
}