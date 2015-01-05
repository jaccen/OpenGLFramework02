/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �t���[�����[�N
//! @brief �t���[�����[�N�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Framework
{
    //-------------------------------------------------------------
    //!
    //! @brief �t���[�����[�N( �C���^�[�t�F�[�X )
    //! @brief �t���[�����[�N�̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_Framework
    {
    public:
        IC_Framework() = default;                           //!< @brief �R���X�g���N�^
        virtual ~IC_Framework() = default;                  //!< @brief �f�X�g���N�^
        virtual bool Run() = 0;                             //!< @brief ���s����
    };


    //-------------------------------------------------------------
    //!
    //! @brief �t���[�����[�N
    //! @brief �t���[�����[�N���Ǘ�����N���X
    //! @brief �Q�[�������ۂɂ͂��̃N���X���p�����A
    //! @brief ���̃N���X���ł��̃N���X�e�����𗘗p����
    //! @brief �܂��A�p�������N���X�͂��̃N���X�̃R���X�g���N�^��
    //! @brief �������g( this )��n������
    //!
    //-------------------------------------------------------------
    class C_Framework : public IC_Framework
    {
    public:
        explicit C_Framework(C_Framework* pGame);                                                                                       // �R���X�g���N�^
        virtual ~C_Framework() override;                                                                                                // �f�X�g���N�^
        bool Run() override final;                                                                                                      // ���s����
    protected:
        virtual bool Initialize();                                                                                                      // ����������
        bool InitializeWithJsonFile(const std::string& rMainWindowDataFilePath = "Projects/LibraryDatas/JSON/MainWindowData.json",      // JSON�t�@�C���ŏ���������
                                    const std::string& rOpenGlDataFilePath = "Projects/LibraryDatas/JSON/OpenGLData.json");
        virtual bool Update();                                                                                                          // �X�V����
        virtual void Draw();                                                                                                            // �`�揈��
        virtual void UpdateScreen();                                                                                                    // ��ʂ̍X�V
        virtual void Finalize();                                                                                                        // �I������
    private:
        C_Framework* pGame_ = nullptr;                                                                                                  ///< @brief �Q�[��

        virtual void FirstProcess();                                                                                                    // �ŏ��̏���
    };
}
