/* �w�b�_�t�@�C�� */
#include "CameraManager.h"
#include "../Camera/Camera.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    /** �J�����̏�� */
    struct S_CameraData
    {
        CameraPtr pCamera_;                                                                 ///< @brief �J����
        bool updateFlag_;                                                                   ///< @brief �X�V�t���O

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �J����
         *  @param  �X�V�t���O
         *
         ****************************************************************/
        S_CameraData(const CameraPtr& prCamera, bool updateFlag) :

            // �J����
            pCamera_(prCamera),

            // �X�V�t���O
            updateFlag_(updateFlag)

        {
        }
    };


    //-------------------------------------------------------------
    //!
    //! @brief �J�����}�l�[�W���[�C���v�������g
    //! @brief �J�����}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_CameraManager::C_CameraManagerImpl
    {
    public:
        C_CameraManagerImpl();                                                              // �R���X�g���N�^
        ~C_CameraManagerImpl();                                                             // �f�X�g���N�^
        void Update();                                                                      // �X�V����
        void Entry(const CameraPtr& prCamera,                                               // �o�^����
                   const std::string& rId,
                   bool updateFlag = true);
        void Remove(const std::string& rId);                                                // ��������
        void AllRemove();                                                                   // �S�ẴJ����������
        boost::optional<const CameraPtr&> GetCamera(const std::string& rId) const;          // �J�������擾
    private:
        std::deque<std::pair<std::string, S_CameraData>> cameraDatas_;                      ///< @brief �J�����̏��
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CameraManager::C_CameraManagerImpl::C_CameraManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CameraManager::C_CameraManagerImpl::~C_CameraManagerImpl()
    {
        if (cameraDatas_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Update()
    {
        for (auto& rCameraData : cameraDatas_)
        {
            if (rCameraData.second.updateFlag_ == true) rCameraData.second.pCamera_->Update();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̓o�^�������s��
     *  @param  �J����
     *  @param  ID
     *  @param  �X�V�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Entry(const CameraPtr& prCamera,
                                                     const std::string& rId,
                                                     bool updateFlag)
    {
        // ���ɓo�^����Ă���ꍇ
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != cameraDatas_.end())
        {
            std::cout << "[ C_CameraManagerImpl::Entry ] : �J���������ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                            ID : " << rId << std::endl;

            return;
        }

        cameraDatas_.emplace_back(std::piecewise_construct,
                                  std::forward_as_tuple(rId),
                                  std::forward_as_tuple(prCamera, updateFlag));
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̏����������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::Remove(const std::string& rId)
    {
        // �J�������o�^����Ă��Ȃ��ꍇ
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rCameraData){ return rCameraData.first == rId; });


        if (iterator == cameraDatas_.end())
        {
            std::cout << "[ C_CameraManagerImpl::Remove ] : �J������o�^���Ă��܂���B" << std::endl;
            std::cout << "                             ID : " << rId << std::endl;

            return;
        }

        cameraDatas_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  �S�ẴJ�����̏����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::C_CameraManagerImpl::AllRemove()
    {
        cameraDatas_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �J�������擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�J����
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const CameraPtr&> C_CameraManager::C_CameraManagerImpl::GetCamera(const std::string& rId) const
    {
        auto iterator = std::find_if(cameraDatas_.begin(),
                                     cameraDatas_.end(),
                                     [&](const std::pair<std::string, S_CameraData>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });

        if (iterator == cameraDatas_.end()) return boost::none;

        return (*iterator).second.pCamera_;
    }
}