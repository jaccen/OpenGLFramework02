/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Material/Manager/MaterialManager.h"
#include "../../Library/Light/Manager/LightManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "BaseBackground.h"


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
    //! @brief �G�O�W�b�g�����O
    //! @brief �V�F���^�[�̏o���̃����O��\���N���X
    //!
    //-------------------------------------------------------------
    class C_ExitRing : public C_BaseBackground
    {
    public:
        C_ExitRing(const std::string& rId, int32_t type);                       // �R���X�g���N�^
        virtual ~C_ExitRing();                                                  // �f�X�g���N�^
    private:
        OpenGL::PrimitiveBufferPtr pModelData_;                                 ///< @brief ���f�����
        Texture::TextureDataPtr pTextureData_;                                  ///< @brief �e�N�X�`���f�[�^
        Texture::TextureDataPtr pNormalTextureData_;                            ///< @brief �@���e�N�X�`���f�[�^
        Matrix4x4 modelMatrix_;                                                 ///< @brief ���f���s��
        Material::MaterialPtr pMaterial_;                                       ///< @brief �}�e���A��
        Light::LightPtr pLight_;                                                ///< @brief ���C�g
        int32_t cameraSubroutineIndex_ = 0;                                     ///< @brief �J�����T�u���[�`���C���f�b�N�X

        virtual void DoUpdate() override;                                       // ����J�̍X�V����
        virtual void DoDraw() override;                                         // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) override;      // ����J�̃��b�Z�[�W����
        void SetMaterial(const Material::MaterialPtr& prMaterial);              // �}�e���A����ݒ�
        void SetLight(const Light::LightPtr& prLight);                          // ���C�g��ݒ�
    };
}