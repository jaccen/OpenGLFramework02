/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "Manager/SceneManager.h"


//-------------------------------------------------------------
//!
//! @brief �V�[��
//! @brief �V�[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Scene
{
    //-------------------------------------------------------------
    //!
    //! @brief �x�[�X�V�[��
    //! @brief �V�[���̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseScene
    {
    public:
        C_BaseScene();                                                      // �R���X�g���N�^
        virtual ~C_BaseScene();                                             // �f�X�g���N�^
        virtual ecSceneReturn Initialize();                                 // ����������
        virtual ecSceneReturn Update() = 0;                                 // �X�V����
        virtual void Draw() = 0;                                            // �`�揈��
        virtual void Finalize();                                            // �I������
        bool IsUpdateFlag() const;                                          // �X�V�t���O���擾
        bool IsDrawFlag() const;                                            // �`��t���O���擾
        void SetUpdateFlag(bool updateFlag);                                // �X�V�t���O��ݒ�
        void SetDrawFlag(bool drawFlag);                                    // �`��t���O��ݒ�
        void SetSceneChanger(IC_SceneChanger* pSceneChanger);               // �V�[���`�F���W���[��ݒ�
        void SetParentScene(C_BaseScene* pParentScene);                     // �e�̃V�[����ݒ�
    protected:
        IC_SceneChanger* GetSceneChanger() const;                           // �V�[���`�F���W���[���擾

        template<typename T>
        T* GetParentScene() const;                                          // �e�̃V�[�����擾
    private:
        bool updateFlag_ = true;                                            ///< @brief �X�V�t���O
        bool drawFlag_ = true;                                              ///< @brief �`��t���O
        IC_SceneChanger* pSceneChanger_ = nullptr;                          ///< @brief �V�[���`�F���W���[
        C_BaseScene* pParentScene_ = nullptr;                               ///< @brief �e�̃V�[��
    };


#pragma region �����o�֐�


    /*************************************************************//**
     *
     *  @brief  �e�̃V�[�����擾����
     *  @param  �Ȃ�
     *  @return �e�̃V�[��
     *
     ****************************************************************/
    template<typename T>
    T* C_BaseScene::GetParentScene() const
    {
        return static_cast<T*>(pParentScene_);
    }


#pragma endregion

}