/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseUi.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** �R���t�B�O�f�[�^ */
    struct S_ConfigData
    {
        int32_t playerLife_ = 3;                                                    ///< @brief �v���C���[�̎c�@
        int32_t SE_ = 5;                                                            ///< @brief SE
        int32_t BGM_ = 5;                                                           ///< @brief BGM
        int32_t shotButton_ = 1;                                                    ///< @brief �V���b�g�{�^��
        int32_t bombButton_ = 3;                                                    ///< @brief �{���{�^��
    };


    //-------------------------------------------------------------
    //!
    //! @brief �^�C�g��UI
    //! @brief �^�C�g��UI��\������N���X
    //!
    //-------------------------------------------------------------
    class C_TitleUi : public C_BaseUi
    {
    public:
        C_TitleUi(const std::string& rId, int32_t type);                            // �R���X�g���N�^
        ~C_TitleUi() override;                                                      // �f�X�g���N�^
    private:
        S_ImageUiData imageUis_[2];                                                 ///< @brief �摜UI
        S_WordUiData initialItems_[3];                                              ///< @brief ��������
        S_WordUiData stageSelectItems_[4];                                          ///< @brief �X�e�[�W�Z���N�g����
        S_WordUiData configItems_[7];                                               ///< @brief �R���t�B�O����
        Sprite::SpriteCreaterWeakPtr wpUiSpriteCreater_;                            ///< @brief �^�C�g���X�v���C�g�N���G�C�^�[
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;                    ///< @brief �w�i�X�v���C�g�N���G�C�^�[    
        bool drawStageSelectItemFlag_ = false;                                      ///< @brief �X�e�[�W�Z���N�g���ڂ̕`��t���O
        bool drawConfigItemFlag_ = false;                                           ///< @brief �R���t�B�O���ڂ̕`��t���O
        int32_t initialItemNumber_ = 0;                                             ///< @brief �������ڔԍ�
        int32_t stageSelectItemNumber_ = 0;                                         ///< @brief �X�e�[�W�Z���N�g���ڔԍ�
        int32_t configItemNumber_ = 0;                                              ///< @brief �R���t�B�O���ڔԍ�
        S_ConfigData configData_;                                                   ///< @brief �R���t�B�O�f�[�^


        void DoUpdate() override;                                                   // ����J�̍X�V����
        void DoDraw() override;                                                     // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;                  // ����J�̃��b�Z�[�W����
        void LoadImageUis(JSON::JsonObject* pData);                                 // �摜UI�̃��[�h����
        void LoadInitialItems(JSON::JsonObject* pData);                             // �������ڂ̃��[�h����
        void LoadStaeSelectItems(JSON::JsonObject* pData);                          // �X�e�[�W�Z���N�g���ڂ̃��[�h����
        void LoadConfigItems(JSON::JsonObject* pData);                              // �R���t�B�O���ڂ̃��[�h����
        void LoadConfigData();                                                      // �R���t�B�O�f�[�^�̃��[�h����
        void SaveConfigData();                                                      // �R���t�B�O�f�[�^�̃Z�[�u����
        void DrawImageUiAndBackground();                                            // �摜UI�Ɣw�i�̕`��
        void DrawInitialItems();                                                    // �������ڂ̕`�揈��
        void DrawStageSelectItems();                                                // �X�e�[�W�Z���N�g���ڂ̕`��
        void DrawConfigItems();                                                     // �R���t�B�O���ڂ̕`��
    };
}