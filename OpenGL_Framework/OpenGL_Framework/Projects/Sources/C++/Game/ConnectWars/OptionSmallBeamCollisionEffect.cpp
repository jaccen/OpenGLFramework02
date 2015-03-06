/* �w�b�_�t�@�C�� */
#include "OptionSmallBeamCollisionEffect.h"
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
    C_OptionSmallBeamCollisionEffect::C_OptionSmallBeamCollisionEffect(const std::string& rId, int32_t type) : C_BaseEffect(rId, type)
    {
        assert(Lua::C_LuaStateManager::s_GetInstance()->GetState());
        pLuaState_ = Lua::C_LuaStateManager::s_GetInstance()->GetState().get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01));
        wpCircleParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pCIRCLE_01).get();

        assert(Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pRING_01));
        wpRingParticleSystem_ = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(ID::Particle::s_pRING_01).get();;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionSmallBeamCollisionEffect::~C_OptionSmallBeamCollisionEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionSmallBeamCollisionEffect::DoUpdate()
    {
        if (wpCircleParticleSystem_.expired() == false && wpRingParticleSystem_.expired() == false)
        {
            auto pCircleParticleSystem = wpCircleParticleSystem_.lock();
            auto pRingParticleSystem = wpRingParticleSystem_.lock();

#ifdef _DEBUG

            try
            {
                // �G�t�F�N�g�̃��W�b�N������
                existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                              "OptionSmallBeamCollisionEffectLogic",
                                                              boost::ref(*pCircleParticleSystem.get()),
                                                              boost::ref(*pRingParticleSystem.get()),
                                                              boost::ref(frameCounter_),
                                                              boost::ref(*Random::C_RandomGenerator::s_GetInstance()),
                                                              boost::ref(position_)) ? true : false;
            }
            catch (luabind::error &rErrorInfo)
            {
                luabind::object errorMessage(luabind::from_stack(rErrorInfo.state(), -1));

                std::stringstream stream;
                stream << errorMessage << std::endl;

                PrintLog("[ C_OptionSmallBeamCollisionEffect::DoUpdate ] : �֐��̌Ăяo���Ɏ��s���܂����B\n");
                PrintLog("                �G���[���b�Z�[�W : %s\n", stream.str().c_str());

                existenceFlag_ = false;
            }

#else

            // �G�t�F�N�g�̃��W�b�N������
            existenceFlag_ = luabind::call_function<bool>(pLuaState_.get(),
                                                          "OptionSmallBeamCollisionEffectLogic",
                                                          boost::ref(*pCircleParticleSystem.get()),
                                                          boost::ref(*pRingParticleSystem.get()),
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
    void C_OptionSmallBeamCollisionEffect::DoDraw()
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
    bool C_OptionSmallBeamCollisionEffect::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}