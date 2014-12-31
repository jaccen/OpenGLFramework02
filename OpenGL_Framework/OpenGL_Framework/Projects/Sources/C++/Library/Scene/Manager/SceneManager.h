/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �V�[��
//! @brief �V�[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Scene
{
    /* �O���錾 */
    class C_BaseScene;


    /** �V�[���̖߂�l */
    enum class ecSceneReturn
    {
        CONTINUATIOIN,                                                      ///< @brief ���s
        SUCCESSFUL,                                                         ///< @brief ����I��
        ERROR_TERMINATION,                                                  ///< @brief �G���[�I��
    };


    //-------------------------------------------------------------
    //!
    //! @brief �V�[���`�F���W���[( �C���^�[�t�F�[�X )
    //! @brief �V�[����ύX���邽�߂̊֐������C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_SceneChanger
    {
    public:
        IC_SceneChanger(){};                                                //!< @brief �R���X�g���N�^
        virtual ~IC_SceneChanger(){};                                       //!< @brief �f�X�g���N�^
        virtual void PushScene(C_BaseScene* pNextScene,                     //!< @brief �V�[�����v�b�V��
                               bool previousUpdateFlag = false,
                               bool presiousDrawFlag = true) = 0;
        virtual void PopScene() = 0;                                        //!< @brief �V�[�����|�b�v
        virtual void ReplaceScene(C_BaseScene* pNextScene) = 0;             //!< @brief �V�[�������ւ�
    };


    //-------------------------------------------------------------
    //!
    //! @brief �V�[���}�l�[�W���[
    //! @brief �V�[�����Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_SceneManager : public IC_SceneChanger
    {
    public:
        explicit C_SceneManager(C_BaseScene* pFirstScene);                  // �R���X�g���N�^
        ~C_SceneManager() override;                                         // �f�X�g���N�^
        ecSceneReturn Initialize();                                         // ����������
        ecSceneReturn Update();                                             // �X�V����
        void Draw();                                                        // �`�揈��
        void Finalize();                                                    // �I������
        void PushScene(C_BaseScene* pNextScene,                             // ���̃V�[�����v�b�V��
                       bool previousUpdateFlag,
                       bool presiousDrawFlag) override;
        void PopScene() override;                                           // ���݂̃V�[�����|�b�v
        void ReplaceScene(C_BaseScene* pNextScene) override;                // ���݂̃V�[���Ɠ���ւ���
    private:
        /* �O���錾 */
        class C_SceneManagerImpl;

        std::unique_ptr<C_SceneManagerImpl> upImpl_;                        // �������
    };
}
