/* �w�b�_�t�@�C�� */
#include "NormalBombEffect.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Random/RandomGenerator.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include <sstream>


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_NormalBombEffect::C_NormalBombEffect(const std::string& rId, int32_t type) : C_BaseEffect(rId, type)
    {
        assert(Lua::C_LuaStateManager::s_GetInstance()->GetState());
        pLuaState_ = Lua::C_LuaStateManager::s_GetInstance()->GetState().get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01));
        wpCircleParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01).get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pSMOKE_01));
        wpSmokeParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pSMOKE_01).get();;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalBombEffect::~C_NormalBombEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalBombEffect::DoUpdate()
    {
        if (wpCircleParticleSystem_.expired() == false && wpSmokeParticleSystem_.expired() == false)
        {
            auto pCircleParticleSystem = wpCircleParticleSystem_.lock();
            auto pSmokeParticleSystem = wpSmokeParticleSystem_.lock();

#ifdef _DEBUG

            try
            {
                // �G�t�F�N�g�̃��W�b�N������
                existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                              "NormalBombEffectLogic",
                                                              boost::ref(*pCircleParticleSystem.get()),
                                                              boost::ref(*pSmokeParticleSystem.get()),
                                                              boost::ref(frameCounter_),
                                                              boost::ref(*Random::C_RandomGenerator::s_GetInstance()),
                                                              boost::ref(position_)) ? true : false;
            }
            catch (luabind::error &rErrorInfo)
            {
                luabind::object errorMessage(luabind::from_stack(rErrorInfo.state(), -1));

                std::stringstream stream;
                stream << errorMessage << std::endl;

                PrintLog("[ C_NormalBombEffect::DoUpdate ] : �֐��̌Ăяo���Ɏ��s���܂����B\n");
                PrintLog("                �G���[���b�Z�[�W : %s\n", stream.str().c_str());

                existenceFlag_ = false;
            }

#else

            // �G�t�F�N�g�̃��W�b�N������
            existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                          "NormalBombEffectLogic",
                                                          boost::ref(*pCircleParticleSystem.get()),
                                                          boost::ref(*pSmokeParticleSystem.get()),
                                                          boost::ref(frameCounter_),
                                                          boost::ref(*Random::C_RandomGenerator::s_GetInstance()),
                                                          boost::ref(position_)) ? true : false;

#endif

        }
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalBombEffect::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̃��b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_NormalBombEffect::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}