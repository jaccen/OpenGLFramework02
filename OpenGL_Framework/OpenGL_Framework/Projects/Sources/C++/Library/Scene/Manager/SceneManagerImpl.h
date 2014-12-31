/* �w�b�_�t�@�C�� */
#include "SceneManager.h"
#include "../BaseScene.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �V�[��
//! @brief �V�[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Scene
{
    /** �V�[���ύX�̃R�}���h */
    enum class ecSceneChangeCommand
    {
        PUSH,                                                                       ///< @brief �v�b�V��
        POP,                                                                        ///< @brief �|�b�v
        REPLACE,                                                                    ///< @brief ���v���C�X
    };


    //-------------------------------------------------------------
    //!
    //! @brief �l�N�X�g�V�[���f�[�^
    //! @brief ���̃V�[���ɐ؂�ւ���f�[�^��\���\����
    //!
    //-------------------------------------------------------------
    struct S_NextSceneData
    {
        bool previousUpdateFlag_ = false;                                           ///< @brief �O�̃V�[���ɐݒ肷��X�V�t���O
        bool previousDrawFlag_ = false;                                             ///< @brief �O�̃V�[���ɐݒ肷��`��t���O
        C_BaseScene* pNextScene_;                                                   ///< @brief ���̃V�[��

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  ���̃V�[��
         *  @param  �O�̃V�[���ɐݒ肷��X�V�t���O
         *  @param  �O�̃V�[���ɐݒ肷��`��t���O
         *
         ****************************************************************/
        S_NextSceneData(C_BaseScene* pNextScene,
                        bool previousUpdateFlag = true,
                        bool previousDrawFlag = true) :

            // �O�̃V�[���ɐݒ肷��e�t���O
            previousUpdateFlag_(previousUpdateFlag),
            previousDrawFlag_(previousDrawFlag),

            // ���̃V�[��
            pNextScene_(pNextScene)

        {
        }
    };


    //-------------------------------------------------------------
    //!
    //! @brief �V�[���}�l�[�W���[�C���v�������g
    //! @brief �V�[���}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_SceneManager::C_SceneManagerImpl
    {
    public:
        C_SceneManagerImpl(C_BaseScene* pFirstScene,                                // �R���X�g���N�^
                           IC_SceneChanger* pSceneChanger);
        ~C_SceneManagerImpl();                                                      // �f�X�g���N�^
        ecSceneReturn Initialize();                                                 // ����������
        ecSceneReturn Update();                                                     // �X�V����
        void Draw();                                                                // �`�揈��
        void Finalize();                                                            // �I������
        void PushScene(C_BaseScene* pNextScene,                                     // ���̃V�[�����v�b�V��
                       bool previousUpdateFlag,
                       bool presiousDrawFlag);
        void PopScene();                                                            // ���݂̃V�[�����|�b�v
        void ReplaceScene(C_BaseScene* pNextScene);                                 // ���݂̃V�[���Ɠ���ւ���
    private:
        IC_SceneChanger* pSceneChanger_ = nullptr;                                  ///< @brief �V�[���`�F���W���[
        std::deque<std::unique_ptr<C_BaseScene>> upScenes_;                         ///< @brief �V�[��
        std::deque<S_NextSceneData> nextSceneDatas_;                                ///< @brief ���̃V�[���ɐ؂�ւ��邽�߂̏��
        std::deque<ecSceneChangeCommand> sceneExchangeCommands_;                    ///< @brief �V�[���ύX�̃R�}���h

        ecSceneReturn SceneChange();                                                // �V�[���̕ύX����
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �ŏ��̃V�[��
     *  @param  �V�[���`�F���W���[
     *
     ****************************************************************/
    C_SceneManager::C_SceneManagerImpl::C_SceneManagerImpl(C_BaseScene* pFirstScene,
                                                           IC_SceneChanger* pSceneChanger) :

        // �V�[���`�F���W���[
        pSceneChanger_(pSceneChanger)

    {
        // �ŏ��̃V�[����ݒ�
        upScenes_.emplace_back(pFirstScene);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SceneManager::C_SceneManagerImpl::~C_SceneManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̏������������s��
     *  @param  �Ȃ�
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERMINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::Initialize()
    {
        assert(upScenes_.size() > 0);
        assert(upScenes_[0]);

        // �ŏ��̃V�[���ɃV�[���`�F���W���[��ݒ�
        upScenes_[0]->SetSceneChanger(pSceneChanger_);

        // �ŏ��̃V�[���̏���������
        if (upScenes_[0]->Initialize() == ecSceneReturn::ERROR_TERMINATION)
        {
            PrintLog("[ C_SceneManagerImpl::Initialize ] : �ŏ��̃V�[���̏����������Ɏ��s���܂����B\n");

            return ecSceneReturn::ERROR_TERMINATION;
        }

        return ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return ����I���FCONTINUATIOIN
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::Update()
    {
        assert(upScenes_.size() > 0);
        assert(upScenes_[0]);

        // �e�����̖߂�l
        ecSceneReturn returnValue = ecSceneReturn::CONTINUATIOIN;

        // �V�[���̕ύX����
        returnValue = SceneChange();

        if (returnValue == ecSceneReturn::ERROR_TERMINATION)
        {
            PrintLog("[ C_SceneManagerImpl::Update ] : �V�[���̕ύX�����Ɏ��s���܂����B\n");

            return ecSceneReturn::ERROR_TERMINATION;
        }

        for (auto& scene : upScenes_)
        {
            // �X�V�t���O�������Ă����ꍇ�͍X�V
            if (scene->IsUpdateFlag() == true)
            {
                // �V�[���̍X�V����
                returnValue = scene->Update();

                if (returnValue != ecSceneReturn::CONTINUATIOIN)
                {
                    if (returnValue == ecSceneReturn::ERROR_TERMINATION)
                    {
                        PrintLog("[ C_SceneManagerImpl::Update ] : �V�[���̍X�V�����Ɏ��s���܂����B\n");

                        return ecSceneReturn::ERROR_TERMINATION;
                    }
                    else
                    {
                        return ecSceneReturn::SUCCESSFUL;
                    }
                }
            }
        }

        return ecSceneReturn::CONTINUATIOIN;
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::Draw()
    {
        for (auto& scene : upScenes_)
        {
            // �`��t���O�������Ă����ꍇ�͕`��
            if (scene->IsDrawFlag() == true) scene->Draw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::Finalize()
    {
        for (auto& scene : upScenes_) scene->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[�����v�b�V������
     *  @param  ���̃V�[��
     *  @param  �ȑO�̃V�[���ɐݒ肷��X�V�t���O
     *  @param  �ȑO�̃V�[���ɐݒ肷��`��t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::PushScene(C_BaseScene* pNextScene,
                                                       bool previousUpdateFlag,
                                                       bool presiousDrawFlag)
    {
        // ���̃V�[���֐؂�ւ��邽�߂̏���ݒ�
        nextSceneDatas_.emplace_back(pNextScene,
                                     previousUpdateFlag,
                                     presiousDrawFlag);

        // �V�[���ύX�̃R�}���h�Ƀv�b�V����ǉ�
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::PUSH);
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[�����|�b�v����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::PopScene()
    {
        // �V�[���ύX�̃R�}���h�Ƀ|�b�v��ǉ�
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::POP);
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃V�[���Ƃ̓���ւ�������
     *  @param  ���̃V�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::C_SceneManagerImpl::ReplaceScene(C_BaseScene* pNextScene)
    {
        // ���̃V�[���֐؂�ւ��邽�߂̏���ݒ�
        nextSceneDatas_.emplace_back(pNextScene);

        // �V�[���ύX�̃R�}���h�Ƀ|�b�v��ǉ�
        sceneExchangeCommands_.emplace_back(ecSceneChangeCommand::REPLACE);
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���̕ύX���s��
     *  @param  �Ȃ�
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::C_SceneManagerImpl::SceneChange()
    {
        // ���̃V�[���ɐ؂�ւ��邽�߂̏��̃C���f�b�N�X
        uint32_t nextSceneDataIndex = 0;

        // �V�[���̐�����1�������l
        int32_t nowSceneIndex = upScenes_.size() - 1;

        for (auto sceneExchangeCommand : sceneExchangeCommands_)
        {
            assert(nowSceneIndex >= 0);

            /* ���v���C�X */
            if (sceneExchangeCommand == ecSceneChangeCommand::REPLACE)
            {
                assert(nextSceneDataIndex < nextSceneDatas_.size());

                // ���݂̃V�[���̏I���������s���A���̃V�[�����폜
                upScenes_[nowSceneIndex]->Finalize();
                upScenes_.pop_back();

                // ���̃V�[�����擾
                std::unique_ptr<C_BaseScene> upNextScene(nextSceneDatas_[nextSceneDataIndex].pNextScene_);

                // ���̃V�[���ɃV�[���`�F���W���[��ݒ肵�A������
                upNextScene->SetSceneChanger(pSceneChanger_);

                if (upNextScene->Initialize() == ecSceneReturn::ERROR_TERMINATION)
                {
                    PrintLog("[ C_SceneManager::SceneChange ] : ���v���C�X���̎��̃V�[���̏����������Ɏ��s���܂����B\n");

                    return ecSceneReturn::ERROR_TERMINATION;
                }

                // ���̃V�[����ǉ�
                upScenes_.emplace_back(std::move(upNextScene));

                // ���̃V�[���ɐ؂�ւ��邽�߂̏��̃C���f�b�N�X��1����
                ++nextSceneDataIndex;
            }
            /* �v�b�V�� */
            else if (sceneExchangeCommand == ecSceneChangeCommand::PUSH)
            {
                assert(nextSceneDataIndex < nextSceneDatas_.size());

                // ���݂̃V�[���ɍX�V�t���O�ƕ`��t���O��ݒ�
                upScenes_[nowSceneIndex]->SetUpdateFlag(nextSceneDatas_[nextSceneDataIndex].previousUpdateFlag_);
                upScenes_[nowSceneIndex]->SetDrawFlag(nextSceneDatas_[nextSceneDataIndex].previousDrawFlag_);

                // ���̃V�[�����擾
                std::unique_ptr<C_BaseScene> upNextScene(nextSceneDatas_[nextSceneDataIndex].pNextScene_);

                // ���̃V�[���ɃV�[���`�F���W���[�Ɛe�̃V�[����ݒ肵�A������
                upNextScene->SetSceneChanger(pSceneChanger_);
                upNextScene->SetParentScene(upScenes_[nowSceneIndex].get());

                if (upNextScene->Initialize() == ecSceneReturn::ERROR_TERMINATION)
                {
                    PrintLog("[ C_SceneManager::SceneChange ] : �v�b�V�����̎��̃V�[���̏����������Ɏ��s���܂����B\n");

                    return ecSceneReturn::ERROR_TERMINATION;
                }

                // ���̃V�[����ǉ�
                upScenes_.emplace_back(std::move(upNextScene));

                // ���̃V�[���ɐ؂�ւ��邽�߂̏��̃C���f�b�N�X��1����
                ++nextSceneDataIndex;

                // �V�[���̐�����1�������l��1����
                ++nowSceneIndex;
            }
            /* �|�b�v */
            else
            {
                // �V�[����2�ȏ�Ȃ���Ώ������Ȃ�
                if (nowSceneIndex > 0)
                {
                    // ���݂̃V�[���̏I������
                    upScenes_[nowSceneIndex]->Finalize();

                    // �V�[���̐�����1�������l��1���炷
                    --nowSceneIndex;

                    // ���݂̃V�[����1�O�̃V�[���̍X�V�t���O�ƕ`��t���O�𗧂Ă�
                    upScenes_[nowSceneIndex]->SetUpdateFlag(true);
                    upScenes_[nowSceneIndex]->SetDrawFlag(true);

                    // ���݂̃V�[�����폜
                    upScenes_.pop_back();
                }
            }
        }

        // �V�[���؂�ւ��̃R�}���h�����݂��Ă���ꍇ�͂��ׂč폜
        if (sceneExchangeCommands_.empty() == false) sceneExchangeCommands_.clear();

        // ���̃V�[���֐؂�ւ��邽�߂̏�񂪑��݂��Ă���ꍇ�͂��ׂč폜
        if (nextSceneDatas_.empty() == false) nextSceneDatas_.clear();

        return ecSceneReturn::SUCCESSFUL;
    }
}