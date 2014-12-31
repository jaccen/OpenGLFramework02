/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �Q�[���I�u�W�F�N�g
//! @brief �Q�[���ɑ��݂���I�u�W�F�N�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace GameObject
{
    /* �O���錾 */
    namespace Message
    {
        struct S_Telegram;
    }


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���I�u�W�F�N�g
    //! @brief �Q�[���I�u�W�F�N�g�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_GameObject
    {
    public:
        C_GameObject() = default;                                                       // �R���X�g���N�^
        C_GameObject(const std::string& rId,                                            // �R���X�g���N�^
                     int32_t type);
        virtual ~C_GameObject();                                                        // �f�X�g���N�^
        virtual bool Update() = 0;                                                      // �X�V����
        virtual void Draw() = 0;                                                        // �`�揈��
        virtual bool MessageProcess(const Message::S_Telegram& rTelegram) = 0;          // ���b�Z�[�W����
        void AddStringToId(const std::string& rString);                                 // ID�ɕ������������
        const std::string& GetId() const;                                               // ID���擾
        int32_t GetType() const;                                                        // ��ނ��擾
        bool IsExistanceFlag() const;                                                   // ���݂��m�F����t���O���擾
        void SetId(const std::string& rId);                                             // ID��ݒ�
        void SetType(int32_t type);                                                     // ��ނ�ݒ�
        void SetExistanceFlag(bool existanceFlag);                                      // ���݂��m�F����t���O��ݒ�
    protected:
        std::string id_;                                                                ///< @brief ID
        int32_t type_ = -1;                                                             ///< @brief ���
        bool existenceFlag_ = true;                                                     ///< @brief ���݂̃t���O
    };
}